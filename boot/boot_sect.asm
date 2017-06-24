[org 0x7c00]
KERNEL_OFFSET equ 0x1000

    ;clear screen
    pusha
    mov ax, 0x0700
    mov bh, 0x07
    mov cx, 0x0000
    mov dx, 0x184f
    int 0x10

    ;move cursor to beginning
    mov ah, 0x02
    mov bh, 0x00
    mov dx, 0x0000
    int 0x10
    popa

    mov [BOOT_DRIVE], dl

    mov bp, 0x9000
    mov sp, bp

    mov bx, MSG_REAL_MODE
    call print_string
    
    call load_kernel 

    call switch_to_pm

    jmp $

%include "print_string.asm"
%include "disk_load.asm"
%include "gdt.asm"
%include "print_string_pm.asm"
%include "switch_to_pm.asm"

[bits 16]

load_kernel:
    mov bx, KERNEL_OFFSET
    mov dh, 15
    mov dl, [BOOT_DRIVE]
    call disk_load

    mov bx, MSG_KERNEL_LOADED
    call print_string

    ret

[bits 32]

BEGIN_PM:

    mov ebx, MSG_PROT_MODE
    call print_string_pm

    call KERNEL_OFFSET

    jmp $

;Global vars
BOOT_DRIVE db 0
MSG_REAL_MODE db "Started in 16-bit real mode.",0
MSG_KERNEL_LOADED db "Kernel loaded from disk.",0
MSG_PROT_MODE db "Entered 32-bit protected mode.",0

times 510-($-$$) db 0
dw 0xaa55
