#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "test.h"

// Parse the CSV file 
// Make sure that double quotes and consecutive commas are handled correctly
// so that Null data are also displayed and the sequence of output is correct
static int parse_csv_line(char *line, char *fields[], int num_col) {
    int count = 0;
    char *ptr = line;

    // Read until the end of line or exceed the maximum number of columns
    while (*ptr && count < num_col) {
        // If starts with double quotes
        if (*ptr == '"') {
            ptr++; // Skip the starting quote
            fields[count] = ptr; // Store the next element after the starting quote
            while (*ptr && !(*ptr == '"' && (*(ptr+1) == ',' ||
                   *(ptr+1) == '\0' || *(ptr+1) == '\n'))) {
                ptr++;
            }
            // Ends until reach the null character
            if (*ptr == '"') { 
                *ptr = '\0'; 
                ptr++;
            }
            // Ends until reach the comma character
            if (*ptr == ',') { 
                *ptr = '\0'; 
                ptr++;
            }
        } 
        // Starts with other characters
        else {
            fields[count] = ptr;
            while (*ptr && *ptr != ',' && *ptr != '\n') {
                ptr++;
            }
            if (*ptr == ',') { 
                *ptr = '\0'; 
                ptr++;
            }
        }
        count++;
    }

    // If still not at the end of the line yet, set all the following 
    // field to be null character
    while (count < num_col) {
        fields[count++] = "";
    }

    return count;
}

