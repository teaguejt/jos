; Begin second stage bootloader
[bits 16]
ORG 0x8000

mov [cursorx], bx
mov [cursory], cx
mov si, success
call print_str
call print_nl
mov si, getmm
call print_str
call get_smap
mov si, success
call print_str
call print_nl

; Reset segments and switch to protected mode
mov si, protsw
call print_str
xor eax, eax
mov eax, prot_switch
call prot_switch

; Get the E820 map. Has to happen BEFORE the protected mode switch
; Yes, it uses extended registers from real mode. This is... weird
get_smap:
    mov ax, 0x0
    mov es, ax
    mov ax, 0x2000
    mov edx, 0x534D4150 ; Magic number
    xor ebx, ebx
get_smap_loop:
    mov di, ax          ; set up address of buffer, for jOS  0x2000
    mov eax, 0xE820     ; Function call
    mov ecx, 0x18       ; Structure size
    int 0x15
    ; last entry can be signified by:
    ; ebx = 0 OR carry flag set. Test both.
    jc get_smap_out
    push ax
    mov ax, [smaps_entries]
    inc ax
    mov [smaps_entries], ax
    pop ax
    mov [smaps_esize], cl
    cmp ebx, 0x0
    jz get_smap_out
    xor eax, 0x534D4150
    jnz get_smap_err
    mov ax, di
    add ax, 0x18
    jmp get_smap_loop
get_smap_out:
    ; Fill in the size and entry number
    ; Yup, my segment trickery is stupid
    ; I need to find a way around this direct addressing,
    ; but without malloc or a real kernel I'm out of
    ; ideas
    mov ax, [smaps_entries]
    mov bx, 0x2400
    mov [bx], ax
    mov ax, [smaps_esize]
    mov bx, 0x2410
    mov [bx], ax
    ret
get_smap_err:
    mov si, error
    call print_str
    hlt
    jmp $
    

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
    mov ah, 0x07
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

[bits 16]
; Create a dummy GDT. Since we're using paging, we don't
; really need this for long.
gdt_start:
    dd 0x0
    dd 0x0

gdt_code:
    dw 0xffff
    dw 0x0
    db 0x0
    db 10011010b
    db 11001111b
    db 0x0

gdt_data:
    dw 0xffff
    dw 0x0
    db 0x0
    db 10010010b
    db 11001111b
    db 0x0


gdt_end:

gdt_desc:
    dw gdt_end - gdt_start - 1
    dq gdt_start

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start
gdtr dw 0x0
     dd 0x0

prot_switch:
    mov eax, 0x0
    mov ds, ax
    cli
    lgdt[gdt_desc]
    mov eax, cr0
    or eax, 0x01
    mov cr0, eax
    jmp CODE_SEG:prot_init

[bits 32]
; Oh wow, I get to write this twice, too. Thank you
; segmentation, followed by a lack thereof
; Whatever. I have a whole 1k here. That's almost
; I N F I N I T E S T O R A G E
print_str32:
    pusha
    xor edx, edx
    xor ecx, ecx
    mov dl, [cursory]
    mov cl, [cursorx]
    push cx
    imul dx, 0xA0
    imul cx, 0x02
    add dx, cx
    add edx, 0xb8000
    mov cl, 0x0
print_str32_loop:
    mov al, [ebx]
    mov ah, 0x07
    cmp al, 0
    je print_str32_done
    inc cl
    mov [edx], ax
    add ebx, 1
    add edx, 2
    jmp print_str32_loop
print_str32_done:
    pop ax
    add al, cl
    mov [cursorx], al
    popa
    ret

print_nl32:
    pusha
    xor ax, ax
    mov [cursorx], al
    mov al, [cursory]
    add al, 1
    mov [cursory], al
    popa
    ret
    

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
    call print_str32

; We can't exactly go back to the beginning here.
; Execute this linearly to finalize.
call print_nl32
mov ebx, findpgs
call print_str32
call find_free_page


; Start setting up paging. First, find a free page above
; 0x10000 for the kernel pgd
find_free_page:
    pusha
    mov ebx, 0x2400         ; starting addr of e820 map
    mov eax, [ebx]          ; how many records to check
find_free_page_loop:
    cmp eax, 0x0
    jz find_free_page_err
    sub eax, 1
    push eax
    mov ebx, 0x2200
    mov eax, [ebx]
    mov ecx, [ebx + 20]
    jmp $
    popa
    ret
find_free_page_err:
    mov ebx, error
    call print_str32
    jmp $

PROT_BEGIN:
    mov esi, 0x8400
    mov edi, 0x100000
    mov ecx, 0x1800
    rep movsw
    jmp $
    jmp 0x100000

[bits 16]
error db "Failed.", 0
success db "Bueno.", 0
getmm db "Getting memory map... ", 0
protsw db "Switching to protected mode... ", 0
findpgs db "Finding space for kernel pg. structs... ", 0

cursorx db 0x0
cursory db 0x0
smaps_entries dw 0x0
smaps_esize dw 0x0
kernel_pgd dd 0x0
kernel_pte dd 0x0

times 1024 - ($ - $$) db 0
