#include "vga.h"

static size_t vga_pos = 0;
static uint8_t vga_color;

void vga_set(enum vga_color fg, enum vga_color bg)
{
    vga_color = (uint16_t)(fg | bg << 4);
}

void vga_writeline(char *str)
{
    volatile uint16_t *vga_text_buffer = VGA_MEMORY;

    for (int i = 0; str[i] != '\0'; i++)
    {
        vga_text_buffer[vga_pos] = (uint16_t)str[i] | (vga_color << 8);
        vga_pos++;
    }

    vga_pos += VGA_CHARACTERS_PER_LINE - (vga_pos % VGA_CHARACTERS_PER_LINE);
}