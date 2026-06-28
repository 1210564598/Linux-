#include<stdio.h>
	int main(){
		int score;
		int dengji;
		
		printf("请输入一个你的成绩：");
		scanf("%d",&score);
		if(score>=90&&score<=100){
			puts("你的成绩为A");
		}else if(score>=80&&score<=89){
			puts("你的成绩为B");
		}else if(score>=70&&score<=79){
			puts("你的成绩为C");
		}else if(score>=60&&score<=69){
			puts("你的成绩为D");
		}else if(score<=60&&score>=0){
			puts("你的成绩为E");
		}else{
			puts("输入的成绩非法，请重新输入");
		}
		
		return 0;
	}