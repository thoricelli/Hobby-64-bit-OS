bits 64
global long_mode_main
extern kernel_main

VGA_MEMORY equ 0xb8000
VGA_COLS equ 80
VGA_ROWS equ 25
VGA_BUFFER_SIZE equ 2 * VGA_COLS * VGA_ROWS

section .text
long_mode_main:
    ; Cleanup
    cli
    mov ax, 0
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    ; Clear VGA buffer
    mov rdi, VGA_MEMORY
    mov rax, 0
    mov rcx, VGA_BUFFER_SIZE / 8
    rep stosq

    call kernel_main
    hlt
