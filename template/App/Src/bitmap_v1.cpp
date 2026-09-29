#include "mcal_reg.h"
#include "uart.h"

typedef struct bit32_type
{
    std::uint8_t b0  : 1;
    std::uint8_t b1  : 1;
    std::uint8_t b2  : 1;
    std::uint8_t b3  : 1;
    std::uint8_t b4  : 1;
    std::uint8_t b5  : 1;
    std::uint8_t b6  : 1;
    std::uint8_t b7  : 1;
    std::uint8_t b8  : 1;
    std::uint8_t b9  : 1;
    std::uint8_t b10 : 1;
    std::uint8_t b11 : 1;
    std::uint8_t b12 : 1;
    std::uint8_t b13 : 1;
    std::uint8_t b14 : 1;
    std::uint8_t b15 : 1;
    std::uint8_t b16 : 1;
    std::uint8_t b17 : 1;
    std::uint8_t b18 : 1;
    std::uint8_t b19 : 1;
    std::uint8_t b20 : 1;
    std::uint8_t b21 : 1;
    std::uint8_t b22 : 1;
    std::uint8_t b23 : 1;
    std::uint8_t b24 : 1;
    std::uint8_t b25 : 1;
    std::uint8_t b26 : 1;
    std::uint8_t b27 : 1;
    std::uint8_t b28 : 1;
    std::uint8_t b29 : 1;
    std::uint8_t b30 : 1;
    std::uint8_t b31 : 1;
}bit32_type;


int main(void)
{
    std::uint32_t ahb1enr = mcal::reg::rcc::ahb1enr;
    std::uint32_t gpioa_m = mcal::reg::gpio::cfg_regs::gpioa_cfg::gpioa_moder;
    std::uint32_t gpioa_o = mcal::reg::gpio::cfg_regs::gpioa_cfg::gpioa_odr;

    /* Enable clock to port B*/
    reinterpret_cast<volatile bit32_type*>(ahb1enr)->b0 = 1U;
    
    /* Set GPIOA5 to output */
    reinterpret_cast<volatile bit32_type*>(gpioa_m)->b10 = 1U;
    reinterpret_cast<volatile bit32_type*>(gpioa_m)->b11 = 0U;

    while(1)
    {
        /* toggle GPIOA5 */
        reinterpret_cast<volatile bit32_type*>(gpioa_o)->b5 ^= 1U;
        for(std::uint32_t i = 0; i < 200000; i++);
    }
}