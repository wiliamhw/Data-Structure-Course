/* Infix to Postfix
https://www.spoj.com/problems/ONP/
Stack -> linked list
Guide:
https://www.includehelp.com/c/infix-to-postfix-conversion-using-stack-with-c-program.aspx
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct node {
    char key;
    struct node *next;
} node;

void push(node **head, char item);
char pop(node **head);
char *infixToPostfix(char *input, int len);
bool isOperator(char x);
bool isChar(char x);
int order(char x);

int main(void)
{
    int loop;
    scanf("%d", &loop);

    while (loop-- != 0) 
    {
        char *input = malloc(sizeof(char) * 401);
        scanf("%s", input);

        int len = strlen(input);
        // printf("Loop %d, input: %s\n", loop + 1, input);

        input = infixToPostfix(input, len);
        printf("%s\n", input);
        free(input);
    }

    return 0;
}

char *infixToPostfix(char *input, int len) 
{
    int i, j;
    i = j = 0;
    node *head = NULL;
    char *infix = calloc(len + 1, sizeof(char) * (len + 1));
    
    while (input[i] != '\0')
    {
        // printf("----- I = %d, Input = %c -----\n", i, input[i]);

        if (input[i] == '(') {
            push(&head, '(');
        }

        else if (isChar(input[i])) {
            infix[j++] = input[i];
        }

        else if (isOperator(input[i])) {
            char top = pop(&head);

            while (order(top) >= order(input[i])) {
                infix[j++] = top;
                top = pop(&head);
            }
            push(&head, top);
            push(&head, input[i]);
        }

        else if (input[i] == ')') {
            char top = pop(&head);

            while (top != '(') {
                infix[j++] = top;
                top = pop(&head);
            }
        }
        i++;
        // printf("ouput = %s\n", infix);
    }
    infix[j] = '\0';

    return infix;
}

int order(char x) {
    if (x == '^') return 3;
    else if (x == '*' || x == '/') return 2;
    else if (x == '+' || x == '-') return 1;
    else return 0;
}

bool isOperator(char x) {
    if (x == '+' || x == '-' || x == '*' || x == '/' || x == '^')
        return true;
    else return false;
}

bool isChar(char x)
{
    if (('A' <= x && x <= 'Z') || ('a' <= x && x <= 'z'))
        return true;
    else return false;
}

char pop(node **head)
{
    char tmp = '\0';

    if (*head)
    {
        node *trav = *head;
        tmp = trav->key;
        *head = trav->next;
        free(trav);
    }
    return tmp;
}

void push(node **head, char item)
{
    // Make new node
    node *newNode = malloc(sizeof(node));
    if (!newNode) return;
    newNode->key = item;

    // Insert node (push front)
    if (head) newNode->next = *head;
    else newNode->next = NULL;

    // Change head
    *head = newNode;
    return;
}