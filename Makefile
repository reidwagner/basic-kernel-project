C_SOURCES = $(wildcard kernel/*.c lib/*.c drivers/*.c)
OBJ = ${C_SOURCES:.c=.o}

all: os-image

run: all #Having trouble with Bochs 2.6.2 on Fedora (not related to X I believe). Currently just scping image back to my Macbook.
	bochs

os-image: boot/boot_sect.bin kernel.bin 
	cat $^ > os-image

kernel.bin: kernel/kernel_entry.o ${OBJ}
	ld -melf_i386 -o kernel.bin -Ttext 0x1000 $^ --oformat binary

%.o: %.c ${HEADERS}
	gcc -m32 -ffreestanding -I $(PWD)/include -c $< -o $@

%.o: %.asm
	nasm $< -f elf -o $@

%.bin: %.asm 
	nasm $< -f bin -I 'lib/' -I 'boot/' -o $@ 

clean: 
	rm -f *.bin os-image
	rm -f kernel/*.o boot/*.o drivers/*.o lib/*.o
