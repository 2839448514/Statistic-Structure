#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>
#include<time.h>

#define LIST_INIT_SIZE 100 // 初始化大小
#define LISTINCREMENT 10   // 顺序表增量



typedef int Status;


typedef struct Node
{
	int data;
} qNode;

typedef struct List
{
	qNode* data; // 使用指向qNode的指针进行动态分配
	int length;
	int listsize;
} qList;



// 初始化
Status InitList(qList* L)
{
	L->data = (qNode*)malloc(LIST_INIT_SIZE * sizeof(qNode));
	if (!L->data)
	{
		printf("链表初始化失败!\n");
		return -1;
	}
	L->length = 0;
	L->listsize = LIST_INIT_SIZE;
	return 0;
}

// 销毁
Status DestroyList(qList* L)
{
	free(L->data);
	L->data = NULL;
	L->length = 0;
	L->listsize = 0;
	return 0;
}

// 清空
Status ClearList(qList* L)
{
	if (L == NULL || L->data == NULL) {
		printf("链表为空!\n");
		return -1;
	}
	L->length = 0;
	return 0;
}

// 判断是否为空
Status ListEmpty(qList L) {
	return L.length == 0 ? 1 : 0;
}
// 求长度
Status ListLength(qList* L)
{
	return L->length;
}

// 取值
Status GetElem(qList* L, int i, qNode* e)
{
	if (i < 1 || i > L->length)
	{
		printf("取值位置不合法!\n");
		return -1;
	}
	*e = L->data[i - 1];
	return 0;
}

// 查找
Status LocateElem(qList* L, qNode e)
{
	for (int i = 0; i < L->length; ++i)
	{
		if (L->data[i].data == e.data)
		{
			return i + 1;
		}
	}
	return 0;
}

// 返回前驱
Status PriorElem(qList* L, qNode cur_e, qNode* pre_e) {
	int i;
	for (i = 0; i < L->length; ++i) {
		if (L->data[i].data == cur_e.data) {
			break;
		}
	}
	if (i == 0) {
		printf("没有前驱!\n");
		return -1;
	}
	*pre_e = L->data[i - 1];
	return 0;
}

// 返回后继
Status NextElem(qList* L, qNode cur_e, qNode* next_e) {
	int i;
	for (i = 0; i < L->length; ++i) {
		if (L->data[i].data == cur_e.data) {
			break;
		}
	}
	if (i == L->length - 1) {
		printf("没有后继!\n");
		return -1;
	}
	*next_e = L->data[i + 1];
	return 0;
}

// 插入
Status ListInsert(qList* L, int i, qNode e)
{
	if (i < 1 || i > L->length + 1)
	{
		printf("插入位置不合法!\n");
		return -1;
	}
	if (L->length >= L->listsize)
	{
		qNode* newbase = (qNode*)realloc(L->data, L->listsize + LISTINCREMENT * sizeof(qNode));
		if (!newbase)
		{
			printf("内存分配失败!\n");
			return -1;
		}
		L->data = newbase;
		L->listsize += LISTINCREMENT;
	}
	qNode* q = &(L->data[i - 1]);
	for (qNode* p = &(L->data[L->length - 1]); p >= q; --p)
	{
		*(p + 1) = *p;
	}
	*q = e;
	++L->length;
	return 0;
}

// 删除
Status ListDelete(qList* L, int i, qNode* e)
{
	if (i < 1 || i > L->length)
	{
		printf("删除位置不合法!\n");
		return -1;
	}
	qNode* p = &(L->data[i - 1]);
	*e = *p;
	qNode* q = L->data + L->length - 1;
	for (++p; p <= q; ++p)
	{
		*(p - 1) = *(p);
	}
	--L->length;
	return 0;
}

// 打印
Status PrintList(qList* L)
{
	for (int i = 0; i < L->length; ++i)
	{
		printf("%d ", L->data[i].data);
	}
	printf("\n");
	return 0;
}

// 初始化界面
int InitInterface(qList* L)
{
	int choice;
	system("color 0C");
	printf("这是一个顺序表的基本操作系统!!!\n");
	printf("###当前的顺序表内容为:总长度:%d\t分配容量:%d\t\n", L->length, L->listsize);
	printf("顺序表的内容为:\n");
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

int main() {
	qList L;
	L.length = 0;
	L.listsize = 0;
	L.data = NULL;
	system("color 0A");
	printf("欢迎使用顺序表的基本操作系统！\n第一次打开请先选择“创建”初始化列表！\n");
	system("pause");
	int ans = 0;
	while (1) {
		system("cls");
		int choice = InitInterface(&L);
		if (ans == 0 && choice != 1) {
			printf("请先选择“创建”初始化列表！\n");
			system("pause");
			continue;
		}
		else {
			ans++;
		}
		switch (choice) {
		case 1: {
			system("cls");
			if (InitList(&L) == 0) {
				printf("链表初始化成功!\n");
			}
			system("pause");
			break;
		}
		case 2: {
			system("cls");
			int n;
			printf("请输入要输入的元素个数（注意：输出的元素插入到末尾）：");
			scanf("%d", &n);
			for (int i = 0; i < n; ++i) {
				qNode data;
				printf("请输入第%d个元素的值：", i + 1);
				scanf("%d", &data.data);
				if (ListInsert(&L, L.length + 1, data) == 0) {
					printf("第%d个元素插入成功！\n", i + 1);
				}
			}
			system("pause");
			break;
		}
		case 3: {
			system("cls");
			qNode e;
			int pos;
			printf("请输入要取值的位置：");
			scanf("%d", &pos);
			if (GetElem(&L, pos, &e) == 0) {
				printf("位置%d的值是: %d\n", pos, e.data);
			}
			system("pause");
			break;
		}
		case 4: {
			system("cls");
			qNode data;
			printf("请输入要查找的数据：");
			scanf("%d", &data.data);
			int pos = LocateElem(&L, data);
			if (pos) {
				printf("数据%d的位置是: %d\n", data.data, pos);
			}
			else {
				printf("未找到数据%d\n", data.data);
			}
			system("pause");
			break;
		}
		case 5: {
			system("cls");
			qNode data;
			int position;
			printf("请输入要插入的数据：");
			scanf("%d", &data.data);
			printf("请输入要插入的位置：");
			scanf("%d", &position);
			if (ListInsert(&L, position, data)) {
				printf("插入成功！\n");
			}
			system("pause");
			break;
		}
		case 6: {
			system("cls");
			qNode data;
			int position;
			printf("请输入要删除的位置：");
			scanf("%d", &position);
			if (ListDelete(&L, position, &data) == 0) {
				printf("删除成功！删除的数据为：%d\n", data.data);
			}
			system("pause");
			break;
		}
		case 7: {
			system("cls");
			printf("当前的顺序表内容为:\n");
			PrintList(&L);
			system("pause");
			break;
		}
		case 8: {
			system("cls");
			DestroyList(&L);
			printf("程序退出!\n");
			system("pause");
			return 0;
		}
		default:
			printf("输入不合法!\n");
			system("pause");
			break;
		}
	}
	return 0;
}
