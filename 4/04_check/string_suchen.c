#include <string.h>
#include <stdio.h>

int string_suchen(char *text, char *string)
{
	int		i;
	char	*s1;
	char	*s2;

	if (text == NULL || string == NULL)
		return (-1);
	if (strlen(string) == 0)
		return (0);
	i = 0;
    // Iteriere über text.
	while (*text)
	{
		s1 = text;
		s2 = string;
		while (*s2 && *s2 == *s1)
		{
			s1++;
			s2++;
		}
		if (*s2 == '\0')
			return (i);
		i++;
		text++;
	}
    // Kein Treffer gefunden, -1 zurückgeben
    return -1;
}
