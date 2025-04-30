#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Stack {
    int top;
    unsigned capacity;
    char* array;
} st;

st* createStack(unsigned capacity) {
    st* stack = (st*)malloc(sizeof(st));
    if (!stack) return NULL;
    stack->top = -1;
    stack->capacity = capacity;
    stack->array = (char*)malloc(stack->capacity * sizeof(char));
    return stack;
}

int isEmpty(st* stack) {
    return stack->top == -1;
}

char peek(st* stack) {
    return stack->array[stack->top];
}

char pop(st* stack) {
    if (!isEmpty(stack))
        return stack->array[stack->top--];
    return '$';
}

void push(st* stack, char op) {
    stack->array[++stack->top] = op;
}

int isOperand(char ch) {
    return isalnum(ch); // Accept letters and digits
}

int Prec(char ch) {
    if (ch == '^') return 3;
    if (ch == '*' || ch == '/') return 2;
    if (ch == '+' || ch == '-') return 1;
    return 0;
}

void infixToPostfix(char* expr) {
    st* stack = createStack(strlen(expr));
    if (!stack) return;

    char result[strlen(expr) + 1];
    int j = 0;

    for (int i = 0; expr[i] != '\0'; i++) {
        char tok = expr[i];

        if (isOperand(tok)) {
            result[j++] = tok;
        }
        else if (tok == '(') {
            push(stack, tok);
        }
        else if (tok == ')') {
            while (!isEmpty(stack) && peek(stack) != '(') {
                result[j++] = pop(stack);
            }
            if (!isEmpty(stack) && peek(stack) == '(')
                pop(stack); // remove '('
        }
        else {
            while (!isEmpty(stack) &&
                  ((Prec(peek(stack)) > Prec(tok)) ||
                   (Prec(peek(stack)) == Prec(tok) && tok != '^'))) {
                result[j++] = pop(stack);
            }
            push(stack, tok);
        }
    }

    while (!isEmpty(stack)) {
        result[j++] = pop(stack);
    }

    result[j] = '\0'; // Null-terminate the string
    printf("%s\n", result);

    free(stack->array);
    free(stack);
}

int main() {
    char exp[100];
    scanf("%s", exp);
    infixToPostfix(exp);
    return 0;
}
