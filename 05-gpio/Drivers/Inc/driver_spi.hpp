#ifndef INC_DRIVER_SPI_HPP_
#define INC_DRIVER_SPI_HPP_

#include "mcal_reg.hpp"

namespace driver
{
    namespace spi
    {
        enum class Instance : uint8_t
        {
            SPI1,
            SPI2,
            SPI3,
            SPI4
        };

        enum class Mode : uint8_t
        {
            Mode0 = 0,  // CPOL=0, CPHA=0
            Mode1 = 1,  // CPOL=0, CPHA=1
            Mode2 = 2,  // CPOL=1, CPHA=0
            Mode3 = 3   // CPOL=1, CPHA=1
        };

        enum class BaudRate : uint8_t 
        {
            Div2   = 0,
            Div4   = 1,
            Div8   = 2,
            Div16  = 3,
            Div32  = 4,
            Div64  = 5,
            Div128 = 6,
            Div256 = 7
        };

        enum class DataSize : uint8_t
        {
            Bits8 = 0,
            Bits16 = 1 // not implemented
        };

        enum class BitOrder : uint8_t
        {
            MSBFirst = 0,
            LSBFirst = 1
        };

        class Spi
        {
            public:
                Spi(Instance instance) : instance_(instance) {}

                void init(  Mode mode,
                            BaudRate baudrate,
                            DataSize data_size = DataSize::Bits8,
                            BitOrder bit_order = BitOrder::MSBFirst ) const;
                
                void enable() const;
                void disable() const;

                bool is_busy() const;
                bool is_tx_empty() const;
                bool is_rx_not_empty() const;

                void read(uint8_t *data, uint32_t Len) const;
                void write(uint8_t *data, uint32_t Len) const;
                void transfer(uint8_t *dataTx, uint8_t *dataRx, uint32_t Len) const;
            private:
                Instance instance_;
                constexpr uint32_t get_base_address() const;
                void enable_clock() const;
                void disable_clock() const;
        };
    } // namespace driver
} // namespace driver


#endif /* INC_DRIVER_SPI_HPP_ */