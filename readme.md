# VoidStar
## An Experimental Hobby Operating System

### Introduction
Not much to say here. VoidStar (formerly jOS) is a small, x86 (as in i386, not x86_64) operating system that I'm writing for fun.

### Building
You need to have an i386 cross-compiler (so, an i386 `binutils` and `gcc`), that I'm not going to go into detail about how to set up. I prefer `binutils 2.29.1` (`2.29` seem to have some issues) and `gcc 6.2.0` or `6.3.0`. I'd LOVE to use `gcc 7.x`, but it has some trouble building with some of the options necessary for OS building. Add all these things to your PATH, and if you have `QEMU` installed just run `make` and it starts up automatically.

I'll add more details soon. They're in handwritten notes right now.

### Design
#### Bootloader I
Bootloader I loads at address `0x7C00` per the PC standard. It does a maxed-out floppy read using BIOS interrupts to load the second stage bootloader and the kernel itself from "disk." It loads all this stuff to physical address `0x8000` then jumps to it. There's really not much more to it.

For fun, examine the Bootloader I output file (`boot1.bin`). You'll notice it's exactly 512 bytes long but most of that isn't used. It HAS to be, because that's the sector length of a floppy, and we're pretending it's still 1993 here. The signature at the end (`0xAA55`) is needed. According to the PC standard, a BIOS shall not boot something that doesn't end with this signature.

#### Bootloader II
Bootloader II does a couple important things. First, it gets the E820 memory map using `int 0x15`. We have to do this early since we lose the ability to call BIOS interrupts once we enable protected mode. The memory map is stored at `0x2000` (an arbitrary decision, this is just an address that is guaranteed to be free by the PC standard). Then, information about the memory map is stored at `0x2400` (again, guaranteed to be free and leaves plenty of room for the map itself). This information includes the number of map entries and the map entry size.

Next, Bootloader II enables protected mode. It creates a dummy GDT (since VoidStar uses paging, it doesn't have to be complete), loads this address and the structure size into the GDT register using `lgdt`, then far jumps back to itself to completely enable 32-bit protected mode.

Bootloader II then enables paging. First, we claim three pages of memory (`0x3000`, `0x4000`, and `0x5000`, again, these are guaranteed to be free by the PC standard and don't interfere with anything else that we've put in memory). These are for the kernel page directory, the first page table of virtual memory, and the first page table the kernel, respectively, although it's not all filled in immediately. The page directory is populated at entry 0 and 768 (virtual addresses 0 and 3GB) so it points to the two page tables, respectively. Then, the page tables are populated. The 0-index page table is incrementally populated from index 0 to 255 to identity map the first megabyte of memory (i.e. page 0 corresponds to frame 0). This allows us to keep references to critical structures, the BIOS data area, and video memory. The first few pages of the kernel are then populated in the 768-index page table, mapping virtual address 3GB + a few pages to physical address 1MB + a few pages, so we have a fairly standard higher-half kernel. Page attributes are pretty normal: supervisor mode, present, 4k size, etc.

Now, we don't enable paging immediately because we still need physical address for one thing. The kernel itself is copied from its temporary home at `0x8400` to 1MB.

Finally, we enable paging by loading the `cr3` register with the physical address of the page directory, setting the PE flag in `cr0`, and jumping to `0xC0000000`. This address, now that paging is set up, is virtual, and the kernel loads up by jumping to it. 

Examination may show that Bootloader II is forced to 1k in size. This is not a standard. It was just a design decision. This way I can modify it, but still know where Bootloader III and the kernel reside in memory for copying and jumping purposes.

#### Bootloader III
This isn't really a bootloader, but I'm including it here for explanation. You'll notice that Bootloaders I and II compile to `.bin` files, but Bootloader III compiles to `boot3.o`. That's because it's linked with the kernel. Basically, because of the way Bootloaders I and II work, I don't want the linker touching them. Bootloader III doesn't do anything the linker could negatively impact, so it exists to call `kmain` and provide an entry point to code that's written in C. It's also some of the first paged code executed, and therefore reconfigures the system stack upon entry to an address that won't page fault, but gives us a decent working size.
