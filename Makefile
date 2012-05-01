all: loader.bin


loader.bin: loader.s
	nasm -f bin -o loader.bin loader.s

clean:
	rm -rf *.bin 

