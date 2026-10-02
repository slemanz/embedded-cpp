#ifndef INC_DRIVER_SYSTICK_HPP_
#define INC_DRIVER_SYSTICK_HPP_

#include "mcal_reg.hpp"

namespace driver
{
    namespace systick
    {
        class Systick
        {
            public:
                static void init();

                static void start();
                static void stop();

                static void enable_interrupt();
                static void disable_interrupt();

                static void ticks_increment();
                static uint64_t ticks_get();
                static void delay_ms(uint64_t milliseconds);
            
            private:
                static uint64_t ticks_;
                static uint64_t ticks_p_;
        };
    } // namespace systick
} // namespace driver

#endif /* INC_DRIVER_SYSTICK_HPP_ */