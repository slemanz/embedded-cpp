#include "mcal_reg.h"
#include "uart.h"

class Led
{
    public:
        int *default_pattern;

        Led()
        {
            printf("Led created\n");
            default_pattern = new int[20];
        }

        ~Led()
        {
            printf("Led destroyed\n");
            delete []default_pattern;
        }
};

int main(void)
{
    uart_init();
    printf("Init the board!\n");

    Led *myLed = new Led();
    printf("Shutdown successfull\n");
    delete myLed;

    while(1)
    {
        
    }
}