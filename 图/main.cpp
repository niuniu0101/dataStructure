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
#define MAX_VERTEX_NUM 20

// ��������Ԫ������
typedef int ElemType;
typedef int status;
typedef int KeyType;
typedef enum {DG,DN,UDG,UDN} GraphKind;

//���嶥�����ͣ������ؼ��ֺ�������Ϣ
typedef struct {
    KeyType key; //�ؼ���
    char others[20]; //������Ϣ
} VertexType;

//�����ڽӱ�������
typedef struct ArcNode {
    int adjvex; //�����ڶ��������е��±�
    struct ArcNode *nextarc; //ָ����һ������ָ��
} ArcNode;

//����ͷ������ͺ��������ͣ�ͷ���ͱ߱���һ������
typedef struct VNode{
    VertexType data; //������Ϣ
    ArcNode *firstarc; //ָ���һ������ָ��
} VNode,AdjList[MAX_VERTEX_NUM];

//�����ڽӱ����ͣ�����ͷ������顢��������������ͼ������
typedef struct {
    AdjList vertices; //ͷ�������
    int vexnum,arcnum; //�������ͻ���
    GraphKind kind; //ͼ�����ͣ�����ͼ������ͼ�ȣ�
} ALGraph;

//����ͼ�������ͣ�����һ���ṹ�����飬ÿ���ṹ�����ͼ�����ƺ��ڽӱ�
typedef struct {
    struct {
        char name[30]="0"; //ͼ������
        ALGraph G; //��Ӧ���ڽӱ�
    }elem[30]; //ͼ�ĸ���
    int length; //ͼ������ͼ������
}Graphs;

Graphs graphs;  //ͼ�ļ��ϵĶ���

/*---- �������� ----*/
status isrepeat(VertexType V[]);  //�ж��Ƿ����ظ����
status CreateCraph(ALGraph &G,VertexType V[],KeyType VR[][2]);  //����
status DestroyGraph(ALGraph &G);  //����
status LocateVex(ALGraph G, KeyType u);  //����
status PutVex(ALGraph &G, KeyType u, VertexType value);  //���㸳ֵ
status FirstAdjVex(ALGraph G, KeyType u);  //��õ�һ�ڽӵ�
status NextAdjVex(ALGraph G, KeyType v, KeyType w);  //�����һ�ڽӵ�
status InsertVex(ALGraph &G,VertexType v);  //���붥��
status DeleteVex(ALGraph &G, KeyType v);  //ɾ������
status InsertArc(ALGraph &G,KeyType v,KeyType w);  //���뻡
status DeleteArc(ALGraph &G,KeyType v,KeyType w);  //ɾ����
void dfs(ALGraph G , void (*visit)(VertexType),int nownode);
status DFSTraverse(ALGraph G,void (*visit)(VertexType));  //dfs����
void BFS(ALGraph G,void  (*visit)(VertexType),int i);
status BFSTraverse(ALGraph G,void (*visit)(VertexType));  //bfs����
void visit(VertexType p);  //������ʱ����õ��������
int * VerticesSetLessThanK(ALGraph  G,int v,int k);  //����С��k�Ķ��㼯��
int ShortestPathLength(ALGraph G,int v,int w);  //���������·��
int ConnectedComponentsNums(ALGraph G);  //ͼ�ķ���
status SaveGraph(ALGraph G, char FileName[]);  //ͼ���ļ�����
status LoadGraph(ALGraph &G, char FileName[]);  //ͼ���ļ���ȡ
void menu();  //���ͼ����Ĳ˵�
void menu2();  //����ͼ����Ĳ˵�
void fun01();  //���ͼ����ķ�װ����
void fun02(ALGraph &G);  //����ͼ����ķ�װ����

/*----  main������  ----*/
int main()
{
	system("color 37");
    fun01();  //��װ������

    return 0;
}




/*----  �����Ķ��� ----*/

status isrepeat(VertexType V[])  // �����ظ��ڵ�
{
    int i=0;
    int flag[1000]={0};  //��Ʊ������
    while (V[i].key != -1)
    {
        if(flag[V[i].key] != 0)  // ������ظ��Ľ�㣬���� 1
        {
            return 1;
        }
        flag[V[i].key]++;  // ��ǹؼ��֣��Լ���ظ��ڵ�
        i++;
    }
    return 0;
}

/*����V��VR����ͼT������OK�����V��VR����ȷ������ERROR*/
status CreateCraph(ALGraph &G, VertexType V[], KeyType VR[][2])
{
    if(G.vexnum != 0)  // ���ͼ�Ѿ������������ٴγ�ʼ��
    {
        printf("��ͼ�Ѿ���ʼ���������ٴγ�ʼ��\n");
        return INFEASIBLE;
    }
    int i=0;
    int flag[100000];  // ���ÿ���ؼ��ֳ��ֵ�λ��
    int flagvr[500][500]={0};  // ���ÿ�����Ƿ���ֹ�����ֹ�ظ��ߺ��Ի��ĳ���

    memset(flag,-1,sizeof(flag));  // ��������ʼ��Ϊ -1
    if(isrepeat(V)== 1 || V[0].key==-1 || (V[1].key ==-1 && VR[0][0]!=-1))
    {
        return ERROR;  // ������ֿ�ͼ���Ի����Լ��ظ����ȣ����ش������
    }

    while (V[i].key!= -1)
    {
        if(i >= MAX_VERTEX_NUM)  // ��������ڵ��������������ش������
        {
            return ERROR;
        }
        G.vertices[i].data = V[i];  // ���ڵ���Ϣ�洢�� vertices ������
        G.vertices[i].firstarc = NULL; // ��ʼ���ڵ�ĵ�һ���ڽӵ�Ϊ��
        flag[V[i].key] = i;  // ���ÿ���ڵ��λ��
        i++;
    }

    G.vexnum=i;   // �洢�ڵ�����

    i=0;

    while (VR[i][0]!= -1) // ������
    {
        flagvr[VR[i][0]][VR[i][1]]++;  // ��Ǳ��Ƿ���ֹ�

        // ������ֻ����ظ��ıߣ����ش������
        if(VR[i][0]==VR[i][1] || (flagvr[VR[i][0]][VR[i][1]]+flagvr[VR[i][1]][VR[i][0]]) > 1)
        {
            return ERROR;
        }

        if(flag[VR[i][0]] == -1)  // ��������ӵĽڵ�û�г��ֹ������ش������
        {
            return ERROR;
        }

        // �����㣬ʹ��ͷ�巨�������뵽�ڽ������ǰ��
        ArcNode *last = G.vertices[flag[VR[i][1]]].firstarc;
        ArcNode *p = (ArcNode *) malloc(sizeof(ArcNode));
        p->adjvex = flag[VR[i][0]];
        p->nextarc = NULL;

        if(last == NULL)  // ����ǵ�һ���ڽӵ㣬ֱ�Ӳ���
        {
            G.vertices[flag[VR[i][1]]].firstarc = p;
            i++; // ������һ���ߵĲ���

        } else{  // ������ǵ�һ���ڽӵ㣬ʹ��ͷ�巨���в���
            p->nextarc = last;
            G.vertices[flag[VR[i][1]]].firstarc = p;
            i++; // ������һ���ߵĲ���
        }
    }

    i=0;

    while(VR[i][1]!=-1) // ������һ������ı�
    {
        if(flag[VR[i][1]] == -1)
        {
            return ERROR;
        }

        // �����㣬ʹ��ͷ�巨�������뵽�ڽ������ǰ��
        ArcNode *last = G.vertices[flag[VR[i][0]]].firstarc;
        ArcNode *p =(ArcNode*) malloc(sizeof(ArcNode));
        p->adjvex = flag[VR[i][1]];
        p->nextarc = NULL;

        if(last == NULL)  // ����ǵ�һ���ڽӵ㣬ֱ�Ӳ���
        {
            G.vertices[flag[VR[i][0]]].firstarc = p;
            i++; // ������һ���ߵĲ���
        }
        else{ // ������ǵ�һ���ڽӵ㣬ʹ��ͷ�巨���в���
            p->nextarc = last;
            G.vertices[flag[VR[i][0]]].firstarc = p;
            i++; // ������һ���ߵĲ���
        }
    }

    G.arcnum=i;  // �洢�ߵ�����
    return OK;
}

