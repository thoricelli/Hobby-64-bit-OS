#include "hardware/io.hpp"

inline void IO::OutB(uint16_t port, uint8_t value)
{
    __asm__ volatile("outb %b0, %w1" : : "a"(value), "Nd"(port) : "memory");
}

inline uint8_t IO::InB(uint16_t port)
{
    uint8_t result;
    __asm__ volatile(
        "inb %w1, %b0"
        : "=a"(result)
        : "Nd"(port)
        : "memory");
    return result;
}