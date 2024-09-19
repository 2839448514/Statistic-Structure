#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>

typedef int Status;



typedef struct QNode {
    int data;
} qNode;


typedef struct ListNode {
    qNode* data;          
    struct ListNode* next; 
} LNode, * LinkList;

// 初始化
Status InitList(LinkList* L)
{
    *L = (LinkList)malloc(sizeof(LNode));
    if (!(*L)) {
        printf("链表初始化失败!\n");
        return -1;
    }
    (*L)->data = NULL;
    (*L)->next = NULL;
    return 0;
}

// 销毁链表
Status DestroyList(LinkList* L)
{
    LinkList p = NULL;
    if (L == NULL || *L == NULL) {
        printf("链表为空!\n");
        return -1;
    }
    p = *L;
    while (p) {
        LinkList temp = p->next;
        if (p->data) free(p->data); // 释放qNode数据
        free(p);
        p = temp;
    }
    *L = NULL;
    return 0;
}

// 清空链表
Status ClearList(LinkList L) {
    LinkList pre, p;

    if (L == NULL) {
        return -1;
    }

    p = L->next;

    while (p != NULL) {
        pre = p;
        p = p->next;
        free(pre);
    }

    L->next = NULL;

    return 0;
}

// 判断链表是否为空
Status ListEmpty(LinkList L) {
    // 链表只有头结点时，认为该链表为空
    if (L != NULL && L->next == NULL) {
        return 0;
    }
    else {
        return -1;
    }
}

// 链表长度
int ListLength(LinkList L) {
    LinkList p;
    int i;

    // 确保链表存在且不为空表
    if (L == NULL || L->next == NULL) {
        return 0;
    }

    i = 0;
    p = L->next;

    // 遍历所有结点
    while (p != NULL) {
        i++;
        p = p->next;
    }

    return i;
}

// 获取元素
Status GetElem(LinkList L, int i, int* data)
{
    if (L == NULL || L->next == NULL) {
        printf("链表为空!\n");
        return -1;
    }
    if (i < 1) {
        printf("取值位置不合法!\n");
        return -1;
    }

    LinkList p = L->next;
    int j = 1;
    while (p && j < i) {
        p = p->next;
        j++;
    }

    if (!p) {
        printf("未找到第%d个元素\n", i);
        return -1;
    }

    *data = p->data->data;
    return 0;
}

// 插入元素
Status ListInsert(LinkList L, int i, int data)
{
    if (i < 1) {
        printf("插入位置不合法!\n");
        return -1;
    }

    LinkList p = L;
    int j = 0;
    while (p && j < i - 1) {
        p = p->next;
        j++;
    }

    if (!p) {
        printf("插入失败，位置超出范围！\n");
        return -1;
    }

    LinkList newNode = (LinkList)malloc(sizeof(LNode));
    if (!newNode) {
        printf("内存分配失败!\n");
        return -1;
    }

    qNode* newQNode = (qNode*)malloc(sizeof(qNode));
    if (!newQNode) {
        printf("内存分配失败!\n");
        free(newNode);
        return -1;
    }

    newQNode->data = data;
    newNode->data = newQNode;
    newNode->next = p->next;
    p->next = newNode;

    return 0;
}

// 删除元素
Status ListDelete(LinkList L, int i, int* data)
{
    if (i < 1) {
        printf("删除位置不合法!\n");
        return -1;
    }

    LinkList p = L;
    int j = 0;
    while (p->next && j < i - 1) {
        p = p->next;
        j++;
    }

    if (!p->next) {
        printf("删除失败，位置超出范围！\n");
        return -1;
    }

    LinkList q = p->next;
    *data = q->data->data; // 获取删除节点的数据
    p->next = q->next;
    free(q->data); // 释放qNode数据
    free(q);       // 释放链表节点

    return 0;
}


// 打印链表
Status PrintList(LinkList L)
{
    LinkList p = L->next; // 跳过头节点
    while (p) {
        printf("%d ", p->data->data);
        p = p->next;
    }
    printf("\n");
    return 0;
}

// 初始化界面
Status InitInterface(LinkList L)
{
    int choice;
    system("color 0C");
    printf("这是一个带头节点的单链表操作系统!!!\n");
    printf("###当前的带头节点的单链表内容为:总长度:%d\n", ListLength(L));
    printf("###当前链表的内容为:\n");
    PrintList(L);

    printf("1.创建\n");
    printf("2.输入\n");
    printf("3.取值\n");
    printf("4.查找\n");
    printf("5.插入\n");
    printf("6.删除\n");
    printf("7.输出\n");
    printf("8.退出\n");
    printf("请输入你的选择：");
    scanf("%d", &choice);
    return choice;
}


int main()
{
    LinkList L;
    InitList(&L);

    while (1) {
        system("cls");
        int choice = InitInterface(L);
        switch (choice) {
        case 1: {
            system("cls");
            DestroyList(&L);
            InitList(&L);
            printf("链表已重新创建。\n");
            system("pause");
            break;
        }
        case 2: {
            system("cls");
            int data;
            printf("请输入要输入的元素个数（注意：输出的元素插入到末尾）：");
            scanf("%d", &data);
            ListInsert(L, 1, data); // 插入到链表头部
            printf("数据已插入。\n");
            system("pause");
            break;
        }
        case 3: {
            system("cls");
            int position, data;
            printf("请输入要取值的位置：");
            scanf("%d", &position);
            if (GetElem(L, position, &data) == 0) {
                printf("位置%d的值是: %d\n", position, data);
            }
            system("pause");
            break;
        }
        case 4: {
            system("cls");
            int data;
            printf("请输入要查找的数据：");
            scanf("%d", &data);
            LinkList p = L->next; // 跳过头节点
            int i = 1;
            while (p) {
                if (p->data->data == data) {
                    printf("找到第%d个元素，值为：%d\n", i, data);
                    break;
                }
                p = p->next;
                i++;
            }
            if (!p) {
                printf("未找到数据%d\n", data);
            }
            system("pause");
            break;
        }
        case 5: {
            system("cls");
            int position, data;
            printf("请输入要插入的位置和数据：");
            scanf("%d %d", &position, &data);
            if (ListInsert(L, position, data) == 0) {
                printf("数据已插入。\n");
            }
            system("pause");
            break;
        }
        case 6: {
            system("cls");
            int position, data;
            printf("请输入要删除的位置：");
            scanf("%d", &position);
            if (ListDelete(L, position, &data) == 0) {
                printf("位置%d的数据%d已删除。\n", position, data);
            }
            system("pause");
            break;
        }
        case 7: {
            system("cls");
            printf("链表的内容为：\n");
            PrintList(L);
            system("pause");
            break;
        }
        case 8: {
            system("cls");
            DestroyList(&L);
            printf("程序退出。\n");
            system("pause");
            return 0;
        }
        default: {
            printf("无效的选择，请重新输入。\n");
            system("pause");
            break;
        }
        }
    }
}

