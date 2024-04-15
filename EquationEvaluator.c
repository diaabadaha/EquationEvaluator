/* Diaa Badaha - 1210478 - sec3
 *
 * This is a C program to convert valid equations
 * from infix to prefix expression and evaluate it
 *
 * the program reads several equations from a file and lets
 * the user to choose what he needs from them
 *
 * */

#include <stdio.h>
#include <stdlib.h>
#include<string.h>

// Define struct node
typedef struct node {
    int element;
    struct node* next;
} node;

// Define typedef of stack as pointer to node
typedef node* stack;

// Prototypes of some functions used later
int isEmpty(stack s);
void pop(stack s);

// Function to pop every element in a stack
void makeEmpty(stack s) {
    if (s == NULL){
        printf("Out of space!");
    } else {
        while (!isEmpty(s)){
            pop(s);
        }
    }
}

// Function to create an empty new stack
stack createStack() {
    stack s;

    s = (struct node*)malloc(sizeof(struct node));

    if (s == NULL) {
        printf("Out of space!\n");
    }

    s->next = NULL;
    makeEmpty(s);

    return s;
}

// Function to push an element into a stack
void push(stack s, int element) {
    node* temp;
    temp = (stack)malloc(sizeof(struct node));

    if(temp == NULL) {
        printf("Out of space!\n");
    } else {
        temp->element = element;
        temp->next = s->next;
        s->next = temp;
    }
}

// Function to check if a stack is empty
int isEmpty(stack s) {
    return s->next == NULL;
}

// Function to pop an element from a stack
void pop(stack s) {
    node* firstCell;

    if (isEmpty(s)) {
        printf("Empty stack\n");
    } else {
        firstCell = s->next;
        s->next = s->next->next;
        free(firstCell);
    }
}

// Function to return top element of a stack
int top(stack s) {
    if (!isEmpty(s)) {
        return s->next->element;
    }
}

// Function to delete a stack completely from the memory
void disposeStack(stack s) {
    makeEmpty(s);
    free(s);
}

// Function to reverse elements of a stack
stack reverseStack(stack s) {
    stack reversed;
    reversed = createStack();

    // Temporary stack to ensure that the stack is not lost
    stack temp;
    temp = createStack();

    while(!isEmpty(s)) {
        push(reversed, top(s));
        push(temp, top(s));
        pop(s);
    }

    // Returning the original elements of the stack
    while(!isEmpty(temp)) {
        push(s, top(temp));
        pop(temp);
    }

    return reversed;
}

// Function to check if a character is opening parentheses
int isOpeningParentheses(char c) {
    if (c == '{' || c == '(' || c == '[') {
        return 1;
    }

    return 0;
}

// Function to check if a character is closing parentheses
int isClosingParentheses(char c) {
    if (c == '}' || c == ')' || c == ']') {
        return 1;
    }

    return 0;
}

// Function to check if a character is number
int isNumber(char c) {
    if (c >= 48 && c <= 57) {
        return 1;
    }

    return 0;
}

// Function to check if a character is operator
int isOperator(char c) {
    if (c == 42 || c == 43 || c == 45 || c == 47 || c == 94) {
        return 1;
    }

    return 0;
}

// Function to check if an operator have higher(or equal) priority than another operator
int isHigherOrEqual(char operator1, char operator2) {
    // Any operator has higher priority than an opening parentheses(in operators stack used later)
    if(isOpeningParentheses(operator2)) {
        return 1;
    }

    int priority1, priority2;

    // Set priorities of first operator
    if (operator1 == '+' || operator1 == '-') {
        priority1 = 1;
    } else if (operator1 == '*' || operator1 == '/' || operator1 == '%') {
        priority1 = 2;
    } else if (operator1 == '^') {
        priority1 = 3;
    } else {
        priority1 = 0;
    }

    // Set priorities of second operator
    if (operator2 == '+' || operator2 == '-') {
        priority2 = 1;
    } else if (operator2 == '*' || operator2 == '/') {
        priority2 = 2;
    } else if (operator2 == '^') {
        priority2 = 3;
    } else {
        priority2 = 0;
    }

    return priority1 >= priority2;
}

