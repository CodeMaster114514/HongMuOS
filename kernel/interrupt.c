#include "common.h"

typedef struct interrupt_frame interrupt_frame;

__attribute__((interrupt))
void DE(interrupt_frame *frame, unsigned long long error_code)
{
	print("Error Code: %d\n", error_code);
	print("You Can't use 0 to be a divisor\n");
}

void InitInterrupt()
{
	IDTR *idtr = alloc_os_data(sizeof(IDTR));
	get_idtr(idtr);
	asm(
		"cli"
	);
	idtr->idt[0].offset_low = (unsigned short)((unsigned long long)DE & 0x000000000000ffff);
	idtr->idt[0].offset_high_1 = (unsigned int)((unsigned long long)DE & 0x00000000ffff0000);
	idtr->idt[0].offset_high_2 = (unsigned int)((unsigned long long)DE & 0xffffffff00000000);
	asm(
		"mov ax, cs\n\t"
		"mov %0, ax\n\t"
		:"=m"(idtr->idt[0].SS)
	);
	idtr->idt[0].TF = 0b10001111;
	asm(
		"mov rbx, %0\n\t"
		"lidt [rbx]\n\t"
		"sti\n\t"
		:"=m"(idtr)
	);

	int b = 0;

	int a = 5 / b;
}