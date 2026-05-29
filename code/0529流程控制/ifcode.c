#include<stdio.h>
	int main(){
		//if判断练习1
		int money;
		printf("请问你有多钱：");
		scanf("%d",&money);
		if(money>100){
			
			puts("你是个有钱人");
		}
		printf("测试完成\n");
		printf("测试结果%d",money>100);
		return 0;
	}