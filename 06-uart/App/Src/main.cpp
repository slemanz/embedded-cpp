#include "driver_gpio.hpp"
#include "driver_uart.hpp"
#include "driver_nvic.hpp"
#include <cstring>
#include <cstdio>

using namespace driver;

uart::Uart serial(uart::Instance::USART2);

extern "C" void USART2_IRQHandler(void)
{
    uint8_t data = serial.read_byte();
    while(!serial.is_ready_to_write());
    serial.write_byte(data);
}

extern "C" int __io_putchar(int ch)
{
    serial.write(reinterpret_cast<uint8_t*>(&ch), 1);
    return ch;
}

int main(void)
{
    gpio::Pin pa5(gpio::Port::A, 5);
    pa5.configure(gpio::Mode::Output);

    gpio::Pin pa2(gpio::Port::A, 2);
    pa2.configure(  gpio::Mode::Alternate,
                    gpio::OutputType::PushPull,
                    gpio::Speed::High,
                    gpio::Pull::None,
                    mcal::reg::gpio::altfn::pa2_usart2_tx);

    gpio::Pin pa3(gpio::Port::A, 3);
    pa3.configure(  gpio::Mode::Alternate,
                    gpio::OutputType::PushPull,
                    gpio::Speed::High,
                    gpio::Pull::None,
                    mcal::reg::gpio::altfn::pa3_usart2_rx);

    serial.init(uart::BaudRate::BR_9600, uart::Mode::TxRx);
    serial.enable_interrupt(uart::Interrupt::RXNEIE);

    nvic::Nvic::global_enable_interrupts();
    nvic::Nvic::enable_irq<mcal::reg::nvic::Irq::USART2>();
    
    for(uint32_t i = 0; i < 200000; i++); // delay to stable pins

    const char* msg = "Hello UART!\n";
    serial.write(reinterpret_cast<uint8_t*>(const_cast<char*>(msg)), strlen(msg));

    const char* msg2 = "Hello with strlen!\n";
    serial.write(reinterpret_cast<uint8_t*>(const_cast<char*>(msg2)), strlen(msg2));
    
    printf("Hello with printf!\n");
    
    while(1)
    {
        /* OLD */
        /*
        if(serial.is_data_available())
        {
            uint8_t data = serial.read_byte();
            while(!serial.is_ready_to_write());
            serial.write_byte(data);
        }*/
    }
}

