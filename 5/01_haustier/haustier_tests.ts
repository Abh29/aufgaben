#include <string.h>
#include "haustier.h"

#test bello_name_setzen_ausgeben
    char name[21];
    memset(name, '?', sizeof(name));
    struct haustier tier;
    name_setzen(&tier, "Bello");
    name_ausgeben(name, &tier);
    ck_assert_str_eq(name, "Bello");

#test leer_name_setzen_ausgeben
    char name[21];
    memset(name, '?', sizeof(name));
    struct haustier tier;
    name_setzen(&tier, "");
    name_ausgeben(name, &tier);
    ck_assert_str_eq(name, "");

#test bello_name_wiederverwenden
    char name[21];
    memset(name, '?', sizeof(name));
    struct haustier tier;
    name_setzen(&tier, "Bello");
    strcpy(name, "Ente");
    name_ausgeben(name, &tier);
    ck_assert_str_eq(name, "Bello");

#test bello_name_aendern
    char name[21];
    memset(name, '?', sizeof(name));
    struct haustier tier;
    name_setzen(&tier, "Bello");
    name_setzen(&tier, "Hasso");
    name_ausgeben(name, &tier);
    ck_assert_str_eq(name, "Hasso");

#test bello_name_anhaengen
    char name[21];
    memset(name, '?', sizeof(name));
    struct haustier tier;
    name_setzen(&tier, "Bello");
    name_anhaengen(&tier, " der Dritte");
    name_ausgeben(name, &tier);
    ck_assert_str_eq(name, "Bello der Dritte");

#test leer_anhaengen
    char name[21];
    memset(name, '?', sizeof(name));
    struct haustier tier;
    name_setzen(&tier, "");
    for (int k = 0; k < 10; k++){
        name_anhaengen(&tier, "");
    }
    name_ausgeben(name, &tier);
    ck_assert_str_eq(name, "");

#test bello_name_anhaengen2
    char name[21];
    memset(name, '?', sizeof(name));
    struct haustier tier;
    name_setzen(&tier, "Bello");
    name_anhaengen(&tier, "");
    name_anhaengen(&tier, " der");
    name_anhaengen(&tier, "");
    name_anhaengen(&tier, " Dritte");
    name_ausgeben(name, &tier);
    ck_assert_str_eq(name, "Bello der Dritte");

#test bello_name_anhaengen3
    char name[21];
    memset(name, '?', sizeof(name));
    struct haustier tier;
    name_setzen(&tier, "Bello");
    name_anhaengen(&tier, " der");
    name_anhaengen(&tier, " Zwanzigste");
    name_ausgeben(name, &tier);
    ck_assert_str_eq(name, "Bello der Zwanzigste");
