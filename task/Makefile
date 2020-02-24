all:
	sh-elf-gcc -c -Wa,-gstabs -o asmfunc.o asmfunc.s
	sh-elf-gcc -c -g -o main.o main.c
	sh-elf-ld -Tsh7262_large.ld -nostartfiles -o task.elf asmfunc.o main.o
	sh-elf-objcopy -j .text -j .data -O binary task.elf task.bin
clean:
	rm task.elf task.bin asmfunc.o main.o
