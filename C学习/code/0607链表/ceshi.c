#include <stdio.h>
#include <stdlib.h>

// 节点结构定义
typedef struct Node {
    int data;
    struct Node *next;
} Node;

// 创建单个节点
Node *createNode(int data) {
    Node *newnode = (Node*)malloc(sizeof(Node));
    if (newnode == NULL) return NULL;
    newnode->data = data;
    newnode->next = NULL;
    return newnode;
}

// 不带头节点的尾插法建立链表
Node *tailInsert(int n) {
    Node* head = NULL;
    Node* tail = NULL;
    int data;
    
    printf("请输入%d个数据:\n", n);
    for (int i = 0; i < n; i++) {
        printf("请输入第%d个数据的值：", i + 1);
        scanf("%d", &data);
        Node* newnode = createNode(data);
        if (newnode == NULL) continue;
        if (head == NULL) {
            head = newnode;
            tail = newnode;
        } else {
            tail->next = newnode;
            tail = newnode;
        }
    }
    return head;
}

// 带头节点的尾插法
Node *htailInsert(int n) {
    Node* head = (Node*)malloc(sizeof(Node));
    if (head == NULL) return NULL;
    head->next = NULL;
    Node* tail = head; // ?? 初始化指向头节点
    int data;
    
    printf("请输入%d个数据:\n", n);
    for (int i = 0; i < n; i++) {
        printf("请输入第%d个数据的值：", i + 1);
        scanf("%d", &data);
        Node* newnode = createNode(data);
        if (newnode == NULL) continue;
        tail->next = newnode;
        tail = newnode;
    }
    return head;
}

// 带头节点头插法
Node *hheadInsert(int n) {
    Node *head = (Node*)malloc(sizeof(Node));
    if (head == NULL) return NULL;
    head->next = NULL;
    int data;
    printf("请输入%d个数据:\n", n);
    for (int i = 0; i < n; i++) {
        printf("请输入第%d个数据的值：", i + 1);
        scanf("%d", &data);
        Node* newnode = createNode(data);
        if (newnode == NULL) continue;
        
        newnode->next = head->next;
        head->next = newnode;    
    }
    return head;
}

// 不带头节点的头插法
Node *headInsert(int n) {
    Node *head = NULL;
    int data;
    printf("请输入%d个数据:\n", n);
    for (int i = 0; i < n; i++) {
        printf("请输入第%d个数据的值：", i + 1);
        scanf("%d", &data);
        Node* newnode = createNode(data);
        if (newnode == NULL) continue;
        newnode->next = head;
        head = newnode;
    }
    return head;
}

// 在指定位置插入（不带头节点）
Node *headwzInsert(Node* head, int Insertwz, int data) {
    if (Insertwz < 1) {
        printf("错误：位置不合法\n");
        return head;
    }

    Node *newnode = createNode(data);
    if (newnode == NULL) {
        printf("内存分配失败\n");
        return head;
    }

    // 处理位置1插入（包括空链表情况）
    if (Insertwz == 1) {
        newnode->next = head;
        return newnode;
    }
    
    if (head == NULL) {
        printf("错误：空链表只能在位置1插入\n");
        free(newnode);
        return NULL;
    }
    
    Node* prev = head;
    int i = 1;
    // 寻找插入位置的前驱节点
    while (prev != NULL && i < Insertwz - 1) {
        prev = prev->next;
        i++;
    }
    
    // ??? 修复：严格检查是否越界
    if (prev == NULL) {
        free(newnode);
        printf("错误：插入位置 %d 超出链表范围\n", Insertwz);
        return head;
    }
    
    newnode->next = prev->next;
    prev->next = newnode;
    return head;
}

// 不带头节点打印
void PrihList(Node* head) {
    Node* p = head;
    while (p != NULL) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

// 带头节点打印
void PrihListhead(Node* head) {
    if (head == NULL) return;
    Node* p = head->next;
    while (p != NULL) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

// 不带头节点寻找
void searchList(Node* head, int data) {
    Node* p = head;
    int i = 1;
    int found = 0;
    while (p != NULL) {
        if (p->data == data) {
            printf("在位置 %d 找到数据：%d\n", i, p->data);
            found = 1;
        }
        p = p->next;
        i++;
    }
    if (!found) printf("未找到数据 %d\n", data);
}

// 获取链表长度
int getLenList(Node* head) {
    Node* p = head;
    int len = 0;
    while (p != NULL) {
        p = p->next;
        len++;
    }
    return len;
}

// 不带头节点删除
Node* DeleteList(Node* head, int target) {
     if (head == NULL) {
        printf("链表为空\n");
        return NULL;
     }
     if (head->data == target) {
        Node* tmp = head;
        head = head->next;
        free(tmp);
        printf("删除头节点成功\n");
        return head;
     }

     Node* prev = head;
     while (prev->next != NULL && prev->next->data != target) {
         prev = prev->next;
     }

     // ??? 修复：未找到时直接返回，不往下送死
     if (prev->next == NULL) {
        printf("未找到%d的节点\n", target);
        return head; 
     }

     Node* temp = prev->next; 
     prev->next = temp->next;
     free(temp);
     printf("删除成功\n");
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
    freeList(head); // 头节点也是个节点，直接复用
}

int main() {
    printf("=== 测试不带头节点尾插法 ===\n");
    Node *list1 = tailInsert(3);
    printf("链表内容：");
    PrihList(list1);
    
    printf("\n=== 测试越界插入操作 ===\n");
    list1 = headwzInsert(list1, 6, 99); // 故意传个大位置测试防御力
    printf("链表内容：");
    PrihList(list1);

    printf("\n=== 测试正常插入操作 ===\n");
    list1 = headwzInsert(list1, 2, 99); 
    printf("插入后：");
    PrihList(list1);
    
    printf("\n=== 测试删除操作 ===\n");
    list1 = DeleteList(list1, 99);
    printf("删除后：");
    PrihList(list1);
    
    freeList(list1);
    return 0;
}