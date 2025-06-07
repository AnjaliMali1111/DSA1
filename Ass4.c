#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

// Stack structure
struct Stack {
    int arr[MAX];
    int top;
};

// Stack functions
void initStack(struct Stack* stack) {
    stack->top = -1;
}

int isFull(struct Stack* stack) {
    return stack->top == MAX - 1;
}

int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

void push(struct Stack* stack, int value) {
    if (isFull(stack)) {
        printf("Stack Overflow\n");
    } else {
        stack->arr[++(stack->top)] = value;
    }
}

int pop(struct Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack Underflow\n");
        return -1; // Error value
    } else {
        return stack->arr[(stack->top)--];
    }
}

int peek(struct Stack* stack) {
    if (isEmpty(stack)) {
        return -1; // Error value
    } else {
        return stack->arr[stack->top];
    }
}

// Function to check precedence of operators
int precedence(char c) {
    if (c == '+' || c == '-') return 1;
    if (c == '*' || c == '/') return 2;
    return 0;
}

// Infix to Postfix conversion
void infixToPostfix(char* infix, char* postfix) {
    struct Stack stack;
    initStack(&stack);
    int i, k = 0;
    for (i = 0; infix[i] != '\0'; i++) {
        char ch = infix[i];

        // If operand, add to postfix expression
        if (isalnum(ch)) {
            postfix[k++] = ch;
        }
        // If '(', push to stack
        else if (ch == '(') {
            push(&stack, ch);
        }
        // If ')', pop until '('
        else if (ch == ')') {
            while (!isEmpty(&stack) && peek(&stack) != '(') {
                postfix[k++] = pop(&stack);
            }
            pop(&stack); // Remove '('
        }
        // If operator, pop from stack based on precedence and push the current operator
        else {
            while (!isEmpty(&stack) && precedence(peek(&stack)) >= precedence(ch)) {
                postfix[k++] = pop(&stack);
            }
            push(&stack, ch);
        }
    }

    // Pop remaining operators from stack
    while (!isEmpty(&stack)) {
        postfix[k++] = pop(&stack);
    }
    postfix[k] = '\0'; // Null-terminate the string
}

// Postfix Evaluation
int evaluatePostfix(char* postfix) {
    struct Stack stack;
    initStack(&stack);
    int i;
    for (i = 0; postfix[i] != '\0'; i++) {
        char ch = postfix[i];

        // If operand, push to stack
        if (isalnum(ch)) {
            push(&stack, ch - '0'); // Convert char to int
        }
        // If operator, pop operands and perform operation
        else {
            int b = pop(&stack);
            int a = pop(&stack);
            int result;

            switch (ch) {
                case '+': result = a + b; break;
                case '-': result = a - b; break;
                case '*': result = a * b; break;
                case '/': result = a / b; break;
            }

            push(&stack, result);
        }
    }

    // The result will be the last element in the stack
    return pop(&stack);
}

int main() {
    char infix[MAX], postfix[MAX];
    
    // Input infix expression
    printf("Enter an infix expression: ");
    fgets(infix, MAX, stdin);
    
    // Remove newline character from input
    infix[strcspn(infix, "\n")] = '\0';

    // Convert infix to postfix
    infixToPostfix(infix, postfix);
    printf("Postfix Expression: %s\n", postfix);

    // Evaluate postfix expression
    int result = evaluatePostfix(postfix);
    printf("Evaluation Result: %d\n", result);

    return 0;
}
