bits 64
global long_mode_main
extern kernel_main
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

    ; Retrieve boot information from EBX we pushed onto stack
    mov edi, dword [rsp]
    add rsp, 4

    call kernel_main
    hlt
