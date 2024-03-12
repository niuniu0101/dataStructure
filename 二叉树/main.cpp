/* Binary Trees Structure*/
/*---- ͷ�ļ������� ----*/
#include<stdio.h>
#include<stdlib.h>
#include "string.h"

/*---- Ԥ���� ----*/
// ���岼������TRUE��FALSE
#define TRUE 1
#define FALSE 0

// ���庯������ֵ����
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

// ��������Ԫ������
typedef int status;
typedef int KeyType;

// ����������������Ͷ���
typedef struct {
    KeyType key; // ���ؼ���
    char others[20]; // ����
} TElemType;

// ����������Ķ���
typedef struct BiTNode {
    TElemType data; // �������
    struct BiTNode *lchild, *rchild; // ��������ָ��
} BiTNode, *BiTree;

// �������ļ������Ͷ���
typedef struct {
// Ԫ�صļ���
    struct {
        char name[30]; // ��ʶԪ�ص�����
        BiTree T; // ������
    } elem[10]; // ���洢 10 ��Ԫ��
    int length; // Ԫ�ظ���
} LISTS;

LISTS Lists; // ���������ϵĶ��� Lists


/*---- �������� ----*/
status CreateBiTree(BiTree &T, TElemType definition[]);  //����
status DestroyBiTree(BiTree &T);  //����
status ClearBiTree(BiTree &T);  //���
status BiTreeEmpty(BiTree &T);  //�п�
int BiTreeDepth(BiTree T);   //�����
BiTNode* LocateNode(BiTree T, KeyType e);   //���ҽ��
status Assign(BiTree &T, KeyType e, TElemType value);  //��㸳ֵ
BiTNode* GetSibling(BiTree T, KeyType e);  //����ֵܽ��
status InsertNode(BiTree &T, KeyType e, int LR, TElemType c);  //������
BiTree findrightTNode(BiTree T);  //�ҵ�������
status DeleteNode(BiTree &T, KeyType e);  //ɾ�����
void visit(BiTree T);  //�����е��õķ��ʺ���
status PreOrderTraverse(BiTree T, void(*visit)(BiTree));  //ǰ�����
status InOrderTraverse(BiTree T, void(*visit)(BiTree));  //�������
status PostOrderTraverse(BiTree T, void(*visit)(BiTree));  //��������
status LevelOrderTraverse(BiTree T, void(*visit)(BiTree));  //�������
status SaveBiTree(BiTree T, char FileName[]);  //���浽�ļ�
status LoadBiTree(BiTree &T, char FileName[]);  //���ļ��м���
int MaxPathSum(BiTree T);  //���·����
BiTree LowestCommonAncestor(BiTree T, int e1, int e2);  //�����������
BiTree InvertTree(BiTree T);  //��ת������
void menufirst();  //������ͼ�Ĳ˵�
void menu();  //������ͼ�Ĳ˵�
void fun01();  //������ͼ�ķ�װ����
void fun02(BiTree & T );    //������ͼ�ķ�װ����

/*---- main������ ----*/
int main()
{
    system("color 37");//������ɫ
    fun01();
}




/*----  ��������  ----*/

status CreateBiTree(BiTree &T, TElemType definition[])
{
    /*
     * ���ݴ���֦�Ķ������ȸ���������definition����һ�ö�������
     * �����ڵ�ָ�븳ֵ��T������OK���������ͬ�Ĺؼ��֣�����ERROR��
     */

    static int i = 0; // ��̬��������¼��ǰ�Ѿ������������±�
    int j = 0, k = 0; // ѭ��������

    // ��һ�ε���ʱ����������Ƿ�Ϸ�
    if (i == 0) {
        // ���μ��ÿ���ڵ�ؼ����Ƿ�Ϸ�
        for (j = 0; (definition + j)->key != -1; j++) {
            for (k = j + 1; (definition + k)->key != -1; k++) {
                // ����������ؼ�����ͬ���Ҳ�Ϊ0�����ش���
                if ((definition + j)->key == (definition + k)->key && (definition + j)->key != 0)
                    return ERROR;
            }
        }
    }

    // �ݹ���ڣ����б���������TΪ��ֵ������OK
    if ((definition + i)->key == -1) {
        T = NULL;
        i = 0;
        return OK;
    }

    // �����ǰ�ڵ�Ϊ0����ʾ�ս�㣬���贴����������㣬i����������OK
    if ((definition + i)->key == 0) {
        i++;
        return OK;
    }

    // ������������㣬�ֱ����������������ݹ鹹�����ö�����
    T = (BiTree)malloc(sizeof(BiTNode));
    T->lchild = NULL;
    T->rchild = NULL;
    T->data = *(definition + i);
    i++;
    CreateBiTree(T->lchild, definition);
    CreateBiTree(T->rchild, definition);
    return OK;
}

status DestroyBiTree(BiTree &T)
{//�����������óɿգ���ɾ�����н�㣬�ͷŽ��ռ�

    if (T != NULL) // ��������������Ϊ��
    {
        if (T->lchild) // �����������Ϊ��
            DestroyBiTree(T->lchild); // �ݹ����������������Ϊ������Ҳ��һ�ö�������

        if (T->rchild) // �����������Ϊ��
            DestroyBiTree(T->rchild); // �ݹ����������������Ϊ������Ҳ��һ�ö�������

        free(T); // �ͷŵ�ǰ�ڵ�Ŀռ䣨��Ϊ��ǰ�ڵ�����������Ѿ��������ˣ�

        T = NULL; // ����ǰ�ڵ��ָ������ΪNULL����ʾ����ڵ��Ѿ���������
    }

    return OK; // ���ز����ɹ�
}

// ��ʼ�����Ƕ����� T ���ڣ���������ǽ������� T ���
status ClearBiTree(BiTree &T)
{
// ��������� T ��Ϊ�գ�����Ҫ�����������ֱ�ӷ��� OK
    if (T != NULL)
    {
// ��� T ����������Ϊ�գ���ݹ����������
        if (T->lchild)
            DestroyBiTree(T->lchild);

        // ��� T ����������Ϊ�գ���ݹ����������
        if (T->rchild)
            DestroyBiTree(T->rchild);

        // �ͷ� T ���ڴ�ռ䣬���� T ��ָ����Ϊ NULL
        free(T); // ʹ�õݹ������ͷ��������������������ڵ�ָ��
        T = NULL;
    }

// ���غ���ִ�н��
    return OK;
}

status BiTreeEmpty(BiTree &T)
{
    //��ʼ�����Ƕ�����T���ڣ������������TΪ�ն������򷵻�TRUE�����򷵻�FALSE
    if (T != NULL)
        return FALSE;
    else
        return TRUE;
}

