[bits 32]
[extern kmain]

mov eax, 'J'
mov eax, 0x90000
mov esp, eax
call kmain
jmp $
