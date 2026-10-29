bits 32
global x32_main
extern kernel_main
section .text
x32_main:
    call kernel_main
    hlt