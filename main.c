#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_TRIES 3  // 最大重试次数

// 节点结构定义
typedef struct Node {
    int data;
    struct Node* next;
} Node, * LinkList;

// 初始化列表
LinkList InitList() {
    LinkList L = (LinkList)malloc(sizeof(Node));
    L->next = NULL;
    return L;
}

// 尾插法创建链表
LinkList CreatList_Tail(int n) {
    LinkList L = InitList();
    Node* tail = L;
    for (int i = 0; i < n; i++) {
        Node* p = (Node*)malloc(sizeof(Node));
        printf("输入第%d个元素的值：", i + 1);
        // 输入验证
        while (scanf("%d", &p->data) != 1) {
            // 清空输入缓冲区
            while (getchar() != '\n');
            printf("输入无效，请输入一个整数：");
        }
        p->next = NULL;
        tail->next = p;
        tail = p;
    }
    return L;
}

// 插入操作
bool InsertList(LinkList L, int pos, int val) {
    int i = 0;
    Node* p = L;
    while (p != NULL && i < pos - 1) {
        p = p->next;
        i++;
    }
    if (p == NULL) return false;

    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = val;
    newNode->next = p->next;
    p->next = newNode;
    return true;
}

// 删除操作
bool DeleteList(LinkList L, int pos) {
    int i = 0;
    Node* p = L;
    while (p != NULL && i < pos - 1) {
        p = p->next;
        i++;
    }
    if (p == NULL || p->next == NULL) return false;

    Node* q = p->next;
    p->next = q->next;
    free(q);
    return true;
}

// 查找操作（按位置）
Node* GetElem(LinkList L, int pos) {
    int i = 0;
    Node* p = L->next;
    while (p != NULL && i < pos - 1) {
        p = p->next;
        i++;
    }
    if (p == NULL) {
        printf("元素不存在！\n");
        return NULL;
    }
    return p;
}

// 按值查找
Node* LocateElem(LinkList L, int val) {
    Node* p = L->next;
    while (p != NULL) {
        if (p->data == val) {
            return p;
        }
        p = p->next;
    }
    printf("未找到值为%d的元素！\n", val);
    return NULL;
}

// 打印链表
void PrintList(LinkList L) {
    Node* p = L->next;
    if (p == NULL) {
        printf("链表为空！\n");
        return;
    }
    printf("链表内容：");
    while (p != NULL) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

// 输入一个有效的整数
int GetValidIntInput() {
    int val;
    int tries = 0;
    while (tries < MAX_TRIES) {
        if (scanf("%d", &val) == 1) {
            return val;
        }
        else {
            while (getchar() != '\n');  // 清空输入缓冲区
            printf("输入无效，请输入一个有效的整数：");
            tries++;
        }
    }
    printf("多次输入无效，程序退出。\n");
    exit(1);  // 超过最大尝试次数后退出程序
}

// 主函数，用户操作菜单
int main() {
    LinkList L = NULL;
    int choice, pos, val, n;

    while (1) {
        printf("\n请选择操作：\n");
        printf("1. 创建链表\n");
        printf("2. 打印链表\n");
        printf("3. 插入元素\n");
        printf("4. 删除元素\n");
        printf("5. 按位置查找元素\n");
        printf("6. 按值查找元素\n");
        printf("7. 退出\n");
        printf("请输入你的选择：");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("请输入链表的元素个数：");
            n = GetValidIntInput();
            L = CreatList_Tail(n);
            break;
        case 2:
            PrintList(L);
            break;
        case 3:
            printf("请输入插入的位置和元素值：");
            pos = GetValidIntInput();
            val = GetValidIntInput();
            if (InsertList(L, pos, val)) {
                printf("插入成功！\n");
            }
            else {
                printf("插入失败！\n");
            }
            break;
        case 4:
            printf("请输入要删除的位置：");
            pos = GetValidIntInput();
            if (DeleteList(L, pos)) {
                printf("删除成功！\n");
            }
            else {
                printf("删除失败！\n");
            }
            break;
        case 5:
            printf("请输入要查找的位置：");
            pos = GetValidIntInput();
            Node* elem = GetElem(L, pos);
            if (elem != NULL) {
                printf("第%d个元素的值是：%d\n", pos, elem->data);
            }
            break;
        case 6:
            printf("请输入要查找的元素值：");
            val = GetValidIntInput();
            Node* locElem = LocateElem(L, val);
            if (locElem != NULL) {
                printf("找到值为%d的元素。\n", val);
            }
            break;
        case 7:
            printf("退出程序。\n");
            return 0;
        default:
            printf("无效的选择，请重新选择。\n");
        }
    }
    return 0;
}
