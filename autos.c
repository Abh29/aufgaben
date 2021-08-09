#include <stddef.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

#define STDOUT_FILENO 1
#define STDERR_FILENO 2

typedef struct s_auto
{
	char	*type;
	int		year;
	int 	km;
}				t_auto;

typedef struct s_data
{
	int		k;
	int		km;
	int		j;
	int		year;
	int		b;
	char	*model;
	char	*file1;
	char	*file2;
	int		fd1;
	int		fd2;
}				t_data;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;



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

void    ft_putstr_fd(char *s, int fd)
{
    if (s == NULL)
        return ;
    write (fd, s, ft_strlen(s));
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

int		ft_wordcount(char const *s, char c)
{
    int count;

    count = 0;
    while (*s)
    {
        while (*s && *s == c)
            s++;
        if (*s)
        {
            count++;
            s++;
        }
        while (*s && *s != c)
            s++;
    }
    return (count);
}

char	**ft_split(char const *s, char c)
{
    char    **out;
	int		i;
    int		w;

    if (s == NULL)
        return (NULL);
    out = malloc(sizeof(char *) * (ft_wordcount(s, c) + 1));
    if (out == NULL)
        return (NULL);
	w = 0;
    while (*s)
    {
        while (*s && *s == c)
            s++;
        if (*s)
        {
            i = 0;
            while (*s && *s != c && i++ > -1)
                s++;
            out[w] = malloc(i + 1);
            s -= i;
            i = 0;
            while (*s && *s != c)
                out[w][i++] = *s++;
            out[w++][i] = '\0';
        }
    }
    out[w] = 0;
    return (out);
}

int  ft_numsize(int *n, int fd)
{
    int size;
    int save;

    size = 0;
    if (*n < 0)
    {
        *n *= -1;
        write (fd, "-", 1);
    }
    save = *n;
    while (save && size++ > -1)
        save /= 10;
    return (size);
}

void        ft_putnbr_fd(int n, int fd)
{
    char    s[11];
    int     i;
    
    if (n == -2147483648)
        write(fd, "-2147483648", 11);
    else if (n == 0)
        write(fd, "0", 1);
    else
    {
        i = ft_numsize(&n, fd);
        s[i--] = 0;
        while (n && (s[i--] = n % 10 + '0') > -1)
            n /= 10;
        write (fd, s, ft_strlen(s));
    }
}

/******************************************************/

t_list	*ft_lstnew(void *content)
{
	t_list	*out;

	out = malloc(sizeof(t_list));
	if (out == NULL)
		return NULL;
	out->content = content;
	out->next = NULL;
	return (out);
}

int		ft_lstsize(t_list *lst)
{
	int		length;

	length = 0;
	while (lst)
	{
		lst = lst->next;
		length++;
	}
	return (length);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*save;

	if(*lst == NULL)
	{
		*lst = new;
		return;	
	}
	save = *lst;
	while(save->next)
		save = save->next;
	save->next = new;
}

t_list	*ft_lstlast(t_list *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if(*lst == NULL)
	{
		*lst = new;
		return;	
	}
	new->next = *lst;
	*lst = new;
}

t_list	*ft_lstfilter(t_list *lst, t_auto *(*f)(t_auto *, void *), void *filter)
{
	t_list	*tmp;
	t_list	*root;
	void 	*cnt;

	if (lst == NULL)
		return (NULL);
	while (lst)
	{
		cnt = f(lst->content, filter);
		if (cnt)
		{
			tmp = ft_lstnew(cnt);
			if (tmp == NULL)
				return (NULL);
			ft_lstadd_front(&root, tmp);	
		}
		lst = lst->next;
	}
	return (root);
}

/*****************************************************/

void 	ft_printdata(t_data *data)
{
	printf("data.b %d %s\ndata.j %d %d \ndata.k %d %d\ndata.file1 %s %d\ndata.file2 %s %d\n", data->b, data->model, data->j, data->year, data->k, data->km, data->file1, data->fd1, data->file2, data->fd2);
	getchar();
}

void	ft_printlist(t_list *lst)
{
	t_auto	*tmp;

	while (lst)
	{
		tmp = (t_auto *)lst->content;
		printf("%s - %d - %d \n", tmp->type, tmp->year, tmp->km);
		lst = lst->next;
	}
	getchar();
}


int		ft_filesize(char *file)
{
	FILE 	*fd;
	int		count;
	char	ch;

	count = 0;
	fd = fopen(file, "r");
	if (fd == NULL)
	{
		perror("Fehler file : ");
		exit(1);
	}
	while((ch = fgetc(fd)) != EOF)
      count++;
	fclose(fd);
	return (count);
}

char	*ft_readfile(char *file)
{
	int		size;
	char	*out;
	FILE	*fd;
	char	ch;
	int		i;

	if (file == NULL)
		return (NULL);
	size = ft_filesize(file);
	fd = fopen(file, "r");
	if (fd == NULL)
	{
		perror("Fehler file : ");
		exit(1);
	}
	out = malloc(size + 1);
	if (out == NULL)
		return (NULL);
	i = -1;
	while((ch = fgetc(fd)) != EOF && ++i > -1)
		out[i] = ch;
	out[size] = 0;
	fclose(fd);
	return (out);
}

void	ft_init(t_data *data)
{
	data->j = 0;
	data->year = 0;
	data->k = 0;
	data->km = 0;
	data->b = 0;
	data->model = NULL;
	data->file1 = NULL;
	data->file2 = NULL;
	data->fd1 = -1;
	data->fd2 = 0;
}

void	ft_getdata(int argc, char **argv, t_data *data)
{
	int i;

	i = 1;
	argv++;
	while (i++ < argc)
	{
		if (ft_strcmp(*argv, "-k"))
		{
			if (i == argc)
				ft_exit("Fehler : unsuficient arguments for -k !");
			argv++;
			if (!ft_isnumber(*argv))
				ft_exit("Fehler : expected a number after -k !");
			data->k = 1;
			data->km = ft_strtonum(*argv);
			if (data->km < 1)
				ft_exit("Fehler : expected a positive integer after -k !");
			i++;
		}
		else if (ft_strcmp(*argv, "-j"))
		{
			if (i == argc)
				ft_exit("Fehler : unsuficient arguments for -j !");
			argv++;
			if (!ft_isnumber(*argv))
				ft_exit("Fehler : expected a number after -j !");
			data->j = 1;
			data->year = ft_strtonum(*argv);
			if (data->year < 1)
				ft_exit("Fehler : expected a positive integer after -j !");
			i++;
		}
		else if (ft_strcmp(*argv, "-b"))
		{
			if (i == argc)
				ft_exit("Fehler : unsuficient arguments for -b !");
			argv++;
			data->b = 1;
			data->model = *argv;
			i++;
		}
		else if (data->file1)
		{
			data->file2 = *argv;
			data->fd2 = open(*argv, O_WRONLY | O_CREAT, 0755);
			if (data->fd2 < 0)
				ft_exit("Fehler : unrecognized file2 !");
		}
		else
		{
			data->file1 = *argv;
			data->fd1 = open(*argv, O_WRONLY);
			if (data->fd1 < 0)
				ft_exit("Fehler : unrecognized file1 !");
		}
		argv++;
	}
}

t_auto *ft_getauto(char *line)
{
	t_auto 	*out;
	char	**sep;

	if (line == NULL)
		return (NULL);
	out = (t_auto *)malloc(sizeof(t_auto));
	if (out == NULL)
		return (NULL);
	sep = ft_split(line, ' ');
	if (sep == NULL)
		return (NULL);
	if (!sep[0] || !sep[1] || !sep[2]) //malformated line will be simply ignored.
		return (NULL);
	out->type = sep[0];
	out->year = ft_strtonum(sep[1]);
	out->km = ft_strtonum(sep[2]);
	free(sep);
	sep = NULL;
	return (out);
}

t_list	*ft_lstFromFile(t_data *data)
{
	char 	*file;
	char	**lines;
	char	**save;
	t_list	*out;
	t_list	*tmp;
	t_auto	*cont;

	file = ft_readfile(data->file1);
	lines = ft_split(file, '\n');
	if (lines == NULL)
		ft_exit("Fehler : error in spliting the file !");
	save = lines;
	out = NULL;
	while (*lines)
	{
		cont = ft_getauto(*lines);
		tmp = ft_lstnew(cont);
		if (tmp)
			ft_lstadd_back(&out, tmp);
		lines++;
	}
	lines = save;
	save = NULL;
	free(lines);
	lines = NULL;
	free(file);
	file = NULL;
	return (out);
}

t_auto	*ft_j(t_auto *data, void *year)
{
	if (data == NULL || year == NULL)
		return (NULL);
	if (data->year == *((int *)year))
		return (data);
	return (NULL);
}

t_auto *ft_k(t_auto *data, void *km)
{
	if (data == NULL || km == NULL)
		return (NULL);
	if (data->km <= *((int *) km))
		return (data);
	return (NULL);
}

t_auto *ft_b(t_auto *data, void *type)
{
	if (data == NULL || type == NULL)
		return (NULL);
	if (ft_strcmp(data->type, (char *)type))
		return (data);
	return (NULL);
}

void	ft_putdata(t_data *data, t_list *lst)
{
	t_auto *tmp;

	if (!data || !lst)
		return ;
	while (lst)
	{
		tmp = (t_auto *) lst->content;
		ft_putstr_fd(tmp->type, data->fd2);
		ft_putstr_fd(" ", data->fd2);
		ft_putnbr_fd(tmp->year, data->fd2);
		ft_putstr_fd(" ", data->fd2);
		ft_putnbr_fd(tmp->km, data->fd2);
		ft_putstr_fd("\n", data->fd2);
		lst = lst->next;
	}
}

t_list	*ft_filterautos(t_data *data, t_list *lst)
{
	t_list	*out;

	out = lst;
	if (data->k)
		lst = ft_lstfilter(out, &ft_k, &(data->km));
	if (data->j)
		out = ft_lstfilter(lst, &ft_j, &(data->year));
	if (data->b)
		out = ft_lstfilter(lst, &ft_b, &(data->model));
	return (out);
}



int main(int argc, char **argv)
{
	t_data data;
	t_list *lst;

	if (argc < 2)
		ft_exit("Fehler : too few arguments !\n");
	if (argc > 9)
		ft_exit("Fehler : too many arguments !\n");
	ft_init(&data);
	ft_getdata(argc, argv, &data);
	lst = ft_lstFromFile(&data);
	if (lst == NULL)
	 	ft_exit("Fehler : unexpected error when reading from the file !\n");
	ft_filterautos(&data, lst);
	ft_putdata(&data, lst);
	return 0;
}
