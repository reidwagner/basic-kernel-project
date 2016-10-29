#include <stddef.h>
#include <stdint.h>
#include <bkp/tty.h>
#include <bkp/iomap.h>
#include <bkp/stdio.h>
#include <bkp/keyboard.h>
#include <bkp/pic.h>

extern void keyboard_int(void);
extern void load_idt(void* idt_ptr);

struct IDT_entry {
    uint16_t offset_low;
    uint16_t selector;
    uint8_t zero;
    uint8_t type_attr;
    uint16_t offset_high;
};

struct IDT_entry IDT[256];

void initialize_idt(void) {
    uint32_t keyboard_handler_address;
    uint32_t idt_address;
    uint32_t idt_ptr[2];

    keyboard_handler_address = (uint32_t)keyboard_int;
    IDT[PIC1_DATA].offset_low = keyboard_handler_address & 0xffff;
    IDT[PIC1_DATA].selector = 0x08;
    IDT[PIC1_DATA].zero = 0;
    IDT[PIC1_DATA].type_attr = 0x8e;
    IDT[PIC1_DATA].offset_high = (keyboard_handler_address & 0xffff0000) >> 16;

    //ICW1
    outb(PIC1_COMMAND,0x11);
    outb(PIC2_COMMAND,0x11);

    //ICW2
    outb(PIC1_DATA,0x20);
    outb(PIC2_DATA,0x28);

    //ICW3
    outb(PIC1_DATA,0x00);
    outb(PIC2_DATA,0x00);

    //ICW4
    outb(PIC1_DATA,0x01);
    outb(PIC2_DATA,0x01);

    //mask interrupts
    outb(PIC1_DATA,0xff);
    outb(PIC2_DATA,0xff);

    idt_address = (uint32_t) IDT;
    idt_ptr[0] = (sizeof (struct IDT_entry) * 256) + ((idt_address & 0xffff) << 16);
    idt_ptr[1] = idt_address >> 16;

    load_idt(idt_ptr);

    outb(PIC1_DATA, 0xfd);
}
