#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "search.h"

int main(int argc, char* argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <stage> <input_file> <output_file>\n", argv[0]);
        return 1;
    }
    
    if (strcmp(argv[1], "1") != 0) {
        fprintf(stderr, "Invalid stage: %s\n", argv[1]);
        return 1;
    }

    FILE* out_file = fopen(argv[3], "a");// w改成a，持续接受输出
    if (!out_file) {
        fprintf(stderr, "Cannot open output file %s\n", argv[3]);
        return 1;
    } else {
        fprintf(stderr, "Opened output file %s\n", argv[3]);
    }
    Node_t* head = read_csv(argv[2], NULL); 
    char keyword[MAX_CHAR];

    while(1){
        fflush(stdout);
        if(fgets(keyword, MAX_CHAR, stdin) == NULL){
            break;

        }//这里可以去掉？
        keyword[strcspn(keyword, "\n")] = '\0';
        // printf("%s\n", keyword);  这句我觉得可以去了，相当于把输入的句子重新又在终端输出一遍
        printf("%s ", keyword);
        // 修改了一下返回值和具体细节操作
        compare_key(head, keyword, out_file);

    }

    
    // 不确定我们需不需要记录节点总数
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