#include "mcal_reg.h"
#include "uart.h"

class Led
{
    public:
        static int totalCount;
    
    Led()
    {
        totalCount++;
    }

};

int Led::totalCount = 0;

int main(void)
{
    uart_init();
    printf("Init the board!\n");

    Led led1, led2, led3;
	
    printf("Total number of LEDs created : %d\n\r",led1.totalCount);

    printf("Total number of LEDs created : %d\n\r",led2.totalCount);

    printf("Total number of LEDs created : %d\n\r",led3.totalCount);

    Led led4,led5,led6;
    printf("Total number of LEDs created : %d\n\r",led1.totalCount);

    while(1)
    {
        
    }
}

