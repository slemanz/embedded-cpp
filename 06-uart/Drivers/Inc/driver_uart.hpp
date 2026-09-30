#ifndef INC_UART_HPP_
#define INC_UART_HPP_

#include <cstdint>
#include "mcal_reg.hpp"

namespace driver
{
    namespace uart
    {
        enum class Instance : uint8_t 
        {
            USART1,
            USART2,
            USART6
        };

        enum class BaudRate : uint32_t 
        {
            BR_9600     = 9600,
            BR_19200    = 19200,
            BR_38400    = 38400,
            BR_57600    = 57600,
            BR_115200   = 115200
        };

        enum class WordLength : uint8_t
        {
            Bits8       = 0,
            Bits9       = 1
        };

        enum class StopBits : uint8_t
        {
            One         = 0,
            Two         = 1
        };

        enum class Parity : uint8_t
        {
            None        = 0,
            Even        = 1,
            Odd         = 2
        };

        enum class Mode : uint8_t
        {
            Rx = 1,
            Tx = 2,
            TxRx = 3
        };

        enum class Interrupt : uint8_t
        {
            RXNEIE = 5
        };

        class Uart
        {
            public:
                constexpr Uart(Instance instance) : instance_(instance) {}

                void init(  BaudRate baudrate,
                            Mode mode = Mode::TxRx,
                            WordLength word_length = WordLength::Bits8,
                            StopBits stop_bits = StopBits::One,
                            Parity parity = Parity::None) const;

                void enable() const;
                void disable() const;

                bool is_data_available() const;
                uint8_t read_byte() const;
                void read(uint8_t *data, uint32_t Len) const;

                bool is_ready_to_write() const;
                void write_byte(uint8_t data) const;
                void write(uint8_t *data, uint32_t Len) const;

                void enable_interrupt(Interrupt interrupt) const;
                void disable_interrupt(Interrupt interrupt) const;

                static void handle_interrupt(Instance instance);

            private:
                Instance instance_;
                constexpr uint32_t get_base_address() const;
                void enable_clock() const;
                void set_baudrate(BaudRate baudrate) const;
        };
    } // uart
} // driver


#endif /* INC_UART_HPP_ */