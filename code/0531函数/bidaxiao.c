#include<stdio.h>

int ScWMax(int a,int b){
	if(a>b){
		return a;
	}else{
		return b;
	}
}
int ScWMax2(int a,int b){

	return a>b?a:b;
}


int main(){
	int a;
	int b;
	int res;
	scanf("%d%d",&a,&b);
	res=ScWMax(a,b);
	printf("%d",res);
	
	puts("\n===========");
	scanf("%d%d",&a,&b);
	res=ScWMax2(a,b);
	printf("%d",res);
	return 0;
}