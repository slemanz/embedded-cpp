#ifndef INC_MCAL_REG_ACCESS_HPP
#define INC_MCAL_REG_ACCESS_HPP

namespace mcal
{
    class reg_access
    {
        public:
            static void reg_set(uint32_t addr, uint32_t val)
            {
                *reinterpret_cast<volatile uint32_t*>(addr) = val;
            }

            static void reg_or(uint32_t addr, uint32_t val)
            {
                *reinterpret_cast<volatile uint32_t*>(addr) |= (val);
            }

            static void reg_and(uint32_t addr, uint32_t val)
            {
                *reinterpret_cast<volatile uint32_t*>(addr) &= val;
            }

            static void reg_not(uint32_t addr, uint32_t val)
            {
                *reinterpret_cast<volatile uint32_t*>(addr) &= ~val;
            }

            static uint32_t reg_get(uint32_t addr)
            {
                return *reinterpret_cast<volatile uint32_t*>(addr);
            }

            static void bit_set(uint32_t addr, uint32_t val)
            {
                *reinterpret_cast<volatile uint32_t*>(addr) |= (1U << val);
            }

            static void bit_clr(uint32_t addr, uint32_t val)
            {
                *reinterpret_cast<volatile uint32_t*>(addr) &= ~(1U<<val);
            }

            static void bit_not(uint32_t addr, uint32_t val)
            {
                *reinterpret_cast<volatile uint32_t*>(addr) ^= (1U << val);
            }

            static bool bit_get(uint32_t addr, uint32_t val)
            {
                return ((reg_get(addr) & static_cast<uint32_t>(1U<<val)) != (0U));
            }
        };
} // namespace mcal

#endif /* INC_MCAL_REG_ACCESS_HPP */