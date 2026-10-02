#include "ds3231.hpp"

using namespace driver;

// Convert BCD to decimal
uint8_t bcd_to_dec(uint8_t bcd)
{
    return ((bcd >> 4) * 10) + (bcd & 0x0F);
}

// Convert decimal to BCD
uint8_t dec_to_bcd(uint8_t dec)
{
    return ((dec / 10) << 4) | (dec % 10);
}

void set_time(driver::i2c::I2C& i2c, uint8_t hours, uint8_t minutes, uint8_t seconds)
{
    uint8_t data[4];
    data[0] = ds3231_reg::SECONDS;
    data[1] = dec_to_bcd(seconds);
    data[2] = dec_to_bcd(minutes);
    data[3] = dec_to_bcd(hours);
    
    i2c.generate_start();
    i2c.send_address(DS3231_ADDRESS, false); // Write operation
    i2c.send_data(data, 4);
    i2c.generate_stop();
}

void get_time(driver::i2c::I2C& i2c, uint8_t& hours, uint8_t& minutes, uint8_t& seconds)
{
    // Write register address
    uint8_t reg = ds3231_reg::SECONDS;
    
    i2c.generate_start();
    i2c.send_address(DS3231_ADDRESS, false); // Write operation
    i2c.send_data(&reg, 1);
    
    // Read data
    i2c.generate_start();
    i2c.send_address(DS3231_ADDRESS, true); // Read operation
    
    uint8_t data[3];
    i2c.receive_data(data, 3, driver::i2c::AckControl::Enable);
    i2c.generate_stop();
    
    seconds = bcd_to_dec(data[0] & 0x7F);
    minutes = bcd_to_dec(data[1]);
    hours = bcd_to_dec(data[2] & 0x3F); // 24-hour format
}

void set_date(driver::i2c::I2C& i2c, uint8_t day, uint8_t date, uint8_t month, uint8_t year)
{
    uint8_t data[5];
    data[0] = ds3231_reg::DAY;
    data[1] = dec_to_bcd(day);
    data[2] = dec_to_bcd(date);
    data[3] = dec_to_bcd(month);
    data[4] = dec_to_bcd(year);
    
    i2c.generate_start();
    i2c.send_address(DS3231_ADDRESS, false); // Write operation
    i2c.send_data(data, 5);
    i2c.generate_stop();
}

void get_date(driver::i2c::I2C& i2c, uint8_t& day, uint8_t& date, uint8_t& month, uint8_t& year)
{
    // Write register address
    uint8_t reg = ds3231_reg::DAY;
    
    i2c.generate_start();
    i2c.send_address(DS3231_ADDRESS, false); // Write operation
    i2c.send_data(&reg, 1);
    
    // Read data
    i2c.generate_start();
    i2c.send_address(DS3231_ADDRESS, true); // Read operation
    
    uint8_t data[4];
    i2c.receive_data(data, 4, driver::i2c::AckControl::Enable);
    i2c.generate_stop();
    
    day = bcd_to_dec(data[0]);
    date = bcd_to_dec(data[1]);
    month = bcd_to_dec(data[2]);
    year = bcd_to_dec(data[3]);
}

const char* days[] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};

const char* get_day_of_week(uint8_t i)
{

	return days[i-1];
}