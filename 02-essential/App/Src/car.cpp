#include "mcal_reg.h"
#include "uart.h"

class Car
{
    public: // Public members are accessible from outside the class
        const char *color;
        int speed;

        void accelerate(int amount)
        {
            speed += amount;
        }

        void displayInfo()
        {
            printf("Color: %s, Speed: %d km/h\n", color, speed);
        }
};

int main(void)
{
    uart_init();
    printf("Init the board!\n");

    Car myCar; // Creating an object named 'myCar' of the Car class

    // Accessing and modifying data members using the dot operator
    myCar.color = "Red";
    myCar.speed = 0;

    // Calling member functions
    myCar.accelerate(50);
    myCar.displayInfo();

    Car anotherCar; // Creating another object
    anotherCar.color = "Blue";
    anotherCar.speed = 20;
    anotherCar.displayInfo(); 

    while(1)
    {
        
    }
}

