#ifndef TEST_H  
#define TEST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR 127
#define MAX_LENGTH 511
#define NUM_DOUBLE 2  // Number of long doubles
#define NUM_COL 35 // Number of columns in total
#define X_FIELD_OFFSET 2
#define Y_FIELD_OFFSET 1

/*
* Our team declares the use of GenAI to convert fixed memory approach to dynamic memory approach.
*/
typedef struct {
    // First 33 string fields, each points to danymic memory
    char* fields[NUM_COL-NUM_DOUBLE];
    // Last 2 long double fields
    long double x;
    long double y;
} Address_t;



typedef struct Node {
    Address_t data;
    struct Node* next;
} Node_t;

Node_t* read_csv(char* filename);
Node_t* create_node(Address_t* address);
#endif 