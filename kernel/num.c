#include "common.h"

char num_str[21] = {0};

char *number_to_string(unsigned long long num)
{
	for (int i = 0;i < 21;++i)
	{
		num_str[i] = 0;
	}
	char str[20];
	int len = 0;
	for (int i = 0;i < 19;++i)
	{
		str[i] = (num % 10) + 0x30;
		num = num / 10;
		++len;
		if (!num)
		{
			break;
		}
	}
	for (int i = 0;i < len;++i)
	{
		num_str[i] = str[len - i - 1];
	}
	return num_str;
}

char *number_to_hex_string(unsigned long long num)
{
	for (int i = 0;i < 21;++i)
	{
		num_str[i] = 0;
	}
	char str[20];
	int len = 0;
	for (int i = 0;i < 19;++i)
	{
		str[i] = num & 0xf;
		if (str[i] >= 0 && str[i] <= 9)
		{
			str[i] += 0x30;
		}
		else if (str[i] > 9 && str[i] < 16)
		{
			str[i] += 0x37;
		}
		num >>= 4;
		++len;
		if (!num)
		{
			break;
		}
	}
	for (int i = 0;i < len;++i)
	{
		num_str[i] = str[len - i -1];
	}
	return num_str;
}