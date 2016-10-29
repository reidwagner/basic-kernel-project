#include <bkp/tty.h>
#include <bkp/iomap.h>

#define VGA_CONTROL_REG 0x3D4
#define VGA_DATA_REG 0x3D5

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

static size_t top_row;
static uint16_t term[100][80];
static uint16_t term_color;
static size_t term_row;
static size_t term_col;
uint16_t* video_memory;

void draw_term(void) {
    size_t i,j;
    for (i = 0; i < VGA_WIDTH; i++) {
        for (j = 0; j < VGA_HEIGHT; j++) {
            *(video_memory + (j*VGA_WIDTH+i)) = term[j+top_row][i];
        }
    }
}

void initialize_term(void) {
    video_memory = (uint16_t*) 0xb8000;
    top_row = 0;
    term_row = 0;
    term_col = 0;
    term_color = colorpair(VGA_COLOR_WHITE,VGA_COLOR_BLACK);
    size_t i,j;
    for (i = 0; i < VGA_WIDTH; i++) {
        for (j = 0; j < VGA_HEIGHT; j++) {
            term[j][i] = vgapair(' ',colorpair(VGA_COLOR_WHITE,VGA_COLOR_BLACK));
        }
    }
    draw_term();
}

void scroll_term(int displacement) {
    top_row += displacement;
    draw_term();
}

void term_printchar(char c) {
    if (c == '\n') {
        term_row++;
        term_col = 0;
    } else {       
        term[term_row][term_col] = vgapair(c,term_color);
        term_col++;
    }
}

int get_cursor(void) {

    outb(VGA_CONTROL_REG, 14);
    int offset = inb(VGA_DATA_REG) << 8;
    outb(VGA_CONTROL_REG, 15);
    offset += inb(VGA_DATA_REG);

    return offset;
}

void set_cursor(int cursor) {
    outb(VGA_CONTROL_REG, 14);
    outb(VGA_DATA_REG, cursor >> 8);
    outb(VGA_CONTROL_REG, 15);
    outb(VGA_DATA_REG, cursor & 0xff);
}

void move_col(int16_t displacement) {
    term_col += displacement;
}

void move_row(int16_t displacement) {
    term_row += displacement;
}

void set_col(uint16_t c) {
    term_col = c;
}

void set_row(uint16_t r) {
    term_row = r;
}
