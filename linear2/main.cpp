/* Linear Table On Sequence Structure*/
/*---- ͷ�ļ������� ----*/
#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
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
typedef int status;

// ˳���������Ԫ�ص�����
typedef int ElemType;

// ����˳���ĳ�ʼ���Ⱥ�ÿ����չ�ĳ���
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10

// ����˳�������
typedef struct{
    ElemType * elem; // �洢����Ԫ�ص�����ָ��
    int length; // ��ǰ����
    int listsize; // ��ǰ�����ɵ���󳤶�
}SqList;

// �������Ա����е�ÿ�����Ա������
typedef struct{
    char name[30]; // ���Ա������
    SqList L; // ���Ա���
}LIST_ELEM;

// �������Ա�������
typedef struct{
    LIST_ELEM elem[10]; // �洢���Ա������
    int length; // ��ǰ���ϳ���
}LISTS;
LISTS Lists; // �������Ա��ϵı�����ΪLists

/*---- �������� ----*/

status InitList(SqList& L); //�½�
status DestroyList(SqList& L); //����
status ClearList(SqList& L); //���
status ListEmpty(SqList L);  //�п�
status ListLength(SqList L);  //�󳤶�
status GetElem(SqList L,int i,ElemType &e);  //��ȡԪ��
status LocateElem(SqList L,ElemType e,int (*p)(int ,int ));  //�ж�λ��
status compare(int a ,int b);  //�ж�λ�ú����е��õ�compare����
status PriorElem(SqList L,ElemType e,ElemType &pre);  //���ǰ��
status NextElem(SqList L,ElemType e,ElemType &next);  //��ú��
status ListInsert(SqList &L,int i,ElemType e);  //����Ԫ��
status ListDelete(SqList &L,int i,ElemType &e);  //ɾ��Ԫ��
status ListTraverse(SqList L,void (*visit)(int)); //�������
void visit(int elem);  //�������ʱ����õ�visit����
status MaxSubArray(SqList L);  //�������������
status SubArrayNum(SqList L , int u); //��Ϊk�����������
status sort(SqList &L);  //˳�������
void show();  //�������Ա�Ĳ˵�
void show1();  //������Ա�Ĳ˵�
void menu();  //������Ա����ڲ˵�
int savetofile(SqList L);  //���Ա��浽�ļ�
int getfromfile(SqList &L);  //���ļ��ж�ȡ���Ա�
status AddList(LISTS &Lists,char ListName[]);  //��Lists������һ�������Ա�
status RemoveList(LISTS &Lists,char ListName[]);  // Lists��ɾ��һ�����Ա�
status LocateList(LISTS Lists,char ListName[]);  // ��Lists�в������Ա�
void funtion();  //������Ա����ķ�װ����
void showplus();  //���ӹ��ܵĲ˵�





