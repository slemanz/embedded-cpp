#ifndef INC_CONFIG_HPP_
#define INC_CONFIG_HPP_

#include "driver_gpio.hpp"
#include "driver_uart.hpp"
#include "driver_systick.hpp"
#include "driver_i2c.hpp"

extern driver::gpio::Pin pa4;
extern driver::gpio::Pin pa5;
extern driver::gpio::Pin pa6;
extern driver::gpio::Pin pa7;

extern driver::i2c::I2C i2c1;

void config_drivers();

#endif /* INC_CONFIG_HPP_ */