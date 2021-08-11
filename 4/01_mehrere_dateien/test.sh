#!/usr/bin/env bash

rm -f berechnung ausgabe.txt *.o

# Dateien kompilieren
./kompilieren_einzeiler.sh

# Zeilen zählen
zeilen="$(cat kompilieren_einzeiler.sh | grep '\S' | wc -l)"

# Sollte genau eine Zeile sein
if [ "$zeilen" -eq 1 ]
then
    printf '\tOK: Einzeiler ist tatsächlich eine Zeile lang.\n'
else
    printf '\tFEHLER: kompilieren_einzeiler.sh sollte eine Zeile beinhalten, hat aber %s Zeilen.\n' "$zeilen"
    exit 1
fi

# Programm ausführen und ausgabe generieren
if ! ./berechnung > ausgabe.txt
then
    exit 1
fi

# Ausgabe überprüfen
if diff ausgabe.txt erwartete_ausgabe.txt
then
    printf '\tOK: Ausgabe ist wie erwartet.\n'
else
    printf '\tFEHLER: Ausgabe entspricht nicht der erwarteten Ausgabe.\n'
    printf '\tErwartete Ausgabe:\n'
    cat erwartete_ausgabe.txt
    printf '\tTatsächliche Ausgabe:\n'
    cat ausgabe.txt
    exit 1
fi

# Krempel entfernen
rm -f berechnung ausgabe.txt *.o

# Das Gleiche nochmal für mehrere Zeilen.

zeilen="$(cat kompilieren_einzeln.sh | grep '\S' | wc -l)"

if [ "$zeilen" -eq 6 ]
then
    printf '\tOK: kompilieren_einzeln.sh hat 6 Zeilen.\n'
else
    printf '\tFEHLER: kompilieren_einzeln.sh sollte 6 Zeilen lang sein, hat aber %s Zeilen.\n' "$zeilen"
    exit 1
fi

./kompilieren_einzeln.sh

if ! ./berechnung > ausgabe.txt
then
    exit 1
fi

if diff ausgabe.txt erwartete_ausgabe.txt
then
    printf '\tOK: Ausgabe ist wie erwartet.\n'
else
    printf '\tFEHLER: Ausgabe entspricht nicht der erwarteten Ausgabe.\n'
    printf '\tErwartete Ausgabe:\n'
    cat erwartete_ausgabe.txt
    printf '\tTatsächliche Ausgabe:\n'
    cat ausgabe.txt
    exit 1
fi

rm -f berechnung ausgabe.txt *.o
