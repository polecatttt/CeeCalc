#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <float.h>
#include <math.h>

#define VERSION "5.1.0"


void flushBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


void help(void) {
    printf("== C Calculator %s ==\n\n", VERSION);
    printf("Add - add <num1> <num2>\n");
    printf("Subtract - sub <num1> <num2>\n");
    printf("Multiply - mul <num1> <num2>\n");
    printf("Divide - div <num1> <num2>\n");
    printf("Sine - sin <num>\n");
    printf("Cosine - cos <num>\n");
    printf("Tangent - tan <num>\n");
    printf("q - quit - but why tho :(\n\n");
    printf("== Flags ==\n");
    printf("Verbose (-v) prints extra output for debugging\n");
}


int main(int argc, char **argv) {

    // argument parsing
    opterr = 0;  // disable automatic error messages
    int verbose = 0;
    int opt;

    while ((opt = getopt(argc, argv, "v")) != -1) {
        switch (opt) {

            case 'v':
                verbose = 1;
                break;
            
            case '?':
                fprintf(stderr, "Unknown option: -%c\n", optopt);
                return 1;

        }
    }

    for (int i=optind; i < argc; i+=1) {
        printf("Option skipped: %s\n", argv[i]);
    }

    if (verbose) {
        printf("Verbose mode enabled.\n");
    }

    // used for input and calculations
    char input[1000];
    char *oper;
    long double num1, num2, result;

    // operations that take 1 arg
    static const char operOneArgs[3][10] = {
        "sin",
        "cos",
        "tan"
    };

    // operations that take 2 ars
    static const char operTwoArgs[5][10] = {
        "add",
        "sub",
        "mul",
        "div",
        "intdiv",
    };

    // size of above arrays
    static const int oneArgSize = sizeof(operOneArgs) / sizeof(operOneArgs[0]);
    static const int twoArgSize = sizeof(operTwoArgs) / sizeof(operTwoArgs[0]);

    // used to check which type of operation it should be at the validity check
    int expectedType;   // 0=invalid, 1=one arg, 2=two arg

    // now for the actual thingy!
    printf("C Calculator v%s\n", VERSION);
    printf("'help' for help!\n\n");

    while(1) {

        expectedType = 0;

        // user input
        printf("> ");
        if (!fgets(input, sizeof(input), stdin)) {
            fprintf(stderr, "Input Error: failed to read input\n");
            return 1;
        }

        // check if input was too long (no newline)
        if (strchr(input, '\n') == NULL) {
            printf("Input Error: too long, max 999 characters\n\n");
            flushBuffer();
            continue;
        }

        // removing newline, checking if quit or help
        input[strcspn(input, "\n")] = '\0';
        if (strcmp(input, "q") == 0) {
            if (verbose) printf("strcmp input, string 'q' passed\n");
            break;
        }

        if (strcmp(input, "help") == 0) {
            if (verbose) printf("strcmp input, string 'help' passed\n");
            help(); printf("\n"); continue; 
        }

        // tokenize expression
        char *token = strtok(input, " ");
        char *tokensArr[4];
        int nTokens = 0;

        while (token && nTokens < 4) {
            tokensArr[nTokens] = token;
            if (verbose) printf("Token %d = %s\n", nTokens, tokensArr[nTokens]);
            nTokens += 1;
            token = strtok(NULL, " ");
        }

        // oper validation
        oper = tokensArr[0];

        for (int i=0; i < oneArgSize; i+=1) {
            if (strcmp(oper, operOneArgs[i]) == 0) {
                expectedType = 1;
                if (verbose) printf("Expected type 1\n");
                break;
            }
        }

        for (int i=0; i < twoArgSize; i+=1) {
            if (strcmp(oper, operTwoArgs[i]) == 0) {
                expectedType = 2;
                if (verbose) printf("Expected type 2\n");
                break;
            }
        }

        if (expectedType == 0) {
            printf("Invalid Operator!\n\n");
            if (verbose) printf("Expected type %d, nTokens %d\n\n", expectedType, nTokens);
            continue;
        }

        // check size, args, etc.
        if ((expectedType == 1 && nTokens != 2) || (expectedType == 2 && nTokens != 3)) {
            if (verbose) printf("Expected type %d, nTokens %d\n\n", expectedType, nTokens);
            printf("Operation %s requires %d argument%s\n\n",
            oper, expectedType, expectedType == 1 ? " " : "s");
            continue;
        }

        // convert the args to numbers
        char *end;

        num1 = strtold(tokensArr[1], &end);
        if (end == tokensArr[1] || *end != '\0') {
            printf("Invalid number: %s\n\n", tokensArr[1]);
            continue;
        }

        if (expectedType == 2) {
            num2 = strtold(tokensArr[2], &end);
            if (end == tokensArr[2] || *end != '\0') {
                printf("Invalid number: %s\n\n", tokensArr[2]);
                continue;
            }
        }


        // calculation

        // 1 arg
        if (strcmp(oper, "add") == 0) { result = num1+num2; }
        else if (strcmp(oper, "sub") == 0) { result = num1-num2; }
        else if (strcmp(oper, "mul") == 0) { result = num1*num2; }
        else if (strcmp(oper, "div") == 0) {
            if (num2 == 0.0L) { printf("Division by zero error!\n\n"); continue; }
            result = num1/num2;
        }

        // 2 arg
        else if (strcmp(oper, "sin") == 0) { result = sinl(num1); }
        else if (strcmp(oper, "cos") == 0) { result = cosl(num1); }
        else if (strcmp(oper, "tan") == 0) { result = tanl(num1); }

        // default
        else { printf("Something has gone dearly wrong.\n\n"); continue; }


        // check if result overflowed
        if (!isfinite(result)) {
            printf("Overflow error: calculation too large to compute\n\n");
            continue;
        }

        // Finally, results!s
        printf("%s%.*Lg\n\n",
            verbose ? "Result: " : "", LDBL_DIG, result);
        continue;

    }
    
    return 0;
}
