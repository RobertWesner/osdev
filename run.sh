#!/bin/bash

nasm boot_sect.asm -f bin -o boot_sect.bin

#Block device options:
#-fda/-fdb file  use 'file' as floppy disk 0/1 image
#-hda/-hdb file  use 'file' as hard disk 0/1 image
#-hdc/-hdd file  use 'file' as hard disk 2/3 image
#-cdrom file     use 'file' as CD-ROM image
qemu-system-x86_64 -fda boot_sect.bin
