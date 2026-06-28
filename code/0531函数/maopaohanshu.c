#include<stdio.h>

void PriArr(int arr[],int len){
	for(int i=0;i<len;i++){
		printf("%d ",arr[i]);
	}
	
}

void mpPaixu(int arr[],int len){
	int tmp;
	for(int i=0;i<len;i++){
		for(int j=0;j<len-1-i;j++){
			if(arr[j+1]>arr[j]){
				tmp=arr[j];
				arr[j]=arr[j+1];
				arr[j+1]=tmp;
			}
		}
	}
	
}


int main(){
	int arr[5]={2,6,45,95,6};
	int len=sizeof(arr)/sizeof(arr[0]);
	mpPaixu(arr,len);
	PriArr(arr,len);
	
	
	return 0;
}