// Function to reverse a stack including flipping the brackets
stack reverseStackParentheses(stack s) {
    stack reversed;
    reversed = createStack();

    // Temporary stack to ensure that the stack is not lost
    stack temp;
    temp = createStack();

    while(!isEmpty(s)) {
         // Flipping opening brackets
        if (isOpeningParentheses(top(s))) {
            if(top(s) == '(') {
                push(reversed, ')');
            } else if (top(s) == '[') {
                push(reversed, ']');
            } else if (top(s) == '{') {
                push(reversed, '}');
            }

        // Flipping closing brackets
        } else if (isClosingParentheses(top(s))) {
            if(top(s) == ')') {
                push(reversed, '(');
            } else if (top(s) == ']') {
                push(reversed, '[');
            } else if (top(s) == '}') {
                push(reversed, '{');
            }
        } else {
            push(reversed, top(s));
        }

        push(temp, top(s));
        pop(s);
    }

    // Returning the original elements of the stack
    while(!isEmpty(temp)) {
        push(s, top(temp));
        pop(temp);
    }

    return reversed;
}

// Function to print a stack of an equation elements
void printStack(stack s) {
    stack temp = reverseStack(s);

    while(!isEmpty(temp)) {
        printf("%c", top(temp));
        pop(temp);
    }
    printf("\n");
}

void printStackToFile(stack s, FILE *ptr) {
    stack temp = reverseStack(s);

    while(!isEmpty(temp)) {
        fprintf(ptr, "%c", top(temp));
        pop(temp);
    }
}

// Function to print a stack of an integers
void printIntegersStack(stack s) {
    stack temp = reverseStack(s);

    int e;
    while(!isEmpty(temp)) {
        e = top(s);
        printf("%d", top(temp));
        pop(temp);
    }
    printf("\n");
}

// Function to convert a string to stack oh it's characters
stack stringToStack (char equation[]) {
    int equationLength = strlen(equation);

    stack s = NULL;
    s = createStack();

    for (int i = 0; i < equationLength; i++) {
        push(s, equation[i]);
    }

    return s;
}

// Function to check if the brackets in an equation are balanced
int isBalanced(stack s, int printingFlag) {
    stack s1;
    s1 = reverseStack(s);

    // Stack for opening brackets
    stack openingSymbolsStack;
    openingSymbolsStack = createStack();

    // Integer to specify the distance between a bracket and its corresponding bracket
    int n;

    while (!isEmpty(s1)) {
        // Filling opening brackets stack
        if (isOpeningParentheses(top(s1))) {
            push(openingSymbolsStack, top(s1));
            pop(s1);
        // Filing closing brackets stack
        } else if (isClosingParentheses(top(s1))) {
            if (isEmpty(openingSymbolsStack)) {
                if(printingFlag) {
                    printf("invalid: %c is not opened\n", top(s1));
                }
                return 0;
            }
            if (top(openingSymbolsStack) == '(') {
                    n = 1;
                } else {
                    n = 2;
                }

            // Checking if every opened bracket is closed
            if (top(s1) == top(openingSymbolsStack) + n) {
                pop(s1);
                pop(openingSymbolsStack);
                } else {
                    // Printing the reason of invalidity depending on the printing flag
                    if (printingFlag && !isEmpty(openingSymbolsStack)) {
                        printf("invalid: %c is not closed\n", top(openingSymbolsStack));
                    } else if (printingFlag && !isEmpty(s1)) {
                        printf("invalid: %c is not opened\n", top(s1));
                    }
                    return 0;
                }
        } else {
            pop(s1);
        }
    }

    if(!isEmpty(openingSymbolsStack)) {
        if(printingFlag) {
            printf("invalid: %c is not closed\n", top(openingSymbolsStack));
        }
        return 0;
    }

    return 1;
}

