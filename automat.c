#include <stdio.h>
#include <stdlib.h>

static int transaction = 0;

/*
 * Diese Funktionen müssen von Ihnen implementiert werden.
 * Alle Funktionen müssen zudem sinnvoll verwendet werden.
 * Das bedeutet, dass Sie zum Beispiel nicht die gesamte
 * Funktionalität in der main-Funktion implementieren dürfen,
 * ohne dabei die geforderten Funktionen aufzurufen.
 */

/*
 * You need to implement these functions.
 * All functions must also be used sensibly.
 * That means that you do not have the entire, for example
 * May implement functionality in the main function,
 * without calling up the required functions.
 * 
 * 
 * 
 * Pointers and functions (compulsory task)
In this exercise you should write a program that represents a Bitcoin machine. In
In the uploaded automat.c file you will find some predefined function prototypes that are used
Need to become. With the exception of the ¨ issue bitcoin function, these have not yet been implemented.
At the beginning the machine has 10 Bitcoin. ¨
The program should run as follows:
1. The machine accepts numbers as input. For the sake of simplicity, this task is used
only worked with whole numbers.
2. After entering a number, the machine reduces the number of available Bitcoin and increases it
Money balance according to the price and spends as many Bitcoin on the standard issue as
were bought. To do this, use the issue bitcoin function.
3. The machine then gives the money balance in the format
"Money balance: <Money balance> \ followed
from a line break, where
"<Money balance> \ by the corresponding numerical value
replace is.
4. It can happen that a user requests more Bitcoin than is available. In this
Fall instead
"Only <number> Bitcoin in the machine. \ And a line break
issued.
5. Bitcoin prices fluctuate a lot. Therefore, a price of 30000 each should be used for the first request
Bitcoin used for the second request a price of 40000 and for the third request ¨
a price of 50,000. The fourth, seventh, tenth, etc. request starts all over again
Come on. This means that the prices follow the course 30000, 40000, 50000, 30000, 40000, 50000,
30000, 40000, 50000,::: follow. The price also changes in the event of unsuccessful inquiries.
6. If the number of Bitcoin requested is zero or even negative, the machine should exit and the message
"The machine will be terminated. \ As well as a line break
output.
7. Check your program by executing the script file ¨ test.sh. The ¨
The input from the file ¨ input.txt is fed to the program via the command line and a ¨
Edition produced. The diff program then checks whether the output corresponds to the
expected output in file expected output.txt is the same. You may have to ¨
first make the test file executable with the command chmod + x test.sh. ¨
For this task you have to implement your own main function, otherwise your program
cannot start. 
 */



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
