#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "search.h"

char* turn_into_binary(char letter){
    int ascii = (int)letter;
    char *binary = malloc(9) ;
    for (int position = 7; position>= 0; position--){
        if(ascii - (int)pow(2, position) >= 0){
            binary[7-position] ='1';
            ascii -=(int)pow(2,position);
        }else{
            binary[7-position] ='0';
        }
    }
    binary[8]='\0';
    return binary;}

