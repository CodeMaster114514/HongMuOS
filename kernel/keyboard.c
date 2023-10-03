#include "common.h"

void Init8259A()
{
	// 设置主8259A，有联级，中断号为0X20，从片在IR2，X86模式
	io_out8(0x20, 0x11);
	io_out8(0x21, 0x20);
	io_out8(0x21, 0x04);
	io_out8(0x21, 0x02);
	io_out8(0x21, 0b11111101);

	// 设置从8259A，有联级，连接主片IR2，中断号为0x28，X86模式
	io_out8(0xa0, 0x11);
	io_out8(0xa1, 0x28);
	io_out8(0xa1, 0x02);
	io_out8(0xa1, 0x02);
	io_out8(0xa1, 0xff);
}

char shift = 0, capslock = 0, number = 0;

__attribute__((interrupt))
void IntKeyboard(interrupt_frame *frame)
{
	unsigned char code = io_in8(0x60);
	char out;
	char CanShow = 0;
	switch (code)
	{
	case 0x1:// esc
		break;
	case 0x2:
		out = shift ? '!' : '1';
		CanShow = -1;
		break;
	case 0x3:
		out = shift ? '@' : '2';
		CanShow = -1;
		break;
	case 0x4:
		out = shift ? '#' : '3';
		CanShow = -1;
		break;
	case 0x5:
		out = shift ? '$' : '4';
		CanShow = -1;
		break;
	case 0x6:
		out = shift ? '%' : '5';
		CanShow = -1;
		break;
	case 0x7:
		out = shift ? '^' : '6';
		CanShow = -1;
		break;
	case 0x8:
		out = shift ? '&' : '7';
		CanShow = -1;
		break;
	case 0x9:
		out = shift ? '*' : '8';
		CanShow = -1;
		break;
	case 0xa:
		out = shift ? '(' : '9';
		CanShow = -1;
		break;
	case 0xb:
		out = shift ? ')' : '0';
		CanShow = -1;
		break;
	case 0xc:
		out = shift ? '_' : '-';
		out = -1;
		break;
	case 0xd:
		out = shift ? '+' : '=';
		CanShow = -1;
		break;
	case 0xe:
		cursor_back();
		break;
	case 0xf:
		out = '\t';
		CanShow = -1;
		break;
	case 0x10:
		out = shift ? 'Q' : 'q';
		CanShow = -1;
		break;
	case 0x11:
		out = shift ? 'W' : 'w';
		CanShow = -1;
		break;
	case 0x12:
		out = shift ? 'E' : 'e';
		CanShow = -1;
		break;
	case 0x13:
		out = shift ? 'R' : 'r';
		CanShow = -1;
		break;
	case 0x14:
		out = shift ? 'T' : 't';
		CanShow = -1;
		break;
	case 0x15:
		out = shift ? 'Y' : 'y';
		CanShow = -1;
		break;
	case 0x16:
		out = shift ? 'U' : 'u';
		CanShow = -1;
		break;
	case 0x17:
		out = shift ? 'I' : 'i';
		CanShow = -1;
		break;
	case 0x18:
		out = shift ? 'O' : 'o';
		CanShow = -1;
		break;
	case 0x19:
		out = shift ? 'P' : 'p';
		CanShow = -1;
		break;
	case 0x1a:
		out = shift ? '{' : '[';
		CanShow = -1;
		break;
	case 0x1b:
		out = shift ? '}' : ']';
		CanShow = -1;
		break;
	case 0x1c:
		out = '\n';
		CanShow = -1;
		break;
	case 0x1d:// left control
		break;
	case 0x1e:
		out = shift ? 'A' : 'a';
		CanShow = -1;
		break;
	case 0x1f:
		out = shift ? 'S' : 's';
		CanShow = -1;
		break;
	case 0x20:
		out = shift ? 'D' : 'd';
		CanShow = -1;
		break;
	case 0x21:
		out = shift ? 'F' : 'f';
		CanShow = -1;
		break;
	case 0x22:
		out = shift ? 'G' : 'g';
		CanShow = -1;
		break;
	case 0x23:
		out = shift ? 'H' : 'h';
		CanShow = -1;
		break;
	case 0x24:
		out = shift ? 'J' : 'j';
		CanShow = -1;
		break;
	case 0x25:
		out = shift ? 'K' : 'k';
		CanShow = -1;
		break;
	case 0x26:
		out = shift ? 'L' : 'l';
		CanShow = -1;
		break;
	case 0x27:
		out = shift ? ':' : ';';
		CanShow = -1;
		break;
	case 0x28:
		out = shift ? '"' : '\'';
		CanShow = -1;
		break;
	case 0x29:
		out = shift ? '~' : '`';
		CanShow = -1;
		break;
	case 0x2a:
	case 0x36:
		shift = -1;
		break;
	case 0x2b:
		out = shift ? '|' : '\\';
		CanShow = -1;
		break;
	case 0x2c:
		out = shift ? 'Z' : 'z';
		CanShow = -1;
		break;
	case 0x2d:
		out = shift ? 'X' : 'x';
		CanShow = -1;
		break;
	case 0x2e:
		out = shift ? 'C' : 'c';
		CanShow = -1;
		break;
	case 0x2f:
		out = shift ? 'V' : 'v';
		CanShow = -1;
		break;
	case 0x30:
		out = shift ? 'B' : 'b';
		CanShow = -1;
		break;
	case 0x31:
		out = shift ? 'N' : 'n';
		CanShow = -1;
		break;
	case 0x32:
		out = shift ? 'M' : 'm';
		CanShow = -1;
		break;
	case 0x33:
		out = shift ? '<' : ',';
		CanShow = -1;
		break;
	case 0x34:
		out = shift ? '>' : '.';
		CanShow = -1;
		break;
	case 0x35:
		out = shift ? '?' : '/';
		CanShow = -1;
		break;
	case 0x37:// at keypad 
		break;
	case 0x38://left alt
		break;
	case 0x39:
		out = ' ';
		CanShow = -1;
		break;
	case 0x3a:// Capslock
		capslock = !capslock;
		char set = 0;
		if (capslock)
		{
			set |= 0b00000100;
		}
		if (number)
		{
			set |= 0b00001000;
		}
		io_out8(0x60, 0xed);
		io_out8(0x60, set);
		io_out8(0x60, 0xff);
		io_out8(0x60, 0xf4);
		io_out8(0x64, 0xae);
		break;
	case 0xaa:
	case 0xb6:
		shift = 0;
		break;
	}
	if (CanShow)
	{
		put_char(out);
	}
	openInterrupt();
}

void InitKeyboard()
{
	AddAInterruptAt((void *)IntKeyboard, get_cs() & 0xfff8, 0, 0b10001110, 0x21);
	Init8259A();
}