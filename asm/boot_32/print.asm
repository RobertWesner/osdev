[bits 32]

VIDEO_MEMORY equ 0xB8000
WHITE_ON_BLACK equ 0x0F

print32:
    pusha
    mov edx, VIDEO_MEMORY

    _print32_loop:
        mov al, [ebx]
        mov ah, WHITE_ON_BLACK

        cmp al, 0
        je _print32_end

        mov [edx], ax

        add ebx, 1
        add edx, 2

        jmp _print32_loop

    _print32_end:
        popa
        ret
