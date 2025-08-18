#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "search.h"

#include "test.h"  

// 单个字符转8位二进制


char* char_turn_into_binary(char letter){
    int ascii = (int)letter;
    char *binary = malloc(9);
    assert(binary);
    for (int position = 7; position>= 0; position--){
        if (ascii & (1 << position)) {
    binary[7 - position] = '1';
} else {
    binary[7 - position] = '0';
}
    }
    binary[8]='\0';
    return binary;
}
char* string_into_binary(const char* whole_str){
    int str_len = strlen(whole_str);
    char* str_binary = malloc(str_len * 8 + 1);
    assert(str_binary);
    str_binary[0] = '\0';
    for(int str_index =0; str_index < str_len; str_index++){
        char * char_binary = char_turn_into_binary(whole_str[str_index]);
        strcat(str_binary, char_binary);
        free(char_binary);
    }
    return str_binary;
}


int count_bit(const char* a, const char* b){
    if (!a || !b) return 0; // 空指针检查
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i]) {
            return i + 1; // 返回第一个不匹配的位数（1-based）
        }
        i++;
    }
    return i+8; // 字符串完全相同或到达较短字符串的末尾，返回比较的位数
}

// 返回值改成了void
void compare_key(Node_t *head, char* input_key, FILE* out_file){
    // Exit if head or input_key is null
    if(!head || !input_key){
        return;
    }
    Node_t * curr_line = head;
    int result = 0;

    // Counters
    int node_comparisons = 0;
    int string_comparisons = 0;
    int bit_comparisons = 0;

    char *input_binary = string_into_binary(input_key);
    fprintf(out_file, "%s \n", input_key);
    while(curr_line){
        node_comparisons++; // 访问了一个节点
        char *curr_line_binary = string_into_binary(curr_line->data.EZI_ADD);
        if (!curr_line_binary) {
            free(input_binary);
            return; // 内存分配失败
        }
        string_comparisons++; // 访问了一个字符串
        
        bit_comparisons += count_bit(input_binary, curr_line_binary);

        if(strcmp(input_binary, curr_line_binary) == 0){
            result++;
            fprintf(out_file, "-->");
            char *every_field = (char *)&(curr_line->data);  

            // 处理前 33 个字符串字段
            for (int i = 0; i < NUM_COL-2; i++) {
                // 拷贝字符串
                every_field[MAX_CHAR - 1] = '\0';               // 确保结尾 '\0'
                fprintf(out_file, " %s: %s ||", field_names[i], every_field); 
                every_field += MAX_CHAR;// 跳到下一个字段
}

            // 处理数值字段
            
            fprintf(out_file," %s: %Lf ||", field_names[NUM_COL-2], curr_line->data.x);
            fprintf(out_file," %s: %Lf ||\n", field_names[NUM_COL-1], curr_line->data.y);
            fflush(out_file);
        }
        free(curr_line_binary);
        // 链接到下一个节点
        curr_line = curr_line->next;
    }
    free(input_binary);

    // 输出终端里的比较结果
    printf("--> %d records found - comparisons: ", result);
    printf("b%d ", bit_comparisons);
    printf("n%d ", node_comparisons);
    printf("s%d", string_comparisons);
    printf("\n");

}
