[bits 32]

VMEM equ 0xb81E0
WTBB equ 0x0f

prints32:
    pusha
    mov edx, VMEM

prints32_loop:
    mov al, [ebx]
    mov ah, WTBB
    cmp al, 0
    je prints32_done
    mov[edx], ax
    add ebx, 1
    add edx, 2
    jmp prints32_loop

prints32_done:
    popa
    ret
