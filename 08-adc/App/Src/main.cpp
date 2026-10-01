#include "config.hpp"
#include "driver_adc.hpp"
#include <cstdio>

using namespace driver;
using namespace mcal;

int main(void)
{
    config_drivers();

    adc::Adc adc1(adc::Instance::ADC1);
    adc1.init(adc::Resolution::Bits12);
    adc1.set_mode(adc::Mode::Continuous);
    adc1.configure_channel(adc::Channel::Ch1);
    adc1.start_conversion();

    uint16_t data = 0;

    printf("\nBoard init!!\n");
    
    while(1)
    {
        pa5.toggle();
        data = adc1.read_conversion_result();
        while(!adc1.is_conversion_complete());
        printf("Adc data: %u\n", data);

        driver::systick::Systick::delay_ms(2000);
    }
}
