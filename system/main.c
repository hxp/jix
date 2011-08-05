#include "main.h"
#include "kstring.h"
#include "vga.h"

// multiboot version
//void kmain( void* mbd, unsigned int magic ) {
void kmain() {
	// multiboot header
	// char * boot_loader_name =(char*) ((long*)mbd)[16];

	vga_clear();

	char *hello = "Hello, world!";

	for (int x; hello[x] != 0; x++) {
		vga_putchar(hello[x]);
	}
}
