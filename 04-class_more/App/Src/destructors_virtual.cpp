#include "mcal_reg.h"
#include "uart.h"

class Led
{
    public:
        Led()
        {
            printf("Led created\n");
        }

        virtual ~Led()
        {
            printf("Led destroyed\n");
        }
};

class PowerLed : public Led
{
    public:
        PowerLed()
        {
            printf("PowerLed is Created\n");
        }

        ~PowerLed()
        {
            printf("PowerLed is destroyed\n");
        }
};

int main(void)
{
    uart_init();
    printf("Init the board!\n");

    Led *led_pt;
    led_pt = new PowerLed();
    delete led_pt;

    while(1)
    {
        
    }
}