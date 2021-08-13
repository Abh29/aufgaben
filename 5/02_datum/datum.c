#include "datum.h"

void	datum_setzen(struct datum *d, int jahr, int monat, int tag)
{
	if (d == NULL)
		return ;
	d->jahr = jahr;
	d->monat = monat;
	d->tag = tag;
}

void	datum_ausgeben(FILE *ausgabe, struct datum *d)
{
	char	buff[10];

	if (ausgabe == NULL || d == NULL)
		return ;
	buff[0] = d->jahr / 1000 + '0';
	buff[1] = (d->jahr / 100) % 10 + '0';
	buff[2] = (d->jahr / 10) % 10 + '0';
	buff[3] = d->jahr % 10 + '0';
	buff[4] = '-';
	buff[5] = (d->monat / 10) % 10 + '0';
	buff[6] = d->monat % 10 + '0';
	buff[7] = '-';
	buff[8] = (d->tag / 10) % 10 + '0';
	buff[9] = d->tag % 10 + '0';
	buff[10] = 0;
	fwrite(buff, 1, 10, ausgabe);
}

int		datum_vergleichen(struct datum *a, struct datum *b)
{
	int d1;
	int d2;

	if (a == b)
		return (0);
	d1 = a->jahr * 10000 + a->monat * 100 + a->tag;
	d2 = a->jahr * 10000 + a->monat * 100 + a->tag;
	return (d1 - d2);
}