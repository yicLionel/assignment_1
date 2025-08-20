#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "search.h"

#include "test.h"  

/* Converts a single character to its 8-bit binary string representation. */
char* char_turn_into_binary(char letter){
    int ascii = (int)letter; // Get ASCII value of the character
    char *binary = malloc(BITS_PER_CHAR + NULL_TERMINATOR); // Allocate space for 8 bits + null terminator
    assert(binary); 

    // Convert the ASCII value of the character to an 8-bit binary string
    for (int position = 7; position>= 0; position--){
        if (ascii & (1 << position)) {
    binary[7 - position] = '1'; // Set '1' if bit is set
} else {
    binary[7 - position] = '0'; // Set '0' if bit is not set
}
    }
    binary[8]='\0';
    return binary;
}

/* Converts an entire string to a concatenated binary string representation. */
char* string_into_binary(const char* whole_str){
    int str_len = strlen(whole_str); // // Get length of input string
    char* str_binary = malloc(str_len * BITS_PER_CHAR + NULL_TERMINATOR);
    assert(str_binary); 
    str_binary[0] = '\0';

    // Convert each character to binary and append to result
    for(int str_index =0; str_index < str_len; str_index++){
        char * char_binary = char_turn_into_binary(whole_str[str_index]);
        strcat(str_binary, char_binary); // Append current character's binary
        free(char_binary);
    }
    return str_binary;
}

/*  Counts the number of bits compared until the first mismatch. */
int count_bit(const char* a, const char* b){
    if (!a || !b) return 0; // 空指针检查
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i]) {
            return i + 1; // Return count including mismatched bit
            }
        i++;
    }
    return i + sizeof(Address_t*); // If all compared bits match, return total bits checked
}

/* Compare keys and return the number of comparisons of bit, node and string */
void compare_key(Node_t *head, char* input_key, FILE* out_file){
    // Check if head or input_key is NULL
    if(!head || !input_key){
        return;
    }

    Node_t * curr_line = head;
    int num_records = 0; // Store the number of records found

    // Store the number of comparisons of bit, node and string
    int bit_comparisons = 0;
    int node_comparisons = 0;
    int string_comparisons = 0;

    // Convert input_key to binary
    char *input_binary = string_into_binary(input_key);
    fprintf(out_file, "%s \n", input_key);
    while(curr_line){
        node_comparisons++; // Read one node
        char *curr_line_binary = string_into_binary(curr_line->data.EZI_ADD);
        if (!curr_line_binary) {
            free(input_binary);
            return; // Fail to allocate memory
        }
        string_comparisons++; // Read one string
        
        bit_comparisons += count_bit(input_binary, curr_line_binary); // Add bit comparisons for one line

        // Check for bit difference
        if(strcmp(input_binary, curr_line_binary) == 0){
            num_records++;
            fprintf(out_file, "-->");
            char *every_field = (char *)&(curr_line->data);  

            // Handle the first 33 fields of strings
            for (int i = 0; i < NUM_COL-2; i++) {
                // Ensure fields ends with null terminator
                every_field[MAX_CHAR - 1] = '\0'; 
                // Print field
                fprintf(out_file, " %s: %s ||", field_names[i], every_field); 
                every_field += MAX_CHAR;// Skip to next field
}

            // Handle the last two long double fields
            fprintf(out_file," %s: %Lf ||", field_names[NUM_COL-2], curr_line->data.x);
            fprintf(out_file," %s: %Lf ||\n", field_names[NUM_COL-1], curr_line->data.y);
            // Flush the output file
            fflush(out_file);
        }
        free(curr_line_binary);
        // Move to next node(line)
        curr_line = curr_line->next;
    }
    free(input_binary);

    // Print the number of records found
    printf(" --> %d records found - comparisons: ", num_records);

    // Print the number of comparisons of bit, node and string in the terminal window
    printf("b%d ", bit_comparisons);
    printf("n%d ", node_comparisons);
    printf("s%d", string_comparisons);
    printf("\n");

}