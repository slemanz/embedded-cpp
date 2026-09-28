#ifndef INC_LED_HPP_
#define INC_LED_HPP_

class Led
{
private:
    int diameter;
    float voltage;
    float current;
public:
    /* Constructors */
    Led();
    Led(int d, float v, float c);

    /* Accessors */
    int getDiameter();
    float getVoltage();
    float getCurrent();

    /* Mutator */
    void setDiameter(int d);
    void setVoltage(float v);
    void setCurrent(float c);

    /* Facilitators */
    float power();

    /* Inspectors */
    int isOn();

    /* Destructors */
    //~Led();
};

#endif /* INC_LED_HPP_ */