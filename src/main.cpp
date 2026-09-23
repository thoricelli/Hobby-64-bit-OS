#include "vga.hpp"

extern "C" void kernel_main()
{
    VGA::set(VGA_COLOR_WHITE, VGA_COLOR_BLACK);

    VGA::writeline("Hello world from 64-bit long mode!");
    VGA::writeline("This kernel is not yet implemented, so your CPU will halt for now :)");
}