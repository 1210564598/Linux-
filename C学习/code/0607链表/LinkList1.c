#include<stdio.h>
#include <stdlib.h>
//节点结构定义
typedef struct Node {
	int data;
	struct Node *next;
}Node;
//创建单个节点
Node *createNode(int data){
	Node *newnode=(Node*)malloc(sizeof(Node));
	if(newnode==NULL)return NULL;
	newnode->data=data;
	newnode->next=NULL;
	return newnode;
}
//不带头节点的尾插法建立链表
Node *tailInsert(int n){
	Node* head=NULL;
	Node* tail=NULL;
	int data;
	
	printf("请输入%d个数据",n);
	for(int i=0;i<n;i++){
		printf("请输入第%d个数据的值：",i+1);
		scanf("%d",&data);
		Node* newnode=(Node*)malloc(sizeof(Node));
		if(newnode==NULL){
    printf("内存分配失败\n");
    continue;
	}
	newnode->data = data;
	newnode->next = NULL; 
		
		
		if(head==NULL){
			head=newnode;
			tail=newnode;
		}else{
			tail->next=newnode;
			tail=newnode;
		}
	}
	return head;
}
//带头节点的尾插法
Node *htailInsert(int n){
	Node* head=(Node*)malloc(sizeof(Node));
	head->next=NULL;
	Node* tail=NULL;
	int data;
	
	printf("请输入%d个数据",n);
	for(int i=0;i<n;i++){
		printf("请输入第%d个数据的值：",i+1);
		scanf("%d",&data);
		Node* newnode=(Node*)malloc(sizeof(Node));
		if(newnode==NULL)continue;
		newnode->data=data;
		newnode->next=NULL;
		if(head->next==NULL){
			head->next=newnode;
			tail=newnode;
		}else{
			tail->next=newnode;
			tail=newnode;
		}
	}
	return head;
}


//带头节点头插法
Node *hheadInsert(int n){
	
	Node *head = (Node*)malloc(sizeof(Node));
	head->next=NULL;
	int data;
	printf("请输入%d个数据",n);
	for(int i=0;i<n;i++){
		printf("请输入第%d个数据的值：",i+1);
		scanf("%d",&data);
		Node* newnode=(Node*)malloc(sizeof(Node));
		if(newnode==NULL)continue;
		
		newnode->data=data;
		newnode->next=head->next;
		head->next=newnode;	
}
return head;
}
//不带头节点的头插法
Node *headInsert(int n){
	Node *head=NULL;
	int data;
	printf("请输入%d个数据",n);
	for(int i=0;i<n;i++){
		printf("请输入第%d个数据的值：",i+1);
		scanf("%d",&data);
		Node* newnode=(Node*)malloc(sizeof(Node));
		if(newnode==NULL)continue;
		newnode->data=data;
		newnode->next=head;
		head=newnode;
		
	}
	return head;
}

//在指定位置插入
Node *headwzInsert(Node* head,int Insertwz,int data){
	Node *newnode = createNode(data);
	if(newnode==NULL){
		printf("内存分配失败\n");
		return head;
	}
    // 处理空链表
    if (head == NULL) {
        if (Insertwz == 1) {
            return newnode;  // ? 空链表只能在位置1插入
        } else {
            printf("错误：空链表只能在位置1插入\n");
            free(newnode);
            return NULL;
        }
    }
	
	if (Insertwz == 1) {
        newnode->next = head;
        return newnode;
    }
    
	Node* prev=head;
	int i=1;
	while(prev->next!=NULL&&i<Insertwz-1){
		prev=prev->next;
		i++;
	}
	
	    // 检查位置是否有效
	if (i < Insertwz - 1) {
    free(newnode);
    printf("错误：插入位置 %d 超出链表范围\n", Insertwz);
    return head;
    }
	
	newnode->next=prev->next;
	prev->next=newnode;
	
	return head;
}


//不带头节点打印
void PrihList(Node* head){
	Node* p=head;
	while(p!=NULL){
		printf("%d ",p->data);
		p=p->next;
	}
}
//不带头节点寻找
void searchList(Node* head,int data){
	Node* p=head;
	int i=1;
	while(p!=NULL){
		if(p->data==data){
			printf("在第%d个位置找到：%d",i,p->data);
		}
		p=p->next;
		i++;
	}
}

//带头节点寻找 
void searchListhead(Node* head,int data){
	Node* p=head->next;
	int i=1;
	while(p!=NULL){
		if(p->data==data){
			printf("在第%d个位置找到：%d",i,p->data);
		}
		p=p->next;
		i++;
	}
}

//带头节点打印
void PrihListhead(Node* head){
	Node* p=head->next;
	while(p!=NULL){
		printf("%d ",p->data);
		p=p->next;
	}
}
//获取链表长度
int getLenList(Node* head){
	Node* p=head;
	int len=0;
	while(p!=NULL){
		p=p->next;
		len++;
	}
	return len;
}
//获取链表长度带head
int getLenListhead(Node* head){
	Node* p=head->next;
	int len=0;
	while(p!=NULL){
		p=p->next;
		len++;
	}
	return len;
}
//删除节点操作
Node* DeleteList(Node* head,int target){
	 // ========== 情况1：空链表 ==========
	 if(head==NULL){
		printf("链表为空\n");
		return NULL;
	 }
	 //========== 情况2：删除的为头节点 ==========
	 if(head->data==target){
		Node* tmp=head;
		head=head->next;
		free(tmp);
        printf("删除头节点成功\n");
        return head;  // 返回新头指针
	 }
	 //========== 情况3：删除的非头节点 ==========
	 Node* prev=head;
	 while(prev->next!=NULL&&prev->next->data!=target){
		 prev=prev->next;
	 }
	 if(prev->next==NULL){
		printf("未找到%d的节点\n",target);
	 }
	 //删除操作
	 Node* temp=prev->next; //将要删除的节点保存
	 prev->next=temp->next;//将前前驱节点指向当前节点的指针转移为当前指针指向后一项的指针
	free(temp);
	return head;
}

//带头节点的删除
Node* DeleteHeList(Node* head,int target){
	//情况1空指针
	if(head==NULL||head->next==NULL){
		printf("空指针\n");
		return NULL;
	}
	//情况2删除
	Node *prev=head;
	while(prev->next!=NULL&&prev->next->data!=target){
		prev=prev->next;
	}
	if(prev->next==NULL){
		printf("未找到\n");
		return head;
	}
	Node* tmp=prev->next;
	prev->next=tmp->next;
	free(tmp);
	return head;
}
// 释放链表内存
void freeList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
}

// 释放带头节点链表
void freeListWithHead(Node* head) {
    if (head == NULL) return;
    Node* current = head->next;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    free(head);  // 释放头节点
}




int main(){
    printf("=== 测试1：不带头节点尾插法 ===\n");
    Node* list1 = tailInsert(3);
    printf("链表内容：");
    PrihList(list1);
    printf("\n链表长度：%d\n", getLenList(list1));
    
    printf("\n=== 测试2：查找元素 ===\n");
    searchList(list1, 1);
    
    printf("\n=== 测试3：指定位置插入 ===\n");
    list1 = headwzInsert(list1, 2, 99);
    PrihList(list1);
    
    printf("\n=== 测试4：删除节点 ===\n");
    list1 = DeleteList(list1, 99);
    PrihList(list1);
    
    freeList(list1);
    return 0;
 
}