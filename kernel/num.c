#include "common.h"

char num_str[21] = {0};

char *number_to_string(int num)
{
	char str[20] = {0};
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