section .data

global GDT64
global LOAD_GDT64

GDT64:
    .Null: equ $ - GDT64
    dq 0
    .Code: equ $ - GDT64
    dw 0
    dw 0
    db 0
    db 10011010b
    db 00100000b
    db 0
    .Data: equ $ - GDT64
    dw 0
    dw 0
    db 0
    db 10010010b
    db 00000000b
    db 0
GDT_END:


GDT_PTR:
    dw GDT_END - GDT64 - 1    ; Limit
    dq GDT64                  ; Base


; lgdt
LOAD_GDT64:
    lgdt[GDT_PTR]

    ; prep for iretq
    mov rax, rsp
    push 0x10   ; ss
    push rax    ; rsp
    pushf       ; rflags
    push 0x8    ; cs
    push rdi    ; rip (return addr = first arg.; sysv_abi)
    iretq
