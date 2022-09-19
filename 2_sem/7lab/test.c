#include <stdio.h>

int mul(int a, int b)
{
    return a*b;
}

int main()
{
    int (*fun)(int, int);
    fun = mul;
    printf("%d\n", fun(3, 4));
    return 0;
}