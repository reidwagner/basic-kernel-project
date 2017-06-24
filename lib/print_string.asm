print_string:
    pusha
    loop:
        mov ah, 0x0e
        mov al, [bx]
        cmp al, 0
        je end
        int 0x10
        add bx, 1
        jmp loop
    end:
        mov al, 0x0a
        int 0x10
        mov al, 0x0d
        int 0x10
        popa
        ret
