#pragma once

#include <stdint.h>

/**
 * Represents x86 Input/Output operations.
 */
class IO
{
public:
    /**
     * Sends the specified byte value to the I/O port.
     */
    inline static void OutB(uint16_t port, uint8_t value);
    /**
     * Requests a byte value from the specified I/O port.
     */
    inline static uint8_t InB(uint16_t port);
};

#include "hardware/io.inl"