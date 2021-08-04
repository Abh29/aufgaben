#include <stdio.h>
#include <stdlib.h>
# include <stddef.h>

static void swap(double *a, double *b)
{
	double c;

	c = *a;
	*a = *b;
	*b = c;
}

int main(void)
{
	double a; 
	double b;

	printf("put the first number :   a =     ");
	scanf("%lf", &a);
	printf("put the second number :  b =     ");
	scanf("%lf",&b);
	swap(&a, &b);
	printf("this is a = %f   and this is b = %f\n", a, b);
	return (0);
}