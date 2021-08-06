#include "troutspeak.h"

static int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 == *s2 ? 1 : 0);
}

static int	to_upper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}

static int	to_lower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}

static int	count_chars(char *string)
{
    int count;
	if (string == NULL)
		return (-1);
	count = 0;
    while (*string++)
		count++;
    return count;
}

static char	*ft_strdup(char *str)
{
	char	*out;
	char	*save;

	if (str == NULL)
		return (NULL);
	out = malloc(count_chars(str) + 1);
	if (out == NULL)
		return (NULL);
	save = out;
	while (*str)
		*save++ = *str++;
	return (out);
}

void	troutspeak(char *string)
{
	int i;

	if (string == NULL)
		return ;
	i = 0;
	while (*string)
	{
		if (i++ % 3 == 0)
			*string = to_upper(*string);
		else
			*string = to_lower(*string);
		string++;
	}
}

int		compare(char *string, char *string_troutspeak)
{
	char	*str;
	int		out;

	if (string == NULL || string_troutspeak == NULL)
		return (0);
	str = ft_strdup(string);
	troutspeak(str);
	out = ft_strcmp(str, string_troutspeak);
	free(str);
	str = NULL;
	return (out);
}
