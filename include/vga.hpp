#pragma once

#include <stdint.h>
#include <stddef.h>

// 2 bytes: COLOR, TEXT
#define VGA_MEMORY (uint16_t *)0xB8000
#define VGA_CHARACTERS_PER_LINE 80

enum vga_color
{
    VGA_COLOR_BLACK = 0,
    VGA_COLOR_BLUE = 1,
    VGA_COLOR_GREEN = 2,
    VGA_COLOR_CYAN = 3,
    VGA_COLOR_RED = 4,
    VGA_COLOR_MAGENTA = 5,
    VGA_COLOR_BROWN = 6,
    VGA_COLOR_LIGHT_GREY = 7,
    VGA_COLOR_DARK_GREY = 8,
    VGA_COLOR_LIGHT_BLUE = 9,
    VGA_COLOR_LIGHT_GREEN = 10,
    VGA_COLOR_LIGHT_CYAN = 11,
    VGA_COLOR_LIGHT_RED = 12,
    VGA_COLOR_LIGHT_MAGENTA = 13,
    VGA_COLOR_LIGHT_BROWN = 14,
    VGA_COLOR_WHITE = 15,
};

class VGA
{
private:
    inline static size_t vgaPos = 0;
    inline static uint8_t vgaColor;

public:
    static void set(enum vga_color fg, enum vga_color bg);
    static void writeline(char *str);
};