bits 32

; MULTIBOOT
MULTIBOOT2_CHECKSUM equ 0x36d76289

; VGA
VGA_MEMORY equ 0xb8000
VGA_RED equ 0x0C

; CPUID
CPUID_HIGHEST_EXTENDED_FUNCTION_IMPLEMENTED equ 0x80000000
CPUID_EXTENDED_PROCESSOR_INFO equ CPUID_HIGHEST_EXTENDED_FUNCTION_IMPLEMENTED + 1

; EXTENDED PROCESSOR INFO
EXTENDED_PROCESSOR_INFO_LM equ 1 << 29

; x86 FLAGS
FLAG_ABLE_TO_USE_CPUID equ 1 << 21

; CR0 FLAGS
CR0_PAGING equ 1 << 31

; CR4 FLAGS
CR4_PAE equ 1 << 5

; Extended Feature Enable Register
EFER_LME equ 1 << 8 ; Long Mode Active

; PAGE TABLES
PAGE_TABLE_MAX_ENTRIES equ 512
PAGE_TABLE_SIZE_PER_ENTRY_BYTES equ 8
PAGE_TABLE_SIZE_BYTES equ PAGE_TABLE_MAX_ENTRIES * PAGE_TABLE_SIZE_PER_ENTRY_BYTES

; PAGE ENTRY
PAGE_PRESENT equ 1 << 0
PAGE_READ_WRITE equ 1 << 1
PAGE_PAGE_SIZE equ 1 << 7

PAGE_L2_SIZE equ 0x200000

; MSR
EFER equ 0xC0000080

; Global Descriptor Table
GDT_ACCESS_READ_WRITE   equ 1 << 1
GDT_ACCESS_EXECUTABLE equ 1 << 3
GDT_ACCESS_DESCRIPTOR equ 1 << 4
GDT_ACCESS_PRESENT equ 1 << 7

GDT_FLAGS_LONG_MODE equ 1 << 5

global _start
extern long_mode_main

section .text
_start:
    mov esp, stack_top ; Set up 16 KiB of stack space before going into C.
    
    call is_multiboot2 ; Check if this kernel was called by multiboot2
    
    call has_cpuid
    call has_long_mode

    call setup_page_tables
    call enable_paging

    call enable_long_mode

    lgdt [gdt.pointer]
    jmp gdt.code_segment:long_mode_main

    hlt

; Multiboot2 checks
is_multiboot2:
    cmp eax, MULTIBOOT2_CHECKSUM
    jne no_multiboot2
    ret

no_multiboot2:
    push multiboot2_err
    call vga_write

    add esp, 8
    hlt

; CPUID & Long mode
has_long_mode:
    mov eax, CPUID_HIGHEST_EXTENDED_FUNCTION_IMPLEMENTED
    cpuid

    mov ecx, eax
    mov eax, CPUID_EXTENDED_PROCESSOR_INFO ; Check if we have Extended Processor Info, but also keep this in eax for future CPUID.

    cmp ecx, eax
    jbe no_long_mode

    cpuid ; Extended Processor Info
    test edx, EXTENDED_PROCESSOR_INFO_LM
    jz no_long_mode

    ret

no_long_mode:
    push no_long_mode_err

    call vga_write

    add esp, 8
    hlt

has_cpuid:
    ; https://en.wikipedia.org/wiki/FLAGS_register#FLAGS
    ; First we flip the 21st bit (able to use CPUID)

    pushfd ; Push FLAGS register onto the stack
    pop eax ; Give me that...
    mov ecx, eax ; Copy
    xor eax, FLAG_ABLE_TO_USE_CPUID ; Flip CPUID
    push eax
    popfd ; Here you go.

    ; Check
    pushfd
    pop eax
    xor eax, ecx
    jz no_cpuid
    
    ret

no_cpuid:
    push no_cpuid_err
    call vga_write

    add esp, 8
    hlt

; Page tables
setup_page_tables:
    mov eax, l3_page_table
    or eax, PAGE_PRESENT | PAGE_READ_WRITE
    mov [l4_page_table], eax

    mov eax, l2_page_table
    or eax, PAGE_PRESENT | PAGE_READ_WRITE
    mov [l3_page_table], eax

    mov ecx, 0

fill_page: ; Allocates 1GB for now in page level 2.

    mov eax, PAGE_L2_SIZE
    mul ecx
    or eax, PAGE_PRESENT | PAGE_READ_WRITE | PAGE_PAGE_SIZE ; 2MB per page
    mov [l2_page_table + ecx * 8], eax

    inc ecx
    cmp ecx, PAGE_TABLE_MAX_ENTRIES
    jne fill_page

    ret

enable_paging:
    mov eax, l4_page_table
    mov cr3, eax

    mov eax, cr4
    or eax, CR4_PAE ; Page Size Extension
    mov cr4, eax

    ret

enable_long_mode:
    ; https://en.wikipedia.org/wiki/Control_register
    mov ecx, EFER
    rdmsr

    or eax, EFER_LME ; Long Mode Enable
    wrmsr
    
    ; https://wiki.osdev.org/CPU_Registers_x86-64#CR0
    mov eax, cr0
    or eax, CR0_PAGING
    mov cr0, eax

    ret

; Writes a string to the VGA text memory.
; Argument 1: char*
vga_write:
    mov ecx, [esp + 4]

    mov edx, VGA_MEMORY
    mov ah, VGA_RED

.write_str_loop:
    mov al, byte [ecx] ; Retrieve char
    test al, al ; End of string reached?
    jz .return ; Then we are done.

    mov word [edx], ax ; Move to VGA text memory
    inc ecx ; 1 byte per character
    add edx, 2 ; VGA memory is 2 bytes.
    jmp .write_str_loop ; While loop

.return:
    ret

section .rodata
multiboot2_err db "This kernel only supports GRUB multiboot 2.", 0
no_cpuid_err db "Your CPU does not support CPUID, cannot determine if long mode is supported.", 0
no_long_mode_err db "Your CPU does not support long mode. Are you using a 64-bit processor?", 0

; https://wiki.osdev.org/Global_Descriptor_Table
gdt:
    .null: equ $ - gdt
        dq 0
    .code_segment: equ $ - gdt
        .code_segment.limit_lo: dw 0
        .code_segment.base_lo: dw 0
        .code.base_mid: db 0
        .code.access: db GDT_ACCESS_PRESENT | GDT_ACCESS_DESCRIPTOR | GDT_ACCESS_EXECUTABLE | GDT_ACCESS_READ_WRITE
        .code.flags: db GDT_FLAGS_LONG_MODE
        .code.base_hi: db 0 ; Hi
    .pointer:
        dw $ - gdt - 1
        dq gdt

section .bss
align PAGE_TABLE_SIZE_BYTES
l4_page_table:
    resb PAGE_TABLE_SIZE_BYTES
l3_page_table:
    resb PAGE_TABLE_SIZE_BYTES
l2_page_table:
    resb PAGE_TABLE_SIZE_BYTES
align 16
stack_bottom:
    resb 16384 ; 16 KB
stack_top: