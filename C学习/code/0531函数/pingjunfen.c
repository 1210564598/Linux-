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

float pingJun(int arr[],int len){
	int sum=0;
	float pj;
	for(int i=0;i<len;i++){
	   sum=sum+arr[i];
	}
	pj=(float)sum/len;
	return pj;
}
 
int main(){
	int arr1[10];
	int arr2[5];
	int len1=sizeof(arr1)/sizeof(arr1[0]);
	int len2=sizeof(arr2)/sizeof(arr2[0]);
	
	iniArr(arr1,len1);
	PriArr(arr1,len1);
	int pj;
	pj=pingJun(arr1,len1);
	printf("%d",pj);
	
	iniArr(arr2,len2);
	PriArr(arr2,len2);
	pj=pingJun(arr2,len2);
	printf("%d",pj);
	return 0;
}