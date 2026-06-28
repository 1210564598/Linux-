#include<stdio.h>
	int main(){
		char str[100];
		printf("请输入一行内容");
		gets(str);
		printf("你输入的内容是：");
		puts(str);
		puts("我是第二行");
		
		return 0;
	}