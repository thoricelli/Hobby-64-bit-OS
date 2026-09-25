#include "hardware/vga/vga-text.hpp"
#include "hardware/io.hpp"

extern "C" void kernel_main()
{
    VGAText::SetColor(VGA_COLOR_WHITE, VGA_COLOR_BLACK);

    VGAText::WriteLine("Hello world from 64-bit long mode!");
    VGAText::WriteLine("This kernel is not yet implemented, so your CPU will halt for now :)");

    VGAText::NextLine();
    VGAText::WriteLine("This VGA text will be replaced with GOP in the future.\nBelow is just a blink test.");
    VGAText::NextLine();

    VGAText::PutChar('>');

    // Doesn't work on QEMU...
    VGAText::SetBlink(true);
    VGAText::PutChar('_');
    VGAText::SetBlink(false);
}