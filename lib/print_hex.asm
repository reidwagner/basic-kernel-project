
 print_hex:

    pusha
    mov bx, HEX_OUT
    add bx, 0x2
    hexloop:
        ;mov ah, 0x0e
        mov al, [bx]

        cmp al, 0x0
        je hexend

        mov al, dh
        shr al, 0x4
        and al, 0xf

        cmp al, 0xa
        jge gten

        add al, 0x30
        jmp cont

        gten: 
        add al, 0x57

        cont:
        ;int 0x10
        mov [bx], byte al
        shl dx, 0x4
        add bx, 0x1

        jmp hexloop

    hexend: 
        ;and bx, 0x0
        mov bx, HEX_OUT
        call print_string
        popa
        ret

 HEX_OUT: db '0x0000',0
