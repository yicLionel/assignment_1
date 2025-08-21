#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "field.h"

#define BITS_PER_CHAR 8    
#define NULL_TERMINATOR 1

char* char_turn_into_binary(char letter);
char* string_into_binary(const char* whole_str);
int count_bit(const char* input_binary, const char* curr_line_binary);
void compare_key(Node_t *head, char* input_key, FILE* out_file);

