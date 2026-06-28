#include<stdio.h>

void Phello(){
	printf("======");
	printf("»¶Ó­µ½¼Ò");
}


int add(int a,int b){

	
	return a+b;
}

int main(){
	Phello();
	int x=1;
	int y=2;
	int ret;
	ret=add(x,y);
	printf("%d",ret);
	
	return 0;
}