int BiTreeDepth(BiTree T)
{
    //�������T�����

    int depth = 0;  //������� depth ����ʼ��Ϊ 0

    if (T != NULL)
    {
        int lchilddepth, rchilddepth;
        //�ݹ���������������
        lchilddepth = BiTreeDepth(T->lchild);
        //�ݹ���������������
        rchilddepth = BiTreeDepth(T->rchild);

        //ȡ����������Ƚϴ�ֵ������� 1����Ϊ��ǰ�ڵ��������������
        if (lchilddepth >= rchilddepth)
            depth = lchilddepth + 1;
        else
            depth = rchilddepth + 1;
    }

    return depth;   //���ص�ǰ�ڵ��������������
}

BiTNode* LocateNode(BiTree T, KeyType e)
{//���ҽ��
    if (T == NULL) // �����Ϊ�գ��򷵻ؿ�ָ��
        return NULL;
    BiTree st[100], p; // ����һ��ջ st �͵�ǰ�����Ľ�� p
    int top = 0; // top ��ʾջ��ָ��
    st[top++] = T; // �����ڵ���ջ
    while (top != 0) // ��ջ��Ϊ��ʱ
    {
        p = st[--top]; // ȡ��ջ��Ԫ��
        if (p->data.key == e) // ����ǰ����ֵ���� e���򷵻ص�ǰ���
            return p;
        if (p->rchild != NULL) // ����ǰ������������Ϊ�գ�����������ջ
            st[top++] = p->rchild;
        if (p->lchild != NULL) // ����ǰ������������Ϊ�գ�����������ջ
            st[top++] = p->lchild;
    }
    return NULL; // ���δ�ҵ���㣬�򷵻ؿ�ָ��
}

//�������ܣ�����������ĳ����㸳ֵ
status Assign(BiTree &T, KeyType e, TElemType value)
{
//�ж϶������Ƿ����
    if (T == NULL)
    {
        printf("������������\n");
        return ERROR;
    }

    int flag = 0;//���ڱ���Ƿ��ҵ���Ŀ����
    BiTree st[100], p;//����һ��������Ϊջ��һ��ָ�����ڱ���������
    int top = 0;//ջ��ָ��
    st[top++] = T;//�����������ڵ���ջ

//ѭ������������
    while (top != 0)
    {
        p = st[--top];//����ջ��Ԫ��

        //�жϲ���Ľ��ؼ����Ƿ�Ͷ������е���������ظ�
        if (p->data.key == value.key && e != value.key)
        {
            printf("�ؼ����ظ�\n");
            return ERROR;
        }

        //�ҵ���Ŀ����
        if (p->data.key == e)
        {
            p->data = value;//��Ŀ����������޸�Ϊ�µ�����
            flag = 1;//���Ϊ���ҵ�
        }

        //������������
        if (p->rchild != NULL)
            st[top++] = p->rchild;//��������ջ
        if (p->lchild != NULL)
            st[top++] = p->lchild;//��������ջ
    }

//�ж��Ƿ�ɹ��޸��˽������
    if(flag)
    {
        return OK;
    }
    return ERROR;
}

status InsertNode(BiTree &T, KeyType e, int LR, TElemType c)
// ����˵����
// T����������Ķ�����
// e����������ĸ��ڵ�ؼ���
// LR��������������ӻ����Һ��ӣ���LRΪ-1ʱ��Ϊ��������
// c����������
{
    BiTree t;  // ����һ�����������t
    int top = 0;  // ջ��ָ���ʼ��Ϊ0�������������û�õ�
    if (LR == -1)  // �����������Ҫ����Ϊ�����
    {
        t = (BiTree)malloc(sizeof(BiTNode));  // ��̬�����ڴ沢����Ϊ���������
        t->rchild = T;  // ��ԭ�еĶ�����T�����½�����������
        t->lchild = NULL;  // �½���������Ϊ��
        t->data = c;  // �½���������Ϊ����������c
        T = t;  // ԭ�еĶ�����T���滻Ϊ�½��t
        return OK;  // ����ɹ�
    }
    if (T == NULL)
        return ERROR;  // ���������Ķ�����Ϊ�գ��򷵻ش���
    BiTree q = (BiTree)malloc(sizeof(BiTNode));  // ��̬�����ڴ沢����Ϊ���������
    q->lchild = q->rchild = NULL;  // ����������Ϊ��
    q->data = c;  // �½���������Ϊ����������c
    if(LocateNode(T,c.key) != NULL)  // ����½��Ĺؼ����Ѿ�������T�У��򷵻ش���
    {
        printf("�ؼ����ظ�\n");
        return ERROR;
    }
    BiTree p = LocateNode(T, e);  // ��λ��������ĸ����
    if (!p)  // ����Ҳ�������㣬�򷵻ش���
        return ERROR;
    else{
        if (LR) {  // ���Ҫ����Ľ��Ϊ���ڵ���Һ���
            q->rchild = p->rchild;  // �����ڵ�������������½�����������
            p->rchild = q;  // ���½����ڸ��ڵ����������
            return OK;  // ����ɹ�
        }
        if (!LR) {  // ���Ҫ����Ľ��Ϊ���ڵ������
            q->rchild = p->lchild;  // �����ڵ�������������½�����������
            p->lchild = q;  // ���½����ڸ��ڵ����������
            return OK;  // ����ɹ�
        }
    }
}

// �ҵ������������ұߵĽ��
BiTree findrightTNode(BiTree T)
{
// ����һ��ջ�������ѱ����Ľ��
    BiTree stack[1000], p = NULL;
// ����ջ�Ķ���ָ��Ϊ0
    int top = 0;
// �����������Ϊ��
    if (T != NULL)
    {
// �Ѷ������ĸ��ڵ����ջ��
        stack[top++] = T;
// ѭ����ֱ��ջΪ��
        while (top)
        {
// ȡ��ջ��Ԫ�أ����Ѹ�Ԫ�ظ���p
            p = stack[--top];
// ��p������������ջ��
            if (p->rchild != NULL)
                stack[top++] = p->rchild;
// ��p������������ջ��
            if (p->lchild != NULL)
                stack[top++] = p->lchild;
        }
    }
// �������һ���������Ľ��
    return p;
}

