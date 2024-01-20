MOD= -e kernel -nostdlib -no-pie -m64 -masm=intel
INC= -I$(INCLUDE)/
OBJ= vdieo.o shell.o asciidata.o cursor.o print.o num.o memory.o io.o interrupt.o keyboard.o

kernel: $(SRC)/main.c $(INCLUDE)/common.h $(OBJ)
	$(COMPILER) $(INC) $(SRC)/main.c $(OBJ) $(MOD) -o kernel

vdieo.o: $(SRC)/io/vdieo.c $(INCLUDE)/common.h
	$(COMPILER) $(INC) $(SRC)/io/vdieo.c $(MOD) -c -o vdieo.o

shell.o: $(SRC)/shell.c $(INCLUDE)/common.h
	$(COMPILER) $(INC) $(SRC)/shell.c $(MOD) -c -o shell.o

asciidata.o: $(SRC)/asciidata.asm
	nasm -f elf64 $(SRC)/asciidata.asm -o asciidata.o

cursor.o: $(SRC)/cursor.c $(INCLUDE)/common.h
	$(COMPILER) $(INC) $(SRC)/cursor.c $(MOD) -c -o cursor.o

print.o: $(SRC)/io/print.c $(INCLUDE)/common.h
	$(COMPILER) $(INC) $(SRC)/io/print.c $(MOD) -Wint-conversion -c -o print.o

num.o: $(SRC)/num.c $(INCLUDE)/common.h
	$(COMPILER) $(INC) $(SRC)/num.c $(MOD) -Wint-conversion -c -o num.o

memory.o: $(SRC)/memory.c $(INCLUDE)/common.h
	$(COMPILER) $(INC) $(SRC)/memory.c $(MOD) -c -o memory.o

io.o: $(SRC)/io/io.c $(INCLUDE)/common.h
	$(COMPILER) $(INC) $(SRC)/io/io.c $(MOD) -c -o io.o

interrupt.o: $(SRC)/interrupt.c $(INCLUDE)/common.h
	$(COMPILER) $(INC) $(SRC)/interrupt.c $(MOD) -mgeneral-regs-only -c -o interrupt.o

keyboard.o: $(SRC)/keyboard.c $(INCLUDE)/common.h
	$(COMPILER) $(INC) $(SRC)/keyboard.c $(MOD) -mgeneral-regs-only -c -o keyboard.o

clean:
	rm $(OBJ) -rf
	rm kernel