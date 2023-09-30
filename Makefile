EFI_BUILD= build
COMPILER= x86_64-linux-gnu-gcc
ARCHITECTURE= X64
INCLUDE= -I./
MOD= -e kernel -nostdlib -no-pie -m64 -masm=intel
OUT_DIR= Build
OBJ= $(OUT_DIR)/vdieo.o $(OUT_DIR)/shell.o $(OUT_DIR)/asciidata.o $(OUT_DIR)/cursor.o $(OUT_DIR)/print.o $(OUT_DIR)/num.o $(OUT_DIR)/memory.o $(OUT_DIR)/io.o

all: Build/DEBUG_GCC5/$(ARCHITECTURE)/HongMuOSLoader.efi Build/kernel

Build/DEBUG_GCC5/$(ARCHITECTURE)/HongMuOSLoader.efi:BootLoader/main.c BootLoader/GUI.c BootLoader/Protocol.c BootLoader/IO.c BootLoader/infomation.c BootLoader/enter.c BootLoader/File.c
	$(EFI_BUILD) -p HongMuOS/HongMuOSLoader.dsc

$(OUT_DIR)/kernel: kernel/main.c common.h $(OBJ)
	$(COMPILER) $(INCLUDE) kernel/main.c $(OBJ) $(MOD) -o Build/kernel

$(OUT_DIR)/vdieo.o: kernel/io/vdieo.c common.h
	$(COMPILER) $(INCLUDE) kernel/io/vdieo.c $(MOD) -c -o Build/vdieo.o

$(OUT_DIR)/shell.o: kernel/shell.c common.h
	$(COMPILER) $(INCLUDE) kernel/shell.c $(MOD) -c -o Build/shell.o

$(OUT_DIR)/asciidata.o: kernel/asciidata.asm
	nasm -f elf64 kernel/asciidata.asm -o Build/asciidata.o

$(OUT_DIR)/cursor.o: kernel/cursor.c common.h
	$(COMPILER) $(INCLUDE) kernel/cursor.c $(MOD) -c -o Build/cursor.o

$(OUT_DIR)/print.o: kernel/io/print.c common.h
	$(COMPILER) $(INCLUDE) kernel/io/print.c $(MOD) -Wint-conversion -c -o Build/print.o

$(OUT_DIR)/num.o: kernel/num.c common.h
	$(COMPILER) $(INCLUDE) kernel/num.c $(MOD) -Wint-conversion -c -o Build/num.o

$(OUT_DIR)/memory.o: kernel/memory.c common.h
	$(COMPILER) $(INCLUDE) kernel/memory.c $(MOD) -c -o Build/memory.o

$(OUT_DIR)/io.o: kernel/io/io.c common.h
	$(COMPILER) $(INCLUDE) kernel/io/io.c $(MOD) -c -o Build/io.o

clean:
	rm Build/kernel $(OBJ) -rf
