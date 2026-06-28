#include<stdio.h>

int TwoArr(int hang,int lie,int arr[hang][lie]){
	int max=arr[0][0];
	for(int i=0;i<hang;i++){
		for(int j=0;j<lie;j++){
			if(arr[i][j]>max){
				max=arr[i][j];
			}
		}
	}
	return max;
	
}

int main(){
	int arr[3][4]={{1,2,3,10},{4,5,6,11},{7,8,9,12}};
	int hang;
	int lie;
	hang=sizeof(arr)/sizeof(arr[0]);
	lie=sizeof(arr[0])/sizeof(arr[0][0]);
	int max=TwoArr(hang,lie,arr);
	printf("%d",max);
	
	return 0;
}