status DestroyGraph(ALGraph &G)
/*��������ͼG,ɾ��G��ȫ������ͱ�*/
{
    // ���ͼ�����ڣ����ء������С��Ĵ�����Ϣ
    if(G.vexnum == 0 )
    {
        return INFEASIBLE;
    }
    ArcNode *p =NULL;
    ArcNode *sub =NULL;
    int i =0;
    // ѭ���������еĶ���
    while (i<G.vexnum)
    {
        sub = G.vertices[i].firstarc;
        // ��ÿ�����㣬ѭ����������ÿ���ڽӵ�
        while (sub)
        {
            p = sub;
            sub = sub->nextarc;
            // ɾ�����ڽӵ��Ӧ�ı�
            free(p);
            p = NULL;
        }
        i++;
    }
    // ���ü���������ʾͼ��û�ж���ͱ�
    G.vexnum =0;
    G.arcnum =0;
    return OK;
}

int LocateVex(ALGraph G, KeyType u)
//����u��ͼG�в��Ҷ��㣬���ҳɹ�����λ�򣬷��򷵻�-1��

{
    // ���ͼ�����ڣ����ء������С��Ĵ�����Ϣ
    if(G.vexnum == 0 )
    {
        printf("��ͼ�����ڻ�δ��ʼ��\n");
        return INFEASIBLE;
    }
    int i =0;
    // ѭ���������еĶ���
    while(i<G.vexnum)
    {
        // ����ҵ��ؼ���ֵΪu�Ķ��㣬��������λ��
        if(G.vertices[i].data.key == u)
        {
            return i;
        }
        i++;
    }
    // ���û�ҵ��ؼ���ֵΪu�Ķ��㣬����-1
    return -1;
}


//���㸳ֵ������������PutVex (G,u,value)����ʼ������ͼG���ڣ�u�Ǻ�G�ж���ؼ���������ͬ�ĸ���ֵ��
//��������ǶԹؼ���Ϊu�Ķ��㸳ֵvalue��
status PutVex(ALGraph &G, KeyType u, VertexType value)
{
    // ���ͼ�����ڣ����ش�����Ϣ INFEASIBLE
    if(G.vexnum == 0 )
    {
        printf("��ͼ�����ڻ�δ��ʼ��\n");
        return INFEASIBLE;
    }
    int i=0;  //������¼�±�
    int num=0; int flag=-1;  //�����ͱ��
    while (i<G.vexnum)
    {
        // ����ؼ��ֲ�Ψһ�����ش�����Ϣ ERROR
        if(value.key == G.vertices[i].data.key  && value.key != u)
        {
            printf("�ؼ��ֲ�Ψһ,����ʧ��\n");
            return ERROR;
        }
        // ������ҵ���ָ���Ķ��㣬��¼����ֵĴ������±�
        if(G.vertices[i].data.key == u)
        {
            num++;       //������¼���ֵĴ���
            flag =i;     //�����±�
        }
        i++;
    }
    // ���δ���ҵ�ָ���Ķ�����߲��ҵ��Ĵ�����Ψһ�����ش�����Ϣ ERROR
    if(num != 1)
    {
        printf("����ʧ��,�޷�����\n");
        return ERROR;
    }
    // ���ҵ��ķ��������Ķ����ֵ�޸ĳ�ָ���� value ֵ
    G.vertices[flag].data = value;
    // �����ɹ������� OK
    return OK;
}
//��õ�һ�ڽӵ㣺����������FirstAdjVex(G, u)����ʼ������ͼG���ڣ�u��G�ж����λ��
//��������Ƿ���u��Ӧ����ĵ�һ���ڽӶ���λ�����u�Ķ���û���ڽӶ��㣬���򷵻�������ʾ�������ڡ�����Ϣ��
int FirstAdjVex(ALGraph G, KeyType u)
{
    // ���ͼ�����ڣ����ش�����Ϣ INFEASIBLE
    if(G.vexnum == 0 )  //ͼ������
    {
        printf("��ͼ�����ڻ�δ��ʼ��\n");
        return INFEASIBLE;
    }
    // ��ͼ G ��Ѱ�Ҹ����ؼ��ֶ�Ӧ�Ķ���
    int i=0;  //��������
    while (i<G.vexnum)
    {
        if(G.vertices[i].data.key == u)
        {
            // ����ҵ��˶��㣬�򷵻ظö����Ӧ�ĵ�һ�ڽӶ����λ��
            return G.vertices[i].firstarc->adjvex;
        }
        i++;
    }
    // ���δ�ҵ������ؼ��ֶ�Ӧ�Ķ��㣬������Ϣ�������ڡ����� -1
    return -1;
}

//�����һ�ڽӵ㣺����������NextAdjVex(G, v, w)����ʼ������ͼG���ڣ�v��w��G�����������λ��v��ӦG��һ������,w��Ӧv���ڽӶ��㣻�������
// �Ƿ���v�ģ������w����һ���ڽӶ����λ�����w�����һ���ڽӶ��㣬����������ʾ�������ڡ�����Ϣ��
// ����˵����GΪ����ͼ��v��Դ�ڵ㣬w��Ŀ��ڵ�
int NextAdjVex(ALGraph G, KeyType v, KeyType w)
{
// ���ͼ�����ڣ��򷵻ء������ڡ�����Ϣ
    if (G.vexnum == 0 )
    {
        printf("��ͼ�����ڻ�δ��ʼ��\n");
        return INFEASIBLE;
    }
    int i = 0;
    int flagv = -1, flagw = -1; // ������¼v��w��Ӧ���±�
// �ҵ�v��w��G.vertices�����е��±�
    while (i < G.vexnum)
    {
        if (G.vertices[i].data.key == v)
        {
            flagv = i;
        }
        if (G.vertices[i].data.key == w)
        {
            flagw = i;
        }
        i++;
    }
// ���Ҳ���v��w��Ӧ�Ľ�㣬���ء������ڡ�����Ϣ
    if (flagv == -1 || flagw == -1)
    {
        printf("v��w��Ӧ�Ľ�㲻����\n");
        return -1;
    }
    ArcNode* p = G.vertices[flagv].firstarc;
    ArcNode* ptail = p->nextarc;
// ����Դ�ڵ���ڽ������ҵ�Ŀ��ڵ�w
    while (ptail)
    {
        if (p->adjvex == flagw)
        {
// ���w�������һ���ڽӶ��㣬�򷵻�����һ���ڽӶ����λ�򣬷��򷵻ء������ڡ�����Ϣ
            return ptail->adjvex;
        }
        p = ptail;
        ptail = p->nextarc;
    }
    return -1;
}

