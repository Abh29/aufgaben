#include <stddef.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdio.h>

#define STDOUT_FILENO 1
#define STDERR_FILENO 2

typedef struct s_data
{
	char	*txt;
	int		g;
	int		w;
	int		repeat;
	int		h;

}				t_data;



/**********************utils**************************/

int		ft_strlen(char *str)
{
	int i;

	if (str == NULL)
		return (-1);
	i = 0;
	while (*str && i++ > -1)
		str++;
	return (i);
}

void	ft_putstr(char *str)
{
	if (str == NULL)
		return ;
	fwrite(str, ft_strlen(str), 1, stdout);
}

void 	ft_exit(char *msg)
{
	ft_putstr(msg);
	exit(1);
}

int		ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}

void	ft_upperstr(char *str)
{
	if (str == NULL)
		return ;
	while (*str && (*str = ft_toupper(*str)))
		str++;
	return ;
}

int		ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

int		ft_isnumber(char *str)
{
	if (str == NULL)
		return (0);
	if (*str == '-' || *str == '+')
		str++;
	while (*str && ft_isdigit(*str))
		str++;
	return (*str == 0);
}

int		ft_strcmp(char *s1, char *s2)
{
	if (s1 == NULL || s2 == NULL)
		return (0);
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 == *s2);
}

int		ft_strtonum(char *str)
{
	int		out;
	int 	sign;

	if (!str || !ft_isnumber(str))
		return (0);
	sign = 1;
	out = 0;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str)
		out = out * 10 + *str++ - '0';
	return (out * sign);
}

/******************************************************/

void	ft_init(t_data *data)
{
	data->txt = NULL;
	data->g = 0;
	data->h = 0;
	data->repeat = 0;
	data->w = 0;
}

void 	ft_showHelpMsg()
{
	char *msg;

	msg = "Hilfe :\n\t-w <num> show the text num times\n\
	-h output this message \n\
	-g output the text with all capital letters \n\n";
	fwrite(msg, ft_strlen(msg), 1, stdout);
	exit (0);
}

void	ft_getdata(int argc, char **argv, t_data *data)
{
	int i;

	i = 1;
	argv++;
	while (i++ < argc)
	{
		if (ft_strcmp(*argv, "-g"))
			data->g = 1;
		else if (ft_strcmp(*argv, "-h"))
			data->h = 1;
		else if (ft_strcmp(*argv, "-w"))
		{
			if (i == argc)
				ft_exit("Fehler : unsuficient arguments for -w !");
			argv++;
			if (!ft_isnumber(*argv))
				ft_exit("Fehler : expected a number after -w !");
			data->w = 1;
			data->repeat = ft_strtonum(*argv);
			if (data->repeat < 1)
				ft_exit("Fehler : expected a positive integer after -w !");
			i++;
		}
		else if (data->txt)
			ft_exit("Fehler : more than one text !");
		else
			data->txt = *argv;
		if (data->txt && *(data->txt) == '-')
			ft_exit("Fehler : undefined option! ");
		argv++;
	}
}

void	ft_putdata(t_data *data)
{
	int rep;

	rep = 1;
	if (data == NULL)
		ft_exit("Error : unexpected error occured !");
	if (data->h)
		ft_showHelpMsg();
	if (data->g)
		ft_upperstr(data->txt);
	if (data->w)
		rep = data->repeat;
	while (rep--)
		ft_putstr(data->txt);
}

int main(int argc, char **argv)
{
	t_data data;

	if (argc < 2)
		ft_exit("Fehler : expected more arguments !");
	if (argc > 6)
		ft_exit("Fehler : too many arguments !");
	ft_init(&data);
	ft_getdata(argc, argv, &data);
	ft_putdata(&data);
	ft_putstr("\n");
	return 0;
}
