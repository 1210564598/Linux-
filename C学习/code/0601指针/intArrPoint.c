#include<stdio.h>
void IniArr(int *p,int len){
	for(int i=0;i<len;i++){
		scanf("%d",(p+i));
	
	}
}
	

void PriArr(int *p,int len){
	for(int i =0;i<len;i++){
		printf("%d ",*(p+i));
		printf("%d ",p[i]);
	}
	
}

int main(){
	int arr[5];
	int len=sizeof(arr)/sizeof(arr[0]);
	IniArr(arr,len);
	PriArr(arr,len);
	return 0;
}