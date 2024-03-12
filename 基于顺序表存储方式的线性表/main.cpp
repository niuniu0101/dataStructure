/* Linear Table On Sequence Structure*/
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

// ��ʼ�������󳤶�
#define LIST_INIT_SIZE 100
// ÿ�������ĳ���
#define LISTINCREMENT 10

// ��������Ԫ������
typedef int ElemType;
typedef int status;

// ���嵥������ʽ�ṹ�����Ľṹ��
typedef struct LNode{
    ElemType data; // ��������Ԫ��
    struct LNode *next; // ָ����һ������ָ��
}LNode, *LinkList;

// ���������ϵĽṹ��
typedef struct {
    struct {
        char name[30]; // ���ϵ����ƣ��������� 30 ���ַ�
        LinkList L; // ָ������ͷ����ָ��
    }elem[30]; // ������������ 30 ������
    int length; // �����а�����������Ŀ
}LISTS;

LISTS Lists;  //������ʵ����ΪLists����

/*---- �������� ----*/
status InitList(LinkList &L);  //�½�
status DestroyList(LinkList &L);  //����
status ClearList(LinkList &L);  //���
status ListEmpty(LinkList L);   //�п�
status ListLength(LinkList L);  //�󳤶�
status GetElem(LinkList L,int i,ElemType &e);  //��ȡԪ��
status LocateElem(LinkList L,ElemType e,int (*vis)(int ,int ));  //�ж�λ��
status PriorElem(LinkList L,ElemType e,ElemType &pre);   //ǰ��
status NextElem(LinkList L,ElemType e,ElemType &next);   //���
status ListInsert(LinkList &L,int i,int num);   //����
status ListDelete(LinkList &L,int i,ElemType &e);  //ɾ��
status ListTraverse(LinkList L,void (*vi)(int ));  //����
status AddList(LISTS &Lists,char ListName[]);
status RemoveList(LISTS &Lists,char ListName[]);
status LocateList(LISTS Lists,char ListName[]);
void SearchList(LISTS Lists);   //չʾ�Ѿ����������Ա�
status  compare(int a,int b);   //�ж�λ�ú���ʱ����õıȽϺ���
void visit(int x);   //��������ʱ����õ��������
void reverseList(LinkList L);   //��ת���Ա�
void RemoveNthFromEnd(LinkList L,int n);  //ɾ������Ԫ��
void sortList(LinkList L);  //����
void savetofile(LinkList L,char name[]);  //���浽�ļ�
void getfromfile(LinkList L,char name[]);  //��ȡ�ļ�
void fun01();   //��װ�Ķ�����Ա�Ĵ�����
void fun02(LinkList &L );  //��װ�Ĵ��������Ա�Ĵ�����
void menu();  //���������Ա�Ĳ˵�
void show_normal();  //�������Ա�Ĳ˵�
void Menuofinsert();  //����Ĳ˵�

/*---- main������ ----*/
int main()
{
	system("color 37");
    fun01();  //���÷�װ����

}


/*----- �������� ----*/
//��1����ʼ��������������InitList(L)����ʼ���������Ա�L�����ڣ���������ǹ���һ���յ����Ա�
status InitList(LinkList &L)
// ���Ա�L�����ڣ�����һ���յ����Ա�����OK�����򷵻�INFEASIBLE��
{
// ������Ա�L�Ѵ��ڣ��򷵻� INFEASIBLE
    if(L)
        return INFEASIBLE;
// ����һ���µĽڵ���Ϊ���Ա�ͷ���
    L = (LinkList)malloc(sizeof(LNode));
// ��ͷ����ָ������Ϊ��
    L->next = NULL;
// ���� OK
    return OK;
}

//��2�����ٱ�����������DestroyList(L)����ʼ���������Ա�L�Ѵ��ڣ�����������������Ա�L��
status DestroyList(LinkList &L)
// ������Ա�L���ڣ��������Ա�L���ͷ�����Ԫ�صĿռ䣬���� OK�����򷵻� INFEASIBLE��
{
// ������Ա�L�����ڣ��򷵻� INFEASIBLE
    if(!L)
    {
// printf("������Ա����ڻ�δ��ʼ��,�޷�����\n");
	//	printf("���Ա����ڻ���δ��ʼ��\n");
        return INFEASIBLE;
    }
// ����ָ�� p ָ��ǰ��㣬q ָ����һ�����
    LinkList p = L, q;
// �����ǰ��㲻Ϊ�գ������ѭ��
    while(p)
    {
// �� q ָ��ǰ������һ�����
        q = p->next;
// �ͷŵ�ǰ���Ŀռ�
        free(p);
// ��ָ�� p ָ�� q������ѭ��
        p = q;
    }
// ���� OK
    return OK;
}

