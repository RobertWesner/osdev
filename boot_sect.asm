[bits 16]
[org 0x7c00]

    mov bx, INIT_MSG
    call print

    ; BIOS stores our boot drive in DL, we keep note of it in the BOOT_DRIVE variable.
    mov [BOOT_DRIVE], dl

    ; Store the stack at 0x8000
    mov bp, 0x8000
    mov sp, bp

    ; Load 5 sectors to 0x0000(ES):0x9000(BX)
    mov bx, 0x9000
    mov dh, 5
    mov dl, [BOOT_DRIVE]
    call disk_load

    ; disk loaded successfully
    mov bx, DISK_SUCCESS_MSG
    call print

    mov dx, [0x9000]
    call print_hex_16

    mov dx, [0x9000 + 512]
    call print_hex_16

    jmp $

%include "boot/print.asm"
%include "boot/disk.asm"

BOOT_DRIVE              db 0

INIT_MSG                db 'Started bootloader!', 0x0D, 0x0A, 0
DISK_SUCCESS_MSG        db 'Loaded disk!', 0x0D, 0x0A, 0

times 510-($-$$) db 0

dw 0xAA55

times 256 dw 0xDADA
times 256 dw 0xFACE
