#include <stddef.h>
#include <stdint.h>
#include <bkp/tty.h>
#include <bkp/iomap.h>
#include <bkp/stdio.h>
#include <bkp/keyboard.h>
#include <bkp/pic.h>

void main(void) {
    initialize_term();
    term_printstring("Booted into Kernel 0.1 succesfully. \nMultiline comment.");
    term_printstring("\nBinary print test. Printing 254: ");
    term_print_binary(254);
    term_printstring("\n");
    //scroll_term(1);
    initialize_keyboard();
    initialize_idt();
    //keyboard_debug();
    draw_term();
}
