#include "mcal_reg.h"
#include "uart.h"

class Led
{
    public:
        virtual void getType() = 0;
        virtual void ledState() = 0;
};

class DisplayLed : public Led
{
    public:
        void getType();
        void ledState();
};

void DisplayLed::getType()
{
    printf("This is a Display LED \n");
}

void DisplayLed::ledState()
{
    printf("Display LED is displaying \n");
}

class MedicalLed : public Led
{
    public:
        void getType();
        void ledState();
};

void MedicalLed::getType()
{
    printf("This is a MedicalLED LED \n");
}

void MedicalLed::ledState()
{
    printf("Medical LED is SCANNING \n");
}


int main(void)
{
    uart_init();
    printf("Init the board!\n");

    Led *mled_pt;
	Led *dled_pt;
	
	mled_pt =  new MedicalLed();
	dled_pt = new DisplayLed();
	
	mled_pt->getType();
	dled_pt->getType();


    while(1)
    {
        
    }
}