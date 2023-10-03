#include "common.h"

int kernel(Table *table)
{
	init_vdieo(&table->vdieo);
	init_shell();

	print("Welcome to HongMuOS\n");

	InitMemory(&table->map);
	print("Total memory: %dMiB\n", GetTotalMemory() / 1024 / 1024);
	print("Total free memory: %dMiB\n", GetTotalFreeMemory() / 1024 / 1024);

	InitInterrupt();
	InitKeyboard();

	for (;;)
	{
		asm("hlt\n");
	}
}