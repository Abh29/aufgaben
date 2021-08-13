#ifndef FAHRZEUGE_H
#define FAHRZEUGE_H

#include "../02_datum/datum.h"



enum fahrzeug_model 
{
	Bus,
	Kleinwagen,
	Kombi,
	Motorrad
};

struct fahrzeug
{
	struct datum		date;
	enum fahrzeug_model	model;
	char				mnfctr[16];
}





/*
 * Gibt für ein Enum den entsprechenden String zurück.
 */
char* modell_enum_zu_string(enum fahrzeug_model modell);

/*
 * Schreibt ein Fahrzeug in die Datei "ausgabe".
 */
void fahrzeug_ausgeben(FILE *ausgabe, struct fahrzeug *fahrzeug);

/*
 * Findet das neuste Fahrzeug in der Datei "eingabe" und schreibt es in die
 * Variable, auf die der Zeiger "neustes" zeigt.
 */
void neustes_fahrzeug_finden(struct fahrzeug *neustes, FILE *eingabe);

#endif

/**
 * A wealthy car collector wanted to digitally manage the following data on his vehicles:
• Date of construction (same format as in the previous exercise)
• Model (bus, small car, station wagon, motorcycle)
• Manufacturer name (less than 15 characters)
For example, a file with vehicles can look like this:
1970-01-01 small car Ferrari
2020-12-24 Bus Tesla

(a) Implement an enum vehicle model in vehicles.h that stores the vehicle model. Use the given files to consider which vehicle classes are required.

(b) Implement a struct vehicle in vehicles.h that stores the vehicle's data. Think about which components of which data type are required. To do this, use the struct from datum.h from the previous exercise again.

(c) Implement a function in vehicles.c that finds the latest vehicle in a file and writes it to the address to which the pointer points latest.

void find new_vehicle (struct vehicle * newest, FILE * input);
Functions for outputting the vehicle are already implemented for you. The main function must not be changed!


(d) Test your program with the make run command*/