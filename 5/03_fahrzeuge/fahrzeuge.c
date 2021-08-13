#include "fahrzeuge.h"

#include <string.h>



static int		ft_wordcount(char const *s, char c)
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

static char	**ft_split(char const *s, char c)
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

static struct datum ft_getDate(char *date)
{
	char			**spt;
	struct datum 	out;
	
	out.jahr = -1;
	if (date == NULL)
		return (out);
	spt = ft_split(date, '-');
	if (!spt || !spt[0] || !spt[1] || !spt[2])
		return (out);
	out.jahr = atoi(spt[0]);
	out.monat = atoi(spt[1]);
	out.tag = atoi(spt[2]);
	return (out);
}

static int ft_getEnum(char *model)
{
	if (model == NULL)
		return (-1);
	if (strcmp(model, "Bus"))
		return (BUS);
	if (strcmp(model, "Kleinwagen"))
		return (KLEINWAGEN);
	if (strcmp(model, "Kombi"))
		return (KOMBI);
	if (strcmp(model, "Motorrad"))
		return (MOTORRAD);
	return (-1);
}

void neustes_fahrzeug_finden(struct fahrzeug *neustes, FILE *eingabe){
    
	char			buff[100];
	char			**spt;
	struct datum	date;
	struct fahrzeug	veh;
	int				i;
	char 			ch;


	//get first car
	i = -1;
	while((ch = fgetc(eingabe)) != EOF && ++i > -1)
	{
		buff[i] = ch;
		if (ch == '\n' || ch == EOF)
		{
			buff[i] = 0;
			spt = ft_split(buff, ' ');
			if (!spt || !spt[0] || !spt[1] || !spt[2])
				i = -1;
			else
			{
				veh.baudatum = ft_getDate(spt[0]);
				strcpy(veh.hersteller, spt[2]);
				if (ft_getEnum(spt[1]) != -1)
				{
					veh.modell = ft_getEnum(spt[1]);
					break;
				}
				//free(spt);
				//spt = NULL;
				i = -1;
			}
		}
		if (ch == EOF)
			i = -2;
	}

	// get the rest of the cars 
	i = -1;
	while((ch = fgetc(eingabe)) != EOF && ++i > -1)
	{
		buff[i] = ch;
		if (ch == '\n' || ch == EOF)
		{
			buff[i] = 0;
			spt = ft_split(buff, ' ');
			if (!spt || !spt[0] || !spt[1] || !spt[2])
				continue ;
			else
			{
				date = ft_getDate(spt[0]);
				if (datum_vergleichen(&veh.baudatum, &date) < 0)
				{
					if (ft_getEnum(spt[1]) != -1)
					{
						veh.modell = ft_getEnum(spt[1]);
						strcpy(veh.hersteller, spt[2]);
						veh.baudatum = date;
					}
				}
				free(spt);
				spt = NULL;
			}
			memset(buff, 0, i);
			i = -1;
		}
	}	


}

char* modell_enum_zu_string(enum fahrzeug_model modell){
    switch (modell){
        case BUS:
            return "Bus";
        case KLEINWAGEN:
            return "Kleinwagen";
        case KOMBI:
            return "Kombi";
        case MOTORRAD:
            return "Motorrad";
        default:
            return "Unbekannt";
    }
}

void fahrzeug_ausgeben(FILE *ausgabe, struct fahrzeug *fahrzeug){
    datum_ausgeben(ausgabe, &fahrzeug->baudatum);

    char *modell = modell_enum_zu_string(fahrzeug->modell);

    fprintf(ausgabe, " %s %s\n", modell, fahrzeug->hersteller);
}

int main(int argc, char **argv){
    /* Diese Funktion darf nicht verändert werden! */

    FILE *eingabe = fopen(argv[1], "r");
    FILE *ausgabe = fopen(argv[2], "w");

    struct fahrzeug neustes;

    neustes_fahrzeug_finden(&neustes, eingabe);

    fahrzeug_ausgeben(ausgabe, &neustes);

    fclose(eingabe);
    fclose(ausgabe);

    return 0;
}
