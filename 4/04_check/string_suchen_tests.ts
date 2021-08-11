#include "string_suchen.h"
#include <stdio.h>

#test ente_ente
    int position = string_suchen("Ente", "Ente");

    ck_assert_int_eq(position, 0);

#test nichts_gefunden
    int position = string_suchen("Ente", "xxxx");

    ck_assert_int_eq(position, -1);
