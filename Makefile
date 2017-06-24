C_SOURCES = $(wildcard kernel/*.c lib/*.c drivers/*.c)
OBJ = ${C_SOURCES:.c=.o}

all: bkp.img

qemu: all
	qemu-system-i386 -drive file=bkp.img,index=0,if=floppy,format=raw

curses: all
	qemu-system-i386 -curses -drive file=bkp.img,index=0,if=floppy,format=raw

bkp.img: boot/boot_sect.bin kernel.bin
	cat $^ > bkp.img

kernel.bin: kernel/kernel_entry.o drivers/keyboard_init.o ${OBJ}
	ld -melf_i386 -o kernel.bin -Ttext 0x1000 $^ --oformat binary

%.o: %.c ${HEADERS}
	gcc -m32 -ffreestanding -I $(PWD)/include -c $< -o $@

%.o: %.asm
	nasm $< -f elf -o $@

%.bin: %.asm 
	nasm $< -f bin -I 'lib/' -I 'boot/' -o $@ 

clean: 
	rm -f *.bin bkp.img
	rm -f kernel/*.o boot/*.o drivers/*.o lib/*.o
