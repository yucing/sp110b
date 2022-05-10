#include<stdio.h>
int main(){
    int s;
    int i;
    s=0;
    i=1;
    while ( i <= 10 ) {
        s = s + i;
        i++;
    }

    printf("%d\n",s);
}