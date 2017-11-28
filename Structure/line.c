#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INIT_SIZE 10 // 初始化表长
#define INCREMENT_SIZE 5 // 分配增量

typedef int Status;
typedef int Elemtype;

/*
 * 存储结构
 */
typedef struct
{
    Elemtype *elem; // 存储空间基址
    int length; // 当前长度
    int size; // 当前分配的表长大小
}SqList;

/*
 * 初始化一个空的线性表
 */
Status InitList(SqList *L)
{
    L->elem = (Elemtype*) malloc(INIT_SIZE * sizeof(Elemtype)); // 动态内存分配
    if (!L->elem) {
        return ERROR;
    }
    L->length = 0;
    L->size = INIT_SIZE;
    return OK;
}

/*
 * 插入元素
 */
Status InsertElem(SqList *L, int i, Elemtype e)
{
    Elemtype * new;

    if (i < 1 || i > L->length + 1) { // 下标在第一个元素之前或者在最后一个元素之后
        return ERROR;
    }

    if (L->length >= L->size) { // 线性表当前位置大于等于表长
        new = realloc(L->elem, (L->size + INCREMENT_SIZE) * sizeof(Elemtype)); // 重新分配存储器块的地址
        if (!new) {
            return ERROR;
        }
        L->elem = new;
        L->size += INCREMENT_SIZE;
    }

    Elemtype *p = &L->elem[i-1];
    Elemtype *q = &L->elem[L->length-1];
    for (; q >= p; q--) {
        *(q+1) = *q;
    }
    *p = e;
    ++L->length;
    return OK;
}

/*
 * 获取长度
 */
Status getLength(const SqList L) {

    return L.length;

}

/*
 * 根据位置获取元素
 */
Status getElem(const SqList L, int i, Elemtype *e)
{
    if (i < 1 || i > L.length) { // 查找位置不合理
        return ERROR;
    }
    *e = L.elem[i-1];
    return OK;
}

/*
 * 判断线性表是否为空
 */
Status isEmpty(const SqList L)
{
    if (0 == L.length) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/*
 * 比较两个元素是否相等
 */
Status compare(Elemtype e1, Elemtype e2)
{
    if (e1 == e2) {
        return 0;
    } else if (e1 < e2) {
        return -1;
    } else {
        return 1;
    }
}

/*
 * 查找元素
 */
Status findElem(const SqList L, Elemtype e, Status (*compare)(Elemtype, Elemtype))
{
    int i;
    for (i = 0; i < L.length; i++) {
        if (!(*compare)(L.elem[i], e)) {
            return i + 1;
        }
    }
    if (i >= L.length) {
        return ERROR;
    }
}

/*
 * 查找前驱元素
 */
Status preElem(const SqList L, Elemtype cur_e, Elemtype *pre_e)
{
    int i;
    for (i = 0; i < L.length; i++) {
        if (cur_e == L.elem[i]) {
            if (i != 0) {
                *pre_e = L.elem[i-1];
                return OK;
            } else {
                return ERROR;
            }
        }
    }
    if (i >= L.length) {
        return ERROR;
    }
}

/*
 * 查找后继元素
 */
Status nextElem(const SqList L, Elemtype cur_e, Elemtype *next_e)
{
    int i;
    for (i = 0; i < L.length; i++) {
        if (cur_e == L.elem[i]) {
            if (i < L.length - 1) {
                *next_e = L.elem[i+1];
                return OK;
            } else {
                return ERROR;
            }
        }
    }
    if (i >= L.length) {
        return ERROR;
    }
}

/*
 * 删除元素并返回其值
 */
Status deleteElem(SqList *L, int i, Elemtype *e)
{
    if (i < 1 || i > L->length) {
        return ERROR;
    }
    Elemtype *p = &L->elem[i-1];
    *e = *p;
    for (; p < &L->elem[L->length]; p++) {
        *p = *(p+1);
    }
    --L->length;
    return OK;
}

/*
 * 访问元素
 */
void visit(Elemtype e)
{
    printf("%d ", e);
}

/*
 * 遍历线性表
 */
Status traverseList(const SqList L, void (*visit)(Elemtype))
{
    int i;
    for (i = 0; i < L.length; i++) {
        visit(L.elem[i]);
    }
    return OK;
}

/*
 * 销毁线性表
 */
Status destoryList(SqList *L)
{
    free(L->elem);
    L->elem = 0;
    L->size = 0;
    return OK;
}

int main(int argc, char const *argv[])
{
    SqList L;
    if (InitList(&L)) {
        Elemtype e;
        printf("init_success\n");

        int i;
        for (i = 0; i < 10; i++){
            InsertElem(&L, i + 1, i);
        }

        printf("length is %d\n", getLength(L));

        if (getElem(L, 1, &e)) {
            printf("The first element is %d\n", e);
        } else {
            printf("element is not exist\n");
        }

        if (isEmpty(L)) {
            printf("list is empty\n");
        } else {
            printf("list is not empty\n");
        }

        printf("The 5 at %d\n", findElem(L, 5, *compare));
        preElem(L, 6, &e);
        printf("The 6's previous element is %d\n", e);
        nextElem(L, 6, &e);
        printf("The 6's next element is %d\n", e);
        deleteElem(&L, 1, &e);
        printf("delete first element is %d\n", e);
        printf("List:\n");
        traverseList(L, visit);
        if (destoryList(&L)) {
            printf("\ndestory_success\n");
        }
    }
    return 0;
}
