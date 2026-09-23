#include "vga.hpp"

void VGA::set(enum vga_color fg, enum vga_color bg)
{
    VGA::vgaColor = (uint16_t)(fg | bg << 4);
}

void VGA::writeline(char *str)
{
    volatile uint16_t *vga_text_buffer = VGA_MEMORY;

    for (uint32_t i = 0; str[i] != '\0'; i++)
    {
        vga_text_buffer[VGA::vgaPos] = (uint16_t)str[i] | (VGA::vgaColor << 8);
        VGA::vgaPos++;
    }

    VGA::vgaPos += VGA_CHARACTERS_PER_LINE - (VGA::vgaPos % VGA_CHARACTERS_PER_LINE);
}