/*---- main������ ----*/
int  main()
{
    //�޸Ŀ���̨�����ɫ
    system("color 0b");
    //��ʾ���ܲ˵�
    show();
    //����������
    int order;
    //����һ�����Ա�
    SqList L;
    scanf("%d",&order);
    while(order)
    {
        //�����Ļ�ϵ�����
        system("cls");
        //���ݲ������ִ����Ӧ�Ĺ���
        switch(order){
            case 1:
                //��ʾ���ܲ˵�
                show();
                //��ʼ�����Ա�
                if(InitList(L)==OK) printf("���Ա����ɹ���\n");
                else printf("���Ա��Ѿ����ڣ�����ʧ�ܣ�\n");
                getchar();
                break;
            case 2:
                //��ʾ���ܲ˵�
                show();
                //�������Ա�
                DestroyList(L);
                getchar();
                break;
            case 3:
                //��ʾ���ܲ˵�
                show();
                //������Ա�
                ClearList(L);
                getchar();
                break;
            case 4:
                //��ʾ���ܲ˵�
                show();
                //�ж����Ա��Ƿ�Ϊ��
                ListEmpty(L);
                getchar();
                break;
            case 5:
                //��ʾ���ܲ˵�
                show();
                //��ȡ���Ա���
                int getdata ;
                getdata = ListLength(L);
                if(getdata !=INFEASIBLE )
                {
                    printf("���Ա�ĳ�����%d",getdata);
                }
                getchar();
                break;
            case 6:
                //��ʾ���ܲ˵�
                show();
                //��ȡָ��λ�õ�Ԫ��
                printf("�����������ȡ�ڼ���Ԫ��\n");
                int i ;
                scanf("%d",&i);
                int n ; int getdata1 ;
                n = GetElem(L,i,getdata1);

                if(n == OK)
                {
                    printf("�ɹ���ȡ����%d��Ԫ�ص�ֵ��%d\n",i,getdata1);
                }
                getchar();
                break;
            case 7:
                //��ʾ���ܲ˵�
                show();
                //����ָ��Ԫ��
                int u ;
                printf("������һ����ֵe\n");
                int e ; scanf("%d",&e);
                printf("�����ڱ������һ����e����С�����ݣ���������1��С������0\n");
                int getorder ;  scanf("%d",&getorder);
                int q;
                if(getorder == 1)
                {
                    printf("����Ҫ������ݱ�e�����\n");

                    scanf("%d",&q);
                    if(LocateElem(L,e+q,compare) > 0)
                    {
                        printf("��Ҫ���ҵ����ݵ��±����%d\n",LocateElem(L,e+q,compare));
                    }
                }
                else{
                    printf("����Ҫ������ݱ�eС����\n");

                    scanf("%d",&q);
                    if(LocateElem(L,e+q,compare) > 0)
                    {
                        printf("��Ҫ���ҵ����ݵ��±����%d\n",LocateElem(L,e+q,compare));
                    }
                }
                getchar();
                break;
            case 8:
                //��ʾ���ܲ˵�
                show();
                //��ȡָ��Ԫ�ص�ǰ��
                printf("�����������Ǹ�Ԫ�ص�ǰ��\n");
                int v ;
                scanf("%d",&v);
                int pre_e;
                if(PriorElem(L,v,pre_e)==OK)
                {
                    printf("�ɹ����ǰ������%d\n",pre_e);
                }
                getchar();
                break;
            case 9:
                //��ʾ���ܲ˵�
                show();
                //��ȡָ��Ԫ�صĺ��
                printf("�����������ĸ�Ԫ�صĺ���\n");
                int p ;
                scanf("%d",&p);
                int next_e;
                if(NextElem(L,p,next_e) == OK)
                {
                    printf("�ɹ���ȡ��������%d\n",next_e);
                }
                getchar();
                break;
            case 10:
                //��ʾ���ܲ˵�
                show();
                //��ָ��λ��֮ǰ����Ԫ��
                printf("���������ڵڼ���λ��֮ǰ����Ԫ��\n");
                int r ;
                scanf("%d",&r);
                printf("�����Ԫ�ص�ֵΪ\n");
                int a ;
                scanf("%d",&a);
                if(ListInsert(L,r,a) == OK)
                {
                    printf("����ɹ�\n");
                }
                getchar();
                break;
            case 11:
                //��ʾ���ܲ˵�
                show();
                //ɾ��ָ��λ�õ�Ԫ��
                printf("��������ɾ���ڼ�������Ԫ��\n");
                int b ;
                scanf("%d",&b);
                int ee;
                if(ListDelete(L,b,ee) == OK)
                {
                    printf("ɾ��������Ԫ����%d\n",ee);
                }
                getchar();
                break;
            case 12:
                //��ʾ���ܲ˵�
                show();
                //�������Ա�
                if(ListTraverse(L,visit) )
                {
                    printf("\n�ɹ�����\n");
                }
                getchar();
                break;
            case 13:
                //��ʾ�����б�
                funtion();
                //�����Ļ�ϵ�����
                system("cls");
                //��ʾ���ܲ˵�
                show();
                break;
            case 0:
                break;
        }//end of switch
        //�ٴ�����������
        scanf("%d",&order);
    }//end of while
    //�˳�����
    printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
    system("pause");
    return 0;
}








// 1. ��ʼ��������������InitList(L)����ʼ���������Ա�L�����ڣ���������ǹ���һ���յ����Ա�
status InitList(SqList& L)//���Ա�L�����ڣ�����һ���յ����Ա�����OK�����򷵻�INFEASIBLE��
{
// �������ﲹ����룬��ɱ�������
/********** Begin *********/
    if(L.elem)
        return INFEASIBLE;//���Ա��Ѵ��ڣ��������Ա����ڵĴ������

    L.elem = (ElemType *)malloc(sizeof(ElemType)*LIST_INIT_SIZE);//Ϊ���Ա�����ڴ�ռ�
    L.length = 0;//�����Ա�ĳ�������Ϊ0
    L.listsize = LIST_INIT_SIZE;//�������Ա������

    return OK;//���ز����ɹ��Ĵ���

/********** End **********/
}

// 2. ���ٱ�����������DestroyList(L)����ʼ���������Ա�L�Ѵ��ڣ�����������������Ա�L��
status DestroyList(SqList& L)//������Ա�L���ڣ��������Ա�L���ͷ�����Ԫ�صĿռ䣬����OK�����򷵻�INFEASIBLE��
{
// �������ﲹ����룬��ɱ�������
/********** Begin *********/
    if(!L.elem)//������Ա����ڣ��������Ա����ڵĴ������
    {
        printf("���Ա�����\n");
        return INFEASIBLE;
    }

    free(L.elem);//�ͷ����Ա���Ԫ�ص��ڴ�ռ�
    L.elem = NULL;//�����Ա�ָ����Ϊ��ָ��
    L.length = 0;//�����Ա�����Ϊ0
    L.listsize = 0;//�����Ա�������Ϊ0
    printf("�ɹ��������Ա�\n");
    return OK;//���ز����ɹ��Ĵ���

/********** End **********/
}
// 3.��ձ�����������ClearList(L)����ʼ���������Ա�L�Ѵ��ڣ���������ǽ�L����Ϊ�ձ�
status ClearList(SqList& L)
// ������Ա�L���ڣ�ɾ�����Ա�L�е�����Ԫ�أ�����OK�����򷵻�INFEASIBLE��
{
// �ж����Ա��Ƿ���ڻ��Ƿ�Ϊ��
    if(!L.length || !L.elem )
    {
        printf("���������Ա����ڻ���û��Ԫ��\n");
        return INFEASIBLE;

    }

    L.length = 0;   // �����Ա�����Ϊ0���൱����������Ա�
    printf("�ɹ�ɾ�����Ա������Ԫ����\n");
    return OK;
}

