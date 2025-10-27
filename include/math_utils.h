#ifndef MATH_UTILS_H
#define MATH_UTILS_H

typedef struct {
    int code;
    const char *msg;
    long double value;
} calcResult;

calcResult add(long double a, long double b);
calcResult sub(long double a, long double b);
calcResult multiply(long double a, long double b);
calcResult divide(long double a, long double b);

calcResult sine(long double num);
calcResult cosine(long double num);
calcResult tangent(long double num);

#endif