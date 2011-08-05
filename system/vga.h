#define VIDEORAM_ADDR  0xb8000

void vga_clear();
void vga_move_cursor(int, int);
void vga_set_colour(int, int);
