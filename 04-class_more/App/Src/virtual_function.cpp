#include "mcal_reg.h"
#include "uart.h"

class Led
{
    private:
        int diameter;
        float voltage;
        float current;

    protected:
        int noOfpins;

    public:

    /* Constructors */
    Led();
    Led(int d, float v, float c);

    /* Accessors */
    int getDiameter();
    virtual float getVoltage();
    float getCurrent();

    /* Mutator */
    void setDiameter(int d);
    void setVoltage(float v);
    void setCurrent(float c);

    /* Facilitators */
    float power();

    /* Inspectors */
    int isOn();

    /* Desctructor */
    virtual ~Led();

    friend void print_led_attributes(Led led);
};

Led::Led()
{
    diameter = 3;
    voltage = 3.3;
    current = 200.0;
}

Led::Led(int d, float v, float c)
{
    setDiameter(d);
    setVoltage(v);
    setCurrent(c);
}

/*
 *  Mutators
 */

int Led::getDiameter()
{
    return diameter;
}

float Led::getVoltage()
{
    return voltage;
}
float Led::getCurrent()
{
    return current;
}

/*
 *  Mutators
 */

void Led::setDiameter(int d)
{
    diameter = d;
}

void Led::setVoltage(float v)
{
    voltage = v;
}
void Led::setCurrent(float c)
{
    current = c;
}

/* 
 * Facilitators
 */

float Led::power()
{
    return (voltage*current);
}

/*
 * Destructors
 */

Led::~Led()
{
    printf("Led object destroyed!\n");
}


void print_led_attributes(Led led)
{
    printf("The led diameter is %d \n",led.diameter);
    printf("The led current is %f \n",led.current);
    printf("The led voltage is %f \n",led.voltage);
}

class MedicalLed : public Led
{
    private:
        int wavelength;

    public:
        MedicalLed(int d, float v, float c, float w, int p)
        {
            setDiameter(d);
            setCurrent(c);
            setVoltage(v);

            wavelength = w;
            noOfpins = p;
        }

        /* Mutators */
        void setWavelength(int w)
        {
            wavelength = w;
        }

        /* Accessors */
        float getWavelength()
        {
            return wavelength;
        }

        /* facilitators */
        float m_factor()
        {
            return (getCurrent()*getDiameter()*wavelength)/100;
        }

        void getLedType()
        {
            if(noOfpins > 3)
            {
                printf("This is a surface mount Led\n");
            }else
            {
                printf("This is a through hole LED\n");
            }
        }

        /* Destructor */
        ~MedicalLed()
        {
            printf("Medical Led destoyed\n");
        }

        float getVoltage()
        {
            printf("This LED has no voltage to show\n");
            return 0.0;
        }
};

int main(void)
{
    uart_init();
    printf("Init the board!\n");

    Led *pt_led;

    pt_led = new MedicalLed(2, 3.3, 200, 990, 4);
    printf("Voltage %.2f\n", pt_led->getVoltage());
    delete pt_led;

    pt_led = new Led(2, 2.2, 200);
    printf("Voltage %.2f\n", pt_led->getVoltage());
    delete pt_led;

    while(1)
    {
        
    }
}

