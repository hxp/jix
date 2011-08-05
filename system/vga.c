#include "vga.h"
#include "x86.h"

// basic textmode vga driver

unsigned char *videoram = (unsigned char *) VIDEORAM_ADDR;

// default background colours, light grey on black like DOS
// attribute is 4 bits of bg in upper, 4 bits of bg in lower
char vga_attribute = 0x07; // default grey on black

void vga_set_colour(int bg, int fg) {

	vga_attribute = (bg << 4) | (fg & 0x0F);

}

struct vga_cursor_position {
	int x;
	int y;
};

struct vga_cursor_position vga_curs;

void vga_clear() {
	// overwrite the VGA buffer with spaces of the 
	// appropriate colour
	
	for (int x = 0; x < 4000; x += 2) {
		videoram[x] = 0x20; // ascii space
		videoram[x+1] = vga_attribute;
	}
	vga_move_cursor(0,0);
}

void vga_move_cursor(int x, int y) {
	unsigned int pos;

	vga_curs.x = x;
	vga_curs.y = y;

	pos = vga_curs.y * 80 + vga_curs.x;

	outb(0x3d4, 14);
	outb(0x3d5, pos >> 8);
	outb(0x3d4, 15);
	outb(0x3d5, pos);
}

void vga_putchar(unsigned char c) {

}