// Function to check if an equation(stack) is valid
int isValid(stack equation, int printingFlag) {
        if (isEmpty(equation)) {
            printf("Empty Stack!\n");
            return 0;
        }

        // Temporary stack to ensure that the stack is not lost
        stack stackToCheck = reverseStack(equation);

        // Stack to print the part if error in the equation
        stack stackToPrintErr = createStack();

        char c;
        while(!isEmpty(stackToCheck)) {
            c = top(stackToCheck);
            // The case which the equation contains an illegal character
            if(!isNumber(c) && !isOperator(c) && !isOpeningParentheses(c) && !isClosingParentheses(c)) {
                // Printing the reason of invalidity depending on the printing flag
                if(printingFlag) {
                    printf("invalid: There's an illegal character: %c\n", c);
                }
                return 0;
            }
            pop(stackToCheck);
        }

        // The case that the brackets in the equation are not balanced
        if(!isBalanced(equation, printingFlag)) {
            return 0;
        }

        // Making the temporary stack equals the original stack
        stackToCheck = reverseStack(reverseStack(equation));

        // The case which the equation ends with an operator
        if(isOperator(top(stackToCheck))) {
            // Printing the reason of invalidity depending on the printing flag
            if(printingFlag) {
                printf("invalid: The equation ends with an operator (%c)\n", top(equation));
            }
            return 0;
        }

        // Stack equals the reverse of the original one
        stack reversedEq = reverseStack(stackToCheck);
        makeEmpty(stackToCheck);

        // The case which the equation starts with an operator (negative sign is not included)
        if(top(reversedEq) == '+' || top(reversedEq) == '/' || top(reversedEq) == '*' || top(reversedEq) == '^') {
            // Printing the reason of invalidity depending on the printing flag
            if(printingFlag) {
                printf("invalid: The equation starts with an operator (%c)\n", top(reversedEq));
            }
            return 0;
        }

        stackToCheck = reverseStack(equation);

        while(!isEmpty(stackToCheck)) {
            if(isOperator(top(stackToCheck))) {
                push(stackToPrintErr, top(stackToCheck));
                pop(stackToCheck);

                if(top(stackToCheck) == '-') {
                    push(stackToPrintErr, top(stackToCheck));
                    pop(stackToCheck);
                    push(stackToPrintErr, top(stackToCheck));

                    // The case which there are more than two operators
                    if(isOperator(top(stackToCheck))) {
                        // Printing the reason of invalidity depending on the printing flag
                        if(printingFlag) {
                            printf("invalid: Too many operators: ");
                            printStack(stackToPrintErr);
                        }
                        return 0;
                    }
                }

                // The case which there's an operator with no number or opening parentheses after it
                if(!isNumber(top(stackToCheck)) && !isOpeningParentheses(top(stackToCheck)) && top(stackToCheck) != '-') {
                    push(stackToPrintErr, top(stackToCheck));
                    pop(stackToCheck);
                    push(stackToPrintErr, top(stackToCheck));

                    // Printing the reason of invalidity depending on the printing flag
                    if(printingFlag ) {
                        printf("invalid: There's an operator with no number or opening parentheses after it: ");
                        printStack(stackToPrintErr);
                    }
                        return 0;
                }
                // If the previous cases are false, make the error stack empty
                makeEmpty(stackToPrintErr);

            } else if(isNumber(top(stackToCheck))) {
                push(stackToPrintErr, top(stackToCheck));
                pop(stackToCheck);

                // The case which there are a number and parentheses with no operation between them
                if(isOpeningParentheses(top(stackToCheck))) {
                    push(stackToPrintErr, top(stackToCheck));
                    pop(stackToCheck);
                    push(stackToPrintErr, top(stackToCheck));

                    // Printing the reason of invalidity depending on the printing flag
                    if(printingFlag) {
                        printf("invalid: There's no operator between ");
                        printStack(stackToPrintErr);
                    }

                    return 0;
                }
                // If the previous case are false, make the error stack empty
                makeEmpty(stackToPrintErr);

            } else if(isOpeningParentheses(top(stackToCheck))) {
                push(stackToPrintErr, top(stackToCheck));
                pop(stackToCheck);

                // The case which there is an operator after an opening parenthesis
                if(top(stackToCheck) == '+' || top(stackToCheck) == '/' || top(stackToCheck) == '*' || top(stackToCheck) == '^') {
                    push(stackToPrintErr, top(stackToCheck));
                    pop(stackToCheck);
                    push(stackToPrintErr, top(stackToCheck));

                    // Printing the reason of invalidity depending on the printing flag
                    if(printingFlag) {
                        printf("invalid: There's an operator after an opening parentheses: ");
                        printStack(stackToPrintErr);
                    }

                    return 0;

                  // The case which there are two brackets with no data between them
                } else if(isClosingParentheses(top(stackToCheck))) {
                    push(stackToPrintErr, top(stackToCheck));
                    pop(stackToCheck);

                    // Printing the reason of invalidity depending on the printing flag
                    if(printingFlag) {
                        printf("invalid: There are two brackets with no data between them: ");
                        printStack(stackToPrintErr);
                    }

                    return 0;
                }
                // If the previous case are false, make the error stack empty
                makeEmpty(stackToPrintErr);

            } else if(isClosingParentheses(top(stackToCheck))) {
                push(stackToPrintErr, top(stackToCheck));
                pop(stackToCheck);

                // The case which there is no operator between a closing parentheses and (a number or an opening parentheses)
                if(isNumber(top(stackToCheck)) || isOpeningParentheses(top(stackToCheck))) {
                    push(stackToPrintErr, top(stackToCheck));
                    pop(stackToCheck);

                    // Printing the reason of invalidity depending on the printing flag
                    if(printingFlag) {
                        printf("invalid: There's no operator between ");
                        printStack(stackToPrintErr);
                    }
                    return 0;
                }
                // If the previous cases are false, make the error stack empty
                makeEmpty(stackToPrintErr);
            }

        }

        return 1;
    }

