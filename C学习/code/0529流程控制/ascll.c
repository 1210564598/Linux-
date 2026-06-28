#include<stdio.h>
	int main(){
		char ca;
		puts("请输入一个字符");
		scanf("%c",&ca);
		
		if(ca>=65&&ca<=90){
			ca=ca+32;
			printf("%c",ca);
		}else if(ca>=97&&ca<=122){
			printf("%c",ca);
		}else{
			puts("输入异常");
		}
		
		
		return 0;
		
	}