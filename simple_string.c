#include "simple_string.h"
#include <stddef.h>

int count_chars(char *string)
{
    int count;
	if (string == NULL)
		return (-1);
	count = 0;
    while (*string++)
		count++;
    return count;
}

int find_char(char *text, char c)
{
   int i;

	if (text == NULL)
		return (-1);
	i = 0;
	while (*text)
	{
		if (*text == c)
			return (i);
		i++;
		text++;
	}

    return (-1);
}
