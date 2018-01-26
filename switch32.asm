[bits 16]
prot_switch:
    mov eax, 0x8BADBEEF
    cli         ; Disable interrupts
    lgdt [gdt_desc]
    mov eax, cr0
    or eax, 0x01
    mov cr0, eax
    jmp $
    jmp CODE_SEG:prot_init

[bits 32]
prot_init:
    mov ax, DATA_SEG
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ebp, 0x90000
    mov esp, ebp
    mov ebx, success
    call prints32
    call PROT_BEGIN

PROT_BEGIN:
    mov esi, 0x80000
    mov edi, 0x100000
    mov ecx, 0x1800
    mov eax, 0xDEADBEEF
    jmp $
