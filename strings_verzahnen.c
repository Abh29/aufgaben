#include "strings_verzahnen.h"

void	strings_verzahnen(char *verzahnt, char *string0, char *string1)
{
	if (verzahnt == NULL)
		return ;
	while (*string0 && *string1)
	{
		*verzahnt++ = *string0++;
		*verzahnt++ = *string1++;
	}
	if (*string0 || *string1)
	{
		if (*string1)
			string0 = string1;
		while (*string0)
			*verzahnt++ = *string0++;
	}
	*verzahnt = 0;
	return ;
}
