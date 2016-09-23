global __asm_test

__asm_test:
    mov eax, 0xDEAD
hang:
    jmp hang