// Function to convert an equation from infix expression to prefix expression
stack infixToPrefix(stack s) {
    // Output(prefix expression) stack
    stack prefix = createStack();

    // Reversed stack to find the prefix expression
    stack reversed = reverseStackParentheses(s);
    reversed = reverseStack(reversed);

    // Operators stack
    stack operators = createStack();

    char temp;

    while(!isEmpty(reversed)) {
        temp = top(reversed);

        if(isNumber(top(reversed))) {
            push(prefix, top(reversed));
            pop(reversed);

            // Loop for pushing consecutive digits of a number
            while(isNumber(top(reversed))) {
                temp = top(reversed);
                push(prefix, top(reversed));
                pop(reversed);
            }

            // If there's no consecutive digits or a negative sign in a number, push a space to the output stack
            if(!isNumber(top(reversed)) && top(reversed) != '-') {
                push(prefix, ' ');
            }

        } else if (isOpeningParentheses(top(reversed))) {
            // Always push opening parentheses to the operators stack
            push(operators, top(reversed));
            pop(reversed);

        } else if (isClosingParentheses(top(reversed))) {
            // Popping operators stack till an opening bracket occurs
            while(!isOpeningParentheses(top(operators))) {
                push(prefix, top(operators));
                pop(operators);
                // Push a space to the output stack after each operation
                push(prefix, ' ');
            }

            // Pop remainder opening bracket from operations stack
            if(isOpeningParentheses(top(operators))) {
                pop(operators);
            }

            pop(reversed);

        } else if (isOperator(top(reversed))) {
            // Handling negative sign if it belongs to a number not an operation
            if (top(reversed) == '-') {
                pop(reversed);
                if(isClosingParentheses(top(reversed)) || isOperator(top(reversed)) || isEmpty(reversed)) {
                    // Push negative sign close to the number
                    push(prefix, '-');
                    push(prefix, ' ');
                } else {
                    push(reversed, '-');
                    push(prefix, ' ');

                    // If negative sign does not belong to a number not an operation, treat it as operator
                    if (isHigherOrEqual(top(reversed), top(operators))) {
                        push(operators, top(reversed));
                        pop(reversed);
                    } else {
                        // Popping operators stack till an operator with lower priority or an opening bracket occurs
                        while(!isHigherOrEqual(top(reversed), top(operators))) {
                            push(prefix, top(operators));
                            pop(operators);
                            push(prefix, ' ');
                        }

                        // Pushing operator to the operators stack if it has higher priority
                        if (isHigherOrEqual(top(reversed), top(operators))) {
                            push(operators, top(reversed));
                            pop(reversed);
                        }
                    }
                }

            } else {
                // Pushing operator to the operators stack if it has higher priority
                if (isHigherOrEqual(top(reversed), top(operators))) {
                        push(operators, top(reversed));
                        pop(reversed);
                    } else {
                        // Popping operators stack till an operator with lower priority or an opening bracket occurs
                        while(!isHigherOrEqual(top(reversed), top(operators))) {
                            push(prefix, top(operators));
                            pop(operators);
                            push(prefix, ' ');
                        }

                        // Pushing operator to the operators stack if it has higher priority
                        if (isHigherOrEqual(top(reversed), top(operators))) {
                            push(operators, top(reversed));
                            pop(reversed);
                        }
                    }
            }
        }
    }

    // Pushing remainder operators to the output stack
    while(!isEmpty(operators)) {
        push(prefix, top(operators));
        pop(operators);

        // Push a space after each operator in the output stack
        if(!isEmpty(operators)) {
            push(prefix, ' ');
        }
    }

    prefix = reverseStack(prefix);

    return prefix;
}

// Function to reverse a string
void reverseString(char* str) {
    int length = strlen(str);
    int i, j;
    char temp;

    for (i = 0, j = length - 1; i < j; i++, j--) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
}

// Function to make a string empty
void makeStringEmpty(char* str) {
    *str = '\0';
}

// Function to evaluate prefix expression of an equation
int evaluatePrefixExpression(stack prefix) {

    // Strings to store numbers temporarly
    char numberString[100] = "";
    char temp[2] = "";
    temp[1] = '\0';

    // Stack of numbers
    stack numbers = createStack();

    // Integer values to perform evaluation
    int n1, n2, tempResult;

    // Iterating elements of the equation
    while(!isEmpty(prefix)) {
        if(top(prefix) == ' ') {
            pop(prefix);

        // Converting numbers from characters to integers
        } else if(isNumber(top(prefix))) {
            do {
                // Concatenating consecutive digits and negative signs
                temp[0] = top(prefix);
                strcat(numberString, temp);
                pop(prefix);

            } while((isNumber(top(prefix)) || top(prefix) == '-') && !isEmpty(prefix));

            reverseString(numberString);
            push(numbers, atoi(numberString));  // Pushing converted numbers to numbers stack
            makeStringEmpty(numberString);

        // Pop two numbers and do the operation between them
        } else if (isOperator(top(prefix))) {
            n1 = top(numbers);
            pop(numbers);
            n2 = top(numbers);
            pop(numbers);

            // Doing operation between popped numbers
            if(top(prefix) == '+') {
                tempResult = n1 + n2;
            } else if (top(prefix) == '-') {
                tempResult = n1 - n2;
            } else if (top(prefix) == '*') {
                tempResult = n1 * n2;
            } else if (top(prefix) == '/') {
                tempResult = n1 / n2;
            } else if (top(prefix) == '^') {
                tempResult = n1 ^ n2;
            }

            push(numbers, tempResult);  // Push result to numbers stack

            pop(prefix);
        }
    }

    return top(numbers);
}

// Function to print menu
void printMenu() {
    printf("\nPlease choose one from these options:\n\n");
    printf("1- Read equations from input file.\n");
    printf("2- Check the validity of equations.\n");
    printf("3- Convert valid equations from infix to prefix.\n");
    printf("4- Evaluate the prefix expressions.\n");
    printf("5- Print invalid equations.\n");
    printf("6- Print all equations and the prefix expression to the output file.\n");
    printf("7- Exit.\n\n");
}

// Main function
int main() {
    printf("Welcome to the equations' operations program...\n\n");

    int menuChoice;
    int ReadingFlag = 0;
    int numberOfEquations = 0;  // The size of equations array(array of stacks)
    stack equationsArray[50];

    do {
        printMenu();

        // Reading menu choice from user
        scanf("%d", &menuChoice);

        switch (menuChoice) {
            case 1: {
                if (ReadingFlag == 0) {
                    printf("\nPlease enter the name of the input file: ");
                    FILE *f1_ptr;

                    // Reading input file name from user
                    char fileName[100];
                    scanf("%s", &fileName);

                    // Open input file in reading mode
                    f1_ptr = fopen(fileName, "r");

                    char c;
                    int index = 0;

                    // 2D array to store equations temporarly
                    char equations[50][200];

                    // Reading numbers from the input file
                    while (fscanf(f1_ptr, "%s", equations[index++]) != EOF) {
                        numberOfEquations++;  // The size of equations array(array of stacks)
                    }

                    // Converting each equation from string to stack
                    for (int i = 0; i < numberOfEquations; i++) {
                    equationsArray[i] = stringToStack(equations[i]);
                    }

                    printf("\nThe input file was read successfully..\n\n");

                    ReadingFlag++;

                    // Close input file
                    fclose(f1_ptr);
                } else {
                    printf ("The input file was already read..\n");
                }

                break;
            }
            case 2: {
                int printingFlag = 1;  // Flag to print invalidity reason

                // Printing if each equation is valid or not
                for (int i = 0; i < numberOfEquations; i++) {
                    printf("Equation No. %d ->", i+1);
                    if (isValid(equationsArray[i], 1)) {
                        printf("valid\n");
                    }
                }
                printf("\n");

                break;
            }
            case 3: {
                int validEquations = 0;  // Number of invalid equations

                for(int i = 0; i < numberOfEquations; i++) {
                    if(isValid(equationsArray[i], 0)) {
                        validEquations++;

                        // Printing equations
                        printf("Equation No. %d: ", i+1);
                        printStack(equationsArray[i]);
                        // Printing prefix expression
                        printf("Prefix expression: ");
                        printStack(infixToPrefix(equationsArray[i]));
                        printf("\n");
                    }
                }

                if(validEquations == 0) {
                    printf("There's no valid equations!\n\n");
                }

                break;
            }
            case 4: {
                // Printing evaluated prefix expression for each equation
                for(int i = 0; i < numberOfEquations; i++) {
                    if(isValid(equationsArray[i], 0)) {
                        printf("Equation No. %d -> ", i+1);
                        printf("%d\n", evaluatePrefixExpression((infixToPrefix(equationsArray[i]))));
                    }
                }
                break;
            }
            case 5: {
                // Printing invalid equations
                printf("Invalid equations:\n");
                for(int i = 0; i < numberOfEquations; i++) {
                    if(!isValid(equationsArray[i], 0)) {
                        printf("Equation No. %d: ", i+1);
                        printStack(equationsArray[i]);
                        printf("\n");
                    }

                }
                break;
            }
            case 6: {
                char fileName[50];
                printf("Please enter a name for the output file: ");
                scanf("%s", &fileName);  // Reading output file name from user

                // Open output file in writing mode
                FILE *fptr = fopen(fileName, "w");

                for(int i = 0; i < numberOfEquations; i++) {
                    // Printing equations to the file
                    fprintf(fptr, "Equation No. %d: ", i+1);
                    printStackToFile(equationsArray[i], fptr);
                    fprintf(fptr, " -> ");

                    if(isValid(equationsArray[i], 0)) {
                        // Printing validity of each equation to the file
                        fprintf(fptr, "Valid\n");

                        // Printing prefix expression of each equation to the file
                        fprintf(fptr, "Prefix expression: ");
                        printStackToFile(infixToPrefix(equationsArray[i]), fptr);

                        // Printing evaluated prefix expression of each equation to the file
                        fprintf(fptr, "\nPrefix evaluation result = ");
                        fprintf(fptr, "%d\n\n", evaluatePrefixExpression(infixToPrefix(equationsArray[i])));
                    } else {
                        // Printing invalidity of each equation to the file
                        fprintf(fptr, "Invalid\n\n");
                    }
                }

                printf("\nInformation about equations are printed to %s file successfully..\n", fileName);

                break;
            }
            case 7:
                // Deleting all stored equations from the memory
                for(int i = 0; i < numberOfEquations; i++) {
                    disposeStack(equationsArray[i]);
                }

                printf("\n\nThanks for using this program...\n\n\n");
                break;

            default:
                printf("\nInvalid option!\n");
                break;
        }

    } while (menuChoice != 7);

        return 0;
    }