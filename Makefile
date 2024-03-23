COMPILER= x86_64-linux-gnu-gcc
ARCHITECTURE= X64
MAKEFILE_PATH :=$(abspath $(lastword $(MAKEFILE_LIST)))
PWD :=$(subst /Makefile,,$(MAKEFILE_PATH))
OUT_DIR :=$(PWD)/Build
INCLUDE= $(PWD)/inc
EFI_BUILD :=build

all: Build/DEBUG_GCC5/$(ARCHITECTURE)/HongMuOSLoader.efi Build/kernel

Build/DEBUG_GCC5/$(ARCHITECTURE)/HongMuOSLoader.efi:BootLoader/main.c BootLoader/GUI.c BootLoader/Protocol.c BootLoader/infomation.c BootLoader/enter.c BootLoader/File.c
		$(EFI_BUILD) -p HongMuOS/HongMuOSLoader.dsc

Build/BootX64.efi:BootLoader/main.c BootLoader/GUI.c BootLoader/Protocol.c BootLoader/infomation.c BootLoader/enter.c BootLoader/File.c

	make -f $(PWD)/BootLoader/Makefile -C Build ARCHITECTURE=$(ARCHITECTURE) SRC=$(PWD)/BootLoader

Build/kernel:
	make -f $(PWD)/kernel/Makefile -C Build ARCHITECTURE=$(ARCHITECTURE) SRC=$(PWD)/kernel COMPILER=$(COMPILER) INCLUDE=$(INCLUDE)

clean:
	make -f $(PWD)/BootLoader/Makefile -C Build ARCHITECTURE=$(ARCHITECTURE) SRC=$(PWD)/BootLoader clean
	make -f $(PWD)/kernel/Makefile -C Build ARCHITECTURE=$(ARCHITECTURE) SRC=$(PWD)/kernel COMPILER=$(COMPILER) clean
