[bits 32]

VMEM equ 0xb8000
WTBB equ 0x0f

prints32:
    pusha
    xor edx, edx
    xor ecx, ecx
    mov dl, [cursory]
    mov cl, [cursorx]
    imul dx, 0xA0
    imul cx, 0x02
    add dx, cx
    add edx, VMEM

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
