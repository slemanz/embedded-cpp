#ifndef INC_CONFIG_HPP_
#define INC_CONFIG_HPP_

#include "driver_gpio.hpp"
#include "driver_uart.hpp"
#include "driver_systick.hpp"

extern driver::gpio::Pin pa5;


void config_drivers();

#endif /* INC_CONFIG_HPP_ */