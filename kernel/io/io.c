#include "common.h"

unsigned char io_in8(short port)
{
	unsigned char data;
	__asm__(
		"mov dx, %1\n\t"
		"in al, dx\n\t"
		"mov %0, al\n\t"
		:"=m"(data)
		:"m"(port)
	);
	return data;
}

unsigned short io_in16(short port)
{
	unsigned short data;
	__asm__(
		"mov dx, %1\n\t"
		"in ax, dx\n\t"
		"mov %0, ax\n\t"
		:"=m"(data)
		:"m"(port)
	);
	return data;
}

unsigned int io_in32(short port)
{
	unsigned int data;
	asm(
		"mov dx, %1\n\t"
		"in eax, dx\n\t"
		"mov %0, eax\n\t"
		:"=m"(data)
		:"m"(port)
	);
	return data;
}

void io_out8(short port, unsigned char data)
{
	asm(
		"mov al, %0\n\t"
		"mov dx, %1\n\t"
		"out dx, al\n\t"
		:
		:"m"(data), "m"(port)
	);
}

void io_out16(short port, unsigned short data)
{
	asm(
		"mov ax, %0\n\t"
		"mov dx, %1\n\t"
		"out dx, ax\n\t"
		:
		:"m"(data), "m"(port)
	);
}

void io_out32(short port, unsigned int data)
{
	asm(
		"mov eax, %0\n\t"
		"mov dx, %1\n\t"
		"out dx, eax\n\t"
		:
		:"m"(data), "m"(port)
	);
}

unsigned long long get_cr3()
{
	unsigned long long data;
	asm(
		"mov rax, cr3\n\t"
		"mov %0, rax"
		:"=m"(data)
	);
	return data;
}

void get_gdtr(GDTR *gdtr)
{
	asm(
		"mov rbx, %0\n\t"
		"sgdt [rbx]\n\t"
		:"=m"(gdtr)
	);
}

void get_idtr(IDTR *idtr)
{
	asm(
		"mov rbx, %0\n\t"
		"sidt [rbx]\n\t"
		:"=m"(idtr)
	);
}
