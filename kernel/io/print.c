#include "common.h"
#include <stdarg.h>

#define X64 1

#if X64
#define POINTER_TO_NUM(p) (unsigned long long)(p)
#endif
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
			char *num_str;
			int num = 0;
			unsigned long long llnum = 0;
			switch (c)
			{
			case 'd':
				c = str[++i];
				num = va_arg(list, int);
				num_str = number_to_string(num);
				put_string(num_str);
				break;
			case 'x':
				c = str[++i];
				num = va_arg(list, int);
				num_str = number_to_hex_string(num);
				put_string(num_str);
				break;
			case 'p':
				c = str[++i];
				void *p = va_arg(list, void *);
				num_str = number_to_hex_string(POINTER_TO_NUM(p));
				put_string(num_str);
				break;

			default:
				if (str[i++] == 'l' && str[i++] == 'l' && str[i++] == 'd')
				{
					llnum = va_arg(list, unsigned long long);
					num_str = number_to_string(llnum);
					put_string(num_str);
					c = str[i];
				}
				break;
			}
		}
		put_char(c);
		c = str[++i];
	}

	va_end(list);
	return i;
}