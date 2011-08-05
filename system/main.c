#include "main.h"
#include "kstring.h"
#include "vga.h"

// multiboot version
//void kmain( void* mbd, unsigned int magic ) {
void kmain() {
	// multiboot header
	// char * boot_loader_name =(char*) ((long*)mbd)[16];

	vga_set_colour(0x3,0xa);
	vga_clear();
}
