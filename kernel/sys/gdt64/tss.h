#pragma once


#include <lib/stdtypes.h>


#pragma pack(1)


typedef struct tss {
    uint32_t reserved0;
    uint64_t rsp0;
    uint64_t rsp1;
    uint64_t rsp2;
    uint64_t reserved1;
    uint64_t ist1;
    uint64_t ist2;
    uint64_t ist3;
    uint64_t ist4;
    uint64_t ist5;
    uint64_t ist6;
    uint64_t ist7;
    uint64_t reserved2;
    uint16_t reserved3;
    uint16_t iopb_offset;
} tss_t;


#pragma pack()


// ref: https://wiki.osdev.org/Getting_to_Ring_3
/*
    Set up a barebones TSS with an ESP0 stack.
    When an interrupt (be it fault, IRQ, or software interrupt) happens while the CPU is in user mode, the CPU needs to know where the kernel stack is located.
    This location is stored in the ESP0 (0 for ring 0) entry of the TSS.
*/
