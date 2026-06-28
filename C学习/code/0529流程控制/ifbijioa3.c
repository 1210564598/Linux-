#include<stdio.h>
	int main(){
		int a,b,c;
		int tmp;
		printf("请输入三个数字");
		scanf("%d %d %d",&a,&b,&c);

		if(a>b){
		 tmp=a;
		 a=b;
		 b=tmp;//此时a的值小于b的值
		}
		if(a>c){
		 tmp=c;
		 a=c;
		 c=tmp;//此时a的值小于c的值
		}
		if(b>c){
		 tmp=b;
		 b=c;
		 c=tmp;
		}
		
		printf("%d %d %d ",a,b,c);
		
		return 0;
	}