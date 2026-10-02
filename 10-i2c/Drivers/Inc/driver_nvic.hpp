#ifndef INC_DRIVER_NVID_HPP_
#define INC_DRIVER_NVID_HPP_

#include "mcal_reg.hpp"

namespace driver
{
    namespace nvic
    {
        class Nvic
        {
            public:
                template <mcal::reg::nvic::Irq irq>
                static void enable_irq()
                {
                    constexpr std::uint8_t irq_num = static_cast<std::uint8_t>(irq);
                    constexpr std::uint32_t reg_offset = mcal::reg::nvic::offset::iser + (irq_num / 32) * 4;
                    constexpr std::uint32_t bit_pos = irq_num % 32;
                    const uint32_t iser_addr = mcal::reg::nvic_base + reg_offset;

                    mcal::reg_access::bit_set(iser_addr, bit_pos);
                }


                template<mcal::reg::nvic::Irq irq>
                static void disable_irq()
                {
                    constexpr std::uint8_t irq_num = static_cast<std::uint8_t>(irq);
                    constexpr std::uint32_t reg_offset = mcal::reg::nvic::offset::icer + (irq_num / 32) * 4;
                    constexpr std::uint32_t bit_pos = irq_num % 32;
                    const uint32_t icer_addr = mcal::reg::nvic_base + reg_offset;
                
                    mcal::reg_access::bit_set(icer_addr, bit_pos);
                }
            
                template<mcal::reg::nvic::Irq irq>
                static void set_priority(std::uint8_t preempt_prio, std::uint8_t sub_prio)
                {
                    constexpr std::uint8_t irq_num = static_cast<std::uint8_t>(irq);
                    constexpr std::uint32_t reg_offset = mcal::reg::nvic::offset::ipr + (irq_num / 4);
                    constexpr std::uint8_t shift = (irq_num % 4) * 8 + 4;
                
                    const std::uint32_t priority = (preempt_prio << 1) | sub_prio;
                    mcal::reg_access::reg_or(mcal::reg::nvic_base + reg_offset, (priority << shift));
                }

                static void global_enable_interrupts();
                static void global_disable_interrupts();
        };
    } // namespace nvic
} // namespace driver

#endif /* INC_DRIVER_NVID_HPP_ */