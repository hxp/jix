#define VIDEORAM_ADDR  0xb8000

void vga_clear();
void vga_move_cursor();
void vga_set_colour(int, int);
void vga_putchar(unsigned char);
