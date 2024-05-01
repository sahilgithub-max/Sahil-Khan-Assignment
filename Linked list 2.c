#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum ListType 
{
    INT = 0,
    FLOAT,
    CHAR,
    STRING,
};

union ListData
{
    int d;
    float f;
    char c;
    char *str;
};

struct Node
{
    struct Node *next;
    enum ListType type;
    union ListData data;
};

void printNode(struct Node *p)
{
    switch (p->type)
    {
        case INT:
            printf("%d ", p->data.d);
            break;
        case FLOAT:
            printf("%f ", p->data.f);
            break;
        case CHAR:
            printf("%c ", p->data.c);
            break;
        case STRING:
            printf("%s ", p->data.str);
            break;
        default:
            printf("ERROR ");
            break;
    }
}

void printList(struct Node *p)
{
    while(p)
    {
        printNode(p);
        p = p->next;
    }
}

void freeListStrings(struct Node *p)
{
    while(p)
    {
        if (p->type == STRING) free(p->data.str);
        p = p->next;
    }
}

int main(void) {
    struct Node *head = NULL;
    struct Node *prev = NULL;
    struct Node *current;

    char input[100];
    int value_i;
    float value_f;
    char value_c;
    char *value_str;

    while (1) {
        printf("Enter the type of data to add (int, float, char, string), or 'done' to finish: ");
        scanf("%s", input);

        if (strcmp(input, "done") == 0)
            break;

        current = malloc(sizeof(struct Node));
        if (current == NULL) {
            printf("Memory allocation failed\n");
            return 1;
        }

        if (strcmp(input, "int") == 0) {
            current->type = INT;
            printf("Enter integer value: ");
            scanf("%d", &value_i);
            current->data.d = value_i;
        } else if (strcmp(input, "float") == 0) {
            current->type = FLOAT;
            printf("Enter float value: ");
            scanf("%f", &value_f);
            current->data.f = value_f;
        } else if (strcmp(input, "char") == 0) {
            current->type = CHAR;
            printf("Enter character value: ");
            scanf(" %c", &value_c); 
            current->data.c = value_c;
        } else if (strcmp(input, "string") == 0) {
            current->type = STRING;
            printf("Enter string value: ");
            value_str = malloc(100 * sizeof(char)); 
            scanf("%s", value_str);
            current->data.str = value_str;
        } else {
            printf("Invalid input. Please enter 'int', 'float', 'char', 'string', or 'done'.\n");
            free(current);
            continue;
        }

        current->next = NULL;
        if (prev == NULL) {
            head = current;
        } else {
            prev->next = current;
        }
        prev = current;
    }

    printList(head);
    freeListStrings(head);

    current = head;
    while (current != NULL) {
        struct Node *next = current->next;
        free(current);
        current = next;
    }

    return 0;
}
