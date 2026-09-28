#include "mcal_reg.h"
#include "uart.h"

class Led
{
    private:
        int diameter;
        float voltage;
        float current;

    public:
        /* Accessors */
        int getDiameter()
        {
            return diameter;
        }

        float getVoltage()
        {
            return voltage;
        }

        float getCurrent()
        {
            return current;
        }

         /* Mutator */
         void setDiameter(int d)
         {
            if(d > 0) diameter = d;
            else diameter = 0;
         }

         void setVoltage(float v)
         {
            voltage = v;
         }

         void setCurrent(float c)
         {
            current = c;
         }

         float power()
         {
            return voltage*current;
         }
};

int main(void)
{
    uart_init();
    printf("Init the board!\n");

    Led green_led;
    Led *pt_green;

    pt_green = &green_led;

    pt_green->setCurrent(0.8);
    pt_green->setVoltage(3.3);
    pt_green->setDiameter(2);

    printf("The power of green led is %f ",green_led.power());

    while(1)
    {
        
    }
}

