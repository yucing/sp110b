#include<stdio.h>

int main(int argc, char * argv[])
{
    for(int i=0;i<argc;i++) printf("argv[%d]=%s\n",i,argv[i]);

    return 0;
}

// argc : 輸入的字串大小
// argv : 字串