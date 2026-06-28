#include<stdio.h>
	int main(){
		int data1;
		int data2;
		int datatmp;
		
		printf("请输入两个数字:从小到大排");
		scanf("%d %d",&data1,&data2);
		if(data1>data2){
			printf("=====\n");
			datatmp=data1;//data1>data2时 进入
			data1=data2;
			data2=datatmp;
		}
		printf("%d %d",data1,data2);
		
	}