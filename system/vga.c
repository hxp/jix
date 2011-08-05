#include "vga.h"
#include "x86.h"

// basic textmode vga driver

unsigned char *videoram = (unsigned char *) VIDEORAM_ADDR;

// default background colours, light grey on black like DOS
// attribute is 4 bits of bg in upper, 4 bits of bg in lower
char vga_attribute = 0x07; // default grey on black

struct vga_cursor_position {
	int x;
	int y;
};

struct vga_cursor_position vga_curs;

void vga_set_colour(int bg, int fg) {

	vga_attribute = (bg << 4) | (fg & 0x0F);

}

void vga_clear() {
	// overwrite the VGA buffer with spaces of the 
	// appropriate colour
	
	for (int x = 0; x < 4000; x += 2) {
		videoram[x] = 0x20; // ascii space
		videoram[x+1] = vga_attribute;
	}
	// move the cursor back to the upper left corner
	vga_move_cursor(0,0);
}

void vga_move_cursor() {
	int pos = vga_curs.y * 80 + vga_curs.x;

	outb(0x3d4, 14);
	outb(0x3d5, pos >> 8);
	outb(0x3d4, 15);
	outb(0x3d5, pos);
}

void vga_scroll() {
	// move all data up one line
	for (int i = 0; i < 24 * 160; i++) {
		videoram[i] = videoram[i+160];
	}

	// blank last line since there may be random data
	for (int i = 24*160; i < 25*160; i += 2) {
		videoram[i] = 0x20; // ascii space
		videoram[i+1] = vga_attribute;
	}

	// move the cursor up a line
	vga_curs.y--;
}

void vga_putchar(unsigned char c) {
	if (vga_curs.y == 24) {
		vga_scroll();
	}

	int loc = vga_curs.y * 160 + vga_curs.x * 2;
	videoram[loc] = c;
	videoram[loc + 1] = vga_attribute;

	// increment cursor
	if (vga_curs.x == 79) {
		vga_curs.x = 0;
		vga_curs.y++;
	} else {
		vga_curs.x++;
	}

	vga_move_cursor();
}
