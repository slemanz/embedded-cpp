#ifndef INC_DS3231_HPP_
#define INC_DS3231_HPP_

#include <cstdint>
#include "driver_i2c.hpp"

// I2C address
constexpr uint8_t DS3231_ADDRESS = 0x68;

// DS3231 register address
namespace ds3231_reg
{
    constexpr uint8_t SECONDS   = 0x00;
    constexpr uint8_t MINUTES   = 0x01;
    constexpr uint8_t HOURS     = 0x02;
    constexpr uint8_t DAY       = 0x03;
    constexpr uint8_t DATE      = 0x04;
    constexpr uint8_t MONTH     = 0x05;
    constexpr uint8_t YEAR      = 0x06;
}

// sunday can be defined as any day, only keep logic sequential!
namespace ds3231_day
{
    constexpr uint8_t SUNDAY    = 1;
    constexpr uint8_t MONDAY    = 2;
    constexpr uint8_t TUESDAY   = 3;
    constexpr uint8_t WEDNESDAY = 4;
    constexpr uint8_t THURSDAY  = 5;
    constexpr uint8_t FRIDAY    = 6;
    constexpr uint8_t SATURDAY  = 7;
}

void set_time(driver::i2c::I2C& i2c, uint8_t hours, uint8_t minutes, uint8_t seconds);
void set_date(driver::i2c::I2C& i2c, uint8_t day, uint8_t date, uint8_t month, uint8_t year);

void get_time(driver::i2c::I2C& i2c, uint8_t& hours, uint8_t& minutes, uint8_t& seconds);
void get_date(driver::i2c::I2C& i2c, uint8_t& day, uint8_t& date, uint8_t& month, uint8_t& year);

const char* get_day_of_week(uint8_t i);


#endif /* INC_DS3231_HPP_ */