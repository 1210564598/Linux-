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

int findmaxArr(int arr[],int len,int *xiabiao){
	int max=arr[0];
	*xiabiao=0;
	for(int i=1;i<len;i++){
			if(arr[i]>max){

				max=arr[i];
				*xiabiao=i;
			}
		}
			return max;
	

	
}

int main(){
	int arr[10];
    int len=sizeof(arr)/sizeof(arr[0]);
	int index;
	iniArr(arr,len);
	PriArr(arr,len);
	int maxVA=findmaxArr(arr,len,&index);

 printf("最大值：%d，下标：%d\n", maxVA, index);
	

	return 0;
}