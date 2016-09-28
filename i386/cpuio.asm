global __asm_outb
global __asm_outw
global __asm_outd
global __asm_inb
global __asm_inw
global __asm_ind

__asm_outb:
    push ebp
    mov ebp, esp
    push eax
    push ebx
    pop ebx
    pop eax
    pop ebp
    ret

__asm_outw:
    push ebp
    mov ebp, esp
    push eax
    push ebx
    pop ebx
    pop eax
    pop ebp
    ret

__asm_outd:
    push ebp
    mov ebp, esp
    push eax
    push ebx
    pop ebx
    pop eax
    pop ebp
    ret

__asm_inb:
    push ebp
    mov ebp, esp
    push eax
    push ebx
    pop ebx
    pop eax
    pop ebp
    ret

__asm_inw:
    push ebp
    mov ebp, esp
    push eax
    push ebx
    pop ebx
    pop eax
    pop ebp
    ret

__asm_ind:
    push ebp
    mov ebp, esp
    push eax
    push ebx
    pop ebx
    pop eax
    pop ebp
    ret