//4. �ж��ձ�����������ListEmpty(L)����ʼ���������Ա�L�Ѵ��ڣ������������LΪ�ձ��򷵻�TRUE,���򷵻�FALSE��
status ListEmpty(SqList L)
// ������Ա�L���ڣ��ж����Ա�L�Ƿ�Ϊ�գ��վͷ���TRUE�����򷵻�FALSE��������Ա�L�����ڣ�����INFEASIBLE��
{
// �ж����Ա��Ƿ����
    if(!L.elem)
    {
        printf("��ͷ�����Ա�����\n");
        return INFEASIBLE;
    }

// �ж����Ա��Ƿ�Ϊ��
    if(L.length==0)
    {
        printf("���Ա��ǿյ�\n");
        return TRUE;
    }
    printf("���Ա��ǿյ�\n");
    return FALSE;
}

// 5.���������������ListLength(L)����ʼ���������Ա��Ѵ��ڣ���������Ƿ���L������Ԫ�صĸ�����
status ListLength(SqList L)
// ������Ա�L���ڣ��������Ա�L�ĳ��ȣ����򷵻�INFEASIBLE��
{
// �ж����Ա��Ƿ����
    if(L.elem==NULL)
    {
        printf("���Ա�����\n");
        return INFEASIBLE;
    }

// �������Ա���
    else {
        return L.length;
    }
}

// 6.���Ԫ�أ�����������GetElem(L,i,e)����ʼ���������Ա��Ѵ��ڣ�1��i��ListLength(L)�������������e����L�е�i������Ԫ�ص�ֵ��
status GetElem(SqList L,int i,ElemType &e)
// ������Ա�L���ڣ���ȡ���Ա�L�ĵ�i��Ԫ�أ�������e�У�����OK�����i���Ϸ�������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
// �ж����Ա��Ƿ����
    if(!L.elem)
    {
        printf("���Ա�����\n");
        return INFEASIBLE;
    }

// �ж����Ա����i�ĺϷ���
    if(i<1 || i>L.length)
    {
        printf("��ȡ��Ԫ��i���Ϸ�\n");
        return ERROR;
    }

// ��ȡ���Ա��i��Ԫ��
    e = L.elem[i-1];
    {
        return OK;
    }
}

// 7.����Ԫ�أ�����������LocateElem(L,e,compare())����ʼ���������Ա��Ѵ��ڣ���������Ƿ���L�е�1����e�����ϵcompare������ϵ������Ԫ�ص�λ��������������Ԫ�ز����ڣ��򷵻�ֵΪ0��
int LocateElem(SqList L,ElemType e,int (*p)(int ,int ))
// ������Ա�L���ڣ�����Ԫ��e�����Ա�L�е�λ����Ų����ظ���ţ����e�����ڣ�����0�������Ա�L������ʱ������INFEASIBLE��
{
// �ж����Ա��Ƿ����
    if(!L.elem)
    {
        printf("���������Ա�����\n");
        return INFEASIBLE;
    }

// �����Ա��в���Ԫ�أ����ҵ�����λ�����
    for(int k=0;k<L.length;k++)
    {
        if(compare(L.elem[k],e))
        {
            return k+1;
        }
    }

// û���ҵ����ϵ�Ԫ��
    printf("��Ǹ��û�ҵ����ϵ�Ԫ��");
    return ERROR;
}
// 8. ���ǰ��������������PriorElem(L,cur_e,pre_e)����ʼ���������Ա�L�Ѵ��ڣ������������cur_e��L������Ԫ�أ��Ҳ��ǵ�һ��������pre_e��������ǰ�����������ʧ�ܣ�pre_e�޶���
status PriorElem(SqList L, ElemType cur_e, ElemType &pre_e) {
    // ������Ա�LΪ�գ�����INFEASIBLE
    if (!L.elem) {
        printf("Error: �����Ա����ڡ�\n");
        return INFEASIBLE;
    }

    // ���Ҫ��ȡǰ����Ԫ���ǵ�һ��������ERROR
    if (L.elem[0] == cur_e) {
        printf("Error: Ҫ��ȡǰ����Ԫ���ǵ�һ����������ǰ����\n");
        return ERROR;
    }

    // ��ѯҪ��ȡǰ����Ԫ���ڱ��е�λ��
    for (int k = 1; k < L.length; k++) {
        if (L.elem[k] == cur_e ) {
            pre_e = L.elem[k-1];
            return OK;
        }
    }

    // ���Ҫ��ȡǰ����Ԫ�ز����ڣ�����ERROR
    printf("Error: ��Ԫ�ز������ڸ����Ա��С�\n");
    return ERROR;
}

