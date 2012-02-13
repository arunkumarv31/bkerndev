all: kernel.bin


kernel.bin: loader.o kernel.o screen.o memory.o gdt.o idt.o
	ld -T linker.ld -o kernel.bin loader.o kernel.o screen.o memory.o gdt.o idt.o

loader.o: loader.s
	nasm -f elf -o loader.o loader.s

kernel.o: kernel.c
	gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -c -o kernel.o kernel.c -I./include

screen.o: screen.c
	gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -c -o screen.o screen.c

memory.o: memory.c
	gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -c -o memory.o memory.c

gdt.o: gdt.c
	gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -c -o gdt.o gdt.c -I./include

idt.o: idt.c
	gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -c -o idt.o idt.c -I./include

clean:
	rm -rf *.o kernel.bin

