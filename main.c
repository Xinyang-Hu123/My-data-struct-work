#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_TRIES 3  // ������Դ���

// �ڵ�ṹ����
typedef struct Node {
    int data;
    struct Node* next;
} Node, * LinkList;

// ��ʼ���б�
LinkList InitList() {
    LinkList L = (LinkList)malloc(sizeof(Node));
    L->next = NULL;
    return L;
}

// β�巨��������
LinkList CreatList_Tail(int n) {
    LinkList L = InitList();
    Node* tail = L;
    for (int i = 0; i < n; i++) {
        Node* p = (Node*)malloc(sizeof(Node));
        printf("�����%d��Ԫ�ص�ֵ��", i + 1);
        // ������֤
        while (scanf("%d", &p->data) != 1) {
            // ������뻺����
            while (getchar() != '\n');
            printf("������Ч��������һ��������");
        }
        p->next = NULL;
        tail->next = p;
        tail = p;
    }
    return L;
}

// �������
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

// ɾ������
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

// ���Ҳ�������λ�ã�
Node* GetElem(LinkList L, int pos) {
    int i = 0;
    Node* p = L->next;
    while (p != NULL && i < pos - 1) {
        p = p->next;
        i++;
    }
    if (p == NULL) {
        printf("Ԫ�ز����ڣ�\n");
        return NULL;
    }
    return p;
}

// ��ֵ����
Node* LocateElem(LinkList L, int val) {
    Node* p = L->next;
    while (p != NULL) {
        if (p->data == val) {
            return p;
        }
        p = p->next;
    }
    printf("δ�ҵ�ֵΪ%d��Ԫ�أ�\n", val);
    return NULL;
}

// ��ӡ����
void PrintList(LinkList L) {
    Node* p = L->next;
    if (p == NULL) {
        printf("����Ϊ�գ�\n");
        return;
    }
    printf("�������ݣ�");
    while (p != NULL) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

// ����һ����Ч������
int GetValidIntInput() {
    int val;
    int tries = 0;
    while (tries < MAX_TRIES) {
        if (scanf("%d", &val) == 1) {
            return val;
        }
        else {
            while (getchar() != '\n');  // ������뻺����
            printf("������Ч��������һ����Ч��������");
            tries++;
        }
    }
    printf("���������Ч�������˳���\n");
    exit(1);  // ��������Դ������˳�����
}

// ���������û������˵�
int main() {
    LinkList L = NULL;
    int choice, pos, val, n;

    while (1) {
        printf("\n��ѡ�������\n");
        printf("1. ��������\n");
        printf("2. ��ӡ����\n");
        printf("3. ����Ԫ��\n");
        printf("4. ɾ��Ԫ��\n");
        printf("5. ��λ�ò���Ԫ��\n");
        printf("6. ��ֵ����Ԫ��\n");
        printf("7. �˳�\n");
        printf("���������ѡ��");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("�����������Ԫ�ظ�����");
            n = GetValidIntInput();
            L = CreatList_Tail(n);
            break;
        case 2:
            PrintList(L);
            break;
        case 3:
            printf("����������λ�ú�Ԫ��ֵ��");
            pos = GetValidIntInput();
            val = GetValidIntInput();
            if (InsertList(L, pos, val)) {
                printf("����ɹ���\n");
            }
            else {
                printf("����ʧ�ܣ�\n");
            }
            break;
        case 4:
            printf("������Ҫɾ����λ�ã�");
            pos = GetValidIntInput();
            if (DeleteList(L, pos)) {
                printf("ɾ���ɹ���\n");
            }
            else {
                printf("ɾ��ʧ�ܣ�\n");
            }
            break;
        case 5:
            printf("������Ҫ���ҵ�λ�ã�");
            pos = GetValidIntInput();
            Node* elem = GetElem(L, pos);
            if (elem != NULL) {
                printf("��%d��Ԫ�ص�ֵ�ǣ�%d\n", pos, elem->data);
            }
            break;
        case 6:
            printf("������Ҫ���ҵ�Ԫ��ֵ��");
            val = GetValidIntInput();
            Node* locElem = LocateElem(L, val);
            if (locElem != NULL) {
                printf("�ҵ�ֵΪ%d��Ԫ�ء�\n", val);
            }
            break;
        case 7:
            printf("�˳�����\n");
            return 0;
        default:
            printf("��Ч��ѡ��������ѡ��\n");
        }
    }
    return 0;
}
