C_SOURCE = $(wildcard kernel/*.c screen/*.c io/*.c string/*.c i386/*.c mm/*.c)
ASSEMBLY = $(wildcard i386/*.asm)
HEADERS  = $(wildcard kernel/*.h screen/*.h io/*.h)
INCLUDE  = $(shell pwd)/include/
OBJ      = ${C_SOURCE:.c=.o}
ASM_ELF  = ${ASSEMBLY:.asm=.elf}
ASM_OBJ  = ${ASSEMBLY:.asm=.o}

CC  = i386-elf-gcc
LD  = i386-elf-ld
GDB = i386-elf-gdb

CFLAGS = -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles \
		 -nodefaultlibs -Wall -Wextra -isystem ${INCLUDE} -D i386

all: run_i386

kernel.bin: boot3.o ${OBJ} ${ASM_ELF}
	i386-elf-ld -T link.ld -o $@ $^ --oformat binary

%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -ffreestanding -c $< -o $@

%.elf: %.asm ${ASSEMBLY}
	nasm $< -f elf -o $@	

boot3.o: boot3.asm
	nasm $< -f elf -o $@	

boot2.bin: boot2.asm
	nasm $< -f bin -o $@

boot1.bin: boot1.asm
	nasm $< -f bin -o $@

jos.bin: boot1.bin boot2.bin kernel.bin
	cat $^ > jos.bin

runbl: boot1.bin boot2.bin
	cat $^ > jos.bin
	qemu-system-x86_64 -fda jos.bin -monitor stdio

run_i386: jos.bin
	qemu-system-x86_64 -fda jos.bin -monitor stdio

debug: jos.bin kernel.elf
	qemu-system-i386 -s -fda jos.bin &
	i386-elf-gdb -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"

kernel.elf: boot3.o ${OBJ} ${ASM_ELF}
	i386-elf-ld -o $@  $^ -Ttext 0x100000

clean:
	rm *.bin ${OBJ} ${ASM_ELF}
