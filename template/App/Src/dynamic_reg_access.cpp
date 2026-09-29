#include "mcal_reg.h"
#include "uart.h"

template <  typename register_address_type,
            typename register_value_type>

class reg_access_dynamic
{
    public:
        static void reg_set(register_address_type address, register_value_type value)
        {
            *reinterpret_cast<volatile register_address_type*>(address) = static_cast<register_value_type>(value);
        }

        static void reg_or(register_address_type address, register_value_type value)
        {
            *reinterpret_cast<volatile register_address_type*>(address) |= static_cast<register_value_type>(value);
        }

        static void reg_and(register_address_type address, register_value_type value)
        {
            *reinterpret_cast<volatile register_address_type*>(address) &= static_cast<register_value_type>(value);
        }

        static void reg_not(register_address_type address, register_value_type value)
        {
            *reinterpret_cast<volatile register_address_type*>(address) &= static_cast<register_value_type>(~value);
        }

        static register_value_type reg_get(register_address_type address)
        {
            return *reinterpret_cast<volatile register_address_type*>(address);
        }

        static void bit_set(register_address_type address, register_value_type value)
        {
            *reinterpret_cast<volatile register_address_type*>(address) |= static_cast<register_value_type>(1U << value);
        }

        static void bit_clear(register_address_type address, register_value_type value)
        {
            *reinterpret_cast<volatile register_address_type*>(address) &= static_cast<register_value_type>(~static_cast<register_value_type>(1U << value));
        }

        static void bit_not(register_address_type address, register_value_type value)
        {
            *reinterpret_cast<volatile register_address_type*>(address) &= static_cast<register_value_type>(1U << value);
        }

        static bool bit_get(register_address_type address, register_value_type value)
        {
            return ((reg_get(address) & static_cast<register_value_type>(1U << value)) != static_cast<register_value_type>(0U));
        }
};


int main(void)
{
    uart_init();
    printf("Init the board!\n");

    /* Enable clock to port B*/
    reg_access_dynamic<std::uint32_t, std::uint32_t>::reg_or(mcal::reg::rcc::ahb1enr, (1U << 0));
    
    /* Set GPIOA5 to output */
    reg_access_dynamic<std::uint32_t, std::uint32_t>::reg_or(mcal::reg::gpio::cfg_regs::gpioa_cfg::gpioa_moder, (1U << 10));
    reg_access_dynamic<std::uint32_t, std::uint32_t>::reg_not(mcal::reg::gpio::cfg_regs::gpioa_cfg::gpioa_moder, (1U << 11));


    while(1)
    {
        /* Set GPIOA5 to HIGH */
        reg_access_dynamic<std::uint32_t, std::uint32_t>::bit_set(mcal::reg::gpio::cfg_regs::gpioa_cfg::gpioa_moder, (5U));
        for(std::uint32_t i = 0; i < 600000; i++);

        /* Set GPIOA5 to LOW */
        reg_access_dynamic<std::uint32_t, std::uint32_t>::bit_clear(mcal::reg::gpio::cfg_regs::gpioa_cfg::gpioa_moder, (5U));
        for(std::uint32_t i = 0; i < 600000; i++);
        
    }
}