#!/usr/bin/env bash

if ! make all
then
    printf 'FEHLER: Der Befehl "make all" schlug fehl.\n'
    exit 1
fi

filenames='zoo.o giraffe.o elefant.o main.o main'

# Check if files have been created
for filename in ${filenames}
do
    if [ -f "$filename" ]
    then
        printf 'OK: Datei "%s" wurde erstellt.\n' "$filename"
    else
        printf 'FEHLER: Datei "%s" wurde nicht erstellt.\n' "$filename"
        exit 1
    fi
done

# Produce output
if ./main > ausgabe.txt
then
    printf 'OK: Die Datei ausgabe.txt wurde erzeugt.\n'
else
    printf 'FEHLER: Das Programm "main" konnte nicht ausgeführt werden.\n'
    exit 1
fi

# Check if output is as expected
if diff -q ausgabe.txt erwartete_ausgabe.txt
then
    printf 'OK: Die Ausgabe stimmt mit der erwarteten Ausgabe überein.\n'
else
    printf 'FEHLER: Die Datei "ausgabe.txt" stimmt nicht mit der erwarteten Ausgabe in Datei "erwartete_ausgabe.txt" überein:\n'
    diff -y ausgabe.txt erwartete_ausgabe.txt
    exit 1
fi

# Write file modification dates to files so we can change them later for changes
for filename in ${filenames}
do
    stat -c %y "$filename" > "change1_$filename.txt"
done

# Check if some files changed, i.e. their modification date changed.
function check_change() {
    for filename in ${1}
    do
        stat -c %y "$filename" > "change2_$filename.txt"
        if diff "change1_$filename.txt" "change2_$filename.txt" > /dev/null
        then
            printf 'FEHLER: Datei "%s" hat sich nicht geändert, obwohl eine Abhängigkeit geändert wurde.\n' "$filename"
            exit 1
        else
            printf 'OK: Datei "%s" hat sich geändert.\n' "$filename"
        fi
    done
}

# Check if some files stayed the same, i.e. their modification date has not changed.
function check_no_change() {
    for filename in ${1}
    do
        stat -c %y "$filename" > "change2_$filename.txt"
        if diff "change1_$filename.txt" "change2_$filename.txt" > /dev/null
        then
            printf 'OK: Datei "%s" hat sich nicht geändert.\n' "$filename"
        else
            printf 'FEHLER: Datei "%s" hat sich geändert, obwohl keine Abhängigkeit geändert wurde.\n' "$filename"
            exit 1
        fi
    done
}

printf 'INFO: "make all" wird nochmals ausgeführt.\n'

if ! make all
then
    printf 'FEHLER: Der Befehl "make all" schlug fehl.\n'
    exit 1
fi

# Check if all files stayed the same
check_no_change "$filenames"

printf 'INFO: Datei "zoo.h" wird verändert und "make all" wird nochmals ausgeführt.\n'
# Append comment to "zoo.h"
printf '//zoo.h wurde durch diesen Kommentar verändert.\n' >> zoo.h

if ! make all
then
    printf 'FEHLER: Der Befehl "make all" schlug fehl.\n'
    exit 1
fi

# Check if some files stayed the same
check_no_change 'elefant.o giraffe.o'
# Check if some files changed
check_change 'zoo.o main.o main'

# Cleanup test files
rm -f ausgabe.txt
for filename in ${filenames}
do
    rm -f "change1_$filename.txt"
    rm -f "change2_$filename.txt"
done

printf 'INFO: "make clean" wird ausgeführt.\n'

make clean

# Check if files have been removed
for filename in ${filenames}
do
    if test -f "$filename"
    then
        printf 'FEHLER: Datei "%s" wurde nicht durch "make clean" entfernt.\n' "$filename"
        exit 1
    else
        printf 'OK: Datei "%s" wurde durch "make clean" entfernt.\n' "$filename"
    fi
done
