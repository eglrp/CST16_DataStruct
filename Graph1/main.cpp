#include<iostream>
#include<cstdio>
#include<malloc.h>
#include<string.h>

using namespace std;

#define INFINITY  10000// ���������ֵ�����
#define MAX_VERTEX_NUM 20 // ��󶥵����
#define OK 1
#define ERROR 0
#define FALSE 0
#define TRUE 1
#define MAXQSIZE100 
typedef int QElemType;
typedef float VRType;
typedef float InfoType;
typedef char  VertexType;
typedef char VexType;

//============�ڽӾ���Ķ���============ 
typedef struct {
	VRType   adj; 
	InfoType info;   // �û������Ϣ��ָ��(����) 
}ArcCell,AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct {
	VertexType vexs[MAX_VERTEX_NUM][100]; // ��������
	AdjMatrix arcs; // �ڽӾ���
	int vexnum,arcnum; // ͼ�ĵ�ǰ�������ͻ���
} MGraph ;
//=======================�ڽӾ���Ķ���========

//=================================�ڽӱ��Ķ���=========
typedef struct ArcNode{      // �����
	int  adjvex;              // �û���ָ��Ķ����λ��
	struct ArcNode *nextarc;   // ָ����һ������ָ��
	float info;                // ����Ȩֵָ��
} ArcNode;    
typedef struct{                   // ͷ���
	VertexType data[100];     // ������Ϣ
	ArcNode *firstarc;        // ��һ�������ĵ�ַ 
} VNode, AdjList[MAX_VERTEX_NUM];   
typedef struct {
	AdjList  vertices;
	int vexnum,arcnum;   // ͼ�ĵ�ǰ�������ͻ���
}ALGraph;
int  visited[MAX_VERTEX_NUM];
//=================�ڽӱ��Ķ���=========================


//=========���ж���ͻ�������===============
typedef struct QNODE{
	QElemType  data;
	struct QNODE *next;
}QNode, *QueuePtr;
typedef struct { //�����еĶ���
	QElemType *base; 
	int  front;  
	int  rear; 
} SqQueue;
typedef struct{  
	QueuePtr  front;
	QueuePtr  rear;
}LinkQueue;

LinkQueue InitQueue(LinkQueue Q){
	
	Q.front=Q.rear=(QueuePtr)malloc(sizeof(QNode));
	if(!Q.front)
		exit(1);	
	Q.front->next=NULL;
	return Q;
}

int EnQueue(LinkQueue* Q, QElemType e){
	QueuePtr p;
	if( !(p=(QueuePtr)malloc(sizeof(QNode))) )     
		return ERROR;
	p->data = e;
	p->next = NULL;
	Q->rear->next = p;
	Q->rear = p;
	return OK;
}

int DeQueue(LinkQueue *Q, QElemType *e) { 
	QueuePtr  p;  
	if( Q->front == Q->rear )
		return ERROR;
	p = Q->front->next;
	*e = p->data;
	Q->front->next = p->next;
	if(Q->rear == p)  Q->rear = Q->front;
	free(p);
	return OK;
}

int QueueEmpty(LinkQueue *Q) {
	if(Q->front ==Q->rear)  return 1;
	else  return 0;
}

int DestroyQueue( LinkQueue *Q ){
	while(Q->front) {
		Q->rear=Q->front->next;
		free(Q->front);
		Q->front=Q->rear;
	}
	return OK;
}

//===================���ж���ͻ�������===============

int LocateVex(MGraph G,char *vert)
{  int  i;

for(i=0; i<G.vexnum; i++)
	if(strcmp(G.vexs[i],vert)==0)
	return i;
return -1;
}

int LocateVex1(ALGraph G,char *vert)
{     int  i;
for(i=0; i<G.vexnum; i++)
	if(strcmp(G.vertices[i].data,vert)==0)
	return i;
return -1;
}

