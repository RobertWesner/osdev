#!/bin/bash

nasm boot_sect.asm -f bin -o boot_sect.bin
nasm -f elf32 kernel_entry.asm -o kernel_entry.o

g++ -m32 -fno-pie -fno-stack-protector -ggdb3 -nostdinc -fno-builtin -I$(pwd)/lib -ffreestanding -c kernel.cpp -o kernel.o || exit
ld -m elf_i386 -o kernel.bin -Ttext 0x1000 kernel_entry.o kernel.o --oformat binary

cat boot_sect.bin kernel.bin > os-image.bin

qemu-system-x86_64  -drive file=os-image.bin,format=raw,index=0,media=disk