//ɾ�����
status DeleteNode(BiTree &T, KeyType e)
{
    if (T == NULL) //���T�ǿ��������޷�ɾ�������ش������
        return INFEASIBLE;

    BiTree stack[1000], p, lp, TNode; //����ջ���Լ�����ָ��
    int top = 0; //ջ��

    if (T != NULL) //���T��Ϊ����
    {
        if (T->data.key == e) //���T�ĸ�������Ҫɾ���Ľ��
        {
            lp = T; //����Ҫɾ���Ľ��
            if (T->lchild == NULL && T->rchild == NULL) //���Ҫɾ���Ľ��û����������
            {
                free(lp); //ֱ���ͷ��ڴ�
                T = NULL; //���������ΪNULL
                return OK; //���سɹ�����
            }
            else if (T->lchild != NULL && T->rchild == NULL) //���Ҫɾ���Ľ��ֻ��������
            {
                T = T->lchild; //������������������µĸ����
                free(lp); //�ͷ��ڴ�
                return OK; //���سɹ�����
            }
            else if (lp->lchild == NULL && lp->rchild != NULL) //���Ҫɾ���Ľ��ֻ��������
            {
                T = T->rchild; //������������������µĸ����
                free(lp); //�ͷ��ڴ�
                return OK; //���سɹ�����
            }
            else //���Ҫɾ���Ľ���������������������
            {
                TNode = findrightTNode(T->lchild); //�ҵ�Ҫɾ���Ľ��������������ҽ��
                TNode->rchild = T->rchild; //��Ҫɾ���Ľ������������������������ҽ����
                T = T->lchild; //����������Ϊ�µ���
                free(lp); //�ͷ��ڴ�
                return OK; //���سɹ�����
            }
        }
        stack[top++] = T; //�������ջ
        while (top) //���ջ����Ԫ��
        {
            p = stack[--top]; //ջ��Ԫ�س�ջ
            if (p->rchild != NULL) //���ջ��Ԫ����������
            {
                if (p->rchild->data.key == e) //���ջ��Ԫ�ص�����������Ҫɾ���Ľ��
                {
                    lp = p->rchild; //����Ҫɾ���Ľ��
                    if (lp->lchild == NULL && lp->rchild == NULL) //���Ҫɾ���Ľ��û����������
                    {
                        free(lp); //ֱ���ͷ��ڴ�
                        p->rchild = NULL; //����������������ΪNULL
                        return OK; //���سɹ�����
                    }
                    else if (lp->lchild != NULL && lp->rchild == NULL) //���Ҫɾ���Ľ��ֻ��������
                    {
                        p->rchild = lp->lchild;
                        free(lp);
                        return OK; //���سɹ�����
                    }
                    else if (lp->lchild == NULL && lp->rchild != NULL) //���Ҫɾ���Ľ��ֻ��������
                    {
                        p->rchild = lp->rchild;
                        free(lp);
                        return OK; //���سɹ�����
                    }
                    else //���Ҫɾ���Ľ���������������������
                    {
                        TNode = findrightTNode(lp->lchild); //�ҵ�Ҫɾ���Ľ��������������ҽ��
                        TNode->rchild = lp->rchild; //��Ҫɾ���Ľ������������������������ҽ����
                        p->rchild = lp->lchild; //����������Ϊ������������
                        free(lp);
                        return OK; //���سɹ�����
                    }
                }
                stack[top++] = p->rchild; //��������ջ
            }
            if (p->lchild != NULL) //���ջ��Ԫ����������
            {
                if (p->lchild->data.key == e) //���ջ��Ԫ�ص�����������Ҫɾ���Ľ��
                {
                    lp = p->lchild; //����Ҫɾ���Ľ��
                    if (lp->lchild == NULL && lp->rchild == NULL) //���Ҫɾ���Ľ��û����������
                    {
                        free(lp); //ֱ���ͷ��ڴ�
                        p->lchild = NULL; //����������������ΪNULL
                        return OK; //���سɹ�����
                    }
                    else if (lp->lchild != NULL && lp->rchild == NULL) //���Ҫɾ���Ľ��ֻ��������
                    {
                        p->lchild = lp->lchild;
                        free(lp);
                        return OK; //���سɹ�����
                    }
                    else if (lp->lchild == NULL && lp->rchild != NULL) //���Ҫɾ���Ľ��ֻ��������
                    {
                        p->lchild = lp->rchild;
                        free(lp);
                        return OK; //���سɹ�����
                    }
                    else //���Ҫɾ���Ľ���������������������
                    {
                        TNode = findrightTNode(lp->lchild); //�ҵ�Ҫɾ���Ľ��������������ҽ��
                        TNode->rchild = lp->rchild; //��Ҫɾ���Ľ������������������������ҽ����
                        p->lchild = lp->lchild; //����������Ϊ������������
                        free(lp);
                        return OK; //���سɹ�����
                    }
                }
                stack[top++] = p->lchild; //��������ջ
            }
        }
    }
    return ERROR; //���ش������
}

//һ���򵥵��������
void visit(BiTree T)
{
    printf(" %d,%s", T->data.key, T->data.others);
}

// �������������T
status PreOrderTraverse(BiTree T, void(*visit)(BiTree))
{
// ���T�ǿ�����ֱ�ӷ���
    if (T == NULL)
        return OK;
// ����һ��ջst��ͬʱ����ջ��ָ��top��һ��ָ��p
    BiTree st[100], p;
    int top = 0;
// ���ڵ�����ջ
    st[top++] = T;
// ��ջ��Ϊ��ʱ��ѭ������
    while (top != 0)
    {
// ָ��pָ��ջ��Ԫ��
        p = st[--top];
// ��p���з���
        visit(p);
// ���p��������Ϊ�գ�����������ջ
        if (p->rchild != NULL)
            st[top++] = p->rchild;
// ���p��������Ϊ�գ�����������ջ����֤�����������ȱ���
        if (p->lchild != NULL)
            st[top++] = p->lchild;
    }
// ������ɣ�����OK
    return OK;
}

//�������������T
status InOrderTraverse(BiTree T, void(*visit)(BiTree))
{
// ���TΪ�գ���ֱ�ӷ���
    if (T == NULL)
        return OK;
// ���T�ǿգ�����б�������
    if (T != NULL)
    {
// ��T�����������б���
        if (InOrderTraverse(T->lchild, visit))
        {
// ��T���з��ʲ���
            visit(T);
// ��T�����������б���
            if (InOrderTraverse(T->rchild, visit))
// ��������ɹ����򷵻�OK����ʾ���������ɹ�
                return OK;
        }
// ���������������������ʧ�ܣ��򷵻�ERROR����ʾ��������ʧ��
        return ERROR;
    }
// ���TΪ�գ���ֱ�ӷ���
    else
        return OK;
}

