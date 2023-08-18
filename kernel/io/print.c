#include "common.h"
#include <stdarg.h>

int print(const char *str, ...)
{
	va_list list;
	int i = 0;

	va_start(list, str);

	char c = str[i];
	while (c != '\0')
	{
		if (c == '%')
		{
			c = str[++i];
			switch (c)
			{
			case 'd':
				c = str[++i];
				int num = va_arg(list, int);
				char *num_str = number_to_string(num);
				put_string(num_str);
				break;
			}
		}
		put_char(c);
		c = str[++i];
	}

	va_end(list);
	return i;
}