Node_t* read_csv(char* filename, FILE* out_file) {
    FILE* file = fopen(filename, "r");
    if (!file) { // Check the file existance
        fprintf(stderr, "Error: File not found: %s\n", filename);
        return NULL;
    }

    if (!out_file) { // Check null pointer
        fprintf(stderr, "Error: Output file is NULL\n");
        fclose(file); 
        return NULL;
    }

    Node_t* head = NULL; // Set null pointer
    char line[MAX_LENGTH]; // Store every line

    // Read but skip the first line, do nothing with it
    if (!fgets(line, sizeof(line), file)) {
        fprintf(stderr, "Error: Empty file: %s\n", filename);
        fclose(file);
        return NULL;
    }

    int record_count = 0;
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0'; // 去掉换行符

        char *fields[NUM_COL]; // Create an array that store the elements with number of fields
        int field_count = parse_csv_line(line, fields, NUM_COL);

        Address_t addr = {0};

        for (int field = 0; field < field_count; field++) {
            char *token = fields[field];

            // 去掉前后空格
            while (*token == ' ') token++;
            char *end = token + strlen(token) - 1;
            while (end > token && *end == ' ') end--;
            *(end + 1) = '\0';

            switch (field) {
                case 0: strncpy(addr.PFI, token, MAX_LEN_NUM-1); addr.PFI[MAX_LEN_NUM-1] = '\0'; break;
                case 1: strncpy(addr.EZI_ADD, token, MAX_CHAR-1); addr.EZI_ADD[MAX_CHAR-1] = '\0'; break;
                case 2: strncpy(addr.SRC_VERIF, token, MAX_CHAR-1); addr.SRC_VERIF[MAX_CHAR-1] = '\0'; break;
                case 3: strncpy(addr.PROPSTATUS, token, MAX_CHAR-1); addr.PROPSTATUS[MAX_CHAR-1] = '\0'; break;
                case 4: strncpy(addr.GCODEFEAT, token, MAX_CHAR-1); addr.GCODEFEAT[MAX_CHAR-1] = '\0'; break;
                case 5: strncpy(addr.LOC_DESC, token, MAX_CHAR-1); addr.LOC_DESC[MAX_CHAR-1] = '\0'; break;
                case 6: strncpy(addr.BLGUNTTYP, token, MAX_CHAR-1); addr.BLGUNTTYP[MAX_CHAR-1] = '\0'; break;
                case 7: strncpy(addr.HSAUNITID, token, MAX_CHAR-1); addr.HSAUNITID[MAX_CHAR-1] = '\0'; break;
                case 8: strncpy(addr.BUNIT_PRE1, token, MAX_CHAR-1); addr.BUNIT_PRE1[MAX_CHAR-1] = '\0'; break;
                case 9: strncpy(addr.BUNIT_ID1, token, MAX_CHAR-1); addr.BUNIT_ID1[MAX_CHAR-1] = '\0'; break;
                case 10: strncpy(addr.BUNIT_SUF1, token, MAX_CHAR-1); addr.BUNIT_SUF1[MAX_CHAR-1] = '\0'; break;
                case 11: strncpy(addr.BUNIT_PRE2, token, MAX_CHAR-1); addr.BUNIT_PRE2[MAX_CHAR-1] = '\0'; break;
                case 12: strncpy(addr.BUNIT_ID2, token, MAX_CHAR-1); addr.BUNIT_ID2[MAX_CHAR-1] = '\0'; break;
                case 13: strncpy(addr.BUNIT_SUF2, token, MAX_CHAR-1); addr.BUNIT_SUF2[MAX_CHAR-1] = '\0'; break;
                case 14: strncpy(addr.FLOOR_TYPE, token, MAX_CHAR-1); addr.FLOOR_TYPE[MAX_CHAR-1] = '\0'; break;
                case 15: strncpy(addr.FLOOR_NO_1, token, MAX_CHAR-1); addr.FLOOR_NO_1[MAX_CHAR-1] = '\0'; break;
                case 16: strncpy(addr.FLOOR_NO_2, token, MAX_CHAR-1); addr.FLOOR_NO_2[MAX_CHAR-1] = '\0'; break;
                case 17: strncpy(addr.BUILDING, token, MAX_CHAR-1); addr.BUILDING[MAX_CHAR-1] = '\0'; break;
                case 18: strncpy(addr.COMPLEX, token, MAX_CHAR-1); addr.COMPLEX[MAX_CHAR-1] = '\0'; break;
                case 19: strncpy(addr.HSE_PREF1, token, MAX_CHAR-1); addr.HSE_PREF1[MAX_CHAR-1] = '\0'; break;
                case 20: strncpy(addr.HSE_NUM1, token, MAX_CHAR-1); addr.HSE_NUM1[MAX_CHAR-1] = '\0'; break;
                case 21: strncpy(addr.HSE_SUF1, token, MAX_CHAR-1); addr.HSE_SUF1[MAX_CHAR-1] = '\0'; break;
                case 22: strncpy(addr.HSE_PREF2, token, MAX_CHAR-1); addr.HSE_PREF2[MAX_CHAR-1] = '\0'; break;
                case 23: strncpy(addr.HSE_NUM2, token, MAX_CHAR-1); addr.HSE_NUM2[MAX_CHAR-1] = '\0'; break;
                case 24: strncpy(addr.HSE_SUF2, token, MAX_CHAR-1); addr.HSE_SUF2[MAX_CHAR-1] = '\0'; break;
                case 25: strncpy(addr.DISP_NUM1, token, MAX_CHAR-1); addr.DISP_NUM1[MAX_CHAR-1] = '\0'; break;
                case 26: strncpy(addr.ROAD_NAME, token, MAX_CHAR-1); addr.ROAD_NAME[MAX_CHAR-1] = '\0'; break;
                case 27: strncpy(addr.ROAD_TYPE, token, MAX_CHAR-1); addr.ROAD_TYPE[MAX_CHAR-1] = '\0'; break;
                case 28: strncpy(addr.RD_SUF, token, MAX_CHAR-1); addr.RD_SUF[MAX_CHAR-1] = '\0'; break;
                case 29: strncpy(addr.LOCALITY, token, MAX_CHAR-1); addr.LOCALITY[MAX_CHAR-1] = '\0'; break;
                case 30: strncpy(addr.STATE, token, MAX_CHAR-1); addr.STATE[MAX_CHAR-1] = '\0'; break;
                case 31: strncpy(addr.POSTCODE, token, MAX_CHAR-1); addr.POSTCODE[MAX_CHAR-1] = '\0'; break;
                case 32: strncpy(addr.ACCESSTYPE, token, MAX_CHAR-1); addr.ACCESSTYPE[MAX_CHAR-1] = '\0'; break;
                case 33: strncpy(addr.x, token, MAX_CHAR-1); addr.x[MAX_CHAR-1] = '\0'; break;
                case 34: strncpy(addr.y, token, MAX_CHAR-1); addr.y[MAX_CHAR-1] = '\0'; break;
            }
        }

        // 输出
        fprintf(out_file,
                "--> PFI: %s || EZI_ADD: %s || SRC_VERIF: %s || PROPSTATUS: %s || GCODEFEAT: %s || "
                "LOC_DESC: %s || BLGUNTTYP: %s || HSAUNITID: %s || BUNIT_PRE1: %s || BUNIT_ID1: %s || "
                "BUNIT_SUF1: %s || BUNIT_PRE2: %s || BUNIT_ID2: %s || BUNIT_SUF2: %s || FLOOR_TYPE: %s || "
                "FLOOR_NO_1: %s || FLOOR_NO_2: %s || BUILDING: %s || COMPLEX: %s || HSE_PREF1: %s || "
                "HSE_NUM1: %s || HSE_SUF1: %s || HSE_PREF2: %s || HSE_NUM2: %s || HSE_SUF2: %s || "
                "DISP_NUM1: %s || ROAD_NAME: %s || ROAD_TYPE: %s || RD_SUF: %s || LOCALITY: %s || "
                "STATE: %s || POSTCODE: %s || ACCESSTYPE: %s || x: %s || y: %s ||\n",
                addr.PFI, addr.EZI_ADD, addr.SRC_VERIF, addr.PROPSTATUS, addr.GCODEFEAT,
                addr.LOC_DESC, addr.BLGUNTTYP, addr.HSAUNITID, addr.BUNIT_PRE1, addr.BUNIT_ID1,
                addr.BUNIT_SUF1, addr.BUNIT_PRE2, addr.BUNIT_ID2, addr.BUNIT_SUF2, addr.FLOOR_TYPE,
                addr.FLOOR_NO_1, addr.FLOOR_NO_2, addr.BUILDING, addr.COMPLEX, addr.HSE_PREF1,
                addr.HSE_NUM1, addr.HSE_SUF1, addr.HSE_PREF2, addr.HSE_NUM2, addr.HSE_SUF2,
                addr.DISP_NUM1, addr.ROAD_NAME, addr.ROAD_TYPE, addr.RD_SUF, addr.LOCALITY,
                addr.STATE, addr.POSTCODE, addr.ACCESSTYPE, addr.x, addr.y);

        // 链表节点
        Node_t* new_node = create_node(&addr);
        if (new_node) {
            new_node->next = head;
            head = new_node;
        } else {
            fprintf(stderr, "Error: Failed to create node for record %d\n", record_count + 1);
        }

        record_count++;
    }

    fclose(file);
    return head;
}

Node_t* create_node(Address_t* address) {
    // 1.Assign space for node
    Node_t* new_node = (Node_t*)malloc(sizeof(Node_t));

    // 2.Check if allocation suceeded
    if (!new_node) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(1);
    }

    // 3.Initialize node
    new_node->data = *address;
    new_node->next = NULL;

    // 4.Return node
    return new_node;
}
