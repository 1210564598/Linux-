#include<stdio.h>


int *zhanshi(int (*p)[4],int weizhi){
	int *date;
	date=(int *)(p+weizhi);
	return date;
}

int main(){
	int a[][4]={{93,53,63,59},
	{100,90,67,77},
	{66,77,55,22}};
	int *px;
	int weizhi;
	scanf("%d",&weizhi);
	px=zhanshi(a,weizhi);
	for(int i=0;i<4;i++){
		printf("%d ",*(p+i));
	}
	
	return 0;
}