//���붥�㣺����������InsertVex(G,v)����ʼ������ͼG���ڣ�v��G�еĶ��������ͬ�����������������ͼG�������¶���v��
// ��������Ҳ���ֶ���ؼ��ֵ�Ψһ�ԣ�
// ����˵����GΪ����ͼ��vΪҪ����Ľ��
status InsertVex(ALGraph& G, VertexType v)
{
// ���ͼ�����ڣ��򷵻ء������ڡ�����Ϣ
    if (G.vexnum == 0)
    {
        printf("��ͼ�����ڻ�δ��ʼ��\n");
        return INFEASIBLE;
    }
    int i = 0;  //��¼�±�
// ���ͼ�ж��������Ѵﵽ������ƣ��򷵻�ERROR
    if (G.vexnum == MAX_VERTEX_NUM)
    {
        printf("�����������ɵ���󶥵����ռ�\n");
        return ERROR;
    }
// ����ͼ���Ƿ�����KEY��ͬ�Ľ��
    while (i < G.vexnum)
    {
        if (G.vertices[i].data.key == v.key)
        {
            printf("�ؼ��ֲ�Ψһ\n");
            return ERROR;
        }
        i++;
    }
// ��G.vertices��������һ��λ�ò����½�㣬����G.vexnum
    G.vertices[G.vexnum].data = v;
    G.vertices[G.vexnum].firstarc = NULL;
    G.vexnum++;
    return OK;
}

//ɾ�����㣺����������DeleteVex(G,v)����ʼ������ͼG���ڣ�v�Ǻ�G�ж���ؼ���������ͬ�ĸ���ֵ��
// �����������ͼG��ɾ���ؼ���v��Ӧ�Ķ����Լ���صĻ�
status DeleteVex(ALGraph &G, KeyType v)
//��ͼG��ɾ���ؼ���v��Ӧ�Ķ����Լ���صĻ����ɹ�����OK,���򷵻�ERROR
{
// �������ﲹ����룬��ɱ�������
//��ͼ�����ڻ�δ��ʼ�����򷵻ز�����״̬
    if(G.vexnum == 0 )
    {
        printf("��ͼ�����ڻ�δ��ʼ��\n");
        return INFEASIBLE;
    }
//��ͼ��ֻ��һ�����㣬���޷�ɾ�������ش���״̬
    if(G.vexnum == 1)
    {
        printf("ͼ��ֻ��һ�����㣬����ɾ��\n");
        return ERROR;
    }
    int i =0;  //����±�
//Ѱ��Ҫɾ���Ķ���
    while (i<G.vexnum)
    {
        if(G.vertices[i].data.key == v)
        {
//ɾ������������йصĻ�
            while (G.vertices[i].firstarc){
                G.arcnum--;
                ArcNode * p = G.vertices[i].firstarc;
                G.vertices[i].firstarc = p->nextarc;
                free(p);
                p = NULL;
            }
            break;
        }
        i++;
    }
    int location = i;  //��¼λ��
//��Ҫɾ���Ķ��㲻���ڣ��򷵻ش���״̬
    if(i == G.vexnum)
    {
        printf("Ҫɾ���Ķ��㲻����.�޷�����\n");
        return ERROR;
    }
//��ɾ������֮��Ķ���λ��ȫ����ǰ�ƶ�һ��λ�ã����ǵ�Ҫɾ����λ��
    while (i<G.vexnum-1)
    {
        G.vertices[i] = G.vertices[i+1];
        i++;
    }
    G.vexnum--;
//���滹Ҫ��������������йصĻ���ɾ���������Լ������д���Ҫɾ��λ�õĶ���λ�ü�һ
    ArcNode * train = NULL;   //��¼����
    ArcNode * p = NULL;
    int k =0;
    while (k < G.vexnum)
    {
        train = G.vertices[k].firstarc;
        p = train;
        while (train != NULL)
        {
//�ҵ���Ҫɾ���Ķ����йصĻ�����ɾ��
            if(location == train->adjvex)
            {
                if(train == p)
                {
                    G.vertices[k].firstarc = train->nextarc;
                    train = train->nextarc;
                    free(p);
                    p = NULL;
                    continue;
                }
                p->nextarc = train->nextarc;
                p = train;
                train = p->nextarc;
                free(p);
                p=NULL;
                continue;

            }
            //�����д���Ҫɾ��λ�õĶ���λ�ü�һ
            if(train->adjvex > location)
            {
                train->adjvex--;
            }
            p = train;
            train = p->nextarc;

        }
        k++;
    }
//ɾ���ɹ������ز����ɹ�״̬
    return OK;
}

//���뻡������������InsertArc(G,v,w)����ʼ������ͼG���ڣ�v��w�Ǻ�G�ж���ؼ���������ͬ�ĸ���ֵ��
//�����������ͼG�����ӻ�<v,w>�����ͼG������ͼ������Ҫ����<w,v>��
status InsertArc(ALGraph &G,KeyType v,KeyType w)
//��ͼG�����ӻ�<v,w>���ɹ�����OK,���򷵻�ERROR
{
    if(G.vexnum == 0 )  //���ͼ������
    {
        printf("��ͼ�����ڻ�δ��ʼ��\n");
        return INFEASIBLE;
    }
    if(v == w)   //�����������ر�
    {
        printf("��������ر�\n");
        return ERROR;
    }
    int flagv =-1, flagw =-1;

    //�ҵ������ v �� w ���±�
    int i =0;
    while (i<G.vexnum)
    {
        if(G.vertices[i].data.key == v)
        {
            flagv =i;
        }
        if(G.vertices[i].data.key == w)
        {
            flagw =i;
        }
        i++;
    }

    //����Ҳ�������� v �� w
    if(flagv == -1 || flagw == -1)
    {
        printf("�Ҳ���Ҫ����Ķ���\n");
        return ERROR;
    }

    ArcNode *pv = NULL;
    ArcNode *pw = NULL;

    //��������Ƿ�Ϊ�ظ��ı�
    pv = G.vertices[flagv].firstarc;
    while (pv)
    {
        if(pv->adjvex == flagw)  //�ҵ����ظ��ı�
        {
            return ERROR;
        }
        pv = pv->nextarc;
    }

    //�ֱ𴴽��ṹ�� newv �� neww�������±�
    ArcNode *newv = (ArcNode *) malloc(sizeof(ArcNode));
    newv->adjvex = flagw; //�ڽӵ��±�Ϊ w
    newv->nextarc = NULL; //��һ����Ϊ��
    if(G.vertices[flagv].firstarc != NULL) //��� v �б�
    {
        newv->nextarc =G.vertices[flagv].firstarc; //�±�ָ�� v �ĵ�һ����
    }
    G.vertices[flagv].firstarc = newv; //����ͷָ�룬�� v �ĵ�һ����Ϊ�±�

    //������Ĳ�������
    ArcNode *neww = (ArcNode *) malloc(sizeof(ArcNode));
    neww->adjvex = flagv; //�ڽӵ��±�Ϊ v
    neww->nextarc = NULL; //��һ����Ϊ��
    if(G.vertices[flagw].firstarc != NULL) //��� w �б�
    {
        neww->nextarc =G.vertices[flagw].firstarc; //�±�ָ�� w �ĵ�һ����
    }
    G.vertices[flagw].firstarc = neww; //����ͷָ�룬�� w �ĵ�һ����Ϊ�±�

    G.arcnum++; //������ 1
    return OK; //����ɹ�
}