// 9. ��ú�̣�����������NextElem(L,cur_e,next_e)����ʼ���������Ա�L�Ѵ��ڣ������������cur_e��L������Ԫ�أ��Ҳ������һ��������next_e�������ĺ�̣��������ʧ�ܣ�next_e�޶��壻
status NextElem(SqList L, ElemType cur_e, ElemType &next_e) {
    // ������Ա�LΪ�գ�����INFEASIBLE
    if (!L.elem) {
        printf("Error: �����Ա����ڡ�\n");
        return INFEASIBLE;
    }

    // ���Ҫ��ȡ��̵�Ԫ�������һ��������ERROR
    if (L.elem[L.length-1] == cur_e) {
        printf("Error: Ҫ��ȡ��̵�Ԫ�������һ���������ں�̡�\n");
        return ERROR;
    }

    // ��ѯҪ��ȡ��̵�Ԫ���ڱ��е�λ��
    for (int k = 0; k < L.length-1; k++) {
        if (L.elem[k] == cur_e) {
            next_e = L.elem[k+1];
            return OK;
        }
    }

    // ���Ҫ��ȡ��̵�Ԫ�ز����ڣ�����ERROR
    printf("Error: ��Ԫ�ز������ڸ����Ա��С�\n");
    return ERROR;
}

// 10.����Ԫ�أ���Ԫ��e���뵽���Ա�L�ĵ�i��Ԫ��֮ǰ������OK��������λ�ò���ȷʱ������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
status ListInsert(SqList &L, int i, ElemType e)
{
    if (!L.elem) {
// ���Ա�Ϊ��
        printf("���Ա�Ϊ��\n");
        return INFEASIBLE;
    }

    if (i < 1 || i > L.length + 1) {
        // ����λ�ò���ȷ
        printf("����λ�ò���ȷ\n");
        return ERROR;
    }

    int k = i - 1;
    if (L.length == L.listsize) {
        // ˳�����������Ҫ���·���ռ�
        ElemType * newbase = (ElemType *)realloc(L.elem, sizeof(ElemType) * (L.listsize + LISTINCREMENT));
        if (!newbase)
            return ERROR;
        L.elem = newbase;
        L.listsize += LISTINCREMENT;
    }

// ��λ��k��������Ԫ�غ���һλ
    for (int p = L.length - 1; p >= k; p--) {
        L.elem[p + 1] = L.elem[p];
    }

// ����Ԫ��e
    L.length++;
    L.elem[k] = e;
    return OK;
}

// 11.ɾ��Ԫ�أ�ɾ�����Ա�L�ĵ�i��Ԫ�أ���������e�У�����OK����ɾ��λ�ò���ȷʱ������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
status ListDelete(SqList &L, int i, ElemType &e)
{
    if (!L.elem) {
// ���Ա�Ϊ��
        printf("���Ա�Ϊ��\n");
        return INFEASIBLE;
    }

    if (i < 1 || i > L.length) {
        // ɾ��λ�ò���ȷ
        printf("ɾ��λ�ò���ȷ\n");
        return ERROR;
    }

    e = L.elem[i - 1];
// ��λ��i�����Ԫ��ǰ��һλ
    for (int k = i - 1; k < L.length - 1; k++) {
        L.elem[k] = L.elem[k + 1];
    }
    L.length--;
    return OK;
}

// 12.������������ʾ���Ա��е�Ԫ�أ�ÿ��Ԫ�ؼ��һ�񣬷���OK��������Ա�L�����ڣ�����INFEASIBLE��
status ListTraverse(SqList L, void (*visit)(int))
{
    if (!L.elem) {
// ���Ա�Ϊ��
        printf("���Ա�Ϊ��\n");
        return INFEASIBLE;
    }

    for (int k = 0; k < L.length; k++) {
        // ����visit��ÿ��Ԫ�ؽ��в���
        visit(L.elem[k]);
        if (k != L.length - 1) {
            putchar(' ');
        }
    }
    return OK;
}

int compare(int a ,int b)
{
    if(a == b)
    {
        return 1;
    }
    return 0;
}
//�������ʱ����õ�visit����
void visit(int elem)
{
    printf("%d",elem);
}
//���������������
int MaxSubArray(SqList L)
{
    if(!L.elem) //������Ա�����
    {
        printf("���������Ա�����");
        return INFEASIBLE;
    }
    int max ,current ; //����max��ʾ���ֵ��current��ʾ��ǰֵ
    max = current = L.elem[0]; //��ʼ��max��currentΪ���Ա�L�ĵ�һ��Ԫ��
    for(int k = 1;k<L.length;k++) //�������Ա�L
    {
        if(current <= 0) //�����ǰֵС�ڵ���0
        {
            current = L.elem[k]; //����ǰֵ��Ϊ��һ��Ԫ�ص�ֵ
        } else{
            current+=L.elem[k]; //����ǰֵ���ۼӲ���
        }
        if(max < current) //������ֵС�ڵ�ǰֵ
        {
            max = current; //�������ֵΪ��ǰֵ
        }
    }
    return max ; //�����������ֵ
}
//�������Ա�L�к�Ϊu�����������
int SubArrayNum(SqList L, int u)
{
    if(!L.elem)
    {
        printf("���������Ա�����");
        return INFEASIBLE; //�������Ա����ڵĴ������
    }
    int count = 0; //���������������
    for(int k = 0; k < L.length; k++)
    {
        int sum = 0; //������Ԫ��֮��
        for(int i = k; i < L.length; i++)
        {
            sum += L.elem[i]; //�ۼ�Ԫ��ֵ
            if(sum == u)
            {
                count ++ ; //�������Ϊu����������һ
            }
        }
    }
    return count ;
}//ð������ʵ��˳�������
int sort(SqList &L)
{
    for(int k = 0; k < L.length - 1; k++)//��������
    {
        for(int i = 0; i < L.length - 1 - k; i++)//ÿ�ֱȽ�����Ԫ��
        {
            if(L.elem[i] > L.elem[i+1])//������Ԫ�ش����ұ�Ԫ��
            {
                int tmp = L.elem[i];//��������Ԫ�ص�λ��
                L.elem[i] = L.elem[i+1];
                L.elem[i+1] = tmp;
            }
        }
    }
}

