#include<stdio.h>

int hanshu2(int n){
	int res;
	if(n==1){
		return 1;
	}else if(n>1){
		res=hanshu2(n-1)*n;
		return res;
	}
	
}

int main(){
	
	int n;
	int res;
	scanf("%d",&n);
	res=hanshu2(n);
	printf("%d",res);
	return 0;
}