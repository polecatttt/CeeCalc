#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <float.h>
#include <math.h>

#include "main_utils.h"
#include "math_utils.h"
#include "calculator.h"


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
    long double num1, num2;
    Result r;

    // operations that take 1 arg
    static const char operOneArgs[3][10] = {
        "sin",
        "cos",
        "tan"
    };

    // operations that take 2 ars
    static const char operTwoArgs[4][10] = {
        "add",
        "sub",
        "mul",
        "div",
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

        // parse expression and compute
        long double args[2];
        int nArgs;
        
        opType type = parseExpr(input, &oper, args, &nArgs, verbose);
        if (type == INVALID) { printf("Invalid!\n\n"); continue; }

        Result r = compute(oper, args, nArgs);


        // Validate result
        if (!r.code) {
            printf("Error: %s\n\n", r.msg);
            continue;
        }

        // check if result overflowed
        if (!isfinite(r.value)) {
            printf("Overflow error: calculation too large to compute\n\n");
            continue;
        }

        // Finally, results!s
        printf("%s%.*Lg\n\n",
            verbose ? "Result: " : "", LDBL_DIG, r.value);
        continue;

    }
    
    return 0;
}