/* �������Ĳ˵� */
void show()
{
    for(int k = 0; k<= 119 ;k++) // ��ӡ�ָ���
    {
        putchar('-');
    }
    printf("           Menu for Linear Table On Sequence Structure \n");
    printf("    	  1. InitList                       7. LocateElem\n");
    printf("    	  2. DestroyList                    8. PriorElem\n");
    printf("    	  3. ClearList                      9. NextElem \n");
    printf("    	  4. ListEmpty                      10. ListInsert\n");
    printf("    	  5. ListLength                     11. ListDelete\n");
    printf("    	  6. GetElem                        12. ListTrabverse\n");
    printf("    	  13. plusfunction                        \n");
    printf("    	  0.exit                        \n");
    for(int k = 0; k<= 119 ;k++) // ��ӡ�ָ���
    {
        putchar('-');
    }
    putchar('\n');
// ������һ�����ж�̬ͼ�������������Թ�
    printf(" ��ѡ����Ĳ���[0~13]:");
    putchar('\n');
    for(int k = 0; k<= 119 ;k++)
    {
        putchar('-');
    }

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
}

void show1()
{
    // ��ӡ�˵�ǰ�ķָ���
    printf("���Ƕ�����Ա�����еĲ˵�\n");
    for(int k = 0; k<=  119 ;k++)
    {
        putchar('-');
    }
    // ��ӡ�˵�����
    printf("           Menu for Linear Table On Sequence Structure \n");
    printf("    	  1. InitList                       7. LocateElem\n");
    printf("    	  2. DestroyList                    8. PriorElem\n");
    printf("    	  3. ClearList                      9. NextElem \n");
    printf("    	  4. ListEmpty                      10. ListInsert\n");
    printf("    	  5. ListLength                     11. ListDelete\n");
    printf("    	  6. GetElem                        12. ListTrabverse\n");
    printf("       0.exit\n");
    // ��ӡ�˵���ķָ���
    for(int k = 0; k<=  119 ;k++)
    {
        putchar('-');
    }  putchar('\n');
    // ��ӡ�����һЩ�˵�����
    printf("    ��ѡ����Ĳ���[0~1]:");
    putchar('\n');
    for(int k = 0; k<=  119 ;k++)
    {
        putchar('-');
    }
    // ��ӡһ�� ASCII ����
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

}

void menu()
{
    printf("1.����һ�����Ա�\n");
    printf("2.ɾ��һ�����Ա�\n");
    printf("3.����һ�����Ա�ͽ��в���\n");
    printf("0.�˳����Ա�Ĺ���\n");

}

// ��������savetofile
// ���ܣ������Ա� L �е�Ԫ�ر��浽�ļ���
// ������������Ա� L
// ����ֵ�������ɹ����� OK�����򷵻� INFEASIBLE
int savetofile(SqList L)
{
    printf("���������뱣�浽���ļ���\n"); // ��ʾ����Ҫ������ļ���
    char arr[30];
    scanf("%s",arr); // ��ȡ�û�������ļ���

    FILE *fp;
    fp = fopen(arr,"w"); // ��д�뷽ʽ���ļ�
    if(fp == NULL){ // ����ļ���ʧ��
        printf("error"); // ���������Ϣ
        return INFEASIBLE; // ���ش������
    }

    int i ;
    for( i =0; i< L.length; i++) // �������Ա��е�Ԫ��
    {
        fprintf(fp,"%d ",L.elem[i]); // ��Ԫ��д���ļ���
    }

    fclose(fp); // �ر��ļ�
    return OK; // ���ز����ɹ�����
}

