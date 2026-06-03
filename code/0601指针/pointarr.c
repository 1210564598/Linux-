#include<stdio.h>

int add(int a,int b){
	return a+b;
}
int sub(int a,int b){
	return a-b;
}
int mul(int a,int b){
	return a*b;
}

int main(){
	int a=10;
	int b=20;
	int (*p[3])(int,int)={add,sub,mul};
	for(int i=0;i<3;i++){
		printf("%d ",(*p[i])(a,b));
	}
	
	
	return 0;
}