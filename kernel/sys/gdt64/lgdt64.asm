USE64                ;generate 64-bit code

section .code


global LOAD_GDT64    ;void LOAD_GDT64(struct gdt_desc* gdt_desc);
LOAD_GDT64:
    lgdt [rdi]       ; load GDT from arg1 (sysv_abi)

    
    mov ax, 0x40     ; TSS seg
    ltr ax           ; Load Task Register


    ; set addr of gdt_entry kernel_ds to ds, es, fs, gs and ss
    cli    ; disable interrupts
    
    mov ax, 0x10
    
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov ss, ax    ; set stack seg

    sti    ; enable interrupts

    pop  rdi          ; save return addr to rdi (sysv_abi)
    mov  rax, 0x08
    push rax
    push rdi

    lretq             ; ret far
