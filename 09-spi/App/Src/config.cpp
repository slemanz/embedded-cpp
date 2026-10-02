#include "config.hpp"
#include "driver_gpio.hpp"
#include "driver_uart.hpp"
#include "driver_systick.hpp"

using namespace driver;

uart::Uart serial(uart::Instance::USART2);

// PA4 - GPIO NSS
// PA5 - SPI1_SCK  (AF05)
// PA6 - SPI1_MISO (AF05)
// PA7 - SPI1_MOSI (AF05)

gpio::Pin pa4(gpio::Port::A, 4);
gpio::Pin pa5(gpio::Port::A, 5);
gpio::Pin pa6(gpio::Port::A, 6);
gpio::Pin pa7(gpio::Port::A, 7);

void config_drivers()
{
    gpio::Pin pa1(gpio::Port::A, 1);
    pa1.configure(  gpio::Mode::Analog,
                    gpio::OutputType::PushPull,
                    gpio::Speed::High,
                    gpio::Pull::None);

    gpio::Pin pa2(gpio::Port::A, 2);
    pa2.configure(  gpio::Mode::Alternate,
                    gpio::OutputType::PushPull,
                    gpio::Speed::High,
                    gpio::Pull::None,
                    mcal::reg::gpio::altfn::pa2_usart2_tx);

    pa4.configure(gpio::Mode::Output);
    pa4.write(gpio::State::High);

    pa5.configure(  gpio::Mode::Alternate,
                    gpio::OutputType::PushPull,
                    gpio::Speed::High,
                    gpio::Pull::None,
                    5U);

    pa6.configure(  gpio::Mode::Alternate,
                    gpio::OutputType::PushPull,
                    gpio::Speed::High,
                    gpio::Pull::None,
                    5U);

    pa7.configure(  gpio::Mode::Alternate,
                    gpio::OutputType::PushPull,
                    gpio::Speed::High,
                    gpio::Pull::None,
                    5U);

    serial.init(uart::BaudRate::BR_9600, uart::Mode::Tx);
    systick::Systick::init();
    systick::Systick::delay_ms(1000);
}

extern "C" int __io_putchar(int ch)
{
    serial.write(reinterpret_cast<uint8_t*>(&ch), 1);
    return ch;
}

extern "C" void SysTick_Handler(void)
{
    systick::Systick::ticks_increment();
}