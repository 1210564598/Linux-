#include<stdio.h>
int main(){
	int arry[]={4,31,21,15,6,12,15};
	int tmp;
	int len=sizeof(arry)/sizeof(arry[0]);
	int max=arry[0];
	for(int i=0;i<len-1;i++){
		
		for(int j=i+1;j<len;j++){
			if(arry[j]>arry[max]){  //更新位置
			max=j;
			}	
		}
		tmp=arry[i];
		arry[i]=arry[max];
		arry[max]=tmp;
		
		
	}
		printf("排序后：");
	for(int i=0; i<len; i++){
		printf("%d ", arry[i]);
	}
	return 0;
}	