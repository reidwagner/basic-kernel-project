#include <stddef.h>
#include <stdint.h>
#ifndef TTY_IO
#define TTY_IO

enum vga_color {
    VGA_COLOR_BLACK = 0x0,
    VGA_COLOR_BLUE = 0x1,
    VGA_COLOR_GREEN = 0x2,
    VGA_COLOR_CYAN = 0x3,
    VGA_COLOR_RED = 0x4,
    VGA_COLOR_MAGENTA = 0x5,
    VGA_COLOR_BROWN = 0x6,
    VGA_COLOR_LIGHT_GREY = 0x7,
    VGA_COLOR_DARK_GREY = 0x8,
    VGA_COLOR_LIGHT_BLUE = 0x9,
    VGA_COLOR_LIGHT_GREEN = 0xa,
    VGA_COLOR_LIGHT_CYAN = 0xb,
    VGA_COLOR_LIGHT_RED = 0xc,
    VGA_COLOR_LIGHT_MAGENTA = 0xd,
    VGA_COLOR_LIGHT_BROWN = 0xe,
    VGA_COLOR_WHITE = 0xf,
};

#define colorpair(foreground,background) (foreground | (background << 4))
#define vgapair(character,color) (character | (color << 8))

void draw_term(void);
void initialize_term(void);
void term_printchar(char c);
void set_col(uint16_t c);
void set_row(uint16_t r);
int get_cursor(void);
void set_cursor(int cursor);
void scroll_term(int displacement);
void move_col(int16_t displacement);
void move_row(int16_t displacement);

#endif