//��3����ձ�����������ClearList(L)����ʼ���������Ա�L�Ѵ��ڣ���������ǽ�L����Ϊ�ձ�
status ClearList(LinkList &L)
{
    //������Ա�L�����ڣ�����INFEASIBLE
    if(!L)
    {
        printf("���Ա����ڻ�δ��ʼ�����޷��������\n");
        return INFEASIBLE;
    }
    //������Ա�LΪ�գ�����Ҫ����
    if(L->next == NULL)
    {
        printf("���Ա��Ѿ��ǿյ��ˣ�����Ҫ����\n");
        return INFEASIBLE;
    }
    LinkList p = L->next;   //ָ���һ��Ԫ�ؽڵ�
    while(p)
    {
        free(p);            //�ͷŵ�ǰ�ڵ�
        p = p->next;        //ָ����һ���ڵ�
    }
    L->next = NULL;         //��ͷ�ڵ�ָ��NULL��������Ա�
    return OK;
}

//��4���ж��ձ�����������ListEmpty(L)����ʼ���������Ա�L�Ѵ��ڣ������������LΪ�ձ��򷵻�TRUE,���򷵻�FALSE��
status ListEmpty(LinkList L)
{
    // ������Ա�L�����ڣ�����INFEASIBLE
    if(!L)
    {
        printf("���Ա����ڻ�δ��ʼ�����޷��������\n");
        return INFEASIBLE;
    }
    // �������L�ĵ�һ��Ԫ��Ϊ�գ��������Ա�Ϊ�գ�����TRUE
    if(L->next == NULL)
    {
        printf("���Ա��ǿյ�\n");
        return TRUE;
    }
    // ���Ա�Ϊ�գ�����FALSE
    printf("���Ա��ǿյ�\n");
    return FALSE;
}

//��5�����������������ListLength(L)����ʼ���������Ա��Ѵ��ڣ���������Ƿ���L������Ԫ�صĸ�����
int ListLength(LinkList L)
// ������Ա�L���ڣ��������Ա�L�ĳ��ȣ����򷵻�INFEASIBLE��
{
    /********** Begin *********/
    // ����Ҫ������Ա��Ƿ����
    if (!L) {
        printf("���Ա����ڻ�δ��ʼ�����޷��������\n");
        return INFEASIBLE;
    }

    L = L->next;    // ��Ҫ��ͷ�ڵ㿼��
    int number = 0;   //���� ��¼���� 
    while (L) {     // ����������������Ԫ�صĸ���
        number++;
        L = L->next;
    }
    return number;

    /********** End **********/
}

//��6�����Ԫ�أ�����������GetElem(L,i,e)����ʼ���������Ա��Ѵ��ڣ�1��i��ListLength(L)�������������e����L�е�i������Ԫ�ص�ֵ��
status GetElem(LinkList L, int i, ElemType &e)
// ��ȡ���Ա�L�е�i��Ԫ�أ�����洢��e��
{
    if(!L) // ��LΪ�գ���ʾ���Ա����ڻ�δ��ʼ��
    {
        printf("���Ա����ڻ�δ��ʼ�����޷��������\n");
        return INFEASIBLE; // ����INFEASIBLE
    }
    int number = 0; // ��¼��ǰ�������Ľڵ�������0��ʼ
    LinkList p = L; // ����pָ�룬ָ��L
    p = L->next; // ����ͷ�ڵ㣬�ӵ�һ���洢���ݵĽڵ㿪ʼ����
    while(p)
    {
        number++; // ������һ���ڵ㣬number��1
        if(number == i) // �ҵ���i���ڵ�
        {
            e = p->data; // ���ҵ��Ľڵ�����ݴ洢��e��
            return OK; // ����OK
        }
        p = p->next; // ָ��pָ����һ���ڵ�
    }
    printf("i��ֵ���Ϸ����޷�����\n");
    return ERROR; // �������������Ա�δ�ҵ���i���ڵ㣬����ERROR
}

//��7������Ԫ�أ�����������LocateElem(L,e,compare())����ʼ���������Ա��Ѵ��ڣ�
// ��������Ƿ���L�е�1����e�����ϵcompare������ϵ������Ԫ�ص�λ��������������Ԫ�ز����ڣ��򷵻�ֵΪ0��
status LocateElem(LinkList L,ElemType e,int (*vis)(int ,int ))
// ����Ԫ��e�����Ա�L�е�λ�����
// ��e����ʱ�������������Ա��е�λ�����
// ��e������ʱ������ERROR
// �����Ա�L������ʱ������INFEASIBLE
{
    // �����Ա�L������ʱ������INFEASIBLE
    if(!L)
    {
        printf("���Ա����ڻ�δ��ʼ�����޷����в���\n");
        return INFEASIBLE;
    }

    // ��ͷ������һ����㿪ʼ������
    LinkList p = L->next;

    // ��¼��ǰλ�����
    int number = 0;

    // ������������Ԫ��e
    while(p)
    {
        number++;

        if(vis(p->data,e) == 1) // ����ҵ�Ԫ��e��������λ�����
        {
            return number;      
        }
        p = p->next;
    }

    // ����������������Ա���δ�ҵ�Ԫ��e������ERROR
    printf("û����Ҫ��ѯ��Ԫ��\n");
    return ERROR;
}

//��8�����ǰ��������������PriorElem(L,cur_e,pre_e)��
// ��ʼ���������Ա�L�Ѵ��ڣ������������cur_e��L������Ԫ�أ��Ҳ��ǵ�һ��������pre_e��������ǰ�����������ʧ�ܣ�pre_e�޶��壻
status PriorElem(LinkList L,ElemType e,ElemType &pre)
// ������Ա�L���ڣ���ȡ���Ա�L��Ԫ��e��ǰ����������pre�У�����OK�����û��ǰ��������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
    if(!L)    // �������L�����ڣ��򷵻�INFEASIBLE����ʾ������
    {
        printf("���Ա����ڻ�δ��ʼ�����޷��������\n");
        return INFEASIBLE;
    }
    if(L->next == NULL)  // �������LΪ�գ��򷵻�ERROR����ʾ����
    {
        printf("���Ա�����û��Ԫ��\n");
        return ERROR;
    }
    LinkList p = L->next;
    if(p->data == e )  // �����Ҫ���ҵ�Ԫ��e�ǵ�һ��Ԫ�أ�������ǰ��������ERROR
    {
        printf("��Ҫ���ҵ�Ԫ���ǵ�һ��Ԫ�أ�û��ǰ��\n");
        return ERROR;
    }
    while(p->next)   // �ӵڶ���Ԫ�ؿ�ʼ����������������ҵ�Ҫ���ҵ�Ԫ��e
    {
        L = p->next;
        if(L->data == e )   // ����ҵ�Ҫ���ҵ�Ԫ��e���򽫸�Ԫ�ص�ǰ��������pre�У�����OK
        {
            pre = p->data;
            return OK;
        }
        p = L;
    }
    printf("��Ҫ���ҵ�Ԫ�ز��������Ա�����,�޷�����\n"); // ������������ж�û���ҵ�Ҫ���ҵ�Ԫ��e���򷵻�ERROR����ʾ����
    return ERROR;
}

//��9����ú�̣�����������NextElem(L,cur_e,next_e)��
// ��ʼ���������Ա�L�Ѵ��ڣ������������cur_e��L������Ԫ�أ��Ҳ������һ��������next_e�������ĺ�̣��������ʧ�ܣ�next_e�޶��壻
status NextElem(LinkList L,ElemType e,ElemType &next)
// ������Ա�L���ڣ���ȡ���Ա�LԪ��e�ĺ�̣�������next�У�����OK�����û�к�̣�����ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
    if(!L)   // ������Ա�L������
    {
        printf("���Ա����ڻ�δ��ʼ�����޷����в�ѯ\n");
        return INFEASIBLE;
    }
    if(L->next==NULL)   // ������Ա�L�ǿձ�
    {
        printf("������Ա��ǿյ�\n");
        return ERROR;
    }
    LinkList p = L->next;   // ��pΪ��һ����㣬p��ǰ�����
    L =  p ->next;   // ��LΪp�ĺ�̽�㣬L����ǰ���
    while(p)   // ���p��Ϊ��
    {
        if( !L)   // ���LΪ�գ���ʾ�Ѿ�û�к�̽����
        {
            printf("��ѯ������̽��\n");
            return ERROR;
        }
        if(p->data == e)   // ���p�����ݵ��ڸ�������e
        {
            next = L->data;   // ��L�����ݸ���next
            return OK;   // ���ز����ɹ�
        }
        p = L ;   // ��p�Ƶ�L��λ�ã���Ϊ�µ�ǰ�����
        L = p->next;   // ��L�Ƶ���һ�����λ�ã���Ϊ�µĵ�ǰ���
    }
    return ERROR;   // ���ѭ������ʱ��δ��ѯ�������ز���ʧ��
}

//��10������Ԫ�أ�����������ListInsert(L,i,e)����ʼ���������Ա�L�Ѵ��ڣ�1��i��ListLength(L)+1�������������L�ĵ�i��λ��֮ǰ�����µ�����Ԫ��e��
status ListInsert(LinkList &L,int i,int num)
{
    // �Ƚ������У�������Ա����ڣ����� INFEASIBLE
    if(!L)
    {
        printf("���Ա����ڻ�δ��ʼ�����޷����в���\n");
        return INFEASIBLE;
    }
    int e;

    // ������ָ�� p �� next �ֱ�ָ��ǰ�������Ľڵ����һ���ڵ�
    LinkList p = L, next = L->next;
    int number = 1;  //����¼��ǰλ�� 

    // ���������ҵ�Ҫ�����λ��
    printf("������Ԫ�أ�\n");
    while(next)
    {
        if(number == i)
        {
            // ���ҵ�����λ��ʱ��ʹ��һ��ѭ������ num ��Ԫ��
            while (num)
            {
                // �����µĽڵ㣬��ȡ�û����������
                LinkList insert = (LinkList)malloc(sizeof(LNode));
                scanf("%d",&e);
                insert->data = e;

                // �޸�����ָ��ָ����ɲ������
                p->next = insert;
                insert->next = next;
                p = insert;
                num--;
            }

            return OK;
        }

        // �������±���
        number++;
        p = next;
        next = p->next;
    }

    // �������λ��Ϊ���һ��λ�ã���������β������
    if( number == i)
    {
        LinkList insert;

        // ʹ��ѭ���� num �����ݲ��뵽β��
        while (num) {
            scanf("%d",&e);
            insert = (LinkList)malloc(sizeof(LNode));
            insert->data = e;
            insert->next = NULL;
            p->next = insert;
            p = insert;
            num--;
        }
        return OK;
    }

    // �������λ�ò���ȷ�����ش���
    printf("�����λ�ò���\n");
    return ERROR;
}

