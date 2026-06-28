#include<stdio.h>
	int main(){
		char a1;
		char a2;
		char a3;
		char a4;
		char a5;

		printf("请输入第一个字符a1:");
		scanf("%c",&a1);
		
		printf("请输入第一个字符a2:");
		scanf(" %c",&a2);
		
		printf("请输入第一个字符a3:");
		scanf(" %c",&a3);
		
		printf("请输入第一个字符a4:");
		scanf(" %c",&a4);
		
		printf("请输入第一个字符a5:");
		scanf(" %c",&a5);
		
		printf("a1=%c\na2=%c\na3=%c\na4=%c\na5=%c\n",a1,a2,a3,a4,a5);
		
		printf("a1=%d\na2=%d\na3=%d\na4=%d\na5=%d\n",a1,a2,a3,a4,a5);
	//China=a1=67，a2=104，a3=105，a4=110，a5=97
	//GImre=a1=71，a2=73，a3=109，a4=114，a5=101
		
		
		printf("%c%c%c%c%c=%c%c%c%c%c\n",a1,a2,a3,a4,a5,a1+4,a2-31,a3+4,a4+4,a5+4);
		
		a1=a1+4;
		a2=a2-31;
		a3=a3+4;
		a4=a4+4;
		a5=a5+4;
		putchar(a1);
		putchar(a2);
		putchar(a3);
		putchar(a4);
		putchar(a5);
	
		
		return 0;
	}