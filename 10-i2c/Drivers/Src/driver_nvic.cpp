#include "driver_nvic.hpp"

using namespace driver::nvic;

void Nvic::global_enable_interrupts()
{
    asm volatile ("cpsie i");
}

void Nvic::global_disable_interrupts()
{
    asm volatile ("cpsid i");
}