#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "math_utils.h"

typedef enum {INVALID, ONE_ARG, TWO_ARG} opType;
typedef struct {
    opType oper;
    const char *msg;
} opResult;

opResult parseExpr(char *expr, char **oper, long double *args, int *nArgs);
calcResult compute(const char *oper, long double *args);

#endif