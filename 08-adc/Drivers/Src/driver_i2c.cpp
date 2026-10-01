#include "driver_i2c.hpp"

using namespace driver::i2c;
using namespace mcal;

void I2C::init(Mode mode, AddressingMode addressing, DutyCycle duty_cycle) const
{
    enable_clock();
    disable();
    
    // Reset I2C
    uint32_t base = get_base_address();
    reg_access::bit_set(base + reg::i2c::offset::cr1, reg::i2c::bitpos::cr1::swrst);
    reg_access::bit_clr(base + reg::i2c::offset::cr1, reg::i2c::bitpos::cr1::swrst);

    
    // Configure timing
    configure_timing(mode, duty_cycle);
    
    // enable ACK
    reg_access::bit_set(base + reg::i2c::offset::cr1, reg::i2c::bitpos::cr1::ack);

    // Enable I2C
    enable();
}

void I2C::enable() const
{
    uint32_t base = get_base_address();
    reg_access::bit_set(base + reg::i2c::offset::cr1, reg::i2c::bitpos::cr1::pe);
}

void I2C::disable() const
{
    uint32_t base = get_base_address();
    reg_access::bit_clr(base + reg::i2c::offset::cr1, reg::i2c::bitpos::cr1::pe);
}

void I2C::set_own_address(uint16_t address, AddressingMode mode) const
{
    // not implemented
}

void I2C::generate_start() const
{
    uint32_t base = get_base_address();
    reg_access::bit_set(base + reg::i2c::offset::cr1, reg::i2c::bitpos::cr1::start);
    while(!(reg_access::bit_get(base + reg::i2c::offset::sr1, reg::i2c::bitpos::sr1::sb)));
}

void I2C::generate_stop() const
{
    uint32_t base = get_base_address();
    reg_access::bit_set(base + reg::i2c::offset::cr1, reg::i2c::bitpos::cr1::stop);
}

void I2C::send_address(uint8_t address, bool read) const
{
    uint32_t base = get_base_address();
    address =  (address << 1);
    address |= static_cast<uint8_t>(read);
    reg_access::reg_set(base + reg::i2c::offset::dr, address);

    // Wait for ADDR flag to set
    while(!(reg_access::bit_get(base + reg::i2c::offset::sr1, reg::i2c::bitpos::sr1::addr)));
    
    // Clear ADDR flag by reading SR2
    uint32_t dummy = reg_access::reg_get(base + reg::i2c::offset::sr2);
    (void)dummy;
}

void I2C::send_data(uint8_t *data, uint32_t Len) const
{
    const uint32_t base = get_base_address();
    volatile uint32_t* dr = reinterpret_cast<volatile uint32_t*>(base + mcal::reg::i2c::offset::dr);
    volatile uint32_t* sr1 = reinterpret_cast<volatile uint32_t*>(base + mcal::reg::i2c::offset::sr1);
    
    for(uint32_t i = 0; i < Len; i++)
    {
        *dr = data[i];
        
        // Wait for TXE flag
        while(!(*sr1 & mcal::reg::i2c::mask::sr1::txe));
    }
    
    // Wait for BTF flag (transfer complete)
    while(!(*sr1 & mcal::reg::i2c::mask::sr1::btf));
}

void I2C::receive_data(uint8_t *data, uint32_t Len, AckControl ack) const
{
    const uint32_t base = get_base_address();
    volatile uint32_t* dr = reinterpret_cast<volatile uint32_t*>(base + mcal::reg::i2c::offset::dr);
    volatile uint32_t* cr1 = reinterpret_cast<volatile uint32_t*>(base + mcal::reg::i2c::offset::cr1);
    volatile uint32_t* sr1 = reinterpret_cast<volatile uint32_t*>(base + mcal::reg::i2c::offset::sr1);
    
    if(ack == AckControl::Enable)
    {
        *cr1 |= mcal::reg::i2c::mask::cr1::ack;
    }
    else
    {
        *cr1 &= ~mcal::reg::i2c::mask::cr1::ack;
    }
    
    for(uint32_t i = 0; i < Len; i++)
    {
        // For last byte, NACK should be sent
        if(i == Len - 1)
        {
            *cr1 &= ~mcal::reg::i2c::mask::cr1::ack;
        }
        
        // Wait for RXNE flag
        while(!(*sr1 & mcal::reg::i2c::mask::sr1::rxne));
        
        data[i] = *dr;
    }
}

bool I2C::is_busy() const
{
    const uint32_t base = get_base_address();
    volatile uint32_t* sr2 = reinterpret_cast<volatile uint32_t*>(base + mcal::reg::i2c::offset::sr2);
    return (*sr2 & (1 << 1)); // BUSY bit in SR2
}

bool I2C::is_transfer_complete() const
{
    const uint32_t base = get_base_address();
    volatile uint32_t* sr1 = reinterpret_cast<volatile uint32_t*>(base + mcal::reg::i2c::offset::sr1);
    return (*sr1 & mcal::reg::i2c::mask::sr1::btf);
}

// ... other method implementations ...

constexpr uint32_t I2C::get_base_address() const
{
    switch(instance_)
    {
        case Instance::I2C1: return reg::i2c1_base;
        case Instance::I2C2: return reg::i2c2_base;
        case Instance::I2C3: return reg::i2c3_base;
        default: return 0;
    }
}

void I2C::enable_clock() const
{
    if      (instance_ == Instance::I2C1) reg_access::bit_set(reg::apb1enr, 21);
    else if (instance_ == Instance::I2C2) reg_access::bit_set(reg::apb1enr, 22);
    else if (instance_ == Instance::I2C3) reg_access::bit_set(reg::apb1enr, 23);
}

void I2C::configure_timing(Mode mode, DutyCycle duty_cycle) const
{
    uint32_t base = get_base_address();
            
    // Standard mode timing (100 kHz)
    // ccr_value = (ClkValue/(2 *SCLSpeed)) and trise = ((clk/Slcspeed) +1) & 0x3F)
    // ccr_value = (16.000.000/(2 *100.000))
    uint32_t ccr_value = 0x50;  // Default for 100 kHz
    uint32_t trise_value = 0x21; // Default for 100 kHz
            
    if(mode == Mode::Fast)
    {
        // not working fine
        if(duty_cycle == DutyCycle::Ratio2_1)
        {
            ccr_value = 0x001D;;  // 400 kHz with 2:1 duty cycle
        }
        else
        {
            ccr_value = 0x0033;  // 400 kHz with 16:9 duty cycle
        }
        trise_value = 0x05;   // For 400 kHz
    }
            
    reg_access::reg_set(base + reg::i2c::offset::ccr, ccr_value);
    reg_access::reg_set(base + reg::i2c::offset::trise, trise_value);
}