status DeleteArc(ALGraph &G,KeyType v,KeyType w)
//��ͼG��ɾ����<v,w>���ɹ�����OK,���򷵻�ERROR
{
    if(G.vexnum == 0 )  //ͼ������
    {
        printf("��ͼ�����ڻ�δ��ʼ��\n");
        return INFEASIBLE;
    }
    if(v == w)  //���v��w��ȣ�˵��ɾ���������ش���
    {
        printf("��������ǻ�\n");
        return ERROR;
    }
    int i = 0;
    int flagv = -1;     //������¼�±�
    int flagw = -1;
    int sign = 0;  //��������Ƿ��б�

    //���ұ�<v,w>��Ӧ�Ķ����±�
    while (i<G.vexnum)
    {
        if(G.vertices[i].data.key == v)
        {
            flagv = i ;
        }
        if(G.vertices[i].data.key == w)
        {
            flagw = i ;
        }
        i++;
    }

    if(flagv == -1 || flagw == -1)   //��<v,w>������
    {
        printf("�����������ߵĶ���\n");
        return ERROR;
    }

    //����v����ĳ���
    ArcNode * getv = NULL;
    ArcNode * getw = NULL;
    ArcNode * pre = NULL;

    //���ұ�<v,w>��Ӧ�ĳ��ߣ�Ȼ��ɾ��
    getv = G.vertices[flagv].firstarc;
    pre = G.vertices[flagv].firstarc;

    while (getv)
    {
        if(getv->adjvex == flagw)  //����ҵ���<v,w>
        {
            sign = 1;  //�б߱��Ϊ1

            if(getv == pre)  //������ǵ�һ������
            {
                G.vertices[flagv].firstarc = getv->nextarc;  //ֱ�ӽ��ñߵ���һ������Ϊ��һ������
                free(getv);  //�ͷŵ�ǰ��
                getv = NULL;
                pre = NULL;
                break;
            }
            else  //����߲��ǵ�һ������
            {
                pre->nextarc = getv->nextarc;  //���ñߴ�ǰһ�����ߵ�nextarc��ɾ�������Ϻ�һ����
                pre = getv;  //����ǰһ���ߵ�ָ�뵽��ǰ��
                free(getv);  //�ͷŵ�ǰ��
                getv = NULL;
                break;
            }
        }
        pre = getv;  //ǰָ�����Ϊ��ǰ��
        getv = pre->nextarc;  //��ǰ�߸���Ϊ��һ������
    }

    if(sign == 0)  //���û���ҵ��ߣ����ش���
    {
        printf("������������\n");
        return ERROR;
    }
    getw = G.vertices[flagw].firstarc;
    pre = G.vertices[flagw].firstarc;
    //���ͼ������ͼ������Ҫɾ����<w,v>
    while (getw)
        {
            if(getw->adjvex == flagv)  //����ҵ���<w,v>
            {
                if(getw == pre)  //������ǵ�һ������
                {
                    G.vertices[flagw].firstarc = getw->nextarc;  //ֱ�ӽ��ñߵ���һ������Ϊ��һ������
                    free(getw);  //�ͷŵ�ǰ��
                    getw = NULL;
                    break;
                }
                else  //����߲��ǵ�һ������
                {
                    pre->nextarc = getw->nextarc;  //���ñߴ�ǰһ�����ߵ�nextarc��ɾ�������Ϻ�һ����
                    pre = getw;  //����ǰһ���ߵ�ָ�뵽��ǰ��
                    free(getw);  //�ͷŵ�ǰ��
                    getw = NULL;
                    break;
                }
            }
            pre = getw;  //ǰָ�����Ϊ��ǰ��
            getw = pre->nextarc;  //��ǰ�߸���Ϊ��һ������
        }


    G.arcnum--;  //������1
    return OK;
}

//��11�������������������
//����������DFSTraverse(G,visit())��
//��ʼ������ͼG���ڣ�
//���������ͼG���������������������
//���ζ�ͼ�е�ÿһ������ʹ�ú���visit����һ�Σ�
//�ҽ�����һ�Σ�

//����һ��������飬���ڱ��ÿ�������Ƿ��Ѿ���������
int flag11[100];

//����һ�������������������������ͼG��visit�����͵�ǰ�����Ľڵ�
void dfs(ALGraph G , void (*visit)(VertexType),int nownode)
{
    //���ȷ��ʵ�ǰ�ڵ�
    visit(G.vertices[nownode].data);
    //����ǰ�ڵ���Ϊ�ѱ�����
    flag11[nownode] = 1;

    //������ǰ�ڵ�������ڽӽڵ�
    ArcNode * p = G.vertices[nownode].firstarc;
    while (p)
    {
        //����ڽӽڵ�û�б�����������ݹ������
        if(flag11[p->adjvex] == 0)
        {
            dfs(G,visit,p->adjvex);
        }
        p = p->nextarc;
    }
}

//����ͼ���������������������
status DFSTraverse(ALGraph G,void (*visit)(VertexType))
{
    //��ͼ��ÿ��������б�ǳ�ʼ��
    memset(flag11,0,sizeof(flag11));
    //���ͼ�����ڣ�����INFEASIBLE�������У�
    if(G.vexnum == 0 )
    {
        printf("��ͼ�����ڻ�δ��ʼ��\n");
        return INFEASIBLE;
    }
    int i ;
    //��ÿ��δ���������Ķ�����������������
    for( i=0;i<G.vexnum ;i++)
    {
        if(flag11[i] == 0)
        {
            dfs(G,visit,i);
        }
    }
    return OK;
}


//��12�����������������������������BFSTraverse(G,visit())����ʼ������ͼG���ڣ�
// ���������ͼG���й�������������������ζ�ͼ�е�ÿһ������ʹ�ú���visit����һ�Σ��ҽ�����һ�Ρ�
int flag12[100] ;
void BFS(ALGraph G,void  (*visit)(VertexType),int i)
{
    int head = 0,tail = 0;  //����ͷָ��head��βָ��tail
    int Que[100];  //һ������Que�����ڴ�Ŵ������Ķ��㡣
    Que[0] = i;
    while (head<=tail)
    {

        visit(G.vertices[Que[head]].data);
        ArcNode * p = G.vertices[Que[head]].firstarc;
        while (p)
        {
            if(flag12[p->adjvex] == 0)
            {

                tail++;
                Que[tail] = p->adjvex;
                flag12[p->adjvex]++;

            }
            p = p->nextarc;
        }
        head++;
    }
}

