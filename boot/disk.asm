; load DH sectors to ES:BX from drive DL
disk_load:
    pusha
    push dx

    mov ah, 0x02        ; BIOS read sector function
    mov al, dh          ; Read DH sectors
    mov ch, 0x00        ; Select cylinder 0
    mov dh, 0x00        ; Select head 0
    mov cl, 0x02        ; Start reading from second sector (right after boot sector)
    int 0x13

    jc disk_error       ; Jump if errror (carry flag set)

    pop dx
    cmp dh, al          ; if AL (sectors read) != DH (sectors expected) -> error
    jne disk_error

    popa
    ret

disk_error_carry:
    mov bx, DISK_ERROR_CARRY_MSG
    call print
    mov ah, 0x01
    call print_hex_8
    jmp $

disk_error:
    mov bx, DISK_ERROR_MSG
    call print
    mov ah, 0x01
    call print_hex_8
    jmp $

DISK_ERROR_CARRY_MSG    db "Disk read carry bit set, code: ", 0
DISK_ERROR_MSG          db "Disk read error, code: ", 0
