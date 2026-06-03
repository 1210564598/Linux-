#include<stdio.h>

void paixu(int *a,int *b,int *c){
	int tmp;
	if(*a<*b){
		tmp=*b;
		*b=*a;
		*a=tmp;
		
	}
	if(*a<*c){
		tmp=*c;
		*c=*a;
		*a=tmp;
		
	}
	if(*b<*c){
		tmp=*c;
		*c=*b;
		*b=tmp;
	}
}

int main(){
	int a,b,c;
	scanf("%d%d%d",&a,&b,&c);
	paixu(&a,&b,&c);
	printf("a=%d b=%d c=%d\n",a,b,c);
	return 0;
}