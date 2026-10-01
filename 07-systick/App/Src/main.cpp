#include "config.hpp"
#include <cstdio>

int main(void)
{
    config_drivers();
    printf("\nBoard init!!\n");
    
    while(1)
    {
        pa5.toggle();
        driver::systick::Systick::delay_ms(200);
    }
}
