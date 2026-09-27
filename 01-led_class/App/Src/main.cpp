/*
 * Blinky PA5
 */
#include "mcal_reg.h"

// GPIOA = AHB1
// GPIOA = 0x4002 0000
// MODER_REG_OFFSET = 0x00
// ODR_REG_OFFSET = 0x14
// AHB1ENR = AHB1 + RCC + 0x30
#define RCC_AHB1ENR     (*((volatile uint32_t *)0x40023830U))

class Led
{
    public:
        typedef uint32_t port_type;
        typedef uint32_t bval_type;

        Led(const port_type p, bval_type b):port(p),bval(b)
        {
            *reinterpret_cast<volatile uint32_t *>(port) &= ~(1 << bval);

            /* set pin mode to output */
            const port_type gpio_mode_reg = port - 0x14;
            *reinterpret_cast<volatile port_type *>(gpio_mode_reg) |= (1U << (bval*2));
        }

        void toggle()const
        {
            *reinterpret_cast<volatile port_type *>(port) ^= (1U << bval);
        }

        void pseudo_delayMs(int n)
        {
            int i;
            for(; n > 0; n--){
                for(i=0; i < 3200; i++);
            }

        }
    
    private:
        const port_type port;
        const port_type bval;
    
};

int main(void)
{
    RCC_AHB1ENR |= (1U << 0); // enable clock to GPIOA
    Led led5(mcal::reg::gpioa, mcal::reg::gpio_pin5);

    while(1)
    {
        led5.toggle();
        led5.pseudo_delayMs(500);
    }
}