//����������G���ڽӾ���
MGraph  CreateGraph_UDN( MGraph G ){
	int  i, j,k;
	float  w;
	VexType v1[100], v2[100];
	printf("���붥����,��������");
	scanf("%d %d", &G.vexnum, &G.arcnum);
	for(i=0; i<G.vexnum; i++)	  // �������еĶ��� 
	{   printf("�����%d���������Ϣ��",i+1);
	scanf("%s", &G.vexs[i]);	
	}
	for(i=0; i <G.vexnum; i++)	  //��ʼ���ڽӾ��� 
		for(j=0; j<G.vexnum; j++)  
		G.arcs[i][j].adj=INFINITY;
		for(k=0; k<G.arcnum; k++) { 	  // �������еı� 
			printf("�����%d������������������ͱ��ϵ�Ȩֵ:",k+1);
			scanf("%s %s %f", &v1, &v2, &w);	
			// ��ѯ����������ͼ�д洢��λ�� 
			i = LocateVex(G, v1);	
			j = LocateVex(G, v2);
			if (i==-1 || j==-1)
			{printf("����ı߲���ȷ\n"); exit(0);}
			G.arcs[i][j].adj = w;
			G.arcs[j][i].adj = G.arcs[i][j].adj;	
		}
		return G;
}
//����������G���ڽӱ�
ALGraph CreateALGraph_UDN(ALGraph G )
{        
	int i,j,k;
	float w;
	ArcNode * p;
	VexType v1[100], v2[100];
	printf("���붥����,��������");
	scanf("%d %d",&(G.vexnum),&(G.arcnum));  /* ���붥�����ͱ��� */
	for(i=0;i<G.vexnum;i++)  /* ������n������Ķ���� */
	{   
		printf("�����%d���������Ϣ��",i+1);
		scanf("%s",&(G.vertices[i].data)) ;    /* ���붥����Ϣ */
		G.vertices[i].firstarc=NULL;  /* ����ı߱�ͷָ����Ϊ�� */
	}
	for(k=0;k<G.arcnum;k++ ) /* �����߱� */
	{   
		printf("����һ������������������ͱ��ϵ�Ȩֵ:");
		scanf("%s %s %f",&v1,&v2,&w) ;  /* �����<Vi��Vj>�Ķ����Ӧ��� */
		i = LocateVex1(G, v1);	
		j = LocateVex1(G, v2);
		if (i==-1 || j==-1)
		{printf("����ı߲���ȷ\n"); exit(0);}
		p=(ArcNode*)malloc(sizeof(ArcNode) );  /* �����±߱����p */
		p->adjvex=j;                                /* �ڽӵ����Ϊj */
		p->info =w;
		p->nextarc=G.vertices[i].firstarc;  /* ���±߱����p���뵽����Vi������ͷ�� */
		G.vertices[i].firstarc=p;
		p=(ArcNode*)malloc(sizeof(ArcNode) );  /* �����±߱����p */
		p->adjvex=i;                                /* �ڽӵ����Ϊi */
		p->info =w;
		p->nextarc=G.vertices[j].firstarc;  /* ���±߱����p���뵽����Vj������ͷ�� */
		G.vertices[j].firstarc=p;
	} 
	return G; 
}  /*CreateALGraph*/ 

VisitFunc(char *ch)//����������Ϣ
{
	printf("%s ",ch);
}

void DFS(ALGraph G, int v ) {
	int  j;
	ArcNode *p;
	VisitFunc(G.vertices[v].data);    // ���ʵ�v������
	visited[v]=TRUE;           // ���÷��ʱ�־ΪTRUE(�ѷ���)
	for(p=G.vertices[v].firstarc; p;p=p->nextarc)
	{
		j=p->adjvex;
		if( !visited[j] ) DFS(G, j); 
	}
}

void DFSTraverse( ALGraph G){//ͼ��������ȱ����㷨
	int v;
	for(v=0; v<G.vexnum; v++)
		visited[v]=FALSE;      // ���ʱ�־�����ʼ��(δ������)
	for(v=0;v<G.vexnum;v++)
		if(!visited[v])
		DFS(G,v);               // ����δ���ʵĶ������DFS
}

