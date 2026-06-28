#include<stdio.h>
int main(){
		int arry[5];
		for(int i=0;i<5;i++){
			arry[i]=i;
		}
		
		for(int i=0;i<5;i++){
			printf("%d",arry[i]);
			
		}
		puts("\n");
		for(int i=5;i>0;i--){
			printf("%d",arry[i]);
			
		}
	
}