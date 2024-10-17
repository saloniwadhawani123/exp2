#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX 100  // Define maximum size for stack

char stack[MAX];  // Stack array for operators
int top = -1;     // Top of the stack

// Function to push an element onto the stack
void push(char ch) {
    if (top == MAX - 1) {
        printf("Stack Overflow!\n");
    } else {
        stack[++top] = ch;
    }
}

// Function to pop an element from the stack
char pop() {
    if (top == -1) {
        printf("Stack Underflow!\n");
        return -1;
    } else {
        return stack[top--];
    }
}

// Function to check precedence of operators
int precedence(char ch) {
    switch (ch) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        default:
            return 0;
    }
}

// Function to check if character is an operator
int isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^');
}

// Function to convert infix to postfix
void infixToPostfix(char* infix, char* postfix) {
    int i = 0, j = 0;
    char ch;

    while (infix[i] != '\0') {
        ch = infix[i];

        // If the character is an operand, add it to the postfix expression
        if (isalnum(ch)) {
            postfix[j++] = ch;
        }
        // If the character is '(', push it to the stack
        else if (ch == '(') {
            push(ch);
        }
        // If the character is ')', pop and output from the stack until '(' is found
        else if (ch == ')') {
            while (top != -1 && stack[top] != '(') {
                postfix[j++] = pop();
            }
            pop();  // Pop '(' from the stack
        }
        // If the character is an operator
        else if (isOperator(ch)) {
            while (top != -1 && precedence(stack[top]) >= precedence(ch)) {
                postfix[j++] = pop();
            }
            push(ch);
        }

        i++;
    }

    // Pop all remaining operators from the stack
    while (top != -1) {
        postfix[j++] = pop();
    }

    postfix[j] = '\0';  // Null-terminate the postfix expression
}

int main() {
    char infix[MAX], postfix[MAX];

    // Input the infix expression
    printf("Enter an infix expression: ");
    scanf("%s", infix);

    // Convert infix to postfix
    infixToPostfix(infix, postfix);

    // Output the postfix expression
    printf("Postfix expression: %s\n", postfix);

    return 0;
}
