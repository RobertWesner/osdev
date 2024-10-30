print_c:
    push ax
    mov ah, 0x0E
    int 0x10
    pop ax
    ret

print:
    push bx
    push ax
    mov ah, 0x0E
    _print_loop:
        cmp byte [bx], 0
        je _print_exit
        mov al, [bx]
        int 0x10
        inc bx
        jmp _print_loop
    _print_exit:
        pop ax
        pop bx
        ret

print_hex_4:
    push ax
    push dx
    mov ah, 0x0E
    cmp dl, 0x09
    jg _print_hex_4_AF
    ; print 0-9
        mov al, dl
        add al, 0x30
        int 0x10
        pop dx
        pop ax
        ret
    _print_hex_4_AF:
        mov al, dl
        add al, 0x37
        int 0x10
        pop dx
        pop ax
        ret

print_hex_8:
    pusha
    push dx
    shr dx, 4
    call print_hex_4
    pop dx
    and dl, 0x0F
    call print_hex_4
    popa
    ret

print_hex_16:
    pusha
    push dx
    shr dx, 8
    call print_hex_8
    pop dx
    call print_hex_8
    popa
    ret
