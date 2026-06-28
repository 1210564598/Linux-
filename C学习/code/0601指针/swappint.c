#include<stdio.h>

void swap(int *a,int *b){
	int tmp;
	tmp=*a;
	*a=*b;
	*b=tmp;
	
}

int main(){
	int a=10;
	int b=20;
	swap(&a,&b);
	printf("½»»»ÉíÌåa=%d,b=%d",a,b);
	
	return 0;
}