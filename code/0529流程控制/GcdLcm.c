#include<stdio.h>
	int main(){
		int m,n;
		int max;
		printf("请输入两个数字");
		scanf("%d %d",&m,&n);
		//最大公约数
		for(int i=1;m>=i&&n>=i;i++){
			
			if(m%i==0&&n%i==0){
			
			max=i;
		
		}	
		}
		printf("%d\n",max);
		//最小公倍数

		printf("%d",m*n/max);
		return 0;
	}