#include<stdio.h>
int main()
{
	int arry[10];
	arry[0]=1;
	arry[1]=1;
	for(int i=2;i<10;i++){
		arry[i]=arry[i-1]+arry[i-2];
		
	}
	
	for(int i=0;i<10;i++){
		
		printf("%d\t",arry[i]);
	}
	
}