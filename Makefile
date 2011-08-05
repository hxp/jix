CROSS = ../crosscompiler

CC = $(CROSS)/bin/i386-elf-gcc
AS = $(CROSS)/bin/i386-elf-as
LD = $(CROSS)/bin/i386-elf-ld
OBJS = system/loader.o system/main.o system/kstring.o system/x86.o system/vga.o

CFLAGS = -Wall -Wextra -nostdlib -nostartfiles -nodefaultlibs -ggdb -std=c99

all: kernel dirs
	cp tools/boot/stage2_eltorito build/cdtree/boot
	cp tools/boot/menu.lst build/cdtree/boot/grub
	cp system/kernel build/cdtree/boot
	mkisofs -input-charset utf-8 -quiet -R -b boot/stage2_eltorito -no-emul-boot -boot-load-size 4 -boot-info-table -o distrib/jix.iso build/cdtree 

kernel: $(OBJS)
	$(LD) -T system/linker.ld -o system/kernel $(OBJS)

clean:
	-rm -rf system/*.o system/kernel build distrib

dirs:
	-mkdir build build/cdtree build/cdtree/boot build/cdtree/boot/grub
	-mkdir distrib

run:
	qemu -cdrom distrib/jix.iso 
