#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assignment_1.h"

int main(int argc, char* argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <stage> <input_file> <output_file>\n", argv[0]);
        return 1;
    }
    
    if (strcmp(argv[1], "1") != 0) {
        fprintf(stderr, "Invalid stage: %s\n", argv[1]);
        return 1;
    }

    FILE* out_file = fopen(argv[3], "w");
    if (!out_file) {
        fprintf(stderr, "Cannot open output file %s\n", argv[3]);
        return 1;
    } else {
        fprintf(stderr, "Opened output file %s\n", argv[3]);
    }

    Node_t* head = read_csv(argv[2], out_file);
    
    int count = 0;
    Node_t* current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    printf("Total records read: %d\n", count);

    fclose(out_file);
    
    current = head;
    while (current != NULL) {
        Node_t* temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}