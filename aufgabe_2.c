#include <stdio.h>
#include <stdlib.h>
# include <stddef.h>

int main(void)
{
	int i;
	double	*arr;
	double *save;

	arr = malloc(12 * sizeof(double));
	if (arr == NULL)
		return (-1);
	i = 0;
	save = arr;
	while (i < 12)
	{
		printf("geben Sie eine Zahl ein : arr[%d]  ==   ", i++);
		scanf("%lf", arr++);
	}
	printf("\n\n");
	arr = save;
	i = 0;
	while (i < 12)
		printf("arr[%02d] = %8f\n", i++, *save++);
	return (0);
}