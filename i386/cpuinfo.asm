global __asm_getcpumaxid
global __asm_getcpustring
global __asm_getcpubrandstring

__asm_getcpumaxid:
    mov eax, 0x80000000
    cpuid
    ret
    

__asm_getcpustring:
    push ebp
    mov ebp, esp
    pushad
    mov esi, [ebp + 8]
    mov eax, 0x0
    cpuid
    mov [esi], ebx
    mov [esi + 4], edx
    mov [esi + 8], ecx
    mov al, 0x0
    mov [esi + 12], al
    popad
    pop ebp
    ret

__asm_getcpubrandstring:
    push ebp
    mov ebp, esp
    pushad
    mov eax, 0x80000002
    mov edi, eax
    mov eax, [ebp + 8]
    mov esi, eax
___brandstring_loop:
    mov eax, edi
    cmp eax, 0x80000004
    ja ___brandstring_out
    cpuid
    mov [esi], eax
    mov [esi + 4], ebx
    mov [esi + 8], ecx
    mov [esi + 12], edx
    add esi, 16
    inc edi
    jmp ___brandstring_loop
___brandstring_out: 
    popad
    pop ebp
    ret
