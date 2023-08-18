EFI_BUILD= build
COMPILER= gcc
ARCHITECTURE= X64
INCLUDE= -I./
MOD= -e kernel -nostdlib -no-pie -m64
OUT_DIR= Build
OBJ= $(OUT_DIR)/vdieo.o $(OUT_DIR)/shell.o $(OUT_DIR)/asciidata.o $(OUT_DIR)/cursor.o $(OUT_DIR)/print.o $(OUT_DIR)/num.o

all: Build/DEBUG_GCC5/$(ARCHITECTURE)/HongMuOSLoader.efi Build/kernel

Build/DEBUG_GCC5/$(ARCHITECTURE)/HongMuOSLoader.efi:BootLoader/main.c BootLoader/GUI.c BootLoader/Protocol.c BootLoader/IO.c BootLoader/infomation.c BootLoader/enter.c BootLoader/File.c
	$(EFI_BUILD) -p HongMuOS/HongMuOSLoader.dsc

$(OUT_DIR)/kernel: kernel/main.c common.h $(OBJ)
	gcc $(INCLUDE) kernel/main.c $(OBJ) $(MOD) -o Build/kernel

$(OUT_DIR)/vdieo.o: kernel/io/vdieo.c common.h
	gcc $(INCLUDE) kernel/io/vdieo.c $(MOD) -c -o Build/vdieo.o

$(OUT_DIR)/shell.o: kernel/shell.c common.h
	gcc $(INCLUDE) kernel/shell.c $(MOD) -c -o Build/shell.o

$(OUT_DIR)/asciidata.o: kernel/asciidata.asm
	nasm -f elf64 kernel/asciidata.asm -o Build/asciidata.o

$(OUT_DIR)/cursor.o: kernel/cursor.c common.h
	gcc $(INCLUDE) kernel/cursor.c $(MOD) -c -o Build/cursor.o

$(OUT_DIR)/print.o: kernel/io/print.c common.h
	gcc $(INCLUDE) kernel/io/print.c $(MOD) -c -o Build/print.o

$(OUT_DIR)/num.o: kernel/num.c common.h
	gcc $(INCLUDE) kernel/num.c $(MOD) -c -o Build/num.o

clean:
	rm Build/kernel $(OBJ) -rf
