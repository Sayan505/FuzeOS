#include <sys/cpu/cpuid/cpuid.h>

CHAR* get_cpu_vendor_string(VOID) {
    static UINT32 cpu_vendor_string[4] = { 0 };

    __asm__("mov $0x0, %eax\n\t");

    __asm__("cpuid\n\t");

    __asm__("mov %%ebx, %0\n\t":"=r" (cpu_vendor_string[0]));
    __asm__("mov %%edx, %0\n\t":"=r" (cpu_vendor_string[1]));
    __asm__("mov %%ecx, %0\n\t":"=r" (cpu_vendor_string[2]));

    cpu_vendor_string[3] = 0u;

    return ((CHAR *)cpu_vendor_string);
}
