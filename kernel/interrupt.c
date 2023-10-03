#include "common.h"

IDTR *idtr = 0;

void InitInterrupt()
{
	IDTR *idtr_init = alloc_os_data(sizeof(IDTR));
	get_idtr(idtr_init);
	idtr = idtr_init;
}

void AddAInterruptAt(void *offset, short SS, char ist, char TF, char at)
{
	closeInterrupt();

	idtr->idt[at].offset_low = (unsigned short)((unsigned long long)offset & 0x000000000000ffff);
	idtr->idt[at].offset_high_1 = (unsigned short)(((unsigned long long)offset & 0x00000000ffff0000) >> 16);
	idtr->idt[at].offset_high_2 = (unsigned int)(((unsigned long long)offset & 0xffffffff00000000) >> 32);
	idtr->idt[at].SS = SS;
	idtr->idt[at].TF = TF;
	idtr->idt[at].ist = ist;
	idtr->idt[at].reserved = 0;

	set_idtr(idtr);

	openInterrupt();
}