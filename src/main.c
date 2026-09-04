#include "vga.h"

void kernel_main()
{
    vga_set(VGA_COLOR_WHITE, VGA_COLOR_BLACK);

    vga_writeline("Hello world from 64-bit long mode!");
    vga_writeline("This kernel is not yet implemented, so your CPU will halt for now :)");
}