//��11��ɾ��Ԫ�أ�����������ListDelete(L,i,e)����ʼ���������Ա�L�Ѵ����ҷǿգ�1��i��ListLength(L)�����������ɾ��L�ĵ�i������Ԫ�أ���e������ֵ��
status ListDelete(LinkList &L,int i,ElemType &e)  // ɾ�����Ա�L�ĵ�i��Ԫ�أ���������e�У�����OK��ERROR��INFEASIBLE
{
    if(!L)  // ������Ա�L�����ڣ�����INFEASIBLE
    {
        printf("���Ա����ڻ�δ��ʼ�����޷��������\n");
        return INFEASIBLE;
    }
    int number = 0;  // ���ڼ�������¼��ǰɨ�赽��Ԫ�ص�λ��

    LinkList pre = L, next = L->next;  // pre���ڼ�¼��ǰɨ�赽��Ԫ�ص�ǰһ��Ԫ�أ�next���ڼ�¼��ǰɨ�赽��Ԫ��

    while(next)  // �������Ա�ֱ�������β
    {
        number++;  // ��������1����¼��ǰɨ�赽��Ԫ�ص�λ��

        if(number == i)  // ����ҵ���i��Ԫ��
        {
            e = next->data;  // ����Ԫ�ص�ֵ������e��
            pre->next = next->next;  // ����ǰԪ�ص�ǰһ��Ԫ�ص�ָ��ָ��ǰԪ�صĺ�һ��Ԫ�أ�ʵ��ɾ������
            free(next);  // �ͷ��ڴ�
            return OK;  // ����ִ�гɹ�
        }
        pre = next;  // ��ǰԪ�ر��浽ǰһ��Ԫ�ر���pre��
        next = pre->next;  // ��һ��Ԫ�ر��浽��ǰԪ�ر���next�У�ʵ�ֱ���
    }
    printf("��Ҫɾ����λ�ô�������\n");  // �����������β��δ�ҵ���i��Ԫ�أ��������ʾ
    return ERROR;  // ����ִ��ʧ��
}

//��12������������������ListTraverse(L,visit())����ʼ���������Ա�L�Ѵ��ڣ�
// ������������ζ�L��ÿ������Ԫ�ص��ú���visit( )��
status ListTraverse(LinkList L,void (*vi)(int ))
// �������Ա� L �е�Ԫ�أ�����ʹ�ú���ָ�� vi ����ÿ��Ԫ�ء�
// ������Ա� L �����ڣ����� INFEASIBLE�����򷵻� OK��
{
    if(!L) // ������Ա� L ������
    {
        printf("���Ա����ڻ�δ��ʼ�����޷����в���\n");
        return INFEASIBLE; // ���� INFEASIBLE
    }
    LinkList p = L->next; // �� L �е�һ��Ԫ�ؿ�ʼ����
    while(p) // ֻҪ��ǰ�ڵ㲻��β�ڵ�
    {
        vi(p->data); // �Ե�ǰ�ڵ��Ԫ��ʹ�ú���ָ�� vi ���д���
        p = p->next; // ָ����һ���ڵ�
        if(p) // �����ǰ�������һ���ڵ�
        {
            putchar(' '); // ���һ���ո�����һ��Ԫ�طָ�����
        }
    }
    return OK; // �������������� OK
}

// ��Lists������һ������ΪListName�Ŀ����Ա�
// Lists: ���Ա��ϣ�����������Ա�
// ListName: ����ӵ����Ա�����
// ����ֵ������״̬���ɹ�ΪOK������ΪINFEASIBLE
status AddList(LISTS &Lists,char ListName[])
{
    // ѭ�������Ƿ��Ѿ�����ͬ�����Ա�
    for(int i = 0; i<Lists.length ;i++)
    {
        if(strcmp(ListName,Lists.elem[i].name) == 0) // �ж����Ա������Ƿ���ͬ
        {
            printf("������ֵ����Ա��Ѿ�������"); // �����ʾ��Ϣ
            return INFEASIBLE; // ����INFEASIBLE��ʾ����ʧ��
        }
    }
    // δ�ҵ�ͬ�����Ա����Լ������
    Lists.length++; // ���Ա��ϳ���+1
    int n = 0;
    // �������Ա�����ƺ����ݳ�ʼ��
    strcpy(Lists.elem[Lists.length-1].name ,ListName); // �����Ա����Ƹ�ֵ
    Lists.elem[Lists.length-1].L = NULL; // ���洢���ݵ�ָ���ʼ��ΪNULL
    return OK; // ����OK��ʾ�����ɹ�
}

