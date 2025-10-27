#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <float.h>
#include <math.h>

#include "main_utils.h"
#include "math_utils.h"
#include "calculator.h"
#include "globals.h"

// args
int verbose = 0;

// envs
int sixseven = 0;


int main(int argc, char **argv, char **envp) {
    // arguments and env vars
    char *env_sixseven = getenv("SIXSEVEN");


    // argument parsing
    opterr = 0;  // disable automatic error messages
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

    // env var parsing
    

    if (verbose) {
        printf("Verbose mode enabled.\n");
    }

    if ((env_sixseven) && (env_sixseven[0] == '1')) {
        sixseven = 1;
        printf("You feel a terrible presence...\n");
    }

    printf("\n");

    // variables
    char input[1000];
    char *oper;
    calcResult cRes;
    opResult oRes;

    // now for the actual thingy!
    printf("C Calculator v%s\n", VERSION);
    printf("'help' for help!\n\n");

    while(1) {

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
        
        oRes = parseExpr(input, &oper, args, &nArgs);
        if (oRes.oper == INVALID) { printf("%s\n\n", oRes.msg); continue; }

        cRes = compute(oper, args);
        if (sixseven) cRes.value = 67;


        // Validate result
        if (!cRes.code) {
            printf("Error: %s\n\n", cRes.msg);
            continue;
        }

        // check if result overflowed
        if (!isfinite(cRes.value)) {
            printf("Overflow error: calculation too large to compute\n\n");
            continue;
        }

        // Finally, results!s
        printf("%s%.*Lg\n\n",
            verbose ? "Result: " : "", LDBL_DIG, cRes.value);
        continue;

    }
    
    return 0;
}
