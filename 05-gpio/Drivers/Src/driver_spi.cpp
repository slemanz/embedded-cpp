#include "driver_spi.hpp"

using namespace driver::spi;
using namespace mcal;

void Spi::init(Mode mode, BaudRate baudrate, DataSize data_size, BitOrder bit_order) const
{
    enable_clock();

    const uint32_t base = get_base_address();

    uint32_t cr1_value = 0;
    cr1_value |= static_cast<uint32_t>(mode);
    cr1_value |= (static_cast<uint32_t>(baudrate) << reg::spi::bitpos::cr1::br);
    cr1_value |= (1U << reg::spi::bitpos::cr1::mstr); // master mode
    cr1_value |= (static_cast<uint32_t>(data_size) << reg::spi::bitpos::cr1::dff);
    cr1_value |= (static_cast<uint32_t>(bit_order) << reg::spi::bitpos::cr1::lsbfirst);

    // Software slave management
    cr1_value |= (1U << reg::spi::bitpos::cr1::ssm);
    cr1_value |= (1U << reg::spi::bitpos::cr1::ssi);

    reg_access::reg_set(base + reg::spi::offset::cr1, cr1_value);
    enable();
}
                
void Spi::enable() const
{
    uint32_t base = get_base_address();
    reg_access::reg_or(base + reg::spi::offset::cr1, (1 << 6));
    //reg_access::bit_set(base + reg::spi::offset::cr1, reg::spi::bitpos::cr1::spe);
}

void Spi::disable() const
{
    uint32_t base = get_base_address();
    reg_access::bit_clr(base + reg::spi::offset::cr1, reg::spi::bitpos::cr1::spe);
}

bool Spi::is_busy() const
{
    const uint32_t base = get_base_address();
    return (reg_access::bit_get(base + reg::spi::offset::sr, reg::spi::bitpos::sr::bsy));
}

bool Spi::is_tx_empty() const
{
    const uint32_t base = get_base_address();
    return (reg_access::bit_get(base + reg::spi::offset::sr, reg::spi::bitpos::sr::txe));
}

bool Spi::is_rx_not_empty() const
{
    const uint32_t base = get_base_address();
    return (reg_access::bit_get(base + reg::spi::offset::sr, reg::spi::bitpos::sr::rxne));
}


void Spi::write(uint8_t *data, uint32_t Len) const
{
    const uint32_t base = get_base_address();
    uint8_t dummy = 0xFF;
    while(Len > 0)
    {
        while(!is_tx_empty());
        reg_access::reg_set(base + reg::spi::offset::dr, *data);

        while(!is_rx_not_empty());
        dummy = static_cast<uint8_t>(reg_access::reg_get(base + reg::spi::offset::dr));
        (void)dummy;

        Len--;
        data++;
    };
}

void Spi::read(uint8_t *data, uint32_t Len) const
{
    uint8_t dummy = 0xFF;
    const uint32_t base = get_base_address();
    while(Len > 0)
    {
        while(!is_tx_empty());
        reg_access::reg_set(base + reg::spi::offset::dr, dummy);

        while(!is_rx_not_empty());
        *data = static_cast<uint8_t>(reg_access::reg_get(base + reg::spi::offset::dr));

        Len--;
        data++;
    };
}

void Spi::transfer(uint8_t *dataTx, uint8_t *dataRx, uint32_t Len) const
{
    const uint32_t base = get_base_address();
    while(!is_tx_empty());
    while(Len > 0)
    {
        while(!is_tx_empty());
        reg_access::reg_set(base + reg::spi::offset::dr, *dataTx);

        while(!is_rx_not_empty());
        *dataRx = static_cast<uint8_t>(reg_access::reg_get(base + reg::spi::offset::dr));

        Len--;
        dataTx++;
        dataRx++;
    };
}

constexpr uint32_t Spi::get_base_address() const
{
    switch(instance_)
    {
        case Instance::SPI1: return reg::spi1_base;
        case Instance::SPI2: return reg::spi2_base;
        case Instance::SPI3: return reg::spi3_base;
        case Instance::SPI4: return reg::spi4_base;
        default: return 0;
    }
}

void Spi::enable_clock() const
{
    if      (instance_ == Instance::SPI1) reg_access::bit_set(reg::apb2enr, 12);
    else if (instance_ == Instance::SPI2) reg_access::bit_set(reg::apb1enr, 14);
    else if (instance_ == Instance::SPI3) reg_access::bit_set(reg::apb1enr, 15);
    else if (instance_ == Instance::SPI4) reg_access::bit_set(reg::apb2enr, 13);
}

void Spi::disable_clock() const
{
    if      (instance_ == Instance::SPI1) reg_access::bit_clr(reg::apb2enr, 12);
    else if (instance_ == Instance::SPI2) reg_access::bit_clr(reg::apb1enr, 14);
    else if (instance_ == Instance::SPI3) reg_access::bit_clr(reg::apb1enr, 15);
    else if (instance_ == Instance::SPI4) reg_access::bit_clr(reg::apb2enr, 13);
}