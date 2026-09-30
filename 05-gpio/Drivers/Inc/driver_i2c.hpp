#ifndef INC_DRIVER_I2C_HPP_
#define INC_DRIVER_I2C_HPP_

#include "mcal_reg.hpp"

namespace driver
{
    namespace i2c
    {
        enum class Instance : uint8_t
        {
            I2C1,
            I2C2,
            I2C3
        };

        enum class Mode : uint8_t
        {
            Standard,   // 100 kHz
            Fast        // 400 kHz
        };

        enum class AddressingMode : uint8_t
        {
            Bit7,
            Bit10
        };

        enum class AckControl : uint8_t
        {
            Disable,
            Enable
        };

        enum class DutyCycle : uint8_t
        {
            Ratio2_1,
            Ratio16_9
        };

        class I2C
        {
            public:
                I2C(Instance instance) : instance_(instance) {}

                void init(Mode mode,
                     AddressingMode addressing = AddressingMode::Bit7,
                     DutyCycle duty_cycle = DutyCycle::Ratio2_1) const;
            
                void enable() const;
                void disable() const;
                
                void set_own_address(uint16_t address, AddressingMode mode) const;
                
                void generate_start() const;
                void generate_stop() const;
                
                void send_address(uint8_t address, bool read) const;
                void send_data(uint8_t *data, uint32_t Len) const;
                void receive_data(uint8_t *data, uint32_t Len, AckControl ack) const;
                
                bool is_busy() const;
                bool is_transfer_complete() const;
            
            private:
                Instance instance_;

                constexpr uint32_t get_base_address() const;
                void enable_clock() const;
                void configure_timing(Mode mode, DutyCycle duty_cycle) const;
        };
    } // namespace i2c
} // namespace driver

#endif /* INC_DRIVER_I2C_HPP_ */