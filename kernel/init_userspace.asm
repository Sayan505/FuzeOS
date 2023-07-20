CPU x86-64
USE64

section .code


global init_userspace   ;void init_userspace(void* usermode_subroutine, void* usermode_stack);
init_userspace:
    mov rcx, rdi        ; new rip
    mov rsp, rsi        ; new rsp
    mov r11, 0x0202     ; correct eflags
    sysretq;            ; to userspace!