// �������������T
status PostOrderTraverse(BiTree T, void(*visit)(BiTree))
{
// ���������Ϊ�գ����������
    if (T == NULL)
        return OK;
// ����������ǿ�
    if (T != NULL)
    {
// �ݹ��������������������������ɹ�
        if (PostOrderTraverse(T->lchild, visit)) {
// �ݹ��������������������������ɹ�
            if (PostOrderTraverse(T->rchild, visit)) {
// ���ʵ�ǰ���
                visit(T);
                return OK;
            }
        }
// ���������������������ʧ�ܣ��򷵻�ʧ��
        return 0;
    }
    else
        return OK;
}

//�������
status LevelOrderTraverse(BiTree T, void(*visit)(BiTree))
{//�������������T
    if (T == NULL) //�������Ķ�����Ϊ������ֱ�ӷ���
        return OK;
    BiTree st[200], p; //����һ�����飬�����ԱΪBiTree���ͣ���һ�����p
    int front = 0, rear = 0; //��������������front������п�ͷ��rear������н�β
    st[rear++] = T; //������Ķ������ĸ��ڵ��������ĵ�һ�����
    do //ʹ��ѭ��ʵ�ֱ���
    {
        p = st[front++]; //�����п�ͷ��Ԫ�ظ�ֵ������p�������¶��п�ͷ
        visit(p); //�Ե�ǰ�����б���
        if (p->lchild != NULL) //�����ǰ��������ӣ���������β
            st[rear++] = p->lchild;
        if (p->rchild != NULL) //�����ǰ������Һ��ӣ���������β
            st[rear++] = p->rchild;
    } while (rear != front); //�������н�㣬����ѭ��
    return OK; //������ɣ�����״̬��
}

//���������Ľ������д�뵽�ļ�FileName��
status SaveBiTree(BiTree T, char FileName[]) {
    if (T == NULL) //������δ������������������
        return INFEASIBLE;
    FILE *fp = fopen(FileName, "w"); //��д�뷽ʽ���ļ�
    if (fp == NULL)
        return ERROR; //�ļ�ָ��򲻿�������
    BiTree st[100]; //��������ģ��ջ
    int mark[100], p = 0; //��¼ÿ������״̬��pΪջ��ָ��
    // ��ʼ��ջ��ָ��
    st[0] = T, mark[0] = 0;
    while (p != -1) { //ջ�ǿ����������
        if (mark[p] == 0) { //��һ�η��ʸý��
            //���������д���ļ�
            fprintf(fp, "%d %s ", st[p]->data.key, st[p]->data.others);
            mark[p]++; //��״̬��Ϊ�ѷ���������
            if (st[p]->lchild == NULL)
                fprintf(fp, "%d null ", 0); //���������Ϊ�գ�д��null
            else {
                st[p + 1] = st[p]->lchild; //���������������ջ
                p++; //ָ�����
                mark[p] = 0; //�½��״̬��ʼ��
            }
        }
        else if (mark[p] == 1) { //�ڶ��η��ʸý��
            mark[p]++; //״̬��Ϊ�ѷ���������
            if (st[p]->rchild == NULL)
                fprintf(fp, "%d null ", 0); //���������Ϊ�գ�д��null
            else {
                st[p + 1] = st[p]->rchild; //���������������ջ
                p++; //ָ�����
                mark[p] = 0; //�½��״̬��ʼ��
            }
        }
        else if (mark[p] == 2) { //�����η��ʸý��
            mark[p] = 0; //״̬��Ϊδ����
            st[p] = NULL; //���ý���ջ
            p--; //ָ��ǰ��
        }
    }
    // д�������־��
    fprintf(fp, "%d null", -1);
    fclose(fp); //�ر��ļ�ָ��
    return OK;
}

//�ú������ڶ�ȡ�ļ��е����ݣ�����һ�Ŷ�����
status LoadBiTree(BiTree &T, char FileName[])
{
    //�������Ķ������Ѿ����ڣ����޷����в���
    if (T != NULL)
    {
        printf("�������Ѿ���ʼ�����޷�����\n");
        return INFEASIBLE;
    }

    //���Դ��ļ�
    FILE *fp = fopen(FileName, "r");
    if (fp == NULL)
        return ERROR;//�ļ�ָ��򲻿������ش���
    TElemType definitionfile[100];//����ṹ���������飬���ڴ洢��ȡ������ֵ
    BiTree st[100];//����ָ��ڵ��ָ������
    int mark[100], p = 0;//����һ��������飬��һ�����λ�õ�ָ��p������ʼ��Ϊ0

    //�����ļ��е����ݣ��洢��definitionfile[]������
    int t = -1;
    do {
        t++;
        fscanf(fp, "%d%s", &definitionfile[t].key, definitionfile[t].others);
    } while (definitionfile[t].key != -1);

    //�ж��ļ��еĵ�һ������Ƿ�ΪNULL����������򴴽����ڵ�
    if (definitionfile[0].key != -1) {
        T = st[0] = (BiTNode*)malloc(sizeof(BiTNode)), mark[0] = 0;
        st[0]->data = definitionfile[t++];
    }
    else
        return INFEASIBLE;//���ش���

    t = 0;
    //����ļ��еĵ�һ����㲻��NULL����ʼѭ���������νṹ
    while (definitionfile[t].key != -1) {
        //������λ���ϵ�ֵΪ0����˵����Ҫ�ڸýڵ�����ӽڵ�����½ڵ�
        if (mark[p] == 0)
        {
            mark[p]++;
            //����ýڵ�����ӽڵ�ΪNULL����Mark����λ��+1�������½ڵ�
            if (definitionfile[t].key == 0)
                st[p]->lchild = NULL;
            else
            {
                st[p]->lchild = (BiTNode*)malloc(sizeof(BiTNode));
                //���½ڵ�ָ���λ�õ�ֵ��ֵΪdefinitionfile[t]��ֵ��Mark����λ��+1
                st[p + 1] = st[p]->lchild;
                p++;
                st[p]->data = definitionfile[t];
                mark[p] = 0;
            }
            t++;
        }
            //������λ���ϵ�ֵΪ1����˵����Ҫ�ڸýڵ�����ӽڵ�����½ڵ�
        else if (mark[p] == 1)
        {
            mark[p]++;
            //����ýڵ�����ӽڵ�ΪNULL����Mark����λ��+1�������½ڵ�
            if (definitionfile[t].key == 0)
                st[p]->rchild = NULL;
            else {
                st[p]->rchild = (BiTNode*)malloc(sizeof(BiTNode));
                //���½ڵ�ָ���λ�õ�ֵ��ֵΪdefinitionfile[t]��ֵ��Mark����λ��+1
                st[p + 1] = st[p]->rchild;
                p++;
                st[p]->data = definitionfile[t];
                mark[p] = 0;
            }
            t++;
        }
            //������λ���ϵ�ֵΪ2����˵���ýڵ�������ӽڵ㶼�������ˣ���Ҫ���˵���һ���ڵ�
        else if (mark[p] == 2)
        {
            mark[p] = 0;//����Mark����λ���ϵ�ֵΪ0
            st[p] = NULL;//����λ�õ�ָ����NULL
            p--;//���λ��ָ���˻���һ���ڵ�
        }
    }

    fclose(fp);//�ر��ļ�
    return OK;
}

