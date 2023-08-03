CPU x86-64
USE64

section .code


; ref: https://wiki.osdev.org/SYSENTER
; ref: https://wiki.osdev.org/CPU_Registers_x86-64#MSRs
global enable_sce   ;void enable_sce(void);
enable_sce:
    mov rcx, 0xc0000080     ; to read: IA32_EFER
    rdmsr                   ; read IA32_EFER
    or eax, 1               ; enable System Call Extensions (SCE) bit
    wrmsr                   ; write the new config to IA32_EFER

    mov rcx, 0xc0000081     ; to read: STAR.    
    rdmsr                   ; read STAR
    mov edx, 0x00180008     ; 0x18: user base selector. 0x08: kernel base selector.
    wrmsr                   ; write the new config to STAR

    ret
