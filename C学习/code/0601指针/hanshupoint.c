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
	int a=12;int b=3;
	int num;
	int (*p)(int,int);
	printf("请输入1，2，3中的一种将数字进行+-x的不同运算");
	scanf("%d",&num);
	switch(num){
		case 1:
			p=add;
		break;
		case 2:
			p=sub;
		break;
		case 3:
			p=mul;
		break;
		default:
		printf("输入异常");
		break;
	}
	printf("%d",p(a,b));
	
	
	return 0;
}