int MaxPathSum(BiTree T)
{//��ʼ�����Ƕ�����T���ڣ���������Ƿ��ظ��ڵ㵽Ҷ�ӽ������·���ͣ�

    // �����ǰ�����Ҷ�ӽ�㣬��ֱ�ӷ��ظý��ļ�ֵ
    if (T->lchild == NULL && T->rchild == NULL)
        return T->data.key;

        // ���������Ϊ�գ���������������ڵ��·����
    else if (T->lchild == NULL && T->rchild != NULL)
        return MaxPathSum(T->rchild) + T->data.key;

        // ���������Ϊ�գ���������������ڵ��·����
    else if (T->lchild != NULL && T->rchild == NULL)
        return MaxPathSum(T->lchild) + T->data.key;

    // ��������������ǿգ�������������������·���ͣ�������ǰ�ڵ�ļ�ֵ�����������������·�����еĽϴ�ֵ
    int leftmax = 0, rightmax = 0;
    leftmax = MaxPathSum(T->lchild);
    rightmax = MaxPathSum(T->rchild);
    if (leftmax > rightmax)
        return leftmax + T->data.key;
    else
        return rightmax + T->data.key;
}

//�ú����Ĺ����ǣ����ض�����T��e1�ڵ��e2�ڵ�������������
BiTree LowestCommonAncestor(BiTree T, int e1, int e2)
{
//���ҵ��ڵ�p1��p2���ֱ����e1��e2�ڶ������ж�Ӧ�Ľ��
    BiTree p1 = LocateNode(T,e1);
    BiTree p2 = LocateNode(T,e2);
//����һ����־����flag�����ڱ���Ƿ��жϹ�����Ƿ����
    static int flag = 0;
    if(flag == 0)//���flag��0��˵����û���жϹ�����Ƿ����
    {
        flag = 1;
//���e1��e2��Ӧ�Ľ�㲻���ڣ�������������һ����Ӧ�Ľ�㲻���ڣ�
//��������󲢷���NULL
        if( p1 == NULL || p2 == NULL)
        {
            printf("����Ĺؼ��ִ���\n");
            return NULL;
        }
    }

//���������Ϊ�գ�����T���Ĺؼ���Ϊe1��e2���򷵻�T���
    if (T == NULL || T->data.key == e1 || T->data.key == e2)
        return T;
//�ݹ����������
    BiTree left = LowestCommonAncestor(T->lchild, e1, e2);
//�ݹ����������
    BiTree right = LowestCommonAncestor(T->rchild, e1, e2);
//���leftΪ�գ�˵���������ڵ���T�����������ϣ�����ֻ��Ҫ�������������ҵĽ������
    if (left == NULL)
        return right;
//���rightΪ�գ�˵���������ڵ���T�����������ϣ�����ֻ��Ҫ�������������ҵĽ������
    if (right == NULL)
        return left;
//���left��right����Ϊ�գ�˵���������ڵ�һ����T����������һ����T����������
//T������e1��e2�Ĺ������ȣ�
    return T;
}

//�������ƣ�BiTree InvertTree(BiTree T)
//�������ܣ���������T��ת��ʹ�����нڵ�����ҽڵ㻥��
//����˵����������T
//����ֵ����ת��Ķ�����T

BiTree InvertTree(BiTree T)
{
//���������Ϊ�գ���ֱ�ӷ���
    if (T == NULL)
        return NULL;

//�ݹ鴦����������������������ת��Ľ��
    BiTree left = InvertTree(T->lchild);

//�ݹ鴦����������������������ת��Ľ��
    BiTree right = InvertTree(T->rchild);

//�������ҽڵ�
    T->lchild = right;
    T->rchild = left;

//���ط�ת��Ľ��
    return T;
}

void fun01()
{
    menufirst(); // ������˵����ṩ��ѡ�Ĳ�������
    int a ; // ������/ѡ��
    printf("������һ������\n");
    scanf("%d",&a);

    while (a) // �������0ʱ���������в���
    {
        fflush(stdin); //�������������ֹ��һ�β������������������ݶ�Ӱ�챾�β���

        int feedback; // ��������ֵ

        switch (a) { // ���������Ž�����Ӧ�Ĳ���
            case 1: // ����һ���µĶ�����
                printf("���ڽ��д���һ���µĶ�����\n");
                printf("���������봴���Ķ�����������\n");
                char name1[30]; // ���ڴ洢����Ķ���������
                scanf("%s",name1);
                int i ,flag ; flag = 0; // ���λ�������ж��Ƿ��Ѵ���ͬ��������

                // Ҫ�������ֵ��жϣ����������е����ж���������
                for( i =0;i<Lists.length;i++)
                {
                    if(strcmp(name1,Lists.elem[i].name)  == 0) //��������Ѿ����ڣ����޷��������������
                    {
                        printf("�ö������Ѿ����ڣ�����ʧ��\n");
                        flag = 1;
                    }
                }

                if(flag == 0) // ���������ͬ��������������Դ���
                {
                    //���µĶ��������ּ��뵽����Lists�У�����Lists�ĳ��ȼ�1
                    strcpy(Lists.elem[Lists.length].name,name1);
                    Lists.length++;
                    printf("�����ɹ���\n");
                }
                break;

            case 2: // ɾ��������
                int flag2 ; // ���λ�����ڼ�¼Ҫɾ���Ķ������������е�λ��
                printf("���ڽ���ɾ���������Ĳ���\n");
                printf("����������ɾ���Ķ�����������\n");
                char name2[30]; // ���ڴ洢Ŀ�����������
                scanf("%s",name2);
                flag2 = -1; //flag2���ڱ��Ҫɾ���Ķ�������Lists�����е�λ��

                //���������е����ж��������֣��������Ŀ�������������±��λ
                for( i =0;i<Lists.length;i++)
                {
                    if(strcmp(name2,Lists.elem[i].name)  == 0)
                    {
                        flag2 = i;
                    }
                }

                if(flag2 == -1) // ���������Ŀ������������޷�����ɾ������
                {
                    printf("�ö����������ڣ��޷�ɾ��\n");
                }
                else{
                    feedback = DestroyBiTree(Lists.elem[flag2].T); // ����DestroyBiTree��������ָ��λ�ô��Ķ�����

                    if(feedback == OK) // ��������ɹ�
                    {
                        //��Lists������ָ��λ��֮���Ԫ����ǰ�ƶ�һ��λ�ã�ͬʱ��Lists�ĳ��ȼ�1
                        int k;
                        for( k = 0 ;k < Lists.length-1 ;k++)
                        {
                            Lists.elem[k] = Lists.elem[k+1];
                        }
                        Lists.length--;
                        printf("ɾ���ɹ�\n");
                    }
                }
                break;

            case 3: // ��ѯ��������Щ������
                printf("���ڽ��в�ѯ��������Щ������\n");
                printf("���еĶ���������:\n");

                //���������е����ж��������֣����ÿ��������������
                for(i = 0; i<Lists.length ;i++)
                {
                    printf("%d)   %s\n",i+1,Lists.elem[i].name);
                }
                break;

            case 4: // �Զ��������в���
                printf("���ڽ��ж������Ĳ��ҺͲ���\n");
                printf("������������ҺͲ����Ķ�����������\n");
                char name3[30]; // ���ڴ洢Ŀ�����������
                scanf("%s",name3);
                int flag3 ;flag3 = -1; //flag3���ڱ��Ҫ�����Ķ�������Lists�����е�λ��

                //���������е����ж��������֣��������Ŀ�������������±��λ
                for( i =0 ; i<Lists.length ;i++)
                {
                    if(strcmp(Lists.elem[i].name,name3) == 0)
                    {
                        flag3 = i;
                    }
                }

                if(flag3 ==-1) // ���������Ŀ������������޷����в���
                {
                    printf("���������������\n");
                    system("pause");
                }
                else {
                    //����fun02�������ض�λ�ô��Ķ��������в���
                    fun02(Lists.elem[flag3].T);
                }
                break;

            default:
                printf("���������������ٴ�����"); //������������ڿ�ѡ��Χ�ڣ�����ʾ�����������
        }

        printf("��������һ������\n");
        scanf("%d",&a);
        system("cls"); //ÿ�β��������������Ļ������������˵�
        menufirst();
    }
}


