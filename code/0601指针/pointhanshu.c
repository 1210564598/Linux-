#include<stdio.h>

int *pArr(int *a,int *b){
	
	return (*a>*b)?a:b;
}

int main(){
	int a =10;
	int b=20;
	int *p=pArr(&a,&b);
	printf("%d",*p);
	
	
	return 0;
}