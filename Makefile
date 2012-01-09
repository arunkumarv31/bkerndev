all: kernel.bin

kernel.bin: loader.o kernel.o screen.o memory.o
	ld -T linker.ld -o kernel.bin loader.o kernel.o screen.o memory.o

loader.o: loader.s
	nasm -f elf -o loader.o loader.s

kernel.o: kernel.c
	gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -c -o kernel.o kernel.c -I./

screen.o: screen.c
	gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -c -o screen.o screen.c

memory.o: memory.c
	gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -c -o memory.o memory.c

clean:
	rm -rf *.o kernel.bin

