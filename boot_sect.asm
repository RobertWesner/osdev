[org 0x7c00]

loop:
    mov bx, HELLO_WORLD
    call print

    mov dl, 0x09
    call print_hex_4

    mov dl, 0x0A
    call print_hex_4

    mov dl, 0xF0
    call print_hex_8

    mov dx, 0xB00B
    call print_hex_16

    jmp $

%include "boot/print.asm"

HELLO_WORLD:
    db 'Hello World!', 0x0D, 0x0A, 0

times 510-($-$$) db 0

dw 0xAA55