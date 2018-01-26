[bits 32]
[extern kmain]

mov ax, 'J'
mov eax, 0x300000
mov esp, eax
call kmain
jmp $