/**
 * ���庯��fun02���������BiTree &T
 */
void fun02(BiTree &T)
{
    /**
     * �������definition[100]�����ڴ洢����Ķ�����������
     * �������op��i��next�����ڽ����û����������
     */
    TElemType definition[100];
    int op = 0,i =0,next = 0;

    /**
     * ��տ���̨���
     * ���ú���menu()��������˵�
     * �����ʾ��䣬���û���������
     */
    system("cls");
    menu();
    printf("�������������\n");
    scanf("%d",&op);

    /**
     * ����ѭ����ֻҪop��Ϊ0����ִ�д�����ڵĲ���
     */
    while (op)
    {
        /**
         * ʹ��switch��䣬���ݲ�ͬ������ִ�в�ͬ�Ĳ���
         */
        switch (op) {
            case 1:
                i = 0;
                /**
                 * ���T�Ѿ����ڣ������Ӧ����ʾ��䣬ִ��break����switch���
                 */
                if(T)
                {
                    printf("�������Ѿ���ʼ��������ʧ��\n");
                    break;
                }
                /**
                 * ������Ҫ�����Ķ�����������
                 * ����CreateBiTree�������д���
                 * ��������ɹ��������Ӧ����ʾ���
                 * �������ʧ�ܣ������Ӧ����ʾ���
                 */
                printf("��������������ݣ�\n");
                do {
                    scanf("%d%s", &definition[i].key, definition[i].others);
                } while (definition[i++].key != -1);
                if (CreateBiTree(T, definition) == OK)
                {
                    printf("�����������ɹ�\n");
                }
                else
                    printf("����������ʧ�ܣ�\n");
                break;
            case 2:
                /**
                 * ����DestroyBiTree�������ж�����������
                 * ������ٳɹ��������Ӧ����ʾ���
                 * �������ʧ�ܣ������Ӧ����ʾ���
                 */
                printf("���ڽ��ж�����������\n");
                if (DestroyBiTree(T) == OK)
                    printf("���������ٳɹ�!\n");
                else
                    printf("����������ʧ��!\n");
                break;
            case 3:
                /**
                 * ����ClearBiTree�������ж����������
                 * �����ճɹ��������Ӧ����ʾ���
                 * ������ʧ�ܣ������Ӧ����ʾ���
                 */
                printf("���ڽ��ж����������\n");
                if (ClearBiTree(T) == OK)
                    printf("��������ճɹ�!\n");
                else
                    printf("���������ʧ��!\n");
                break;
            case 4:
                /**
                 * ����BiTreeEmpty�����ж϶������Ƿ�Ϊ��
                 * ���Ϊ�գ������Ӧ����ʾ���
                 * �����Ϊ�գ������Ӧ����ʾ���
                 */
                printf("���ڽ��ж��������пղ���\n");
                if (BiTreeEmpty(T) == TRUE)
                    printf("�������ǿ���!\n");
                else if (BiTreeEmpty(T) == FALSE)
                    printf("���������ǿ���!\n");
                else
                    printf("������������!\n");
                break;
            case 5:
                /**
                 * ����BiTreeDepth����������������
                 * ������ɹ��������Ӧ����ʾ���
                 * ������ʧ�ܣ������Ӧ����ʾ���
                 */
                printf("����������������\n");
                int j5;  //���ն���������Ⱥ����ķ���ֵ
                if (T == NULL) {
                    printf("������������!\n");
                    break;
                }
                j5 = BiTreeDepth(T);
                if(j5 == -1)
                {
                    printf("����ʧ��\n");
                }
                else{
                    printf("�����������Ϊ%d!\n", j5);
                }
                break;
            case 6:
                /**
                 * ������Ҫ���ҵĽ��ؼ���
                 * ����LocateNode�������в���
                 * ������ҳɹ��������Ӧ����ʾ��估���ҽ��
                 * �������ʧ�ܣ������Ӧ����ʾ���
                 */
                // ������Ҫ���ҵĽ��ؼ���
                int e6;
                // ������������ָ��
                BiTree p6;
                // �ж϶������Ƿ����
                if (T == NULL) {
                    printf("������������!\n");
                    break;
                }
                // ��ʾ�û�������Ҫ���ҵĽ��ؼ���
                printf("��������Ҫ���ҵĽ��ؼ��֣�\n");
                // �����û��������Ҫ���ҵĽ��ؼ���
                scanf("%d", &e6);
                // ����LocateNode�������ж������Ĳ��Ҳ��������ز��ҽ����p6��
                p6 = LocateNode(T, e6);
                // �ж��Ƿ���ҵ�Ŀ����
                if (p6 == NULL)
                    printf("����ʧ��!\n");
                else
                    // ������ҽ��
                    printf("���ҳɹ�!��ֵΪ��%s\n",p6->data.others);
                break;
            case 7:
                int e7, j7; // �������
                KeyType k7; // ����ؼ�������
                TElemType value7; // ��������������
                if (T == NULL) { // ���������Ϊ�գ������ʾ���
                    printf("������������!\n");
                    break;
                }
                printf("��������Ҫ��ֵ�Ľ��Ĺؼ��֣�\n"); // ��ʾ����
                scanf("%d", &k7); // ��ȡ�ؼ���
                printf("��������Ҫ��ֵ�����ݣ�\n"); // ��ʾ����������
                scanf("%d %s", &value7.key, &value7.others); // ��ȡ�������
                j7 = Assign(T,k7,value7); // ���ø�ֵ����������״ֵ̬
                if (j7 == ERROR) // �����ֵʧ�ܣ������Ӧ����ʾ���
                    printf("��ֵʧ��!\n");
                else if (j7 == INFEASIBLE) // ��������������ڣ������Ӧ����ʾ���
                    printf("������������!\n");
                else // �����ֵ�ɹ��������Ӧ����ʾ���
                    printf("��ֵ�ɹ�!\n");
                break;

             case 8:
                int e8; // �������
                BiTree p8; // ���������ָ��
                if (T == NULL) { // ���������Ϊ�գ������Ӧ����ʾ���
                    printf("������������!\n");
                    break;
                }
                printf("��������Ҫ��õ��ֵܽ��Ĺؼ��֣�\n"); // ��ʾ����
                scanf("%d", &e8); // ��ȡ�ؼ���
                p8 = GetSibling(T, e8); // ���û�ȡ�ֵܽ�㺯���������ֵܽ��ָ��
                if (p8 == NULL) // �����ȡʧ�ܣ������Ӧ����ʾ���
                    printf("��ȡʧ��!\n");
                else // �����ȡ�ɹ��������Ӧ����ʾ�����ֵܽ������
                    printf("��ȡ�ֵܽ��ɹ�!��ֵΪ��%d %s\n",p8->data.key, p8->data.others);
                break;
                case 9:    //������
                int e9, j9, LR; // e9��j9��LRΪ���������ڴ洢�û������ֵ
                TElemType value9; // value9Ϊ�ṹ�����ͣ����ڴ洢�û����������
                if (T == NULL) { // ��������������ڣ��������ʾ��Ϣ������
                    printf("������������!\n");
                    getchar(); getchar();
                    break;
                }
                printf("��������Ҫ������Ĺؼ��ֺ�LR��\n"); // ��ʾ�û�����ؼ��ֺ�LR
                scanf("%d %d", &e9, &LR); // ���������л�ȡ�û�����

                printf("���������������ݣ���ʽ��1 a����\n"); // ��ʾ�û��������������
                scanf("%d%s", &value9.key,value9.others); // ���������л�ȡ�û�����
                j9 = InsertNode(T, e9, LR,value9); // ����InsertNode����������
                if (j9 == ERROR) // �������ʧ�ܣ������ʾ��Ϣ
                    printf("������ʧ��!\n");
                else if (j9 == OK) // �������ɹ��������ʾ��Ϣ
                    printf("������ɹ�!\n");

                break; // ����case 9

                case 10:   //ɾ�����
                int e10, j10; // e10��j10Ϊ���������ڴ洢�û������ֵ
                if (T == NULL) { // ��������������ڣ��������ʾ��Ϣ������
                    printf("������������!\n");
                    break;
                }
                printf("��������Ҫɾ�����Ĺؼ��֣�\n"); // ��ʾ�û������ɾ�����Ĺؼ���
                scanf("%d", &e10); // ���������л�ȡ�û�����
                j10 = DeleteNode(T, e10); // ����DeleteNode����ɾ�����
                if (j10 == ERROR) // ���ɾ��ʧ�ܣ������ʾ��Ϣ
                    printf("ɾ�����ʧ��!\n");
                else if (j10 == OK) // ���ɾ���ɹ��������ʾ��Ϣ
                    printf("ɾ�����ɹ�!\n");

                break; // ����case 10

             case 11:  //�������
                int j11; // j11Ϊ���������ڴ洢������������ķ���ֵ
                if (T == NULL) { // ��������������ڣ��������ʾ��Ϣ������
                    printf("������������!\n");
                    break;
                }
                j11 = PreOrderTraverse(T,visit); // ����PreOrderTraverse��������������
                if (j11 == OK) // ��������ɹ��������ʾ��Ϣ
                    printf("\n����������!\n");
                else{ // �������ʧ�ܣ������ʾ��Ϣ
                    printf("����ʧ��\n");
                }

                break; // ����case 11

            case 12:
                int j12;//����һ�����ͱ��� j12�����ڴ洢 InOrderTraverse �����ķ���ֵ
                if (T == NULL) {//��������� T ������
                    printf("������������!\n");//�����ʾ��Ϣ
                    break;//���� switch-case ѭ��
                }
                j12 = InOrderTraverse(T, visit);//ִ������������� InOrderTraverse����������ֵ�洢�� j12 ������
                if (j12 == OK)//��������ɹ�
                    printf("\n����������!\n");//�����ʾ��Ϣ
                else
                    printf("\n����ʧ��!\n");//�����ʾ��Ϣ

                break;//���� switch-case ѭ��
            case 13:
                int j13;//����һ�����ͱ��� j13�����ڴ洢 PostOrderTraverse �����ķ���ֵ
                if (T == NULL) {//��������� T ������
                    printf("������������!\n");//�����ʾ��Ϣ

                    break;//���� switch-case ѭ��
                }
                j13 = PostOrderTraverse(T,visit);//ִ�к���������� PostOrderTraverse����������ֵ�洢�� j13 ������
                if (j13 == OK)//��������ɹ�
                    printf("\n��ɺ������!\n");//�����ʾ��Ϣ
                else
                    printf("\n����ʧ��!\n");//�����ʾ��Ϣ

                break;//���� switch-case ѭ��
            case 14:
                int j14;//����һ�����ͱ��� j14�����ڴ洢 LevelOrderTraverse �����ķ���ֵ
                if (T == NULL) {//��������� T ������
                    printf("������������!\n");//�����ʾ��Ϣ

                    break;//���� switch-case ѭ��
                }
                j14 = LevelOrderTraverse(T, visit);//ִ�а���������� LevelOrderTraverse����������ֵ�洢�� j14 ������
                if (j14 == OK)//��������ɹ�
                    printf("\n��ɰ������!\n");//�����ʾ��Ϣ
                else
                    printf("\n����ʧ��!\n");//�����ʾ��Ϣ

                break;//���� switch-case ѭ��
            case 15:
                int j15;//����һ�����ͱ��� j15�����ڴ洢 MaxPathSum �����ķ���ֵ
                if (T == NULL) {//��������� T ������
                    printf("������������!\n");//�����ʾ��Ϣ
                    getchar(); getchar();//��ͣ����ִ�У��ȴ��û�����

                    break;//���� switch-case ѭ��
                }
                j15 = MaxPathSum(T);//ִ�м�����������·���ͺ��� MaxPathSum����������ֵ�洢�� j15 ������
                printf("���������·����Ϊ��%d!\n",j15);//���������

                break;//���� switch-case ѭ��

            case 16:
                if (T == NULL) {
                    printf("������������!\n");

                    break;
                }
               
				
                int i16, j16; //��Ҫ���ҹ������ȵĵ�һ���ڵ�Ĺؼ��ֺ͵ڶ����ڵ�Ĺؼ���
                BiTree T16;  //���ҵ��Ĺ������Ƚڵ�
                printf("��������Ҫ�����������ȵ��������Ĺؼ��֣�\n");
                scanf("%d %d", &i16, &j16);
                T16 = LowestCommonAncestor(T, i16, j16);
                if (T16 == NULL)
                {
                    printf("����ʧ��!\n");
                }

                else
                {
                    printf("���ҳɹ���\n");
                    printf("�������ȵĹؼ���Ϊ��%d,������Ϊ%s\n", T16->data.key, T16->data.others);
                }
                

                break;

            case 17:
                if (T == NULL) {
                    printf("������������!\n");
                    getchar();
                    break;
                }
                InvertTree(T);
                printf("�ѳɹ���ת��������\n");

                break;
            case 18:
                int j18;
                char FileName18[30];  //���浽���ļ���
                printf("������Ҫд����ļ�����\n");
                scanf("%s", FileName18);
                j18 = SaveBiTree(T, FileName18);
                if (j18 == INFEASIBLE)
                    printf("������������!\n");
                else
                    printf("�ɹ���������д���ļ���Ϊ��%s���ļ���!\n", FileName18);

                break;
            case 19:
                int j19;
                char FileName19[30];   //����ȡ���ݵ��ļ���
                printf("������Ҫ��ȡ���ļ�����\n");
                scanf("%s", FileName19);
                j19 = LoadBiTree(T, FileName19);
                if (j19 == INFEASIBLE)
                    printf("����������!�޷����ǣ�\n");
                else if (j19 == ERROR) {
                    printf("��ȡ�ļ�ʧ�ܣ�\n");
                }
                else{
                    printf("�ɹ���%s�ļ��е����ݶ��뵽��������!\n", FileName19);
                }

                break;


            case 0:
                break;
        }
        putchar('\n');
        printf("��������һ������\n");
        scanf("%d",&op);
        system("cls");
        if(op != 0)   //����˳��ͼ��ص�һ���˵�
        {
            menu();
        }
        else{
            menufirst();
        }


    }
}