// ��������getfromfile
// ���ܣ����ļ��ж�ȡ���Ա� L ��Ԫ��
// ������������Ա� L �ĵ�ַ
// ����ֵ�������ɹ����� OK�����򷵻� INFEASIBLE
int getfromfile(SqList &L)
{
    if(!L.elem) // ������Ա�����
    {
        printf("���������Ա�����\n"); // ���������Ϣ
        return INFEASIBLE; // ���ش������
    }

    printf("��������Ҫ��ȡ���ļ���:\n"); // ��ʾ����Ҫ��ȡ���ļ���
    char name[30] = {'\0'};
    scanf("%s",name); // ��ȡ�û�������ļ���

    FILE *fp = fopen(name,"r"); // ��ֻ����ʽ���ļ�
    if(fp == NULL){ // ����ļ���ʧ��
        printf("error"); // ���������Ϣ
        return INFEASIBLE; // ���ش������
    }

    int j;
    while(fscanf(fp,"%d ",&j) !=EOF) // ��ȡ�ļ��е�Ԫ��
    {
        L.elem[L.length++] = j; // ��Ԫ����ӵ����Ա���
    }

    fclose(fp); // �ر��ļ�
    return OK; // ���ز����ɹ�����
}

// �������Ĺ���Ϊ�����Ա����ϵͳLists������һ����ΪListName�Ŀ����Ա�
// ����Ѿ�������ΪListName�����Ա��򷵻�INFEASIBLE�����򷵻�OK
status AddList(LISTS &Lists,char ListName[])
{
// �����������Ա������Ƿ��Ѿ�������ΪListName�����Ա�
    for(int i = 0; i<Lists.length ;i++)
    {
        if(strcmp(ListName,Lists.elem[i].name) == 0)
        {
            printf("������ֵ����Ա��Ѿ�������");
            return INFEASIBLE;
        }
    }

// �����������ΪListName�����Ա�����Lists�����һ���µ����Ա�
    Lists.length++; // �����Ա����ϵͳ������һ�����Ա�
    int n = 0; // ��ʼ�����Ա�ĳ���nΪ0�������Ա�Ϊ��

// �������Ա����������ΪListName
    strcpy(Lists.elem[Lists.length-1].name ,ListName);

// �������Ա�����ݳ�ʼ��Ϊ�գ���û��Ԫ��
    Lists.elem[Lists.length-1].L.elem=NULL;

// ע�͵���InitList����Ҫ���ã���ΪL.elem������ΪNULL
// InitList(Lists.elem[Lists.length-1].L);

// ����������Ա����ִ�гɹ�
    return OK;
}

status RemoveList(LISTS &Lists,char ListName[])
// Lists��ɾ��һ������ΪListName�����Ա�
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    // �������Ա�
    for(int k = 0;k<Lists.length;k++)
    {
        // �ҵ�����ΪListName�����Ա�
        if(strcmp(Lists.elem[k].name,ListName)==0)
        {
            // �������Ա�
            DestroyList(Lists.elem[k].L);
            // ����������Ա�ǰ�ƣ����ǵ�ǰλ��
            for(int i = k;i<Lists.length-1;i++)
            {
                strcpy(Lists.elem[i].name, Lists.elem[i+1].name);   //ע��Ҫ���ֺͽṹ��һ���ƶ����Ҹо�û�нݾ�
                Lists.elem[i].L.elem =Lists.elem[i+1].L.elem;
                Lists.elem[i].L.length = Lists.elem[i+1].L.length;
                Lists.elem[i].L.listsize =Lists.elem[i+1].L.listsize;
            }
            Lists.length--; // ���Ա�������һ
            return OK;
        }
    }
    // û���ҵ�Ŀ�����Ա����ش���
    return ERROR;

    /********** End **********/
}

int LocateList(LISTS Lists,char ListName[])
// ��Lists�в���һ������ΪListName�����Ա��ɹ������߼���ţ����򷵻�-1
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    // ѭ���������Ա�����
    for(int k = 0 ;k< Lists.length;k++)
    {
        // ����ҵ���ָ�����Ƶ����Ա�
        if(strcmp(Lists.elem[k].name,ListName)==0)
        {
            // ���ظ����Ա���߼���ţ�����λ��+1��
            return k+1;
        }
    }
    // ���δ�ҵ�ָ�����Ƶ����Ա��򷵻�-1
    return -1;

    /********** End **********/
}


