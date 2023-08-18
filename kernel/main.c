#include "common.h"

int kernel(Table *table)
{
	init_vdieo(&table->vdieo);
	init_shell();

	print("Welcome to HongMuOS\n");
	print("%d\n", table->vdieo.hight);

	for (;;)
	{}
}