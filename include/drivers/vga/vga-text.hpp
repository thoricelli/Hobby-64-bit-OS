#pragma once

#include <stdint.h>
#include <stddef.h>

#include <runtime/string.h>

// 2 bytes: COLOR, TEXT
#define VGA_TEXT_MEMORY_ADDRESS 0xB8000
#define VGA_TEXT_MEMORY (uint16_t *)VGA_TEXT_MEMORY_ADDRESS

#define VGA_TEXT_CHARACTERS_PER_LINE 80
#define VGA_TEXT_TOTAL_LINES 25

#define VGA_TEXT_TOTAL_CHARACTERS VGA_TEXT_CHARACTERS_PER_LINE *VGA_TEXT_TOTAL_LINES

// 8 MSB are attribute, 8 LSB are character.
#define VGA_ENTRY_SIZE_BYTES 2

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

/**
 * This class represents the VGA text buffer.
 * See https://en.wikipedia.org/wiki/VGA_text_mode.
 */
class VGAText
{
private:
    inline volatile static uint16_t *vgaTextBuffer = VGA_TEXT_MEMORY;

    inline static size_t vgaPos = 0;
    inline static uint8_t vgaColor;
    inline static bool blink;

public:
    /**
     * Enables blink for the current character.
     */
    static void SetBlink(bool blink);
    /**
     * Sets the VGA color of the text.
     */
    static void SetColor(enum vga_color fg, enum vga_color bg);
    /**
     * Writes a line to the text buffer.
     */
    static void WriteLine(char *str);
    /**
     * Writes a single character to the text buffer.
     */
    static void PutChar(char character);
    /**
     * Moves the text cursor to the next line.
     */
    static void NextLine();
    /**
     * Moves the text cursor the previous line.
     */
    static void PreviousLine();
    /**
     * Moves each text line to the one above, discards the top line.
     */
    static void ScrollUpLine();
};