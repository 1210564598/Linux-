#include<stdio.h>

int  FindTArr(int (*p)[3],int hang,int lie){
	int date;
	date=*(*(p+hang)+lie);
	return date;
}

void HL(int *hang,int *lie){
	printf("请输入你要查找数组的行列");
	scanf("%d%d",hang,lie);
	puts("done");
	
}
int main(){
	int TArr[2][3]={{1,2,3},{4,5,6}};
	int lie;
	int hang;
	int date;
	HL(&hang,&lie);
	date=FindTArr(TArr,hang,lie);
	printf("第%d行第%d列,值为%d",hang+1,lie+1,date);
	return 0;
}