status RemoveList(LISTS &Lists,char ListName[])
// Lists��ɾ��һ������ΪListName�����Ա�
{
    // �������Ա������ҵ���Ҫɾ�������Ա�
    for(int k = 0;k<Lists.length;k++)
    {
        if(strcmp(Lists.elem[k].name,ListName)==0)  // ��һ�ж����Ա������Ƿ���Ҫɾ����������ͬ
        {
            DestroyList(Lists.elem[k].L);  // ������������Ա���Ŀռ�
            // ָ���������һ��ǰ�ƶ�
            for(int i = k;i<Lists.length-1;i++)
            {
                strcpy(Lists.elem[i].name, Lists.elem[i+1].name);   // ��һ����������Ա�����Ƹ��Ƶ�ǰ��
                Lists.elem[i].L =Lists.elem[i+1].L;   // ���������Ա��ָ�븴�Ƶ�ǰ��
            }
            // ���Ա�����ĳ��ȼ� 1
            Lists.length--;
            return OK;  // ɾ���ɹ�
        }
    }
    return ERROR;   // û���ҵ�Ҫɾ�������Ա�ɾ��ʧ��
}

int LocateList(LISTS Lists,char ListName[])
// ����һ������ΪListName�����Ա���Lists�е�λ�ã��ɹ������߼���ţ����򷵻�-1
{
    // ��ʼ�������Ա�
    for(int k = 0 ;k< Lists.length;k++)
    {
        // �Ƚ����Ա������Ƿ�ƥ��
        if(strcmp(Lists.elem[k].name,ListName)==0)
        {
            return k+1;  // ������ţ���Ŵ� 1 ��ʼ��
        }
    }
    return -1;  // ����ʧ�ܣ����� -1
}

void SearchList(LISTS Lists)   //�����������չʾ�Ѿ����������Ա�
{
    int i =0;
    printf("�Ѿ����ڵ����Ա��У�\n");
    for( ;i<Lists.length;i++)
    {
        printf("��� %d)  ���Ա������:%s\n",(i+1),Lists.elem[i].name);

    }
}

//��ת���Ա�
void reverseList(LinkList L)
{
    // �ж����Ա��Ƿ���ڻ�δ��ʼ��
    if(!L)
    {
        printf("���Ա����ڻ�δ��ʼ��\n");
        return;
    }
    // ��ȡ���Ա�ĳ���
    int len = ListLength(L);
    // ����һ������Ϊ len ������
    int *arr =(int *) malloc(sizeof(int)*len);
    // ���������洢�����е�Ԫ�ص�������
    LinkList p1 = L->next;
    for(int k=0;k<len;k++)
    {
        arr[k] = p1->data;
        p1 = p1->next;
    }
    // ��β��ͷ���������������е�Ԫ�����δ洢��������
    LinkList p2 = L->next;
    for(int i =len;i>0;i--)
    {
        p2->data = arr[i-1];
        p2 = p2->next;
    }
    printf("�ɹ���ת��\n");
    return;
}

void RemoveNthFromEnd(LinkList L,int n) // RemoveNthFromEnd�����Ķ��壬����Ϊһ���������Ҫɾ���Ľڵ�λ��
{
    if(!L) // ���������Ϊ�ջ�δ��ʼ��
    {
        printf("���Ա����ڻ���δ��ʼ��\n"); // ��ӡ������Ϣ
        return; // �˳�����
    }

    int len = ListLength(L); // ��ȡ������ĳ���
    int e; // �����洢��ɾ���ڵ������Ԫ��
    int feedback; // �洢ListDelete�����ķ���ֵ����ɾ�������Ľ��

    feedback = ListDelete(L,len-n+1,e); // ����ListDelete����ɾ����(len-n+1)���ڵ㣬������ɾ���ڵ��ֵ����e��

    if(feedback == OK) // ���ɾ���ɹ�
    {
        printf("�ɹ�ɾ����ɾ����Ԫ���� :%d\n",e); // ��ӡ�ɹ���Ϣ����ɾ���ڵ��ֵ
    }
}
//����
void sortList(LinkList L)
{
    //�ж����Ա��Ƿ���ڻ���δ��ʼ��
    if(!L)
    {
        printf("���Ա����ڻ���δ��ʼ��\n");
        return;
    }
    //��ȡ���Ա���
    int len = ListLength(L);
    //���붯̬�ڴ棬���ڴ�����Ա�����
    int *arr =(int *) malloc(sizeof(int)*len);
    //�������Ա������ݴ�ŵ�arr������
    LinkList p1 = L->next;
    for(int k=0;k<len;k++)
    {
        arr[k] = p1->data;
        p1 = p1->next;
    }
    //��arr�������ð������
    for(int k=0;k<len-1;k++)
    {
        for(int i=0;i<len-1-k;i++)
        {
            if(arr[i] > arr[i+1])
            {
                int tmp = arr[i];  //�м����tmp
                arr[i] = arr[i+1];
                arr[i+1] = tmp;
            }
        }
    }
    //������������д�����Ա���
    LinkList p2 = L->next;
    for(int k =0;k<len;k++)
    {
        p2->data = arr[k];
        p2 = p2->next;
    }
}

