#include <cstdio>
#include "config.hpp"
#include "ds3231.hpp"

using namespace driver;

int main(void)
{
    config_drivers();

    printf("\nBoard init!!\n");


    driver::systick::Systick::delay_ms(1000);

    // Set initial time and date
    //set_time(i2c1, 4, 48, 0);    // 14:30:00
    //set_date(i2c1, ds3231_day::MONDAY, 18, 8, 25); // Monday, 18th Aug 2025
    
    // Read back time and date
    uint8_t hours, minutes, seconds;
    uint8_t day, date, month, year;

    driver::systick::Systick::delay_ms(100);

    while(1)
    {
        get_time(i2c1, hours, minutes, seconds);
        get_date(i2c1, day, date, month, year);
        printf("time: %02d:%02d:%02d\n", hours, minutes, seconds);
        printf("Day:  %02d/%02d/20%02d - %s\n", date, month, year, get_day_of_week(day));
        driver::systick::Systick::delay_ms(5000);
    }
}
