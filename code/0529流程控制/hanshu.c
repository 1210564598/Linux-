#include<stdio.h>
	int main(){
		int x;
		int y;
		printf("请输入一个数字");
		scanf("%d",&x);
		if(x<1){
		   y=x;
			printf("y=%d",y);
		}
		
		else if(x>=1&&x<10){
			y=(2*x-1);
			printf("y=2*%d-1=%d",x,y);
		}
		
		else if(x>=10){
			y=(3*x-11);
			printf("y=3*%d-11=%d",x,y);
		}	
		
		return 0;
	}