#include<stdio.h>
	int main(){
		//getchar()/putchar()练习
		char ar;
		
		printf("请输入一个字符：");
		ar = getchar();
		
		printf("你输出的字符是：");
		putchar(ar);
		putchar('\n');
		return 0;
	}