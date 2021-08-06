#include "strings_finden.h"

int strings_finden(char zahlen[50][40], char *text)
{
	int w;
	int i;

	if (zahlen == NULL || text == NULL)
		return (-1);
	w = 0;
	while (*text && w < 50)
	{
		if (*text++ == '\"')
		{
			i = 0;
			while (*text && *text != '\"' && i < 39)
				zahlen[w][i++] = *text++;
			zahlen[w][i] = 0;
			w++;
			if (*text)
				text++;
		}
	}
	return (w);
}
