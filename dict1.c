/* dict1.c 
*
* Created by Yichen YAN (yicyan2@student.unimelb.edu.au) and
*            Chang Lu (CLLU8@student.unimelb.edu.au)
* Date: 20/08/2025
*
*
* Build a dictionary by reading data from a file. 
* It will insert each address record as a node in a linked list.
* Also implementing a search tool that looks for a key in the list 
* and outputs any records that match the key.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "search.h"

int main(int argc, char* argv[]) {
    // Check if the number of command-line arguments is 4
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <stage> <input_file> <output_file>\n", argv[0]);
        return 1;
    }
    
    // Check if the stage parameter is "1"
    if (strcmp(argv[1], "1") != 0) {
        fprintf(stderr, "Invalid stage: %s\n", argv[1]);
        return 1;
    }

    // Open the output file
    FILE* out_file = fopen(argv[3], "w");

    // Check if file opening failed
    if (!out_file) {
        fprintf(stderr, "Cannot open output file %s\n", argv[3]);
        return 1;
    }
    
    // Read the CSV file into a linked list, and head is pointing to the first node
    Node_t* head = read_csv(argv[2]); 
    // Array to store the keyword
    char keyword[MAX_CHAR];

    // Continuously read the keyword from stdin that user inputs 
    while(1){
        // Exit on the end of file or input error
        if(fgets(keyword, MAX_CHAR, stdin) == NULL){
            break;
        }
        // Replace newline character to null character
        keyword[strcspn(keyword, "\n")] = '\0';

        printf("%s ", keyword);
        compare_key(head, keyword, out_file);
    }

    fclose(out_file);
    
    // Free memory allocated for the linked list
    Node_t* current = head;
    while (current != NULL) {
        Node_t* temp = current;
        // Free the first 33 fields
        for (int i = 0; i < NUM_COL - NUM_DOUBLE; i++) {
            free(temp->data.fields[i]);  // Free the memory allocated for each field
        }
        current = current->next;
        free(temp);  // Free the node
    }
}