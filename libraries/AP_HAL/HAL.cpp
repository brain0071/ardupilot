#include <assert.h>

#include "HAL.h"

namespace AP_HAL {

/**
 * naodai:2021.09.10
 * void (*setup_fun)(void), void (*loop_fun)(void)声明函数指针
 * *setup_fun为指向函数的函数指针
 * **/
HAL::FunCallbacks::FunCallbacks(void (*setup_fun)(void), void (*loop_fun)(void))
    : _setup(setup_fun)
    , _loop(loop_fun)
{
    assert(setup_fun);
    assert(loop_fun);
}

}

// access serial ports using SERIALn numbering
AP_HAL::UARTDriver* AP_HAL::HAL::serial(uint8_t sernum) const
{
    UARTDriver **uart_array = const_cast<UARTDriver**>(&uartA);
    // this mapping captures the historical use of uartB as SERIAL3
    const uint8_t mapping[] = { 0, 2, 3, 1, 4, 5, 6, 7, 8 };
    static_assert(sizeof(mapping) == num_serial, "num_serial must match mapping");
    if (sernum >= num_serial) {
        return nullptr;
    }
    return uart_array[mapping[sernum]];
}
