CPU x86-64
USE64

section .code


global LOAD_GDT64    ;void LOAD_GDT64(struct gdt_desc* gdt_desc);
LOAD_GDT64:
    lgdt [rdi]       ; load GDT from arg1 (sysv_abi)


    ; set kernel_ds
    mov ax, 0x10
    
    mov ds, ax

    mov es, ax
    mov fs, ax
    mov gs, ax

    cli    ; disable interrupts
    mov ss, ax    ; set stack seg
    sti    ; enable interrupts

    
    pop  rdi          ; save return addr to rdi (sysv_abi)
    
    ; set kernel_cs
    mov  rax, 0x08
    push rax
    push rdi

    retfq             ; ret far