#include<stdio.h>



void FanZuanArr(int *arr,int len){
	int tmp;
	int i=0;
	int j=len-1;
	while(i<j){
		tmp=arr[i];
		arr[i]=arr[j]
		arr[j]=tmp;
		i++;
		j--;
	}
	
}



int main(){
	
	int arr[5]={1,2,3,4,5};
	int len=sizeof(arr)/sizeof(arr[0]);
	
	return 0;
}