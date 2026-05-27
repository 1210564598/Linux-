#include<stdio.h>
	int main(){
		//scanf练习
		int age;
		float score;
		char NO;
		char name[20];
		
		
		printf("请输入你的年龄");
		scanf("%d",&age);
		
		printf("请输入你的得分");
		scanf("%f",&score);		
		
		printf("请输入你的号码");
		scanf(" %c",&NO);		
		
		printf("请输入你的姓名");
		scanf("%s",name);		
		
		printf("\n===== 输入结果 =====\n");
		printf("年龄：%d\n", age);
		printf("分数：%.2f\n", score);
		printf("号码：%c\n", NO);
		printf("姓名：%s\n", name);
		
		return 0;
	}
	