void menufirst()
{
    for(int k = 0; k<=  119 ;k++)
    {
        putchar('-');
    }  putchar('\n');
    printf("1.����һ��������\n");
    printf("2.ɾ��һ��������\n");
    printf("3.��ѯ�Ѿ������Ķ�����\n");
    printf("4.����һ���������ͽ��в���\n");
    printf("0.�˳�����������Ĺ���\n");

    printf("    �ء�����������|\n");
    printf("����/��7������ �ϣ�/\n");
    printf("�� /�������� ������\n");
    printf("������Z ��,���������� /`�c\n");
    printf("���������������c���� /������\n");
    printf(" Y����������`�� /����/\n");
    printf("��?��?���񡡡�??������/\n");
    printf("��()�� �ء�������|���ܡ�\n");
    printf("��>? ?_�� ���� �� ����\n");
    printf("�� / �ء��� /��?��| �ܣ�\n");
    printf("�� �c_?����(_���� ������\n");
    printf("����7��������������|��\n");
    printf("�������Dr����`?�D��\n");
    for(int k = 0; k<=  119 ;k++)
    {
        putchar('-');
    }  putchar('\n');
}

void menu()
{

    printf("       Menu for Binary Tree On Binary Linked List    \n");
    printf("------------------------------------------------------\n");
    printf("**     1. ������ʼ��������    11.ǰ�����              **\n");
    printf("**     2. ���ٶ�����         12. �������             **\n");
    printf("**     3. ��ն�����         13. �������             **\n");
    printf("**     4. �������п�         14. �������             **\n");
    printf("**     5. ������������      15. ���·����           **\n");
    printf("**     6. ���ҽ��           16. �����������         **\n");
    printf("**     7. ��㸳ֵ           17. ��ת������           **\n");
    printf("**     8. ����ֵܽ��        18. ���������ļ�����      **\n");
    printf("**     9. ������           19. ���������ļ�����      **\n");
    printf("**     10. ɾ�����          0. Exit                **\n");
    printf("------------------------------------------------------\n");
    printf("    ��ѡ����Ĳ���[0~19]:\n");

}