void funtion()
{
    showplus();  // ��ʾ�˵�ҳ��ͷ��
    SqList S ;  // ���ڲ��������Ա�S���������Ա�

    int order ;
    scanf("%d",&order);   // ��ȡ�û����������
    while(order) {    // ����û��������������0�������ѭ��

        system("cls");  // ��տ���̨��Ļ
        showplus();    // ������ʾ�˵�ҳ��ͷ��

        switch (order) {   // �����û����������Ӧ����
            case 1:
                // �������Ա�

                S.elem = (ElemType *) malloc(sizeof(ElemType) * LIST_INIT_SIZE);   // Ϊ���Ա�����ڴ�ռ�
                S.length = 0;   // ��ʼ�����Ա���Ϊ0
                S.listsize = LIST_INIT_SIZE;   // ��ʼ�����Ա���ô�СΪLIST_INIT_SIZE


                printf("������һ�����ݣ�����֮���ÿո����,���һ������������ֱ�ӻس�\n");
                int number;
                scanf("%d", &number);
                char c;
                c = getchar();
                while (c != '\n') {   // ������δ����ʱ��ѭ����ȡ���ݲ���ӵ����Ա���
                    S.elem[S.length++] = number;
                    scanf("%d", &number);
                    c = getchar();
                }
                S.elem[S.length++] = number;  // �����һ��������ӵ����Ա���
                break;
            case 2:
                // Ѱ�����������
                int r;

                r = MaxSubArray(S);   // ����MaxSubArray�����������������֮��
                if (r != -1) {
                    printf("�������������֮����%d\n", r);
                }
                // printf("��������һ������\n");
                break;
            case 3:
                // Ѱ�Һ�ΪK������������
                printf("���������Ѱ��һ����ΪK������������\n");
                int k;
                printf("������һ��Kֵ\n");
                scanf("%d", &k);
                if (SubArrayNum(S, k) != -1) {   // ����SubArrayNum���������Ա��в��Һ�ΪK������������
                    printf("���Ա��к�Ϊk��������������Ϊ%d\n", SubArrayNum(S, k));
                }
                break;
            case 4:
                // �����Ա��������
                sort(S);    // ����sort���������Ա��������
                printf("�����������Ա�����:\n");
                ListTraverse(S, visit);   // ʹ��ListTraverse����������������Ա��е�����
                putchar('\n');
                break;
            case 5:
                // �����Ա��浽�ļ���
                printf("���ڽ������Ա���ļ���ʽ����\n");
                int message;
                message =  savetofile(S);  // ����savetofile���������Ա��浽�ļ���
                if(message == OK)
                {
                    printf("�洢�ɹ�\n");
                    //printf("��������һ������\n");
                }
                break;
            case 6:
                // ���ļ��ж�ȡ���Ա�����
                printf("���ڽ����ļ��Ķ�ȡ\n");
                SqList p;
                p.elem = NULL;
                InitList(p);   //��������Ա����洢��ȡ������
                if(getfromfile(p) == OK)   // ����getfromfile�������ļ��ж�ȡ���ݲ����浽p��
                {
                    printf("��ȡ�ɹ�\n��ȡ����������:\n");
                    ListTraverse(p,visit);  // ʹ��ListTraverse����������������Ա��е�����
                }
                else {
                    printf("��ȡʧ��");
                }
                //printf("��������һ������\n");
                break;
                // ���ж�����Ա�Ĺ���
            case 7:
                printf("���ڽ��ж�����Ա�Ĺ���\n");
                menu(); // ��ʾ�˵�
                int a;
                scanf("%d", &a);
                while (a) {
                    switch (a) {
                        // �������Ա�
                        case 1:
                            printf("���ڽ��д������Ա�\n");
                            printf("���������봴�������Ա������\n");
                            char name1[30];
                            scanf("%s", name1);
                            int u;
                            u = AddList(Lists, name1); // ������Ա�
                            if (u == OK) {
                                printf("�����ɹ���\n");
                            }
                            if (u == INFEASIBLE) {
                                system("pause");
                            }
                            break;
                            // ɾ�����Ա�
                        case 2:
                            printf("���ڽ���ɾ�����Ա�\n");
                            printf("���������봴�������Ա������\n");
                            char name2[30];
                            scanf("%s", name2);
                            RemoveList(Lists, name2); // ɾ�����Ա�
                            break;
                            // ���ҺͲ������Ա�
                        case 3:
                            printf("���ڽ������Ա�Ĳ��ҺͲ���\n");
                            printf("������������ҺͲ��������Ա������\n");
                            char name3[30];
                            scanf("%s", name3);
                            int judge;
                            judge = LocateList(Lists, name3); // �������Ա�
                            if (judge == -1) {
                                printf("������������Ա�\n");
                                system("pause");
                            } else {
                                printf("���Ա����ѼѼ\n");
                                printf("���ڶ�������Ա���в���\n");
                                int order;
                                show(); // ��ʾ���Ա�����˵�
                                scanf("%d", &order);
                                while (order) {
                                    switch (order) {
                                        // ��ʼ�����Ա�
                                        case 1:
                                            show1(); // ��ʾ������ʾ
                                            if (InitList(Lists.elem[judge - 1].L) == OK)
                                                printf("���Ա����ɹ���\n");
                                            else printf("���Ա��Ѿ����ڣ�����ʧ�ܣ�\n");
                                            getchar();
                                            break;
                                            // ɾ�����Ա�
                                        case 2:
                                            show1();
                                            DestroyList(Lists.elem[judge - 1].L); // �������Ա�
                                            getchar();
                                            break;
                                            // ������Ա�
                                        case 3:
                                            show1();
                                            ClearList(Lists.elem[judge - 1].L); //������Ա�
                                            getchar();
                                            break;
                                            // �ж����Ա��Ƿ�Ϊ��
                                        case 4:
                                            show1();
                                            ListEmpty(Lists.elem[judge - 1].L);
                                            getchar();
                                            break;
                                            // ��ȡ���Ա�ĳ���
                                        case 5:
                                            show1();
                                            int getdata;
                                            getdata = ListLength(Lists.elem[judge - 1].L);
                                            if (getdata != INFEASIBLE) {
                                                printf("���Ա�ĳ�����%d", getdata);
                                            }
                                            getchar();
                                            break;
                                            // ��ȡ���Ա��е�Ԫ��
                                        case 6:
                                            show1();
                                            printf("�����������ȡ�ڼ���Ԫ��\n");
                                            int i;
                                            scanf("%d", &i);
                                            int n;
                                            int getdata1;
                                            n = GetElem(Lists.elem[judge - 1].L, i, getdata1);
                                            if (n == OK) {
                                                printf("�ɹ���ȡ����%d��Ԫ�ص�ֵ��%d\n", i, getdata1);
                                            }
                                            getchar();
                                            break;
                                            // �������Ա��е�Ԫ��
                                        case 7:
                                            show1();
                                            int u;
                                            printf("������һ����ֵe\n");
                                            int e;
                                            scanf("%d", &e);
                                            printf("�����ڱ������һ����e����С�����ݣ���������1��С������0\n");
                                            int getorder;
                                            scanf("%d", &getorder);
                                            int q;
                                            if (getorder == 1) {
                                                printf("����Ҫ������ݱ�e�����\n");
                                                scanf("%d", &q);
                                                if (LocateElem(Lists.elem[order - 1].L, e + q, compare) > 0) {
                                                    printf("��Ҫ���ҵ����ݵ��±����%d\n", LocateElem(Lists.elem[judge - 1].L, e + q, compare));
                                                }
                                            } else {
                                                printf("����Ҫ������ݱ�eС����\n");
                                                scanf("%d", &q);
                                                if (LocateElem(Lists.elem[judge - 1].L, e + q, compare) > 0) {
                                                    printf("��Ҫ���ҵ����ݵ��±����%d\n", LocateElem(Lists.elem[judge - 1].L, e + q, compare));
                                                }
                                            }
                                            getchar();
                                            break;
                                            // ��ȡ���Ա���ĳ��Ԫ�ص�ǰ��
                                        case 8:
                                            show1();
                                            printf("�����������Ǹ�Ԫ�ص�ǰ��\n");
                                            int v;
                                            scanf("%d", &v);
                                            int pre_e;
                                            if (PriorElem(Lists.elem[judge - 1].L, v, pre_e) == OK) {
                                                printf("�ɹ����ǰ������%d\n", pre_e);
                                            }
                                            getchar();
                                            break;
                                            // ��ȡ���Ա���ĳ��Ԫ�صĺ���
                                        case 9:
                                            show1();
                                            printf("�����������ĸ�Ԫ�صĺ���\n");
                                            int p;
                                            scanf("%d", &p);
                                            int next_e;
                                            if (NextElem(Lists.elem[judge - 1].L, p, next_e) == OK) {
                                                printf("�ɹ���ȡ��������%d\n", next_e);
                                            }
                                            getchar();
                                            break;
                                            // �����Ա��в���Ԫ��
                                        case 10:
                                            show1();
                                            printf("���������ڵڼ���λ��֮ǰ����Ԫ��\n");
                                            int r;
                                            scanf("%d", &r);
                                            printf("�����Ԫ�ص�ֵΪ\n");
                                            int a;
                                            scanf("%d", &a);
                                            if (ListInsert(Lists.elem[judge - 1].L, r, a) == OK) {
                                                printf("����ɹ�\n");
                                            }
                                            getchar();
                                            break;
                                            // �����Ա���ɾ��Ԫ��
                                        case 11:
                                            show1();
                                            printf("��������ɾ���ڼ�������Ԫ��\n");
                                            int b;
                                            scanf("%d", &b);
                                            int ee;
                                            if (ListDelete(Lists.elem[judge - 1].L, b, ee) == OK) {
                                                printf("ɾ��������Ԫ����%d\n", ee);
                                            }
                                            getchar();
                                            break;
                                            // �������Ա�
                                        case 12:
                                            show1();
                                            if (ListTraverse(Lists.elem[judge - 1].L, visit)) {
                                                printf("\n�ɹ�����\n");
                                            }
                                            getchar();
                                            break;
                                        case 0:
                                            break;
                                    }
                                    scanf("%d", &order);
                                }
                            }
                            break;
                        case 0:
                            break;
                    }
                    system("cls");
                    menu(); // ��ʾ�˵�
                    printf("��������һ������\n");
                    scanf("%d", &a);
                }
                break;
            default:
                printf("����������ȷ�����ٴ�����\n");
                break;
        }
        printf("��������һ������\n");
        scanf("%d", &order);
    }
}

void showplus()
{
    for(int k = 0; k<=  119 ;k++)
    {
        putchar('-');
    }  putchar('\n');
    printf("����һЩ���ӵĹ��ܣ���֮ǰ�����Ա�����\n");
    printf("    	  1.��ʼ�����Ա�\n");
    printf("    	  2.maxSubarray                     3.subarrayNum\n");
    printf("    	  4.sortList                        5.savetofile\n");
    printf("    	  6.getfromfile                     7.managelist\n");
    printf("    	  0. Exit\n");
    for(int k = 0; k<=  119 ;k++)
    {
        putchar('-');
    }  putchar('\n');
}
