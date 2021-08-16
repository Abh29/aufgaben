#!/usr/bin/env bash

logfile="valgrind_log.txt"

# Kompilieren
if gcc -g liste.c -std=c99 -g -Wall -o liste
then
    for i in 1 2
    do
        printf 'Prüfe eingabe%s.txt.\n' "$i"

        # Programm ausführen und mit valgrind überprüfen
        (
            set -x
            valgrind \
                --leak-check=full \
                --show-leak-kinds=all \
                --track-origins=yes \
                --log-file="$logfile" \
                ./liste "eingabe$i.txt" "ausgabe$i.txt"
        )

        # Rückgabewert überprüfen
        return_value="$?"

        if [ $return_value -eq 0 ]
        then
            printf '\tOK: Rückgabewert ist 0.\n'
        else
            printf '\tFEHLER: Rückgabewert ist nicht 0, sondern %s. Wahrscheinlich ist das Programm abgestürzt.\n\n' "$return_value"
            cat "$logfile"
            exit 1
        fi

        # Ausgabe überprüfen
        if diff "ausgabe$i.txt" "erwartete_ausgabe$i.txt"
        then
            printf '\tOK: Ausgabe ist wie erwartet.\n'
        else
            printf '\tFEHLER: Ausgaben unterscheiden sich:\n'
            diff -y "ausgabe$i.txt" "erwartete_ausgabe$i.txt"
            exit 1
        fi

        ./valgrind_log_pruefen.sh "$logfile"

        # Aufräumen
        rm -f "ausgabe$i.txt" "$logfile"

        printf '\n'
    done

    rm -f liste
else
    printf "Programm konnte nicht kompiliert werden.\n"
    exit 1
fi
