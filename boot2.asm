; Begin second stage bootloader
[bits 32]
[extern kmain]

mov ax, 'J'
call kmain
jmp $
