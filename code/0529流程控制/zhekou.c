#include<stdio.h>
	int main(){
	float zhekou;
	int s;
	puts("请输入的要购买的商品价值");
	scanf("%d",&s);
	if(s>0&&s<250){
		puts("没有折扣");
		
	}
	else if(s>=250&&s<500){
		zhekou=0.02;
		printf("折扣为%.2f\n",zhekou);
	}
	else if(s>=500&&s<1000){
		zhekou=0.05;
		printf("折扣为%.2f\n",zhekou);
		
	}
	else if(s>=1000&&s<2000){
		zhekou=0.08;
		printf("折扣为%.2f\n",zhekou);
	}
	else if(s>=2000&&s<3000){
		zhekou=0.10;
		printf("折扣为%.2f\n",zhekou);
	}
	else{
	 zhekou=0.15;
		printf("折扣为%f\n",zhekou);
	}
	
		return 0;
}