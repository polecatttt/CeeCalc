#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "math_utils.h"

typedef enum {INVALID, ONE_ARG, TWO_ARG} opType;

opType parseExpr(char *inp, char **op, long double *args, int *nArgs, int verbose);
Result compute(const char *oper, long double *args, int nArgs);

#endif