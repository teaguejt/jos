; Begin second stage bootloader
[bits 32]
[extern kmain]

mov ax, 'J'
; Set up the stack, woot woot
mov eax, 0x7BFFF
mov esp, eax
call kmain
jmp $
