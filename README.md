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
&nbsp; &nbsp; `make init edk2` after cloning to fetch EDK2 + all its submodules.  
&nbsp; &nbsp; `make delete edk2` to remove the edk2 folder after working.
&nbsp;  

### &nbsp; Requirements
* clang (for Kernel)
* GCC (for the Bootloader)
* GNU LD
* nasm
* GNU Parted
* dosfstools
* EDK II (optional; binary included, to build the bootloader)
&nbsp;  

### &nbsp; Process
&nbsp; Build full system with disk images (losetup requires root):  
&nbsp; &nbsp; `make`  
  
&nbsp; Build full system in `$(FSDIR)` without generating disk images:  
&nbsp; &nbsp; `make testbuildall`  
  
&nbsp; Build the kernel only, in `$(FSDIR)` without generating disk images and use the pre-built bootloader:  
&nbsp; &nbsp; `make testbuild`. Then do `make img` to generate a disk image. This is what you should use to test the system out.

&nbsp;

## Run Fuze
&nbsp; Run the full system from the disk image:  
&nbsp; &nbsp; `make run`  
&nbsp; Run the full system from $(FSDIR) in RW mode:  
&nbsp; &nbsp; `make testrun`  

&nbsp;

## Build FuzeBoot UEFI bootloader
### &nbsp; Requirements
* Atleast GCC5 (build-essential)
* libuuid-devel
* iasl
* nasm
* python3-distutils
* [EDK II](https://github.com/tianocore/edk2):  
###### &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; Dependencies of EDK II are subject to change.

### &nbsp; Process
+ Build with FuzeBoot. (Platform and inf included)
+ just do `make bootloader`.
