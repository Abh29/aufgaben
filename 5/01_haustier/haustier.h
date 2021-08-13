#ifndef HAUSTIER_H
#define HAUSTIER_H

#include <string.h>

typedef struct haustier
{
	char	name[21];
}				t_haustier;

void	name_setzen(t_haustier *pet, const char *name);
void	name_anhaengen(t_haustier *pet, const char *name);
void	name_ausgeben(const char *name, t_haustier *pet);

#endif

