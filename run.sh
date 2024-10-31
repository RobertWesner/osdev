#!/bin/bash

(
  cd asm
  nasm boot_sect.asm -f bin -o ../build/boot_sect.bin
  nasm -f elf32 kernel_entry.asm -o ../build/kernel_entry.o
  nasm -f elf32 isr.asm -o ../build/isr.o
)

g++ -m32 -fno-pie -fno-stack-protector -ggdb3 -nostdinc -fno-builtin -I$(pwd)/lib -ffreestanding -c kernel.cpp -o build/kernel.o || exit
ld -m elf_i386 -o build/kernel.bin -Ttext 0x1000 build/kernel_entry.o build/isr.o build/kernel.o --oformat binary

cat build/boot_sect.bin build/kernel.bin > build/os-image.bin

qemu-system-x86_64 \
  -m 1048576K \
  -drive file=build/os-image.bin,format=raw,index=0,media=disk
