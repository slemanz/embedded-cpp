#ifndef INC_DRIVER_ADC_HPP__
#define INC_DRIVER_ADC_HPP__

#include "mcal_reg.hpp"

namespace driver
{
    namespace adc
    {
        enum class Instance : std::uint8_t
        {
            ADC1,
        };

        enum class Mode : std::uint8_t
        {
            Single = 0U,
            Continuous = 1U
        };
        enum class Trigger : std::uint8_t
        {
            Software,
            Timer1CC1,
            Timer1CC2,
            Timer1CC3,
            Timer2CC2,
            Timer3TRGO,
            Timer4CC4,
            ExternalInterrupt
        };

        enum class Channel : std::uint8_t
        {
            Ch0 = 0,
            Ch1 = 1,
            Ch2 = 2,
            Ch3 = 3,
            Ch4 = 4,
            Ch5 = 5,
            Ch6 = 6,
            Ch7 = 7,
            Ch8 = 8,
            Ch9 = 9,
            Ch10 = 10,
            Ch11 = 11,
            Ch12 = 12,
            Ch13 = 13,
            Ch14 = 14,
            Ch15 = 15,
            TempSensor = 16,
            VrefInt = 17,
            Vbat = 18
        };

        enum class SampleTime : std::uint8_t
        {
            Cycles3     = 0,
            Cycles15    = 1,
            Cycles28    = 2,
            Cycles56    = 3,
            Cycles84    = 4,
            Cycles112   = 5,
            Cycles144   = 6,
            Cycles480   = 7
        };

        enum class Resolution : std::uint8_t
        {
            Bits12 = 0,
            Bits10 = 1,
            Bits8 = 2,
            Bits6 = 3
        };

        class Adc
        {
            public:
                constexpr Adc(Instance instance) : instance_(instance) {}

                void init(  Resolution resolution,
                            SampleTime default_sample_time = SampleTime::Cycles56) const;

                void configure_channel( Channel channel,
                                        SampleTime sample_time = SampleTime::Cycles56,
                                        bool enable = true) const;

                void set_mode(Mode mode) const;

                void start_conversion() const;
                void stop_conversion() const;

                bool is_conversion_complete() const;
                uint16_t read_conversion_result() const;


            private:
                Instance instance_;

                constexpr uint32_t get_base_address() const;
                void enable_clock() const;
                void disable_clock() const;
                void calibrate() const; // not implemented
                void configure_resolution(Resolution resolution) const;
        };

    } // namespace adc
} // namespace driver

#endif /* INC_DRIVER_ADC_HPP__ */