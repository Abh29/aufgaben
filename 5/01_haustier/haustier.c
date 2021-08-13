#include "haustier.h"

void	name_setzen(t_haustier *pet, const char *name)
{
	int i;

	if (pet == NULL || name == NULL)
		return ;
	if (strlen(name) > 20)
		return ;
	strncpy(pet->name, name, strlen(name));
}


void	name_anhaengen(t_haustier *pet, const char *name)
{
	if (pet == NULL || name == NULL)
		return ;
	if (strlen(name) + strlen(pet->name) > 20)
		return ;
	strlcat(pet->name, name, 20);
}


void	name_ausgeben(const char *name, t_haustier *pet)
{
	if (pet == NULL || name == NULL)
		return ;
	strcpy(name, pet->name);
}
