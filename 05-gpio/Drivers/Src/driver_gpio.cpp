#include "driver_gpio.hpp"
#include "mcal_reg.hpp"

using namespace driver::gpio;
using namespace mcal;

void Pin::configure(Mode mode, OutputType otype, Speed speed, Pull pull, uint8_t alternate) const
{
    enable_clock();

    set_mode(mode);
    set_output_type(otype);
    set_speed(speed);
    set_pull(pull);

    if(mode == Mode::Alternate)
    {
        set_alternate_function(alternate);
    }
}

void Pin::set_mode(Mode mode) const
{
    const uint32_t moder_addr = port_ + reg::gpio::offset::moder;
    const uint32_t shift = 2 * pin_;

    reg_access::reg_not(moder_addr, (0x3 << shift));
    reg_access::reg_or(moder_addr, (static_cast<uint32_t>(mode) << shift));
}

void Pin::set_output_type(OutputType otype) const
{
    const uint32_t otyper_addr = port_ + reg::gpio::offset::otyper;
    reg_access::reg_not(otyper_addr, (0x1 << pin_));
    reg_access::reg_or(otyper_addr, (static_cast<uint32_t>(otype) << pin_));
}

void Pin::set_speed(Speed speed) const
{
    const uint32_t ospeedr_addr = port_ + reg::gpio::offset::ospeedr;
    const uint32_t shift = 2*pin_;
    reg_access::reg_not(ospeedr_addr, (0x3 << shift));
    reg_access::reg_or(ospeedr_addr, (static_cast<uint32_t>(speed) << shift));
}

void Pin::set_pull(Pull pull) const
{
    const uint32_t pupdr_addr = port_ + reg::gpio::offset::pupdr;
    const uint32_t shift = 2*pin_;

    reg_access::reg_not(pupdr_addr, (0x3 << shift));
    reg_access::reg_or(pupdr_addr, (static_cast<uint32_t>(pull) << shift));
}

void Pin::set_alternate_function(uint8_t alternate) const
{
    const uint32_t afr_addr = port_ + reg::gpio::offset::afrl + (pin_ < 8 ? 0 : 4);
    const uint32_t shift = 4*(pin_ % 8);

    reg_access::reg_not(afr_addr, (0xF << shift));
    reg_access::reg_or(afr_addr, (static_cast<uint32_t>(alternate) << shift));
}

void Pin::write(State state) const
{
    const uint32_t odr_address = port_ + reg::gpio::offset::odr;
    if(state == State::High) reg_access::bit_set(odr_address, pin_);
    else reg_access::bit_clr(odr_address, pin_);
}

State Pin::read() const
{
    const uint32_t idr_addr = port_ + reg::gpio::offset::idr;
    if(reg_access::bit_get(idr_addr, pin_) == true) return State::High;
    else return State::Low;
}

void Pin::toggle() const
{
    const uint32_t odr_addr = port_ + reg::gpio::offset::odr;
    reg_access::bit_not(odr_addr, pin_);
}

void Pin::enable_clock() const
{
    if(port_ == reg::gpioa_base) reg_access::reg_or(reg::ahb1enr, (1 << 0));
    if(port_ == reg::gpiob_base) reg_access::reg_or(reg::ahb1enr, (1 << 1));
    if(port_ == reg::gpioc_base) reg_access::reg_or(reg::ahb1enr, (1 << 2));
    if(port_ == reg::gpiod_base) reg_access::reg_or(reg::ahb1enr, (1 << 3));
    if(port_ == reg::gpioe_base) reg_access::reg_or(reg::ahb1enr, (1 << 4));
}