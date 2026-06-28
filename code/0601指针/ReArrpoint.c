#include<stdio.h>
void reArr(int *p,int len){
	int tmp;
	int i=0,j=len-1;
	while(i<j){
		for(i=0,j=len-1;i<j;i++,j--){
			tmp=p[i];
			p[i]=p[j];
			p[j]=tmp;
			//tmp=*(p+i);
			//*(p+i)=*(p+j);
			//*(p+j)=tmp;
		}
	}
}

void PriArr(int *p,int len){
	for(int i =0;i<len;i++){
		printf("%d ",*(p+i));
	}
	
}

int main(){
	int arr[]={2,23,4,6,6};
	int len=sizeof(arr)/sizeof(arr[0]);
	
	reArr(arr,len);
	PriArr(arr,len);
	
	
	return 0;
}