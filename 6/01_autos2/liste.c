#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Auto Auto;

struct Auto {
	void	*content;
	Auto	*next;
};


void	ft_putstr(char *str)
{
	if (str == NULL)
		return ;
	fwrite(str, strlen(str), 1, stdout);
}

void 	ft_exit(char *msg)
{
	ft_putstr(msg);
	exit(1);
}

Auto	*ft_lstnew(void *content)
{
	Auto	*out;

	out = malloc(sizeof(Auto));
	if (out == NULL)
		return NULL;
	out->content = content;
	out->next = NULL;
	return (out);
}

void	ft_lstadd_sorted(Auto **lst, Auto *new, int (*f)(Auto *n1, Auto *n2))
{
	Auto	*save;
	Auto	*tmp;

	if(*lst == NULL)
	{
		*lst = new;
		return ;	
	}
	save = *lst;
	if (f(new , save) <= 0)
	{
		*lst = new;
		new->next = save;
		return ;
	}
	while(save->next && f(new, save->next) >= 0)
		save = save->next;
	tmp = save->next;
	save->next = new;
	new->next = tmp;
}

void 	ft_lstclear(Auto **lst, void (*del)(void*))
{
	Auto	*p;

	if (*lst == NULL)
		return;
	while (*lst)
	{
		p = *lst;
		*lst = (*lst)->next;
		del(p->content);
		free(p);
	}
	free(*lst);
}

int 	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

int		ft_cmpAutos(Auto *a1, Auto *a2)
{
	char	*s1;
	char	*s2;

	s1 = (char *) a1->content;
	s2 = (char *) a2->content;
	return (ft_strcmp(s1, s2));
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

int		ft_filesize(FILE *file)
{
	int		count;
	char	ch;

	count = 0;

	fseek(file, 0, SEEK_SET);
	while((ch = fgetc(file)) != EOF)
      count++;
	return (count);
}

char	*ft_readfile(FILE *fd)
{
	int		size;
	char	*out;
	char	ch;
	int		i;

	if (fd == NULL)
	{
		perror("Fehler file : \n");
		exit(1);
	}
	size = ft_filesize(fd);
	out = malloc(size + 1);
	if (out == NULL)
		return (NULL);
	i = -1;
	fseek(fd, 0, SEEK_SET);
	while((ch = fgetc(fd)) != EOF && ++i > -1)
		out[i] = ch;
	out[size] = 0;
	return (out);
}

/**************************************************************/

Auto* autos_einlesen(FILE *eingabe)
{
	char	*text;
	char	**save;
	char	**lines;
	Auto	*node;
	Auto	*out;

	text = ft_readfile(eingabe);
	if (text == NULL)
		ft_exit("Error in reading the file!\n");
	lines = ft_split(text, '\n');
	if (lines == NULL)
		ft_exit("Error in spliting the text !\n");
	free(text);
	text = NULL;
	out = NULL;
	save = lines;
	while (*lines)
	{
		node = ft_lstnew(*lines);
		if (node == NULL)
			ft_exit("Error in creating a new list element!\n");
		ft_lstadd_sorted(&out, node, &ft_cmpAutos);
		lines++;
	}
	free(save);
	save = NULL;
	return (out);
}

void autos_ausgeben(FILE *ausgabe, Auto *autos)
{
	while (autos)
	{
		fprintf(ausgabe, "%s\n", (char *)autos->content);
		autos = autos->next;
	}
}

void autos_freigeben(Auto *autos){
   ft_lstclear(&autos, &free);
   autos = NULL;
}

int main(int argc, char **argv){
    /* Diese Funktion darf nicht verändert werden. */
    if (argc < 3){
        fprintf(stderr, "Zu wenige Parameter übergeben.\n");
        return EXIT_FAILURE;
    }

    // Autos einlesen.
    FILE *eingabe = fopen(argv[1], "r");
    Auto* autos = autos_einlesen(eingabe);
    fclose(eingabe);

    // Autos ausgeben.
    FILE *ausgabe = fopen(argv[2], "w");
    autos_ausgeben(ausgabe, autos);
    fclose(ausgabe);

    autos_freigeben(autos);

    return 0;
}
