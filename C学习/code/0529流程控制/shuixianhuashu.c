#include<stdio.h>
	int main(){
		for(int i=999;i>100;i--){	
		int c=i%10;
		int b=i/10%10;
		int a= i/100;
			
		if(a*a*a+b*b*b+c*c*c==a*100+b*10+c)
			printf("Ë®ÏÉ»¨Êı%d\n",i);
		}
		
		return 0;
	}