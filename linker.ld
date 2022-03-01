OUTPUT_FORMAT(elf64-x86-64)
OUTPUT_ARCH(i386:x86-64)

ENTRY(start_kernel)


__LNK_SYM_kernel_VMA_start = 0x0000000000000000; /*TODO: higher-half kernel, -2GiB (0xFFFFFFFF80000000)*/

SECTIONS
{
    . = ALIGN(0x1000);
    . = __LNK_SYM_kernel_VMA_start + 0x0000000000100000;

    __LNK_SYM_kernel_start = .;

    .text : ALIGN(0x1000)
    {
        __LNK_SYM_text_start = .;
        *(.text*)
        __LNK_SYM_text_end   = .;

        __LNK_SYM_rodata_start = .;
        *(.rodata*)
        __LNK_SYM_rodata_end   = .;
    }

    .data : ALIGN(0x1000)
    {
        __LNK_SYM_data_start = .;
        *(.data*)
        __LNK_SYM_data_end   = .;
    }

    .sym : ALIGN(0x1000) {
        *(.sym*)
        *(COMMON)
    }

    .bss : ALIGN(0x1000)
    {
        __LNK_SYM_bss_start = .;
        *(.bss*)
        LONG(0)     /* "The LONG(0) forces the bss section to be written to the file." */
        __LNK_SYM_bss_end   = .;

        *(COMMON)
    }

    /DISCARD/ :
    {
        *(.eh_frame)
        *(.comment)
    }


    . = ALIGN(0x1000);
    __LNK_SYM_kernel_end = .;
}
