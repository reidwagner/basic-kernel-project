extern handle_keyboard_int
extern term_printchar
global keyboard_int
global load_idt

load_idt:
    mov edx, [esp + 4]
    lidt [edx]
    sti
    ret

keyboard_int:
    push ebp
    mov ebp, esp
    pushad
    call handle_keyboard_int
    popad
    leave
    iret
