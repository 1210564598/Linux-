#include<stdio.h>
int main(){
	int arry[5]={5,6,41,12,16};
	int max=arry[0];
	
	for(int i=0;i<5;i++){
		if(arry[i]>max){
			max=arry[i];
		}
	}
	printf("%d",max);
	

	
	
}