# Fuze
An experimental x86_64 hobby OS project.
&nbsp;  
&nbsp;  
&nbsp;  

[![FuzeOS Kernel CI](https://github.com/Sayan505/FuzeOS/actions/workflows/test_knl.yml/badge.svg)](https://github.com/Sayan505/FuzeOS/actions/workflows/test_knl.yml)

&nbsp;
&nbsp;

## Build Fuze
### &nbsp; Get the source
&nbsp; &nbsp; `git clone` to test the kernel with the pre-build bootloader or,  
&nbsp; &nbsp; `make init_edk2` after cloning to fetch EDK2 + all its submodules.  
&nbsp;  

### &nbsp; Requirements
* clang (for Kernel)
* GCC (>=5) (for the Bootloader)
* GNU LD
* nasm
* GNU Parted
* dosfstools
* EDK II (optional. binary included to build the bootloader)
&nbsp;  

### &nbsp; Process
&nbsp; Build full system with disk images (losetup requires root):  
&nbsp; &nbsp; `make kernel`  
&nbsp; &nbsp; `make fs`  
&nbsp; &nbsp; `make img`  
&nbsp;

## Run Fuze
&nbsp; Run the full system from the disk image:  
&nbsp; &nbsp; `make run`   
&nbsp;

## Build FuzeBoot UEFI bootloader
### &nbsp; Requirements
* Atleast GCC5 (build-essential)
* libuuid-devel
* iasl
* nasm
* [EDK II](https://github.com/tianocore/edk2):  
###### &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; Dependencies of EDK II are subject to change.

### &nbsp; Process
+ Build with FuzeBoot. (Platform and inf included)
+ just do `make bootloader`.