// �����Ա�L�н����ݱ��浽�ļ�name��
void savetofile(LinkList L,char name[])
{
    if(!L) // ���L�����ڻ�δ��ʼ�����޷����в���
    {
        printf("���Ա����ڻ�δ��ʼ��\n");
        return;
    }
    FILE *fp = fopen(name,"w"); // ���ļ�����д�ķ�ʽ
    if(fp == NULL) // ����޷��ҵ��ļ�������
    {
        printf("���ļ�ʧ��\n");
        return;
    }
    LinkList current = L->next; // ָ���һ���ڵ�
    while (current != NULL) // ѭ���������Ա��е�ÿ���ڵ�
    {
        fprintf(fp, "%d ", current->data); // ���ڵ������д���ļ���
        current = current->next;
    }
    fclose(fp); // �ر��ļ�
    printf("�ɹ����浽�ļ���\n"); // ��ʾ��Ϣ�����������ɹ�
    return;
}

// ���ļ�name�ж�ȡ���ݣ����浽���Ա�L��
void getfromfile(LinkList L,char name[])
{
    if(L->next) // ���L���ǿյģ�˵���Ѿ��������ˣ��޷����в���
    {
        printf("�ⲻ��һ���յ����Ա���ȡ���ݻᵼ��ԭ�������ݱ����ǣ��޷�����\n");
        return;
    }
    FILE *fp = fopen(name,"r"); // ���ļ����Զ��ķ�ʽ
    if(fp == NULL) // ����޷��ҵ��ļ�������
    {
        printf("���ļ�ʧ��\n");
        return;
    }
    LinkList p = L; // ���ڱ������Ա�
    LinkList insert= (LinkList) malloc(sizeof(LNode)); // ��̬�����ڴ棬���ڴ�Ŵ��ļ��ж�ȡ������
    while (fscanf(fp,"%d ",&insert->data) != EOF) // ѭ����ȡ�ļ��е�����
    {
        p->next = insert; // ���뵽���Ա���
        p = insert; // ָ��ղ���Ľڵ�
        p->next = NULL; // �ýڵ����һ���ڵ�Ϊ��
        insert= (LinkList) malloc(sizeof(LNode)); // Ϊ��һ���ڵ㶯̬�����ڴ�
    }
    fclose(fp); // �ر��ļ�
    return;
}

void fun01() //����һ������
{
    menu(); //���ò˵�
    int a; //����һ�����ͱ���
    printf("������һ������\n"); //�����ʾ��Ϣ
    scanf("%d", &a); //��ȡһ�����ͱ���

    //ͨ��whileѭ�������������
    while (a) //��a��Ϊ0ʱִ��ѭ����
    {
        fflush(stdin); //�������������ֹ��һ�β���Ӱ�챾�β���

        switch (a) {
            //���a����1��ִ�����´���
            case 1:
                printf("���ڽ��д������Ա�\n"); //�����ʾ��Ϣ
                printf("���������봴�������Ա������\n"); //�����ʾ��Ϣ
                char name1[30]; //����һ������Ϊname1�ҳ������Ϊ30���ַ�����
                scanf("%s", name1); //��ȡ�ַ���

                int u; //����һ�����ͱ���
                u = AddList(Lists, name1); //��һ�����Ա������в���һ���µĿ����Ա�
                if(u == OK) //�������ɹ�
                {
                    printf("�����ɹ���\n"); //�����ʾ��Ϣ
                }
                if(u == INFEASIBLE) //�������ʧ��
                {
                    system("pause"); //��ͣ��������
                }
                break;

                //���a����2��ִ�����´���
            case 2:
                printf("���ڽ���ɾ�����Ա�\n"); //�����ʾ��Ϣ
                printf("���������봴�������Ա������\n"); //�����ʾ��Ϣ
                char name2[30]; //����һ������Ϊname2�ҳ������Ϊ30���ַ�����
                scanf("%s", name2); //��ȡ�ַ���
                RemoveList(Lists, name2); //�����Ա�������ɾ��ָ�������Ա�
                break;

                //���a����3��ִ�����´���
            case 3:
                printf("���ڽ��в�ѯ��������Щ���Ա�\n"); //�����ʾ��Ϣ
                SearchList(Lists); //��ѯ���Ա��������������Ա�����ֲ����
                break;

                //���a����4��ִ�����´���
            case 4:
                printf("���ڽ������Ա�Ĳ��ҺͲ���\n"); //�����ʾ��Ϣ
                printf("������������ҺͲ��������Ա������\n"); //�����ʾ��Ϣ
                char name3[30]; //����һ������Ϊname3�ҳ������Ϊ30���ַ�����
                scanf("%s", name3); //��ȡ�ַ���
                int judge; //����һ�����ͱ���
                judge=LocateList(Lists, name3); //�������Ա�������ָ�����ֵ����Ա����������±�

                if(judge ==-1) //�������ʧ��
                {
                    printf("������������Ա�\n"); //�����ʾ��Ϣ
                    system("pause"); //��ͣ��������
                }
                else { //������ҳɹ�
                    fun02(Lists.elem[judge-1].L); //ִ����һ������
                }
                break;

                //���a������1��2��3��4��ִ�����´���
            default:
                printf("���������������ٴ�����"); //�����ʾ��Ϣ
        }

        printf("��������һ������\n"); //�����ʾ��Ϣ
        scanf("%d", &a); //��ȡһ�����ͱ���
        system("cls"); //����
        menu(); //�ٴε�����һ������
    }
}

