#!/usr/bin/env bash

rm -f lottozahlen

if sha256sum -c 'pruefsummen.txt'
then
    printf 'OK: Die C-Datei wurde nicht modifiziert.\n'
else
    printf 'FEHLER: Die C-Datei darf bei dieser Aufgabe nicht modifiziert werden!\n'
    exit 1
fi

if gcc -g -std=c99 -Wall lottozahlen.c -o lottozahlen
then
    gdb -q ./lottozahlen < gdb_eingabe.txt > ausgabe.txt

    function test_output(){
        expected="$1"
        if grep -qF "$expected" ausgabe.txt
        then
            printf 'OK: Die Ausgabe enthält "%s".\n' "$expected"
        else
            cat ausgabe.txt
            printf 'FEHLER: Die Ausgabe enthält nicht "%s".\n' "$expected"
            exit 1
        fi
    }

    test_output 'Woche 7: 3 8 19 30 35 49'
    test_output 'Woche 20: 3 6 8 25 28 37'

    rm -f lottozahlen ausgabe.txt
else
    printf 'Konnte nicht kompiliert werden.\n'
    exit 1
fi