status BFSTraverse(ALGraph G,void (*visit)(VertexType))
//��ͼG���й�������������������ζ�ͼ�е�ÿһ������ʹ�ú���visit����һ�Σ��ҽ�����һ��
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    memset(flag12,0,sizeof (flag12));  //��flag12����ȫ����Ϊ0
    if(G.vexnum == 0 )  //ͼ������
    {
        printf("��ͼ�����ڻ�δ��ʼ��\n");
        return INFEASIBLE;
    }
    int i ;
    for( i =0;i< G.vexnum ;i++)
    {
        if(flag12[i] == 0)
        {  //�������ж��㣬����ö���δ�����ʣ�������Ϊ�ѷ��ʲ�����BFS����
            flag12[i]=1;
            BFS(G,visit,i);
        }
    }
    return OK;



    /********** End **********/
}

//visit ����

void visit(VertexType p)
{
    printf("%d %s",p.key,p.others);
}

int * VerticesSetLessThanK(ALGraph  G,int v,int k)  //�������壬����ָ�����ͣ������������ͼG����ʼ����v�;�������k
{
    k--;  //�����Ǵ���ʼ������ľ��룬���Ծ�������k��Ҫ��1
    if(G.vexnum == 0 )  //���ͼ�����ڣ�����NULL
    {
        printf("��ͼ�����ڻ�δ��ʼ��\n");
        return NULL;
    }
    int record[100] = {0};  //��¼���ʹ��Ľ�㣬��ʼ��Ϊ0����ʾδ���ʹ���
    int i = 0;
    int flag = -1;  //flag������ʼ��Ϊ-1����ʾû�ҵ���ʼ��㣩

    //����ͼ�Ķ��㣬�ҵ���ʼ���v����¼��λ�õ�flag������
    for( ; i < G.vexnum ; i++)
    {
        if(G.vertices[i].data.key == v)
        {
            flag = i;
            break;
        }
    }
    record[flag] = 1;  //�����ʼ���v�Ѿ������ʹ�

    if(flag == -1)  //���δ�ҵ���ʼ�㣬����NULL
    {
        printf("�Ҳ������\n");
        return NULL;
    }
    static int srr[100];  //��̬�������ڴ洢����С��k�Ķ��㼯��
    int num = 0;  //num�������ڼ�¼�Ѿ��洢�˶��ٸ�����
    srr[num++] = flag;  //����ʼ��v���뵽���㼯����
    //������в���
    int Que[100][2];  //��ά�����ʾ���У����ڴ洢�����ʵĽ�㼰�����
    memset(Que,0,sizeof (Que));  //��ʼ������Ϊ0����ʾδ�����ʹ���
    int head = 0, tail = 0;  //���е�ͷ��βָ��
    Que[head][0] = flag;  //��ʼ���v��Ϊ���еĵ�һ��Ԫ��
    Que[head][1] = 0;  //��ʼ���v�ľ���Ϊ0

    //���зǿ��Ҷ����е�һ�������벻����k������£����ж��еı���
    while (head <= tail && Que[head][1] != (k+1))
    {

        ArcNode * p = G.vertices[Que[head][0]].firstarc;  //��ȡ��ͷԪ�ص��ڽ�����
        while (p)
        {
            if(record[p->adjvex] == 0)  //����ڽӽ��δ�����ʹ�
            {
                if(Que[head][1] <= (k-1))
                {
                    srr[num++] = p->adjvex;  //���ڽӽ����뵽���㼯����
                }

                tail++;  //����βָ���1
                Que[tail][0] = p->adjvex;  //���ڽӽ����뵽������
                Que[tail][1] = Que[head][1] + 1;  //�����ڽӽ�����
                record[p->adjvex]++;  //����ڽӽ���Ѿ������ʹ�
            }
            p = p->nextarc;  //������һ���ڽӽ��
        }
        head++;  //�������ͷ��㣬��ͷָ���1
    }
    srr[num] = -1;  //��������-1��β���Ա��ں����ⲿ���ʵ����鳤��

    return srr;  //���ش洢���㼯�ϵ�����ָ��
}

int ShortestPathLength(ALGraph G, int v, int w)
{
    if (G.vexnum == 0) //ͼ������
    {
        printf("��ͼ�����ڻ�δ��ʼ��\n");
        return INFEASIBLE;
    }
    int head = 0, tail = 0; // �������ͷ��β
    int record[100] = {0}; // ��¼ÿ���ڵ��Ƿ񱻷��ʹ�
    int arr[100][2]; // ����洢�ڵ�;���Ķ���
    memset(arr, 0, sizeof(arr)); // ��ʼ������
    int i = 0;
    int flag = -1; // ��¼v�ڵ������ֵ
    int flagw = -1; // ��¼w�ڵ������ֵ
    for (; i < G.vexnum; i++) // �������нڵ�
    {
        if (G.vertices[i].data.key == v) // �ҵ�v�ڵ�
        {
            flag = i;
        }
        if (G.vertices[i].data.key == w) // �ҵ�w�ڵ�
        {
            flagw = i;
        }
    }
    if (flag == -1 || flagw == -1) // ���v��w�ڵ㲻����
    {
        printf("û���ҵ�v��Ӧ�Ľ��\n");
        return INFEASIBLE;
    }
    arr[head][0] = flag; // �׸��ڵ�Ϊv�ڵ�
    while (head <= tail) // �����зǿ�ʱѭ��
    {
        ArcNode *p = G.vertices[arr[head][0]].firstarc; // �ҵ���ǰ�ڵ�ĵ�һ����

        if (G.vertices[arr[head][0]].data.key == w) // ����ҵ�w�ڵ�
        {
            return arr[head][1]; // ���ؾ���
        }
        while (p) // ������ǰ�ڵ�����б�
        {
            if (record[p->adjvex] == 0) // ����ýڵ�δ�����ʹ�
            {
                tail++; // ����β������ýڵ�
                arr[tail][0] = p->adjvex; // �洢�ڵ�
                arr[tail][1] = arr[head][1] + 1; // �洢����
                record[arr[head][0]]++; // ��Ǹýڵ��ѱ�����
            }
            p = p->nextarc; // ������һ����
        }
        head++; // ������һ���ڵ�
    }
    return -1; // ���û���ҵ�·��������-1
}

// ����һ��ȫ������flag16���ڱ�Ƕ����Ƿ񱻷��ʹ�
int flag16[100] = {0};

// �������������������dfs������GΪͼ��nownodeΪ��ǰ�ڵ�
void dfs(ALGraph G, int nownode) {
    // ����ǰ�ڵ���Ϊ�ѷ���
    flag16[nownode] = 1;

    // ������ǰ�ڵ���ڽӽڵ�
    ArcNode *p = G.vertices[nownode].firstarc;
    while (p) {
        // �����ǰ�ڽӽڵ�δ�����ʣ���ݹ����dfs����
        if (flag16[p->adjvex] == 0) {
            dfs(G, p->adjvex);
        }
        // ����������һ���ڽӽڵ�
        p = p->nextarc;
    }
}

