#include<stdio.h>

void iniArr(int arr[],int len){
	for(int i=0;i<len;i++){
	scanf("%d",&arr[i]);
	}
}

void PriArr(int arr[],int len){
	for(int i=0;i<len;i++){
	printf("%d ",arr[i]);
	}
	puts("\n");
	
}

float pingJun(int arr[],int len,int *max,int *min){
	int sum=0;
	*max=arr[0];
	*min=arr[0];
	float pj;
	
	for(int i=0;i<len;i++){
	  if(arr[i]>*max){
		 *max=arr[i];
	  }
	  if(arr[i]<*min){
		 *min=arr[i];
	  }
	  
	  sum=sum+arr[i];
	}
	pj=(float)sum/len;
	return pj;
}
 
int main(){
	int arr1[10];
	int len1=sizeof(arr1)/sizeof(arr1[0]);
	int max;
	int min;
	iniArr(arr1,len1);
	PriArr(arr1,len1);
	int pj;
	pj=pingJun(arr1,len1,&max,&min);
	printf("平均值:%d 最大值：%d 最小值%d",pj,max,min);
	
}