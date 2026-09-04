; https://www.gnu.org/software/grub/manual/multiboot2/multiboot.html#Header-layout
MAGIC equ 0xE85250D6 ; Multiboot2 magic
ARCHITECTURE equ 0 ; 32-bit protected mode
HEADER_LENGTH equ (multiboot_header_end - multiboot_header_start)

section .multiboot
align 4

multiboot_header_start:
    dd MAGIC
    dd ARCHITECTURE
    dd HEADER_LENGTH
    dd -(MAGIC + ARCHITECTURE + HEADER_LENGTH)  

    ; End tag
    dw 0 ; Type
    dw 0 ; Flag
    dd 8 ; Size
multiboot_header_end: