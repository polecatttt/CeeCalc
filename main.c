#include <stdio.h>
#include <string.h>
#include <float.h>


void flushBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


int main(void) {
    char input[999];
    char oper;
    long double num1, num2, result;

    static const char validOpers[] = {'+', '-', '*', '/'};
    static const int validSize = sizeof(validOpers) / sizeof(validOpers[0]);
    int isValid;

    printf("C Calculator v4.0\n");
    printf("Operators: + - * /\n\n");

    while(1) {


        isValid = 0;

        // user input
        printf("Enter expression (or q to quit): ");
        if (!fgets(input, sizeof(input), stdin)) {
            printf("Input Error!\n");
            return 1;
        }

        // Removing newline, checking if quit
        input[strcspn(input, "\n")] = '\0';
        if (strcmp(input, "q") == 0) break;

        // parse expression
        if (sscanf(input, "%Lf %c %Lf", &num1, &oper, &num2) != 3) {
            printf("Invalid Expression!\n\n");
            flushBuffer();
            continue;
        }

        // check if operation is valid
        for (int i = 0; i < validSize; i+=1) {
            if (oper == validOpers[i]) {
                isValid = 1;
                break;
            }
        }

        if (!isValid) {
            printf("Invalid Operator!\n\n");
            continue;
        }

        // now time for the calculations!
        switch(oper) {
            case '+': result = num1+num2; break;
            case '-': result = num1-num2; break;
            case '*': result = num1*num2; break;
            case '/':
                if (num2 == 0.0L) {
                    printf("Division by zero error!\n\n");
                    continue;
                }
            default: printf("Something has gone dearly wrong."); continue;
        }

        printf("Result: %.*Lg\n\n", LDBL_DIG, result);
        continue;


    }

    return 0;
}