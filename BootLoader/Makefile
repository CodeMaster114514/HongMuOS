OUT_DIR = ./Boot
OBJ = $(OUT_DIR)/main.o $(OUT_DIR)/enter.o $(OUT_DIR)/infomation.o $(OUT_DIR)/Protocol.o $(OUT_DIR)/GUI.o $(OUT_DIR)/File.o

all: $(OUT_DIR)/main.so
	objcopy                     \
		-j .text                \
		-j .sdata               \
		-j .data                \
		-j .dynamic             \
		-j .dynsym              \
		-j .rel                 \
		-j .rela                \
		-j .reloc               \
		--target=efi-app-x86_64 \
		$(OUT_DIR)/main.so      \
		BootX64.efi

$(OUT_DIR)/main.so: $(OBJ)
	ld $(OBJ)                          \
		/usr/lib/crt0-efi-x86_64.o     \
		-nostdlib                      \
		-znocombreloc                  \
		-T /usr/lib/elf_x86_64_efi.lds \
		-shared                        \
		-Bsymbolic                     \
		-L /usr/lib                    \
		-l:libgnuefi.a                 \
		-l:libefi.a                    \
		-g                             \
		-o $(OUT_DIR)/main.so

$(OUT_DIR)/main.o: $(SRC)/main.c
	gcc $(SRC)/main.c                      \
		-c                                 \
		-fno-stack-protector               \
		-fpic                              \
		-fshort-wchar                      \
		-mno-red-zone                      \
		-DEFI_FUNCTION_WRAPPER             \
		-maccumulate-outgoing-args         \
		-g                                 \
		-o $(OUT_DIR)/main.o

$(OUT_DIR)/enter.o: $(SRC)/enter.c
	gcc $(SRC)/enter.c                     \
		-c                                 \
		-fno-stack-protector               \
		-fpic                              \
		-fshort-wchar                      \
		-mno-red-zone                      \
		-DEFI_FUNCTION_WRAPPER             \
		-maccumulate-outgoing-args         \
		-g                                 \
		-o $(OUT_DIR)/enter.o

$(OUT_DIR)/infomation.o: $(SRC)/infomation.c
	gcc $(SRC)/infomation.c                \
		-c                                 \
		-fno-stack-protector               \
		-fpic                              \
		-fshort-wchar                      \
		-mno-red-zone                      \
		-DEFI_FUNCTION_WRAPPER             \
		-maccumulate-outgoing-args         \
		-g                                 \
		-o $(OUT_DIR)/infomation.o

$(OUT_DIR)/Protocol.o: $(SRC)/Protocol.c
	gcc $(SRC)/Protocol.c                  \
		-c                                 \
		-fno-stack-protector               \
		-fpic                              \
		-fshort-wchar                      \
		-mno-red-zone                      \
		-DEFI_FUNCTION_WRAPPER             \
		-maccumulate-outgoing-args         \
		-g                                 \
		-o $(OUT_DIR)/Protocol.o

$(OUT_DIR)/GUI.o: $(SRC)/GUI.c
	gcc $(SRC)/GUI.c                       \
		-c                                 \
		-fno-stack-protector               \
		-fpic                              \
		-fshort-wchar                      \
		-mno-red-zone                      \
		-DEFI_FUNCTION_WRAPPER             \
		-maccumulate-outgoing-args         \
		-g                                 \
		-o $(OUT_DIR)/GUI.o

$(OUT_DIR)/File.o: $(SRC)/File.c
	gcc $(SRC)/File.c                      \
		-c                                 \
		-fno-stack-protector               \
		-fpic                              \
		-fshort-wchar                      \
		-mno-red-zone                      \
		-DEFI_FUNCTION_WRAPPER             \
		-maccumulate-outgoing-args         \
		-g                                 \
		-o $(OUT_DIR)/File.o

clean:
	rm -rf $(OUT_DIR)/*.o $(OUT_DIR)/*.so
	rm BootX64.efi