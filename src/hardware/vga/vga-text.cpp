#include "hardware/vga/vga-text.hpp"

void VGAText::SetColor(enum vga_color fg, enum vga_color bg)
{
    VGAText::vgaColor = (uint16_t)(fg | bg << 4);
}

void VGAText::WriteLine(char *str)
{
    for (uint32_t i = 0; str[i] != '\0'; i++)
    {
        VGAText::PutChar(str[i]);
    }

    VGAText::NextLine();
}

void VGAText::PutChar(char character)
{
    if (VGAText::vgaPos >= VGA_TEXT_TOTAL_CHARACTERS)
    {
        VGAText::ScrollUpLine();
        VGAText::PreviousLine();
    }

    if (character == '\n')
    {
        VGAText::NextLine();
        return;
    }

    VGAText::vgaTextBuffer[VGAText::vgaPos] = (uint16_t)character | (((VGAText::vgaColor) | (blink << 7)) << 8);

    VGAText::vgaPos++;
}

void VGAText::NextLine()
{
    VGAText::vgaPos += VGA_TEXT_CHARACTERS_PER_LINE - (VGAText::vgaPos % VGA_TEXT_CHARACTERS_PER_LINE);
}

void VGAText::PreviousLine()
{
    VGAText::vgaPos -= VGA_TEXT_CHARACTERS_PER_LINE - (VGAText::vgaPos % VGA_TEXT_CHARACTERS_PER_LINE);
}

void VGAText::SetBlink(bool blink)
{
    VGAText::blink = blink;
}

void VGAText::ScrollUpLine()
{
    // Memcpy copies byte per byte, but each entry in the VGA text memory is 2 bytes.
    memcpy(
        (char *)VGA_TEXT_MEMORY_ADDRESS,
        (char *)VGA_TEXT_MEMORY_ADDRESS + (VGA_TEXT_CHARACTERS_PER_LINE * VGA_ENTRY_SIZE_BYTES),
        ((VGA_TEXT_TOTAL_LINES - 1) * VGA_TEXT_CHARACTERS_PER_LINE) * VGA_ENTRY_SIZE_BYTES);
}