void BFSTraverse(ALGraph G) //ͼ�Ĺ�����ȱ����㷨
{ 
	int v,j,u ;
	ArcNode *p;
	LinkQueue Q; 
	Q=InitQueue(Q);  // �ÿյĸ�������Q
	for(v=0; v<G.vexnum; v++)
		visited[v]=FALSE; // �ó�ֵ
	for(v=0; v<G.vexnum; v++)
		if(!visited[v]){
		visited[v]=TRUE;  // ���÷��ʱ�־ΪTRUE(�ѷ���)
		VisitFunc(G.vertices[v].data);
		EnQueue( &Q, v );        // v�����
		while(!QueueEmpty(&Q)){
			DeQueue(&Q,&u);     // ��ͷԪ�س��Ӳ���Ϊu 
			for(p=G.vertices[u].firstarc; p;p=p->nextarc)
			{
				j=p->adjvex;
				if( !visited[j] ) 
				{visited[j]=TRUE;
				VisitFunc(G.vertices[j].data);
				EnQueue(&Q, j);
				}
			}           
		}
	}
		DestroyQueue( &Q );
		
}
//ʵ�ֽ������������ڽӾ�����ڽӱ��ĺ���
MGraph  CreateGraph_DN( MGraph G ){//����������G���ڽӾ���
	
		return G;
}

//����������G���ڽӱ�
ALGraph CreateALGraph_DN(ALGraph G ){  

	return G;
}

Print_MGraph(MGraph G)//���ͼ���ڽӾ����ʾ
{
	int i,j;
	for(i=0;i<G.vexnum;i++)	{ 
		for(j=0;j<G.vexnum;j++)
			printf("%f ",G.arcs[i][j].adj );  /*�ڽӾ���*/
		printf("\n");
	}     
}

Print_ALGraph(ALGraph G) //���ͼ���ڽӱ���ʾ
{
	int i,j;
	ArcNode *p;
	for(i=0;i<G.vexnum;i++)  
	{   
		printf("%s",G.vertices[i].data );    /* ������Ϣ */
		p=G.vertices[i].firstarc ;
		while(p!=NULL)                       /* ���ڵ���Ϣ */
		{
			printf("->%s",G.vertices[p->adjvex ].data);
			p=p->nextarc ;
		}                	   /* ����ı߱�ͷָ����Ϊ�� */
		printf("\n");  
	}
}

void FindInDegree(ALGraph G, int *indegree)
{
	int i,k;ArcNode *p;    	 
	for (i=0; i<G.vexnum; ++i)
	{
		for (p=G.vertices[i].firstarc;  p;  p=p->nextarc) {
			{k = p->adjvex;indegree[k]++;  }              
		}
	}
}

//===================��������==============================
int TopologicalSort(ALGraph G) {  
	// ����ͼG�����ڽӱ��洢�ṹ��
	// ��G�޻�·�������G�Ķ����һ���������в�����OK������ERROR��
	int SqStack[MAX_VERTEX_NUM],top=0;
	int count,k,i;
	ArcNode *p;
	int  indegree[MAX_VERTEX_NUM];
	for (i=0;i<MAX_VERTEX_NUM;i++) indegree[i]=0;
	FindInDegree(G, indegree);   // �Ը����������indegree[0..vernum-1]
	for (i=0; i<G.vexnum; ++i)       // ������ȶ���ջS
		if (!indegree[i]) {SqStack[top]=i;top++;}  // ���Ϊ0�߽�ջ
		count = 0;                       // ������������
		while (top) {
			top--;
			i=SqStack[top];
			printf("%d-> ", G.vertices[i].data);  ++count;  // ���i�Ŷ��㲢����
			for (p=G.vertices[i].firstarc;  p;  p=p->nextarc) {
				k = p->adjvex;               // ��i�Ŷ����ÿ���ڽӵ����ȼ�1
				if (!(--indegree[k])) {SqStack[top]=k;top++;}  // ����ȼ�Ϊ0������ջ
			}
		}
		if (count<G.vexnum) { printf("���ڻ�·��");return ERROR;} // ������ͼ�л�·
		else return OK;
} // TopologicalSort
//======================��������=====================

int main()
{
	MGraph G1,G3;
	ALGraph G2,G4;
	int P[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
	float D[MAX_VERTEX_NUM];
	G1=CreateGraph_UDN( G1 );
	G2=CreateALGraph_UDN (G2);
	Print_ALGraph(G2);
	DFSTraverse( G2);
	BFSTraverse( G2) ;
	//����������G3���ڽӾ���
	
	//����������G4���ڽӱ�
	
	//���������G3�ڽӾ���
	
	//���������G4�ڽӱ�
	
	//������Ⱥ͹�����ȱ���������G4
//	DFSTraverse( G4);
//	BFSTraverse( G4) ;
	//TopologicalSort(G4);//���ڽӱ���ʾ������ͼ����������
	
	return 0;
}