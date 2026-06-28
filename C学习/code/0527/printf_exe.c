#include<stdio.h>

int main(){
	//printf练习 
	int a=65;
	float b=3.4;
	char c='a';
	char str[] = "好好学习";
	
	printf("整形a=%d\n",a);
	printf("字符串b=%f\n",b);
	printf("字符c=%c\n",c);
	printf("字符c=%c\n",a);
	printf("字符串str：%s\n", str);
	printf("16进制a=%x",a);
	printf("取地址a=%p",&a);
	
	
	return 0;
}