//��ȡָ�����e���ֵܽ��
BiTNode* GetSibling(BiTree T, KeyType e)
{
    if (T == NULL) //��������Ϊ�գ��򷵻ؿ�ָ��
    {
        printf("������������\n");
        return NULL;
    }

    BiTree st[100], p; //����һ����Ž��ָ������飬ͬʱ����һ��ָ�����ṹ���ָ��p
    int top = 0; //����һ��ջ��ָ�룬��ʼֵΪ0
    st[top++] = T; //��������ѹ��ջ��

    while (top != 0) { //��ջ��Ϊ��ʱ���������²���
        p = st[--top]; //ȡ��ջ��Ԫ�أ�ͬʱջ��ָ���1
        if (p->rchild->data.key == e) //���p�����ӽ��ΪҪ�����ֵܽ��Ľ��e
            return p->lchild; //�򷵻�p�����ӽ��
        if (p->lchild->data.key == e) //���p�����ӽ��ΪҪ�����ֵܽ��Ľ��e
            return p->rchild; //�򷵻�p�����ӽ��
        //���p��������������������Ϊ�գ������Ƿֱ�ѹ��ջ��
        if (p->rchild->rchild != NULL && p->rchild->lchild != NULL)
            st[top++] = p->rchild;
        if (p->lchild->rchild != NULL && p->lchild->lchild != NULL)
            st[top++] = p->lchild;
    }
    return NULL; //��δ�ҵ��ֵܽ�㣬�򷵻ؿ�ָ��
}





