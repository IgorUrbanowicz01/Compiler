#include <stdio.h>
#include <stdlib.h>
#include "addOperation.h"

int main(int argc, char *argv[])
{
    // check for correct number of arguments
    if (argc != 2)
    {
        printf("Usage: %s <file>\n", argv[0]);
        return 1;
    }

    // open input file
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Error: Could not open file %s\n", argv[1]);
        return 1;
    }
    int line;
    struct CodeList *list = (struct CodeList *)malloc(sizeof(struct CodeList *));
    init_code_list(list);
    /*add_line(list, "GET", "1");
    add_line(list, "GET", "2");
    add_line(list, "SET", "1");
    add_line(list, "STORE", "10");
    add_line(list, "SET", "49");
    add_line(list, "STORE", "8");

    input = fopen("divide", "r");
    add_Operation_to_list(list, input);
    line = get_last_line_index(list) + 1;
    printf("%d <--- line where divide ends\n", line);
    add_line(list, "PUT", "3");*/

    /*END DIV ---------------------------- START MOD*/

    /*add_line(list, "SET", "95");
    add_line(list, "STORE", "8");
    input = fopen("mod", "r");
    add_Operation_to_list(list, input);
    line = get_last_line_index(list) + 1;
    add_line(list, "PUT", "3");
    printf("%d <--- line where divide starts\n", line);*/

    /*END MOD ------------------------------- START MUL*/

    /*add_line(list, "SET", "127");
    add_line(list, "STORE", "8");
    input = fopen("mul", "r");
    add_Operation_to_list(list, input);
    line = get_last_line_index(list) + 1;
    printf("%d <--- line where divide ends\n", line);
    add_line(list, "PUT", "3");
    add_line(list, "HALT", NULL);*/

    add_line(list, "JUMP", "12");
    line = get_last_line_index(list) + 1;
    printf("%d <--- line where divide starts\n", line);
    add_Operation_to_list(list, "divide");

    line = get_last_line_index(list) + 1;
    printf("%d <--- line where mod starts\n", line);
    add_Operation_to_list(list, "mod");

    line = get_last_line_index(list) + 1;
    printf("%d <--- line where mul starts\n", line);
    add_Operation_to_list(list, "mul");
    line = get_last_line_index(list) + 1;
    printf("%d <--- line where divide ENDS\n", line);
    print_code_list(list);

    return 0;
}