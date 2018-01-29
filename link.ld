OUTPUT_FORMAT("binary")
ENTRY(kmain)
phys = 0x100000;
virt = 0xC0000000;
SECTIONS
{
    .text virt : AT(virt) {
        code = .;
        *(.text)
        *(.rodata*)
        . = ALIGN(4096);
    }
    .data : 
    {
        data = .;
        *(.data)
        . = ALIGN(4096);
    }
    .bss :
    {
        bss = .;
        *(.bss)
        . = ALIGN(4096);
    }
    end = .;
}
