#include<stdio.h>
int Maxtwo(int a,int b){
	if(a>b){
		return a;
	}else{
		return b;
	}
}

int Maxfour(int a,int b,int c,int d){
	int max;
	max=Maxtwo(a,b);
	max=Maxtwo(max,c);
	max=Maxtwo(max,d);
	return max;
}

int main(){
	int a,b,c,d;
	int res;
	scanf("%d%d%d%d",&a,&b,&c,&d);
	res=Maxfour(a,b,c,d);
	printf("%d",res);
	
	
	return 0;
}