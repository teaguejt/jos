ORG 0x7C00

; Setup segments
mov ax, cs
mov ds, ax
mov es, ax
mov ss, ax

; Since we're using "call" here, we need to have a (small) stack
mov sp, 0x9C00

; Do it all. Clear the screen, print some stuff, load the rest of jOS from
; disk, switch to protected mode, relocate the kernel to 1 MiB, and jump to
; its first instruction. Not bad considering we're limited to 512 bytes ;-)
call clear_scr
mov si, welcome
call print_str
call print_nl
mov si, loading
call print_str
call load_jos
mov si, preswitch
call print_str
call prot_switch

hang:
    jmp hang

load_jos:
    mov cx, 3
load_loop:
    xor ah, ah
    int 0x13
    mov bx, 0x8000
    mov es, bx
    xor bx, bx
    mov dx, 0
    mov ch, 0
    mov cl, 2
    mov al, 0x0F
    mov ah, 0x02
    int 0x13
    jnc load_exit
    sub cx, 1
    cmp cx, 0
    jz load_err
load_err:
    mov si, error
    call print_str
    jmp hang
load_exit:
    mov si, success
    call print_str
    call print_nl
    ret

print_str:
    mov bx, 0xB800
    mov es, bx
    xor bx, bx
    xor ax, ax
    mov bl, [cursory]
    mov al, [cursorx]
    mov cl, al
    imul bx, 0xA0
    imul ax, 0x02
    add bx, ax
    mov ah, 0x0F
print_str_loop:
    lodsb
    cmp al,0
    jz print_str_out
    mov [es:bx], ax
    add bx, 0x02
    inc cl
    jmp print_str_loop
print_str_out:
    mov [cursorx], cl
    ret

print_nl:
    xor ax, ax
    mov [cursorx], al
    mov al, [cursory]
    add al, 1
    mov [cursory], al
    ret

clear_scr:
    mov bx, 0xB800
    mov es, bx
    mov al, 0x0
clear_scr_loop:
    cmp bx, 0xFA0
    jz clear_scr_out
    mov [es:bx], al
    add bx, 0x01
    jmp clear_scr_loop
clear_scr_out:
    ret

[bits 32]
PROT_BEGIN:
    ; Relocate the kernel to the one-meg mark
    mov esi, 0x80000    ; FROM where we loaded from floppy
    mov edi, 0x100000   ; TO 1MiB
    mov ecx, 0x1000     ; 4k words (two pages, but paging is off)
    rep movsw
    jmp 0x100000
stop:
    mov si, error
    call print_nl
    call print_str
    jmp stop
 
[bits 16]
%include 'gdt_dummy.asm'
%include 'switch32.asm'
%include 'print32.asm'

error db " Failed", 0
success db " Bueno", 0
welcome db "jOS v0.1 alpha s1 BL", 0
loading db "Loading BL2/kernel from disk...", 0
preswitch db "About to switch to protected mode...", 0
postswitch db "Success.", 0
attempt db 0x3
cursorx db 0x0
cursory db 0x0

times 510-($-$$) db 0
dw 0xaa55
