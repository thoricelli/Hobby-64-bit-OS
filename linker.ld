ENTRY(_start)

/* https://wiki.osdev.org/Linker_Scripts */
SECTIONS
{
    . = 1M;

    .text ALIGN(CONSTANT(MAXPAGESIZE)) :
    {
        *(.multiboot)
        *(.text)
    }

    .rodata ALIGN(CONSTANT(MAXPAGESIZE)) :
    {
        *(.rodata)
    }

    .data ALIGN(CONSTANT(MAXPAGESIZE)) :
    {
        *(.data)
    }

    .bss ALIGN(CONSTANT(MAXPAGESIZE)) :
    {
        *(COMMON)
        *(.bss*)
    }
}