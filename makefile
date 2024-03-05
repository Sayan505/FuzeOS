# REQUIRES ROOT ACCESS TO BUILD THE FINAL DISK IMAGE

# make init_edk2 : fetch EDK2 and it's submodules.

# make all	: build full system with disk images.

# make testbuildall : build full system in $(FSDIR) without generating disk images.

# make bootloader : build the FuzeBoot bootloader only.
# make kernel	  : build the kernel only.

# make testbuild  : build the kernel and copies the bootloader over into in $(FSDIR), if present.
# make testboot   : build the bootloader and copies the kernel over into in $(FSDIR), if present.

# make run		  : run full system from the disk image in $(IMGDIR).
# make testrun	  : run full system from the $(FSDIR) with the disk in R/W mode.


# STEPS FOR A FULL MANUAL BUILD:

# make init_edk2 # (optional; binary included)
# make dirs
# make bootloader
# make kernel
# make fs
#	(at this stage, make any manual changes to the filesystem if any)
# make img


# DEV WORKFLOW:

# code...
# make testbuild
# make testrun



# toolchain:
CC   = clang
LD   = ld
AS   = nasm
QEMU = qemu-system-x86_64

# outputs:
KNL = kernel
BOOTX64.EFI = BootX64.efi

IMG = OS.img

# disk image size in MiB:
IMGMB = 1

# QEMU Memory:
RAM = 8G

# output dirs:
  # extra sources:
EDKDIR     = edk2
EDKBRANCH  = master
BOOTSRCDIR = boot

  # EDK2 init & FuzeBootPkg:
EDKCFGDIR = edk2config

  # output:
    # base build folder:
BUILDDIR  = build

    # base binary folder:
BINDIR    = $(BUILDDIR)/bin

    # kernel:
KNLDIR    = $(BINDIR)/kernel

    # bootloader:
LDRBINDIR = $(BOOTSRCDIR)/$(BUILDDIR)

    # root filesystem directory:
FSDIR     = $(BUILDDIR)/fs

    # bootloader in $(FSDIR):
EFIDIR    = $(FSDIR)/EFI/BOOT

	# kernel in $(FSDIR):
SYSDIR    = $(FSDIR)/sys

    # disk image output folder: 
IMGDIR    = $(BUILDDIR)/img

    # loop-disk mount point:
MNTPNT    = $(BUILDDIR)/mnt


# kernel sources:
C_KERNELSRC   := $(shell find ./kernel/ -type f -name '*.c')
ASM_KERNELSRC := $(shell find ./kernel/ -type f -name '*.asm')
##$(shell find ./ -type d \( -path ./boot -o -path ./progs \) -prune -false -o -name '*.c')

# objs:
OBJ := ${C_KERNELSRC:.c=.o} ${ASM_KERNELSRC:.asm=.o}


# toolchain flags:
CFLAGS =       -target x86_64-unknown-none-elf64                              \
               -O2                                                            \
               -std=c11                                                       \
               -Wall                                                          \
               -Wextra                                                        \
               -Werror                                                        \
               -Wno-unused-but-set-variable                                   \
               -Wno-unused-parameter                                          \
               -Wno-unused-variable                                           \
               -Wno-pointer-arith                                             \
               -Wno-int-conversion                                            \
               -Wno-gnu-label-as-value                                        \
               -ffreestanding                                                 \
               -nostdlib                                                      \
               -nostdinc                                                      \
               -nodefaultlibs                                                 \
               -fno-pic                                                       \
               -fno-stack-protector                                           \
               -fno-omit-frame-pointer                                        \
               -mcmodel=kernel                                                \
               -mno-red-zone                                                  \
               -mno-mmx                                                       \
               -mno-sse                                                       \
               -mno-sse2                                                      \
               -mno-sse3                                                      \
               -mno-ssse3                                                     \
               -mno-sse4                                                      \
               -mno-sse4.1                                                    \
               -mno-sse4.2                                                    \
               -mno-80387                                                     \
               -I.                                                            \
               -Ikernel -g3

LDFLAGS =      -T linker.ld                                                   \
               -no-pie                                                        \
               -nostdlib                                                      \
               -z max-page-size=0x1000

ASFLAGS =      -O0                                                            \
               -f elf64
		  

QEMUFLAGS =    -bios ovmf/OVMF.fd                                             \
               -machine q35                                                   \
               -cpu max,kvm=off                                               \
               -d cpu_reset                                                   \
               -serial stdio                                                  \
               -device VGA,vgamem_mb=64                                       \
               -hda $(IMGDIR)/$(IMG)                                          \
               -m $(RAM)                                                      \
               -display sdl                                                   \
               -smp cpus=4

# testing:
QEMURUNFLAGS = -bios ovmf/OVMF.fd                                             \
               -machine q35                                                   \
               -cpu max,kvm=off                                               \
               -d cpu_reset                                                   \
               -serial stdio                                                  \
               -device VGA,vgamem_mb=64                                       \
               fat:rw:$(FSDIR)/                                               \
               -m $(RAM)                                                      \
               -display gtk                                                   \
               -D log.txt                                                     \
               -smp cpus=4 -no-reboot -no-shutdown -d int

# /dev/loop???:
LOOPDSK := 0




# START:
all : build_system
	@echo "Output: $(IMGDIR)/$(IMG)"
	@echo "make run"


# build the whole system with disk images:
build_system : dirs bootloader kernel fs img




# generate the build folder hierarchy:
dirs : build_dir bin_dir knl_dir fs_dir efi_dir_fs knl_dir_fs img_dir mnt_pnt

