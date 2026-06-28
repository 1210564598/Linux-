#include<stdio.h>

int hanshu1(int n){
	int res;
	if(n==1){
		res=10;
		return res;
	}else if(n>1){
		res=hanshu1(n-1)+2;
		return res;
	}
}

int  main(){
	int n;
	int res;
	scanf("%d",&n);
	res=hanshu1(n);
	printf("%d",res);
	
	return 0;
}