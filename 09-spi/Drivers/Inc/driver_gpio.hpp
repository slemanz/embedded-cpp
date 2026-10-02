#ifndef INC_DRIVER_GPIO_HPP
#define INC_DRIVER_GPIO_HPP

#include <cstdint>
#include "mcal_reg.hpp"

namespace driver
{
    namespace gpio
    {
        enum class Port : uint8_t
        {
            A,
            B,
            C,
            D,
            E
        };

        enum class Mode : uint8_t
        {
            Input = 0x00,
            Output = 0x01,
            Alternate = 0x02,
            Analog = 0x03
        };

        enum class OutputType : uint8_t
        {
            PushPull = 0x00,
            OpenDrain = 0x01
        };

        enum class Speed : uint8_t
        {
            Low = 0x00,
            Medium = 0x01,
            High = 0x02,
            VeryHigh = 0x03
        };

        enum class Pull : uint8_t
        {
            None = 0x00,
            Up = 0x01,
            Down = 0x02
        };

        enum class State : bool
        {
            Low = false,
            High = true
        };

        class Pin
        {
            public:
                Pin(Port port, uint8_t pin_num) : pin_(pin_num)
                {
                    port_ = get_port_base(port);
                    //static_assert(sizeof(RegType) == 4, "Register type size mismatch");
                }

                void configure( Mode mode,
                                OutputType otype = OutputType::PushPull, 
                                Speed speed = Speed::Low,
                                Pull pull = Pull::None,
                                uint8_t alternate = 0) const;

                void set_mode(Mode mode) const;
                void set_output_type(OutputType otype) const;
                void set_speed(Speed speed) const;
                void set_pull(Pull pull) const;
                void set_alternate_function(uint8_t alternate) const;

                void write(State state) const;
                void toggle() const;
                State read() const;


            private:
                uint32_t port_;
                uint8_t pin_;
            
                using RegType = uint32_t;

                constexpr uint32_t get_port_base(Port port) const
                {
                    switch (port)
                    {
                        case Port::A: return mcal::reg::gpioa_base;
                        case Port::B: return mcal::reg::gpiob_base;
                        case Port::C: return mcal::reg::gpioc_base;
                        case Port::D: return mcal::reg::gpiod_base;
                        case Port::E: return mcal::reg::gpioe_base;
                        default: return 0;
                    }
                }

                void enable_clock() const;
        };
    } // namespace gpio
} // namespace driver

#endif /* INC_DRIVER_GPIO_HPP */