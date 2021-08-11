#include "string_suchen.h"
#include <stdio.h>
#include <stddef.h>


#test null_string
	ck_assert_int_eq(string_suchen("lorem ipsum dolor sit amet", NULL), -1);
	ck_assert_int_eq(string_suchen(NULL, "lorem ipsum dolor sit amet"), -1);	
	ck_assert_int_eq(string_suchen(NULL, NULL), -1);

#test empty_string
	ck_assert_int_eq(string_suchen("lorem ipsum dolor sit amet", ""), 0);
	ck_assert_int_eq(string_suchen("", ""), 0);	
	ck_assert_int_eq(string_suchen("", "lorem ipsum dolor sit amet"), -1);

#test basic_test
	ck_assert_int_eq(string_suchen("lorem ipsum dolor sit amet", "lorem"), 0);
	ck_assert_int_eq(string_suchen("lorem ipsum dolor sit amet", "ipsum"), 6);	
	ck_assert_int_eq(string_suchen("lorem ipsum dolor sit amet amet.", "amet"), 22);
	ck_assert_int_eq(string_suchen("lorem ipsum dolor sit amet amet.", "amet "), 22);
	ck_assert_int_eq(string_suchen("lorem ipsum dolor sit amet amet.", "amet."), 27);
	ck_assert_int_eq(string_suchen("lorem ipsum dolor sit amet amet.", "amet,"), -1);
	

