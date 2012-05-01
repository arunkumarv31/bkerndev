all: kernel.bin

kernel.bin: loader.o kernel.o  linker.ld
	ld -T linker.ld -o kernel.bin loader.o kernel.o 

loader.o: loader.s
	nasm -f elf -o loader.o loader.s

kernel.o: kernel.c
	gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -c -o kernel.o kernel.c

clean:
	rm -rf *.o kernel.bin

