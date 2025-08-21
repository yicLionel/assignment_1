#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "field.h"

/* Parses a CSV line into an array of field strings, up to a maximum number of fields */
static int parse_csv_line(char *line, char *fields[], int max_fields) {
    int count = 0;
    char *current_posi = line; // Points to the current position in the input line

    // Process the line until the end or max_fields is reached
    while (*current_posi && count < max_fields) {
            fields[count] = current_posi;
            // Move to the next comma, newline, or end of string
            while (*current_posi && *current_posi != ',' && *current_posi != '\n') {
                current_posi++;
            }
            // If a comma is found, replace it with a null character and move to next field
            if (*current_posi == ',') { 
                *current_posi = '\0'; 
                current_posi++;
            }
        
        count++;
    }

    // Fill remaining fields with empty strings to ensure consistent field count
    while (count < max_fields) {
        fields[count++] = "";
    }

    return count;
}

/* Reads CSV file and converts data into a linked list */
Node_t* read_csv(char* filename) {
    FILE* file = fopen(filename, "r");
    // Check if file exists
    if (!file) {
        fprintf(stderr, "Error: File not found: %s\n", filename);
        return NULL;
    }

    // Initialize head and tail node to be Null
    Node_t* head = NULL;
    Node_t* tail = NULL;
    char line[MAX_LENGTH];

    // Skip the first line of the CSV file
    if (!fgets(line, sizeof(line), file)) {
        fclose(file); // Close the file if not able to read
        return NULL;
    }


    while (fgets(line, sizeof(line), file)) {
        // Replace newline character with null character
        for (int i = 0; line[i] != '\0'; i++) {
            if (line[i] == '\n') {  
            line[i] = '\0';     
            break;              
            }
        }   

        char *fields[NUM_COL]; // Array to hold parsed fields
        int field_count = parse_csv_line(line, fields, NUM_COL); // Parse current line
        Address_t addr = {0};


        // Handle the first 33 fields
        for (int i = 0; i < NUM_COL - NUM_DOUBLE; i++) {
            addr.fields[i] = fields[i]; 
        }
        // Handle the last two long double fields
        addr.x = strtold(fields[field_count - X_FIELD_OFFSET], NULL);
        addr.y = strtold(fields[field_count - Y_FIELD_OFFSET], NULL);


        // Create a new node with "addr" structure
        Node_t* new_node = create_node(&addr);
        if (!head) { head = tail = new_node; }
        else { tail->next = new_node; tail = new_node; }
    }
    fclose(file);
    return head;
}


/* Creates a new node for a linked list with the given address data */
Node_t* create_node(Address_t* address) {
    // Allocate memory for a new Node_t structure
    Node_t* new_node = (Node_t*)malloc(sizeof(Node_t));
    assert(new_node);

    // Copy the address data into the new node
    for (int i = 0; i < NUM_COL - NUM_DOUBLE; i++) {
        int str_len = strlen(address->fields[i]);
        new_node->data.fields[i] = malloc(str_len + 1);  
        assert(new_node->data.fields[i] != NULL);
        strcpy(new_node->data.fields[i], address->fields[i]);  
    }
    // Copy the long doubles
    new_node->data.x = address->x;
    new_node->data.y = address->y;

    // Initialize the next pointer to NULL
    new_node->next = NULL;
    return new_node;
}