#include<stdio.h>

int main(){
	int s;
	int i;
	i = 0;
	s = 1;
	do {
		s = i + s;
		i = i + 1;
		printf("do while: s=%d i=%d\n",s,i);
	} while(i < 10);
	printf("s=%d i=%d\n",s,i);
	
	for (i = 0; i < 10; i = i + 1){
		s = i + s;
		i = i + 1;
		printf("for: s=%d i=%d\n",s,i);
	}
	
	return 0;
}