// ������ͨ������������ConnectedComponentsNums������GΪͼ
int ConnectedComponentsNums(ALGraph G) {
    // ÿ��ʹ��֮ǰҪ��flag16�������
    memset(flag16, 0, sizeof(flag16));

    int i;
    // ��ͼΪ�ջ�δ��ʼ��ʱ������0
    if (G.vexnum == 0) {
        printf("Ϊ��ʼ������Ϊ��\n");
        return 0;
    }

    int count = 0;
    // �������ж���
    for (i = 0; i < G.vexnum; i++) {
        // �����ǰ����δ�����ʣ���ݹ����dfs����������������count��1
        if (flag16[i] == 0) {
            count++;
            dfs(G, i);
        }
    }

    // ������ͨ�����ļ�����count
    return count;
}

status SaveGraph(ALGraph G, char FileName[])  //����ͼ�����ݵ��ļ�
{
    if(G.vexnum ==0 )  //���ͼ�ǿյģ�ֱ�ӷ��ش���
    {

        printf("ͼ�ǿյ�\n");

        return -1;

    }
    FILE * fp = fopen(FileName,"w");  //���ļ���ֻ��д��
    if(fp == NULL)
    {
        return ERROR;  //����޷����ļ������ش���
    }

    //��д�� ����� �� ����
    fprintf(fp,"%d %d\n",G.vexnum,G.arcnum);  //д�붥�����ͱ���
    // ��д�붥��
    for(int k = 0;k<G.vexnum;k++)   //����ÿһ������
    {
        fprintf(fp,"%d %s\n",G.vertices[k].data.key,G.vertices[k].data.others);  //д�붥���key��others
    }
    //��������ÿ������Ӧ�ı�

    for(int i = 0;i< G.vexnum ;i++)  //����ÿһ�����
    {
        ArcNode * p = G.vertices[i].firstarc;  //�Ӷ���ĵ�һ���߿�ʼ����
        while (p)
        {
            fprintf(fp,"%d ",p->adjvex);  //д��ߵ��ڽӵ���
            p = p->nextarc;  //������һ����
        }
        fprintf(fp,"-1\n");  //һ���߽�����д��-1
    }
    fclose(fp);  //�ر��ļ�
    return OK;  //���سɹ�
}

status LoadGraph(ALGraph &G, char FileName[])  //���ļ��ж�ȡͼ������
{
    if(G.vexnum !=0)  //���ͼ��Ϊ�գ����޷���ȡ
    {
        printf("���ͼ���ǿյģ��޷���ȡ\n");
    }
    FILE *fp = fopen(FileName,"r");  //���ļ���ֻ�ɶ�ȡ
    if(fp == NULL)
    {
        return ERROR;  //����޷����ļ������ش���
    }
    fscanf(fp,"%d %d\n",&G.vexnum,&G.arcnum);  //��ȡ�������ͱ���
    for(int i = 0;i<G.vexnum ;i++)  //����ÿһ������
    {
        fscanf(fp,"%d %s\n",&G.vertices[i].data.key,G.vertices[i].data.others);  //��ȡ�����key��others
        G.vertices[i].firstarc = NULL;  //����ĵ�һ����ΪNULL
    }
    for(int k = 0;k<G.vexnum ;k++)  //����ÿһ�����
    {
        ArcNode *p = G.vertices[k].firstarc;  //�Ӷ���ĵ�һ���߿�ʼ����
        ArcNode * newnode = (ArcNode * ) malloc(sizeof(ArcNode));  //�½�һ�����
        fscanf(fp,"%d ",&newnode->adjvex);  //��ȡ�½����ڽӵ���
        newnode->nextarc = NULL;  //���½�����һ������ΪNULL
        while (newnode->adjvex != -1)  //�����ȡ���ڽӵ��Ų���-1
        {
            if(G.vertices[k].firstarc == NULL)  //�����ǰ����ĵ�һ����ΪNULL
            {
                G.vertices[k].firstarc = newnode;  //���½����Ϊ�ö���ĵ�һ����
                p = G.vertices[k].firstarc;  //��pָ��ö���ĵ�һ����
            }
            else{
                p->nextarc = newnode;  //���½��ӵ�pָ��ıߵĺ���
                p = newnode;  //��pָ���½��
            }
            newnode = (ArcNode * ) malloc(sizeof(ArcNode));   //�½�һ�����
            fscanf(fp,"%d ",&newnode->adjvex);  //��ȡ�½����ڽӵ���
            newnode->nextarc = NULL;  //���½�����һ������ΪNULL
        }

    }
    fclose(fp);  //�ر��ļ�
    return OK;  //���سɹ�
}

