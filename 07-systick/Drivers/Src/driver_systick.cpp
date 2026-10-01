#include "driver_systick.hpp"
#include "driver_nvic.hpp"

using namespace driver::systick;
using namespace driver::nvic;
using namespace mcal;

uint64_t Systick::ticks_ = 0;
uint64_t Systick::ticks_p_ = 0;

// init to 1ms
void Systick::init()
{
    // clear the value of SVR (value reload)
    const uint32_t load_addr = reg::systick_base + reg::systick::offset::load;
    reg_access::reg_not(load_addr, 0x00FFFFFFFF);
    
    // load the value
    const uint32_t count_value = 16000000/1000;
    reg_access::reg_or(load_addr, count_value);

    // setting and enable
    const uint32_t ctrl_addr = reg::systick_base + reg::systick::offset::ctrl;

    enable_interrupt();
    reg_access::bit_set(ctrl_addr, reg::systick::bitpos::ctrl::clksource); // clksrc
    start();
}

void Systick::start()
{
    constexpr uint32_t ctrl_addr = reg::systick_base + reg::systick::offset::ctrl;
    reg_access::bit_set(ctrl_addr, reg::systick::bitpos::ctrl::enable);
}

void Systick::stop()
{
    constexpr uint32_t ctrl_addr = reg::systick_base + reg::systick::offset::ctrl;
    reg_access::bit_clr(ctrl_addr, reg::systick::bitpos::ctrl::enable);
}

void Systick::enable_interrupt()
{
    constexpr uint32_t ctrl_addr = reg::systick_base + reg::systick::offset::ctrl;
    reg_access::bit_set(ctrl_addr, reg::systick::bitpos::ctrl::tickint);
}

void Systick::disable_interrupt()
{
    constexpr uint32_t ctrl_addr = reg::systick_base + reg::systick::offset::ctrl;
    reg_access::bit_clr(ctrl_addr, reg::systick::bitpos::ctrl::tickint);
}

void Systick::ticks_increment()
{
    ticks_++;
}

uint64_t Systick::ticks_get()
{
    nvic::Nvic::global_disable_interrupts();
    ticks_p_ = ticks_;
    nvic::Nvic::global_enable_interrupts();

    return ticks_p_;
}

void Systick::delay_ms(uint64_t milliseconds)
{
    uint64_t ticks_start = ticks_get();

    while((ticks_get() - ticks_start) < milliseconds)
    {
        __asm("NOP");
    }
}