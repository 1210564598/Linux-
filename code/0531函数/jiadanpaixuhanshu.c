#include<stdio.h>

void iniArr(int arr[],int len){  //初始化
	printf("请输入10个数字\n");
	for(int i=0;i<len;i++){
		scanf("%d",&arr[i]);
	}
}

void PriArr(int arr[],int len){
	for(int i=0;i<len;i++){
		printf("%d ",arr[i]);
		
	}	
	printf("\n");
}

void maxArr(int arr[],int len){
	
	int tmp;
	for(int i=0;i<len-1;i++){
		int max=i;
		for(int j=i+1;j<len;j++){
			if(arr[j]>arr[max]){
				max=j;
			}
		}
			tmp=arr[i];
			arr[i]=arr[max];
			arr[max]=tmp;
	}
	
}

int main(){
	int arr[10];
    int len=sizeof(arr)/sizeof(arr[0]);

	iniArr(arr,len);
	PriArr(arr,len);
	maxArr(arr,len);
	PriArr(arr,len);
	
	

	return 0;
}