; Begin second stage bootloader
[bits 32]
[extern kmain]

mov ax, 'J'
; Set up the stack, woot woot
; Current plan: stack goes at 3 MiB and grows down, heap goes at 2 Mib and
; grows up. This gives us 1 Mib for kernel; everything (processes and
; whatnot) can go above the stack
mov eax, 0x300000
mov esp, eax
; Seriously? We have a separate ASM file just for this?
call kmain
jmp $