void fun02(LinkList &L)       //�����������ÿ�����Ա����ϸ����ʵ��
{
    system("cls");  //��������д���
    printf("���Ա����ѼѼ\n");
    printf("���ڶ�������Ա���в���\n");
    printf("�����ǳ�ʼ��������Ա�Ѽ\n");

    //����������и��ֲ�����Ҫ���û���������
    int order;
    show_normal();  //��ʾ�����б�
    scanf("%d",&order);  //��ȡ�û�������������
    while (order)   //����û�����������0���˳������ͼ���ѭ��
    {
        fflush(stdin); //������뻺��������ֹӰ����һ������
        int feedback;   //�����պ�������ֵ
        switch (order) {    //����������Ž�����Ӧ�Ĳ���
            case 1:
                //�������Ա�
                if (InitList(L) == OK)
                    printf("���Ա����ɹ���\n");
                else printf("���Ա��Ѿ����ڣ�����ʧ�ܣ�\n");
                break;
            case 2:
                //�������Ա�
                printf("���ڽ������Ա������\n");
                feedback = DestroyList(L);
                if(feedback == OK)
                {
                    printf("�ɹ�������\n");
                }
                else if(feedback == INFEASIBLE)
                {
                    printf("������Ա����ڻ�δ��ʼ��,�޷�����\n");
                }
                break;
            case 3:
                //������Ա�
                printf("���ڽ������Ա����ղ���\n");
                feedback = ClearList(L);
                if(feedback == OK)
                {
                    printf("�ɹ�������Ա�\n");
                }
                break;
            case 4:
                //�ж����Ա��Ƿ�Ϊ��
                printf("���ڶ����Ա�����пղ���\n");
                ListEmpty(L);
                break;
            case 5:
                //�����Ա�ĳ���
                printf("���ڽ��������Ա�ĳ���\n");
                feedback = ListLength(L);
                if(feedback != INFEASIBLE)
                {
                    printf("���Ա�ĳ���Ϊ:%d",feedback);
                }
                break;
            case 6:
                //��ȡ���Ա���ָ��λ�õ�Ԫ��
                printf("���ڽ���Ԫ�ػ�ȡ����\n");
                int e; int i;      //��e������Ԫ�ص�ֵ��i����Ҫ��ȡԪ�ص�λ��
                printf("�����������ȡ�ڼ���Ԫ�ص�ֵ\n");
                scanf("%d",&i);
                feedback =  GetElem(L,i,e);
                if(feedback == OK)
                {
                    printf("�ɹ���ȡ����%d��Ԫ�ص�ֵΪ��%d",i,e);
                }
                break;
            case 7:
                //�������Ա���ָ��ֵ��Ԫ��
                printf("���ڽ��в���Ԫ�صĲ���\n");
                int ee;  //������Ҫ���ҵ�Ԫ��
                printf("������������ҵ�Ԫ��\n");
                scanf("%d",&ee);
                feedback =  LocateElem(L,ee,compare);
                if(feedback >0)
                {
                    printf("��Ҫ���ҵ�Ԫ���ǵ�%d��\n",feedback);
                }
                break;
            case 8:
                //����ָ��Ԫ�ص�ǰ��
                printf("���ڽ��в���ǰ���Ĳ���\n");
                int cur_e,pre_e;   //����Ԫ�أ����洢ǰ��
                printf("��������������ĸ�Ԫ�ص�ǰ��\n");
                scanf("%d",&cur_e);
                feedback =  PriorElem(L,cur_e,pre_e);
                if(feedback == OK)
                {
                    printf("����Ҫ���ҵ�ǰ����:  %d\n",pre_e);
                }
                break;
            case 9:
                //����ָ��Ԫ�صĺ���
                printf("���ڽ��в��Һ����Ĳ���\n");
                int cur,next_e;   //����Ԫ�أ����洢���
                printf("��������������ĸ�Ԫ�صĺ���\n");
                scanf("%d",&cur);
                feedback = NextElem(L,cur,next_e);
                if(feedback == OK)
                {
                    printf("����Ҫ���ҵ�Ԫ�صĺ�����:   %d\n",next_e);
                }
                break;
            case 10:
                //��ָ��λ�ò���Ԫ��
                printf("���ڽ��в���Ԫ�صĲ���\n");
                printf("���������ڵڼ���λ�ò���Ԫ��\n");
                int position;   //����Ԫ�ص�λ��
                scanf("%d",&position);
                printf("�����������Ԫ�صĸ���\n");
                int number;
                scanf("%d",&number);
                feedback =  ListInsert(L,position,number);
                if(feedback == OK)
                {
                    printf("����ɹ�\n");
                }
                break;
            case 11:
                //ɾ��ָ��λ�õ�Ԫ��
                printf("���ڽ���ɾ��Ԫ�صĲ���\n");
                printf("��������ɾ���ڼ���λ�õ�Ԫ��\n");
                int position01;
                int e1;
                scanf("%d",&position01);
                feedback =  ListDelete(L,position01,e1);
                if(feedback == OK)
                {
                    printf("ɾ���ɹ���ɾ����Ԫ����:  %d\n",e1);
                }
                break;
            case 12:
                //�������Ա�
                printf("���ڽ������Ա�ı���\n");
                ListTraverse(L,visit);
                break;
            case 13:
                //��ת���Ա�
                printf("���ڽ������Ա�ķ�ת\n");
                reverseList(L);
                break;
            case 14:
                //ɾ��������n��Ԫ��
                printf("���ڽ���ɾ��������Ԫ�صĲ���\n");
                printf("����ɾ���������ڼ����ڵ�\n");
                int positon2;
                scanf("%d",&positon2);
                RemoveNthFromEnd(L,positon2);
                break;
            case 15:
                //�������Ա�
                printf("���ڽ������������\n");
                sortList(L);
                printf("�㶨��\n");
                break;
            case 16:
                //�����Ա��浽�ļ�
                printf("���ڽ������Ա���ļ�����\n");
                printf("�������뱣�浽��һ���ļ�\n");
                char name1[30];
                scanf("%s",name1);
                savetofile(L,name1);
                break;
            case 17:
                //���ļ��ж�ȡ���Ա�
                printf("���ڽ������Ա�Ķ�ȡ����\n");
                printf("�����ȡ��һ���ļ�������\n");
                char name2[30];
                scanf("%s",name2);
                getfromfile(L,name2);
                break;
            default:
                //��������������
                printf("��������������\n");
        }
        putchar('\n');
        printf("��������һ������\n");
        scanf("%d",&order);
        system("cls");  //��������д���
        if(order != 0)
        {
            show_normal();  //��ʾ�����б�
        }
        else{
            menu(); //�������˵�
        }

    }
}

