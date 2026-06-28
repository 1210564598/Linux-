#include<stdio.h>
	int main(){
		int rich;
		int handsome;
		int spend;
		printf("你是否富裕 富裕扣1 不富裕扣0\n");
		scanf("%d",&rich);
		if(rich!=1){
			
			puts("我们不合适");
			return -1;
		}
		printf("你是否帅气 帅气 扣1 不帅气 扣0\n");
		scanf("%d",&handsome);
		
		printf("你是否给我花钱 花钱扣1 不花钱扣0\n");
		scanf("%d",&spend);
		
			if(handsome==1&&spend==1){
			
			puts("我要嫁给你");
		}	else{
			printf("我们不合适捏");
		}		
			
		return 0;
	}