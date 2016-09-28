global __asm_test

__asm_test:
    push ebp
    mov ebp, esp
    mov eax, [ebp + 8]
    ;mov eax, 0xDEAD
    pop ebp
    ret
