#include<stdio.h>
	int main(){
		int arry[5]={5,13,15,10,4};
		int tmp=0;
		int len=sizeof(arry)/sizeof(arry[0]);
		for(int i=0;i<len-1;i++){
			for(int j=0;j<len-i-1;j++){
			if(arry[j]>arry[j+1]){
				tmp=arry[j];
				arry[j]=arry[j+1];
				arry[j+1]=tmp;
			}
			}
			
		}
		for(int i=0;i<len;i++){
			printf("%d ",arry[i]);
		}
		
		return 0;
	}