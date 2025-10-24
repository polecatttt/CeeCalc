#ifndef MATH_UTILS_H
#define MATH_UTILS_H

typedef struct {
    int code;
    const char *msg;
    long double value;
} Result;

Result add(long double a, long double b);
Result sub(long double a, long double b);
Result multiply(long double a, long double b);
Result divide(long double a, long double b);

Result sine(long double num);
Result cosine(long double num);
Result tangent(long double num);

#endif