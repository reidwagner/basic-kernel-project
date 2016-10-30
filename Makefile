C_SOURCES = $(wildcard kernel/*.c lib/*.c drivers/*.c)
OBJ = ${C_SOURCES:.c=.o}

all: bkp.img

run: all #Having trouble with Bochs 2.6.2 on Fedora. Currently just scping image back to my Macbook.
	bochs

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
