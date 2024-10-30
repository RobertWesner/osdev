[org 0x7c00]
KERNEL_OFFSET equ 0x1000

    pusha
    ; get memory limit (https://wiki.osdev.org/Detecting_Memory_(x86))
    XOR CX, CX
    XOR DX, DX
    MOV AX, 0xE801
    INT 0x15		; request upper memory size
;    JC SHORT .ERR
    CMP AH, 0x86		; unsupported function
;    JE SHORT .ERR
    CMP AH, 0x80		; invalid command
;    JE SHORT .ERR
;    JCXZ .USEAX		; was the CX result invalid?

	; MEM_1 = number of contiguous Kb, 1M to 16M
	; MEM_2 = contiguous 64Kb pages above 16M
	MOV [MEM_1], cx
	MOV [MEM_2], dx

    popa

    ; disable blinking cursor
    mov ch, 32
    mov ah, 1
    int 10h

    mov [BOOT_DRIVE], dl

    mov bp, 0x9000
    mov sp, bp

    mov bx, MSG_REAL_MODE
    call print

    call load_kernel

    call switch_to_pm

%include "boot_16/print.asm"
%include "boot_16/disk.asm"
%include "gdt.asm"
%include "boot_32/print.asm"
%include "switch_to_pm.asm"

[bits 16]

load_kernel:
    mov bx, MSG_LOAD_KERNEL
    call print

    mov bx, KERNEL_OFFSET
    mov dh, 25
    mov dl, [BOOT_DRIVE]
    call disk_load

    ret

[bits 32]

BEGIN_PM:
    mov ebx, MSG_PROT_MODE
    call print32

    call KERNEL_OFFSET

    jmp $

; GLOBALS
BOOT_DRIVE              db 0
MSG_REAL_MODE           db "Started in 16-bit Real Mode", 0
MSG_PROT_MODE           db "Successfully landed in 32-bit Protected Mode", 0
MSG_LOAD_KERNEL         db "Loading kernel into memory.", 0

times 506-($-$$)        db 0

; Store the memory information in the last 4 bytes, ugly but hey idek what i'm really doing here

MEM_1                   dw 0
MEM_2                   dw 0

dw 0xAA55
