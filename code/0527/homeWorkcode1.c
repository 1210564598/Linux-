#include<stdio.h>
	int main(){
		int a;
		int b;
		printf("请输入两个数字空格隔开");
		scanf("%d %d",&a,&b);
		
		printf("两数之和%d+%d=%d\n",a,b,(a+b));
		printf("两数之差%d-%d=%d\n",a,b,(a-b));
		printf("两数之积%dx%d=%d\n",a,b,(a*b));
		printf("两数之除%d/%d=%.1f\n",a,b,((float)a/b));
		
		 return 0;
	}