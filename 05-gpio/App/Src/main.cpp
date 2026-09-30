#include "driver_gpio.hpp"

using namespace driver;

int main(void)
{
    gpio::Pin pa5(gpio::Port::A, 5);
    pa5.configure(gpio::Mode::Output);
    
    gpio::Pin pa0(gpio::Port::A, 0);
    pa0.configure(  gpio::Mode::Input,
                    gpio::OutputType::PushPull,
                    gpio::Speed::High,
                    gpio::Pull::Up);

    while(1)
    {
        if(pa0.read() == gpio::State::High)
        {
            pa5.write(gpio::State::Low);
        }else
        {
            pa5.write(gpio::State::High);
        }
    }
}