void menu()
{
    for(int k = 0; k<=  119 ;k++)
    {
        putchar('-');
    }  putchar('\n');
    printf("1.����һ��ͼ\n");
    printf("2.ɾ��һ��ͼ\n");
    printf("3.��ѯ�Ѿ�������ͼ\n");
    printf("4.����һ��ͼ�ͽ��в���\n");
    printf("0.�˳����ͼ�Ĺ���\n");

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

void menu2()
{
    for(int k = 0; k<=  119 ;k++)
    {
        putchar('-');
    }
    putchar('\n');
    printf("           Menu for Graph On Sequence Structure \n");
//	printf("-------------------------------------------------\n");
    printf("    	  1. ������ʼ��ͼ                    7. ���붥��\n");
    printf("    	  2. ����ͼ                          8. ɾ������\n");
    printf("    	  3. ���Ҷ���                        9. ���뻡 \n");
    printf("    	  4. ���㸳ֵ                        10. ɾ����\n");
    printf("    	  5. ��ȡ��һ�ڽӵ�                  11. �����������\n");
    printf("    	  6. ��ȡ��һ�ڽӵ�                  12. �����������\n");
    printf("         13.�鿴ͼ��ϵ\n");
    for(int k = 0; k<=  119 ;k++)
    {
        putchar('-');
    }  putchar('\n');
    printf("    	  14.����С��k�Ķ��㼯��                15.��������·��\n");
    printf("    	  16.ͼ����ͨ����                      17.���浽�ļ�\n");
    printf("    	  18.���ļ��������                      \n");
    printf("    	  0.exit                        \n");
    for(int k = 0; k<=  119 ;k++)
    {
        putchar('-');
    }  putchar('\n');
    //printf("һЩ���ӵĹ���");

    printf("    ��ѡ����Ĳ���[0~13]:");
    putchar('\n');
    for(int k = 0; k<=  119 ;k++)
    {
        putchar('-');
    }
    putchar('\n');

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

void fun01()        //���������������Ա�Ĺ���
{
    menu(); //���ò˵�����
    int a ; //�������ͱ���a
    printf("������һ������\n");
    scanf("%d",&a); //�������������a��
    while (a) //���a��ֵ��Ϊ0����ѭ��ִ�д����
    {
        fflush(stdin); //�������������ֹ��һ�β���������Ӱ�챾�β���
        int feedback; //�������ͱ���feedback
        switch (a) { //���ݲ�ͬ������в�ͬ�Ĳ���
            case 1: //�������Ϊ1
                printf("���ڽ��д���һ���µ�ͼ\n");
                printf("���������봴����ͼ������\n");
                char name1[30]; //�����ַ�������name1������Ϊ30
                scanf("%s",name1); //����ͼ�����֣�������name1��
                int i ,flag ; flag = 0; //�������ͱ���i��flag��flag ��ʼ��Ϊ0
                //Ҫ�������ֵ��ж�
                for( i =0;i<graphs.length;i++) //���������Ѿ����ڵ�ͼ
                {
                    if(strcmp(name1,graphs.elem[i].name)  == 0) //��������Ѿ���ʹ�ã�����ʾ����ʧ��
                    {
                        printf("��ͼ�Ѿ����ڣ�����ʧ��\n");
                        flag = 1; //��flag��ֵ��Ϊ1����ʾ����ʧ��
                    }
                }
                if(flag == 0) //���flag��ֵΪ0����ʾû����ͬ�����֣��򴴽���ͼ����������
                {
                    strcpy(graphs.elem[graphs.length].name,name1); //ʹ��strcpy������name1�е��ַ������Ƶ�graphs.elem[graphs.length].name��
                    graphs.length++; //���Ѿ����ڵ�ͼ��������1
                    printf("�����ɹ���\n");
                }
                break;
            case 2: //�������Ϊ2
                int flag2 ; //�������ͱ���flag2
                printf("���ڽ���ɾ��ͼ�Ĳ���\n");
                printf("����������ɾ����ͼ������\n");
                char name2[30]; //�����ַ�������name2������Ϊ30
                scanf("%s",name2); //����Ҫɾ����ͼ�����֣�������name2��

                flag2 = -1; //flag2 ��ʼ��Ϊ-1

                //Ҫ�������ֵ��ж�
                for( i =0;i<graphs.length;i++) //���������Ѿ����ڵ�ͼ
                {
                    if(strcmp(name2,graphs.elem[i].name)  == 0) //����ҵ���Ҫɾ����ͼ�����֣���flag2����Ϊ��ͼ���Ѵ���ͼ�����е��±�
                    {
                        flag2 = i;
                    }
                }

                if(flag2 == -1) //���flag2��ֵ����-1����ʾû���ҵ�Ҫɾ����ͼ�����֣����޷�ɾ��
                {
                    printf("��ͼ�����ڣ��޷�ɾ��\n");
                }
                else{ //����ҵ���Ҫɾ����ͼ������
                    if(1)
                    {
                        int k;
                        for( k = flag2 ;k < graphs.length-1 ;k++) //����ͼ���Ѵ���ͼ�����е��±�֮�������ͼ��ǰ�ƶ�һ��λ��
                        {
                            graphs.elem[k] = graphs.elem[k+1];
                        }
                        graphs.length--; //�Ѵ���ͼ��������1
                        printf("ɾ���ɹ�\n");
                    }
                }
                break;
            case 3: //�������Ϊ3
                printf("���ڽ��в�ѯ��������Щͼ\n");
                printf("���е�ͼ����:\n");
                for(i = 0; i<graphs.length ;i++) //�����Ѵ��ڵ�ͼ�����飬����˳�����ÿ��ͼ������
                {
                    printf("%d)   %s\n",i+1,graphs.elem[i].name);
                }
                break;
            case 4: //�������Ϊ4
                printf("���ڽ���ͼ�Ĳ��ҺͲ���\n");
                printf("������������ҺͲ�����ͼ������\n");
                char name3[30]; //�����ַ�������name3������Ϊ30
                scanf("%s",name3); //����Ҫ���ҺͲ�����ͼ�����֣�������name3��

                int flag3 ;flag3 = -1; //�������ͱ���flag3����ʼ��Ϊ-1
                for( i =0 ; i<graphs.length ;i++) //�����Ѵ��ڵ�ͼ������
                {
                    if(strcmp(graphs.elem[i].name,name3) == 0) //����ҵ���Ҫ���ҺͲ�����ͼ�����֣���flag3����Ϊ��ͼ���Ѵ���ͼ�����е��±�
                    {
                        flag3 = i;
                    }
                }

                if(flag3 ==-1) //���flag3����-1����ʾû���ҵ�Ҫ���ҺͲ�����ͼ�����֣�����ʾ���������ͼ
                {
                    printf("���������ͼ\n");
                    system("pause"); //��ͣ�����ִ�У��ȴ��û����������
                }
                else { //����ҵ���Ҫ���ҺͲ�����ͼ������
                    fun02(graphs.elem[flag3].G); //����fun02�����Ը�ͼ���в���
                }
                break;

            default: //��������޷�ʶ������ʾ������󣬲�������ʾ�˵�
                printf("���������������ٴ�����");
        }
        printf("��������һ������\n");
        scanf("%d",&a); //��ʾ������һ�����������a��
        system("cls"); //��տ���̨�������׼����ʾ�˵�
        menu(); //�ٴ���ʾ�˵�
    }
}


void fun02(ALGraph &G)
{
    system("cls");     //�����Ļ 
    printf("ͼ����ѼѼ\n");      
    printf("���ڶ����ͼ���в���\n");
    printf("�����ǳ�ʼ�����ͼѼ\n");
    int order;   //���������� 
    menu2();    //չʾ�˵� 
    scanf("%d",&order);
    while (order)
    {
        fflush(stdin); //���������������Ƿ�ֹ��һ�β������������������ݶ�Ӱ�챾�β���
        int feedback;
        switch (order) {
            int feedback;
            case 1:
                printf("�����붥�����к͹�ϵ������:\n");

                VertexType V[30];   //װ���㼯�� 
                KeyType VR[100][2];  //װ�߼��� 
                int i,j; i =0;  //�������� 
                do {
                    scanf("%d%s",&V[i].key,V[i].others);
                } while(V[i++].key!=-1);
                i=0;
                do {
                    scanf("%d%d",&VR[i][0],&VR[i][1]);
                } while(VR[i++][0]!=-1);
                feedback = CreateCraph(graphs.elem[graphs.length-1].G,V,VR);
                if(feedback == OK)
                {
                    printf("ͼ��ʼ���ɹ�\n");
                }
                else{
                    printf("��ʼ��ʧ��\n");
                }
                break;
            case 2:
                printf("���ڽ���ͼ�����ٲ���\n");
                feedback = DestroyGraph(G);
                if(feedback == OK)
                {
                    printf("ͼ���ٳɹ���\n");
                }
                else{
                    printf("���Ա�δ��ʼ�����߲�����\n");
                }
                break;
            case 3:
                printf("���ڽ��в��Ҷ���Ĳ���\n");
                printf("������������ҵĶ���Ĺؼ���\n");
                int key ;     //���洢�ؼ��� 
                scanf("%d",&key);
                feedback = LocateVex(G,key);
                if(feedback != -1)
                {
                    printf("��Ҫ���ҵĹؼ���Ϊ  %d  �Ķ����λ�����Ϊ %d \n",key,feedback);
                    printf("������ϢΪ%d  %s\n",G.vertices[feedback].data.key,G.vertices[feedback].data.others);
                } else{
                    printf("��Ҫ���ҵĶ��㲻����\n");
                }
                break;
            case 4:
                printf("���ڽ��ж��㸳ֵ�Ĳ���\n");
                printf("�������������һ���ؼ��ֽ��в���\n");
                int key4;      //�洢�ؼ��� 
                scanf("%d",&key4);
                printf("����������ı�Ĺؼ��ֺ�����\n");
                VertexType value;
                scanf("%d %s",&value.key,value.others);
                feedback = PutVex(G,key4,value);
                if(feedback == OK)
                {
                    printf("�����ɹ�\n");
                }
                break;
            case 5:
                printf("���ڽ��л�ȡ��һ�ڽӵ�Ĳ���\n");
                printf("������������Ĺؼ���\n");
                int key5;     //�洢�ؼ��� 
                scanf("%d",&key5);
                feedback =  FirstAdjVex(G,key5);
                if(feedback != -1)
                {
                    printf("��ȡ�ɹ�,��һ�ڽӵ��λ����%d,������ϢΪ%d  %s",feedback,G.vertices[feedback].data.key,G.vertices[feedback].data.others);
                } else{
                    printf("����ʧ��\n");
                }
                break;
            case 6:
                printf("���ڽ��л�ȡ��һ�ڽӵ�Ĳ���\n");
                printf("������G�����������λ��v��ӦG��һ������,w��Ӧv���ڽӶ���\n");
                int v,w;   //���洢�����ֵ 
                scanf("%d %d",&v,&w);
                feedback = NextAdjVex(G,v,w);
                if(feedback != -1)
                {
                    printf("��ȡ�ɹ�,��һ�ڽӵ��λ����%d,������ϢΪ%d  %s",feedback,G.vertices[feedback].data.key,G.vertices[feedback].data.others);
                } else{
                    printf("����ʧ��\n");
                }
                break;
            case 7:
                printf("���ڽ��в��붥��Ĳ���\n");
                printf("�����������Ķ���Ĺؼ��ֺ�����\n");
                VertexType v7;  //�洢����Ķ�����Ϣ
                scanf("%d %s",&v7.key,v7.others);
                feedback = InsertVex(G,v7);
                if(feedback == OK)
                {
                    printf("����ɹ�\n");
                } else{
                    printf("����ʧ��\n");
                }
                break;
            case 8:
                printf("���ڽ���ɾ������Ĳ���\n");
                printf("����������ɾ���Ķ���Ĺؼ���\n");
                int key8;     //�洢�ؼ���
                scanf("%d",&key8);
                feedback = DeleteVex(G,key8);
                if(feedback == OK)
                {
                    printf("�����ɹ�\n");
                }
                else{
                    printf("����ʧ��\n");
                }
                break;
            case 9:
                printf("���ڽ��в��뻡�Ĳ���\n");
                int v9,w9;      //�洢�ߵ���������
                printf("�����������Ļ�\n");
                scanf("%d %d",&v9,&w9);
                feedback = InsertArc(G,v9,w9);
                if(feedback == OK)
                {
                    printf("�����ɹ�\n");
                }
                else{
                    printf("����ʧ��\n");
                }
                break;
            case 10:
                printf("���ڽ���ɾ�����Ĳ���\n");
                int v10,w10;      //�洢Ҫɾ���ıߵ���������
                printf("��������ɾ���Ļ�\n");
                scanf("%d %d",&v10,&w10);
                feedback = DeleteArc(G,v10,w10);
                if(feedback == OK)
                {
                    printf("�����ɹ�\n");
                } else{
                    printf("����ʧ��\n");
                }
                break;
            case 11:
                printf("���ڽ��������������\n");
                feedback = DFSTraverse(G,visit);
                if(feedback == OK)
                {
                    printf("�����ɹ�\n");
                }
                else{
                    printf("����ʧ��\n");
                }
                break;
            case 12:
                printf("���ڽ��й����������\n");
                feedback = BFSTraverse(G,visit);
                if(feedback == OK)
                {
                    printf("�����ɹ�\n");

                } else{
                    printf("����ʧ��\n");

                }
                break;
            case 13:
                int u ;  //��������
                for(u = 0;u< G.vexnum ;u++)
                {
                    printf("%d %s  ",G.vertices[u].data.key,G.vertices[u].data.others);
                    ArcNode * p = G.vertices[u].firstarc;
                    while (p){
                        printf(" %d ",p->adjvex);
                        p = p->nextarc;
                    }
                    putchar('\n');
                }
                break;
            case 14:
                printf("���ڽ��в���С��k�Ķ��㼯�ϵĲ���\n");
                printf("���붥��Ĺؼ���\n");
                int key14;  //�洢�ؼ���
                scanf("%d",&key14);
                printf("�������k\n");
                int k;
                scanf("%d",&k);
                int * p;
                p = VerticesSetLessThanK(G,key14,k);

                if(p == NULL)
                {
                    printf("����ʧ��\n");
                }
                else{
                    printf("����С��%d �Ķ���ļ����ǣ�\n",k);
                    while ((*p) != -1)
                    {
                        printf("%d %s\n",G.vertices[*p].data.key,G.vertices[*p].data.others);

                        p++;
                    }
                    printf("�����ɹ�\n");
                }
                break;
            case 15:
                printf("���ڽ��ж��������·�̵Ĳ���\n");
                printf("�����붥��v�Ͷ���w�Ĺؼ���\n");
                int v15,w15;      //�洢�����ؼ���
                scanf("%d %d",&v15,&w15);
                feedback = ShortestPathLength(G,v15,w15);
                if(feedback != -1)
                {
                    printf("���·��Ϊ %d \n",feedback);

                } else{
                    printf("����ʧ��\n");
                }
                break;
            case 16:
                printf("���ڽ���ͼ����ͨ�����ļ���\n");
                feedback = ConnectedComponentsNums(G);
                if(feedback != 0)
                {
                    printf("ͼ����ͨ������%d\n",feedback);

                }

                break;
            case 17:
                printf("���ڽ����ļ��ı������\n");
                printf("���������뱣�浽��һ���ļ�\n");
                char name17[30];   //�洢Ҫ������ļ���
                scanf("%s",name17);
                feedback= SaveGraph(G,name17);
                if(feedback == OK)
                {
                    printf("����ɹ�\n");
                }
                break;
            case 18:
                printf("���ڽ����ļ��Ķ�ȡ����\n");
                printf("�����ȡ��һ���ļ�������\n");
                char name18[30];  //�洢Ҫ��ȡ���ļ���
                scanf("%s",name18);
                feedback = LoadGraph(G,name18);
                if(feedback == OK)
                {
                    printf("��ȡ�ɹ�\n");
                }
                break;
            default:
                printf("��������������\n");



        }
        putchar('\n');
        printf("��������һ������\n");
        scanf("%d",&order);
        system("cls");
        if(order != 0)
        {
            menu2();
        }
        else{
            menu();
        }

    }
}