void show_normal()   //�������Ա�Ĳ˵�
{
    // �������
    for(int k = 0; k<=  119 ;k++)
    {
        putchar('-');
    }
    putchar('\n');

    // ����˵�����
    printf("           Menu for Linear Table On Sequence Structure \n");

    // ����˵�ѡ��
    printf("    	  1. InitList                       7. LocateElem\n");
    printf("    	  2. DestroyList                    8. PriorElem\n");
    printf("    	  3. ClearList                      9. NextElem \n");
    printf("    	  4. ListEmpty                      10. ListInsert\n");
    printf("    	  5. ListLength                     11. ListDelete\n");
    printf("    	  6. GetElem                        12. ListTrabverse\n");

    // �������
    for(int k = 0; k<=  119 ;k++)
    {
        putchar('-');
    }

    putchar('\n');

    // �������Ĳ˵�ѡ��
    printf("    	  13.reverseList                    14.RemoveNthFromEnd\n");
    printf("    	  15.sortList                       16.saveFile\n");
    printf("    	  17.getFile                        \n");
    printf("    	  0.exit                        \n");

    // �������
    for(int k = 0; k<=  119 ;k++)
    {
        putchar('-');
    }

    putchar('\n');

    // ���Сè��
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

    putchar('\n');

    // �������
    for(int k = 0; k<=  119 ;k++)
    {
        putchar('-');
    }

    putchar('\n');

    // �����ʾ����
    printf("    ��ѡ����Ĳ���[0~13]:");

    putchar('\n');

    // �������
    for(int k = 0; k<=  119 ;k++)
    {
        putchar('-');
    }

    putchar('\n');
}

void menu()
{
    for(int k = 0; k<=  119 ;k++) // ��ӡ�ָ��ߣ���120�� '-'
    {
        putchar('-');
    }
    putchar('\n'); // ��ӡ���з�

    printf("1.����һ�����Ա�\n"); // ��ӡ����1������
    printf("2.ɾ��һ�����Ա�\n"); // ��ӡ����2������
    printf("3.��ѯ�Ѿ����������Ա�\n"); // ��ӡ����3������
    printf("4.����һ�����Ա�ͽ��в���\n"); // ��ӡ����4������
    printf("0.�˳����Ա�Ĺ���\n"); // ��ӡ����0������

    // ��ӡһֻè�� ASCII Art�����Ӳ˵���Ȥζ��
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

    for(int k = 0; k<=  119 ;k++) // ����ͬ�ϣ���ӡ�ָ���
    {
        putchar('-');
    }
    putchar('\n'); // ����ٴ�ӡһ�п��У������Ӿ��ϵķ���
}

// �·���һ����������Ĳ˵���������ǰ��� menu()����
void Menuofinsert()
{
    for(int k = 0; k<=  119 ;k++)
    {
        putchar('-');
    }
    putchar('\n');

    printf("1.������Ԫ��\n");
    printf("2.�������Ԫ��\n");

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
    }
    putchar('\n');
}

int  compare(int a,int b)
{
    if(a == b)
    {
        return 1;
    }
    return 0;
}

void visit(int x)
{
    printf("%d",x);
}

