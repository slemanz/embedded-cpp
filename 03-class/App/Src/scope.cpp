#include "mcal_reg.h"
#include "uart.h"
#include "led.hpp"

int main(void)
{
    uart_init();
    printf("Init the board!\n");

    Led  power_led;
	Led  indicator_led(5,5.0,100);

	printf("The power_led voltage is %f \n", power_led.getVoltage());
	printf("The indicator_led voltage is %f\n", indicator_led.getVoltage());


    while(1)
    {
        
    }
}

