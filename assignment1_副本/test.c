
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CHAR 128
#define MAX_LENGTH 512

typedef struct Address {
    char PFI[MAX_CHAR];
    char EZI_ADD[MAX_CHAR];
    char SRC_VERIF[MAX_CHAR];
    char PROPSTATUS[MAX_CHAR];
    char GCODEFEAT[MAX_CHAR];
    char LOC_DESC[MAX_CHAR];
    char BLGUNTTYP[MAX_CHAR];
    char HSAUNITID[MAX_CHAR];
    char BUNIT_PRE1[MAX_CHAR];
    char BUNIT_ID1[MAX_CHAR];
    char BUNIT_SUF1[MAX_CHAR];
    char BUNIT_PRE2[MAX_CHAR];
    char BUNIT_ID2[MAX_CHAR];
    char BUNIT_SUF2[MAX_CHAR];
    char FLOOR_TYPE[MAX_CHAR];
    char FLOOR_NO_1[MAX_CHAR];
    char FLOOR_NO_2[MAX_CHAR];
    char BUILDING[MAX_CHAR];
    char COMPLEX[MAX_CHAR];
    char HSE_PREF1[MAX_CHAR];
    char HSE_NUM1[MAX_CHAR];
    char HSE_SUF1[MAX_CHAR];
    char HSE_PREF2[MAX_CHAR];
    char HSE_NUM2[MAX_CHAR];
    char HSE_SUF2[MAX_CHAR];
    char DISP_NUM1[MAX_CHAR];
    char ROAD_NAME[MAX_CHAR];
    char ROAD_TYPE[MAX_CHAR];
    char RD_SUF[MAX_CHAR];
    char LOCALITY[MAX_CHAR];
    char STATE[MAX_CHAR];
    char POSTCODE[MAX_CHAR];
    char ACCESSTYPE[MAX_CHAR];
    char x[MAX_CHAR];
    char y[MAX_CHAR];
} Address;

typedef struct Node {
    Address data;
    struct Node* next;
} Node;


Node* read_csv(char* filename, FILE* out_file) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error: File not found\n");
        return NULL;
    }
    Node* head = NULL;
    char line[MAX_LENGTH];

    
    return head;
}


Node* create_node(Address* address) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(1);
    }
    new_node->data = *address;
    new_node->next = NULL;
    return new_node;
}


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

    Node* head = read_csv(argv[2], out_file);
    
    int count = 0;
    Node* current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    printf("Total records read: %d\n", count);

    fclose(out_file);
    
    current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}