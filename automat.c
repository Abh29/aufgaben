#include <stdio.h>
#include <stdlib.h>

static int transaction = 0;

void	bitcoin_ausgeben(){
    printf("    ###########\n");
    printf("  ###         ###\n");
    printf(" ##             ##\n");
    printf("##     #  #      ##\n");
    printf("#    ########     #\n");
    printf("#     #      #    #\n");
    printf("#     #      #    #\n");
    printf("#     #######     #\n");
    printf("#     #      #    #\n");
    printf("#     #      #    #\n");
    printf("#    ########     #\n");
    printf("##     #  #      ##\n");
    printf(" ##             ##\n");
    printf("  ###         ###\n");
    printf("    ###########\n");
    printf("\n");
}

int		anzahl_einlesen()
{
	int x;

	scanf("%i", &x);
	return (x);
}

int		getPrice()
{
	int prices[] = {30000, 40000, 50000};
	return (prices[transaction++ % 3]);
}

void	exit_msg(char *msg)
{
	printf("%s\n", msg);
	exit(1);
}

void	bitcoins_kaufen(int anzahl, int preis, int *bitcoinstand, int *geldstand)
{
	if (anzahl < 1)
		exit_msg("Der Automat wird beendet.");
	if (anzahl > *bitcoinstand)
		printf("Nur noch %d Bitcoin im Automaten.\n", *bitcoinstand);
	else
	{
		*bitcoinstand -= anzahl;
		*geldstand += anzahl * preis;
		while (anzahl--)
			bitcoin_ausgeben();
		printf("Geldstand: %d\n", *geldstand);
	}
}



int main(void)
{
	int bitcoinstand;
	int geldstand;

	bitcoinstand = 10;
	geldstand = 0;
	while (1)
		bitcoins_kaufen(anzahl_einlesen(), getPrice(), &bitcoinstand, &geldstand);
	return 0;
}