build_dir :
	@mkdir -p $(BUILDDIR)

bin_dir :
	@mkdir -p $(BUILDDIR)
		@mkdir -p $(BINDIR)

knl_dir :
	@mkdir -p $(BUILDDIR)
		@mkdir -p $(BINDIR)
			@mkdir -p $(KNLDIR)

fs_dir :
	@mkdir -p $(BUILDDIR)
		@mkdir -p $(FSDIR)

efi_dir_fs :
	@mkdir -p $(BUILDDIR)
		@mkdir -p $(FSDIR)
			@mkdir -p $(EFIDIR)

knl_dir_fs :
	@mkdir -p $(BUILDDIR)
		@mkdir -p $(FSDIR)
			@mkdir -p $(SYSDIR)

img_dir :
	@mkdir -p $(BUILDDIR)
		@mkdir -p $(IMGDIR)

mnt_pnt :
	@mkdir -p $(BUILDDIR)
		@mkdir -p $(MNTPNT)



# build FuzeBoot bootloader:
bootloader : compile_loader fetch_loader

compile_loader :
	\cp  -rf $(EDKCFGDIR)/* $(EDKDIR)/
	cd $(EDKDIR); bash build.sh

fetch_loader :
	mkdir -p $(LDRBINDIR)
	\cp -f $(EDKDIR)/Build/FuzeBootPkg/RELEASE_GCC5/X64/$(BOOTX64.EFI) $(LDRBINDIR)/




# build Fuze kernel:
kernel : build_dir bin_dir knl_dir compile_kernel

# compile & link kernel:
compile_kernel : $(OBJ)
	$(LD) $(LDFLAGS) $^ -o $(KNLDIR)/$(KNL)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@
%.o : %.asm
	$(AS) $(ASFLAGS) $< -o $@




# load the system into the filesystem directory in $(FSDIR):
fs : fs_dir load_bootloader load_kernel

# load the bootloader into the filesystem:
load_bootloader : efi_dir_fs
	\cp -f $(BOOTSRCDIR)/$(BUILDDIR)/$(BOOTX64.EFI) $(EFIDIR)/ 2> /dev/null || :

# load the kernel into the filesystem:
load_kernel : knl_dir knl_dir_fs
	\cp -f $(KNLDIR)/$(KNL) $(SYSDIR) 2> /dev/null || :




# generate disk image from $(FSDIR):
img : gen_img fmt_img mount_img load_img umount_img

gen_img : img_dir
	dd if=/dev/zero of=$(IMGDIR)/$(IMG) bs=1M count=$(IMGMB) oflag=sync

fmt_img : gen_img
	@echo "sudo losetup -fP $(IMGDIR)/$(IMG)"
	$(eval LOOPDSK=$(shell sudo losetup --show -fP $(IMGDIR)/$(IMG)))

	sudo parted -s $(IMGDIR)/$(IMG) mktable gpt
	sudo parted -s $(LOOPDSK) mkpart OS 1MiB 100%
	sudo parted -s $(LOOPDSK) set 1 esp on

	sudo mkfs.fat -F 32 $(LOOPDSK)p1

mount_img : mnt_pnt
	sudo mount $(LOOPDSK)p1 -t msdos -o umask=0000 $(MNTPNT)

load_img : mount_img
	\cp -rf $(FSDIR)/* $(MNTPNT)

umount_img :
	sudo umount $(MNTPNT)
	sudo losetup -d $(LOOPDSK)




# TESTING:

# build both bootloader and kernel into $(FSDIR) without generating disk images:
testbuildall : dirs bootloader kernel fs

# build bootloader only:
testbuildboot       : testbuildloader
testbuildloader     : testbuildbootloader
testbuildbootloader : bootloader fs

# build kernel only:
testbuild : testbuildkernel
testbuildkernel : kernel fs


# CI/CD:
ci	   : ci_ldr ci_knl
ci_knl : kernel
ci_ldr : compile_loader


# TEST-RUNNING:
# run the system from $(FSDIR) with the disk in R/W mode:
testrun :
	@clear
	$(QEMU) $(QEMURUNFLAGS)




# RUNNING:
run :
	@clear
	$(QEMU) $(QEMUFLAGS)



# EDK2: https://github.com/tianocore/edk2
edk : init_edk
init_edk : edk2
edk2 : init_edk2
init_edk2 :
	rm -rf $(EDKDIR)
	@mkdir -p $(EDKDIR)

	git clone --depth=1 --branch $(EDKBRANCH) https://github.com/tianocore/edk2.git edk2
	git -C ./$(EDKDIR)/ submodule update --init --recursive --progress


delete_edk2 :
	rm -rf $(EDKDIR)




# clean:
clean :
	rm -rf $(BUILDDIR)
	rm -rf $(shell find ./ -type d \( -path ./edk2 \) -prune -false -o -name '*.o')
	rm -rf edk2/Build/
	rm -rf log.txt

clean_ci :
	rm -rf $(BUILDDIR)
	rm -rf $(shell find ./ -type d \( -path ./edk2 \) -prune -false -o -name '*.o')
	rm -rf $(EDKDIR)/Build/FuzeBootPkg/RELEASE_GCC5/X64/$(BOOTX64.EFI)

clean_ci_knl :
	rm -rf $(BUILDDIR)
	rm -rf $(shell find ./ -type d \( -path ./edk2 \) -prune -false -o -name '*.o')

clean_ci_ldr :
	rm -rf $(EDKDIR)/Build/FuzeBootPkg/RELEASE_GCC5/X64/$(BOOTX64.EFI)
