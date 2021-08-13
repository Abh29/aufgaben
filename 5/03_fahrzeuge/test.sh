#!/usr/bin/env bash

# Check output
for i in 1 2
do
    output="ausgabe$i.txt"
    expected_output="neustes_fahrzeug$i.txt"

    if diff "$output" "$expected_output"
    then
        printf 'OK: %s entspricht %s.\n' "$output" "$expected_output"
    else
        printf 'FEHLER: Erwartet:\n'
        cat "$expected_output"
        printf 'Tatsächliche Ausgabe:\n'
        cat "$output"
        exit 1
    fi
done
