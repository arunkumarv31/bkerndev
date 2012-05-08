all: kernel.bin


kernel.bin: loader.o kernel.o screen.o memory.o gdt.o idt.o irq.o timer.o kb.o linker.ld
	ld -T linker.ld -o kernel.bin loader.o kernel.o screen.o memory.o gdt.o idt.o irq.o timer.o kb.o

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

irq.o: irq.c
	gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -c -o irq.o irq.c -I./include

timer.o: timer.c
	gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -c -o timer.o timer.c -I./include

kb.o: kb.c
	gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -c -o kb.o kb.c -I./include
clean:
	rm -rf *.o kernel.bin

