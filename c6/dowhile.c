#include <stdio.h>

int main()
{
    int n;
    int i;
    n=0;
    i=10;
    do {
        n = n + 1;
    } while (n <= i);
    printf("%d\n",n);
    return 0;
}