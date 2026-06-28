#include<stdio.h>

char CharMAX(char a,char b){
	if(a>b){
		return a;
	}else{
		return b;
	}
	
}

int main(){
	char a,b;
	char res;
	scanf("%c %c",&a,&b);
	res=CharMAX(a,b);
	printf("%c\n",res);
	
	return 0;
}