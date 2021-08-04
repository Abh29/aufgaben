#include <stdio.h>

static int even(int a)
{
	return (a % 2 == 0);
}

int main(void)
{
	int x;

	printf("Geben Sie eine Zahl ein:		");
	scanf("%d", &x);
	if (even(x))
		printf("Die Zahl ist gerade!\n");
	else
		printf("Die Zahl ist nicht gerade!\n");
}