/*
*�ļ���DSA03.C
*����ļ���ʵ�����������в���
*���ߣ�������
*����: 2012-09-10
*/

#include "DSA03.h"

//��[min, max]֮������n�������������
ElemType RandElem(ElemType min, ElemType max){
	ElemType x;
	int minValue=min, maxValue=max;
	//time_t tx;
	srand((unsigned) time(NULL));
	x = min+(int)max*(rand() % (maxValue-minValue+1))/max;
	return x;
}
// SL�Ǵ�ͷ����������ͷָ�룬�� x ���ص� i ��Ԫ��
int GetLinkListElem(LinkList LL, int i, ElemType *x) {
	LinkNode* p = LL->next;
	int j = 1;  // pָ���һ����㣬jΪ������
	while (p && j<i)  {
		p = p->next;
		++j;
	}
	// ˳ָ�������ң�ֱ�� p ָ��� i ��Ԫ�ػ� p Ϊ��
	if ( !p || j>i )
		return 0;  //�� i ��Ԫ�ز�����
	*x = p->data;  //  ȡ�õ� i ��Ԫ��
	return 1;//�ɹ�
} // GetElem
 
int InsertLinkListElem(LinkList LL, int i, ElemType x, int speed) {
     // SL Ϊ��ͷ���ĵ�������ͷָ�룬���㷨
     // �������е�i �����֮ǰ�����µ�Ԫ�� x
	int ii;
	LinkNode *s, *q=LL;
	LinkNode *p = LL;
    int j = 0;
	
	printf("\n������ʾ����������̣���%d λ��ǰ����%d Ԫ��...\n", i, x);
	PrintLinkList(LL);
	printf("���ں���ָ��^\n");
	Sleep(speed);
	while (p && j < i-1) {
		system("CLS");
		printf("������ʾ����������̣���%d λ��ǰ����%d Ԫ��...\n", i, x);
		PrintLinkList(LL);
		printf("���ں���ָ��^\n\n");
		Sleep(speed);
		p = p->next;
		for(ii=0;ii<GetLinkListLength(LL);ii++){
			q=q->next;
			if(ii%10==0 && ii!=0 )printf("\n");
				if(ii==j)
					printf("%5d->^ ", q->data);
				else
					printf("%5d-> ", q->data);
		}
		q=LL;
		Sleep(speed);
		++j;
	}   // Ѱ�ҵ� i-1 �����
	system("CLS");
	printf("�ҵ�%d(%d)λ��!\n", i, i-1);

	if (!p || j > i-1)
		return 0;   // i ���ڱ�������С��1
	Sleep(speed/10);
	printf("�����½��ռ� ");
	s = (LinkNode*) malloc ( sizeof (LinkNode));  // �����½��
	s->data = x; 
	Sleep(speed/10);
	printf(" �½������ ");
	s->next = p->next;
	Sleep(speed/10);
	printf(" �������������� ");
	p->next = s; // ����
	Sleep(speed/10);
	printf(" ����%d����%d���! \n", i, x);
	return 1;

} // LinstInsert

int DeleteLinkListElem(LinkList LL, int i, ElemType *x, int speed) {
   // ɾ���� LL Ϊͷָ��(��ͷ���)�ĵ������е� i �����
	LinkNode* p;
	LinkNode* q;
	LinkNode* t;
	int j, ii;
	p = LL;
    t = LL;
	j = 0;

	printf("\n������ʾɾ���������̣�ɾ����%d λ����%d Ԫ��...\n", i, *x);
	PrintLinkList(LL);
	printf("���ں���ָ��^\n");
	Sleep(speed);

	while (p->next && j < i-1) {
		system("CLS");
		printf("������ʾɾ���������̣���%d λ���ϲ���%d Ԫ��...\n", i, *x);
		PrintLinkList(LL);
		printf("���ں���ָ��^\n\n");
		Sleep(speed/2);
		
		p = p->next;
		
		for(ii=0;ii<GetLinkListLength(LL);ii++){
			t=t->next;
			if(ii%10==0 && ii!=0 )printf("\n");
				if(ii==j)
					printf("%5d->^ ", t->data);
				else
					printf("%5d-> ", t->data);
		}
		t=LL;
		Sleep(speed);
		++j;
	} 
	system("CLS");
	printf("�ҵ�%d(%d)λ��!\n", i, i-1);
	Sleep(speed/10);
	// Ѱ�ҵ� i ����㣬���� p ָ����ǰ��
	if  (!(p->next) || j > i-1) 
		return 0;  // ɾ��λ�ò�����

	printf("������λ ");
	q = p->next;
	Sleep(speed/10);
	printf("��������� ");
	p->next = q->next;  // ɾ�����
	*x = q->data;
	Sleep(speed/2);
	printf("�ͷŽ��ռ� ");
	free(q);//�ͷŽ��

	Sleep(speed/10);
	printf(" ����%dλ����ɾ��%d���! \n", i, *x);
	return 1;
} // LinkListDelete

void ClearLinkList(LinkList * LL) {
   // ��������������Ϊһ���ձ�
    LinkNode* p=*LL;
	while ((*LL)->next) {
        p=(*LL)->next;    (*LL)->next=p->next; 
		free(p);
    }
	(*LL)->next=NULL;
} // ClearLinkList

void CreateLinkList(LinkList *LL, int n) {
    // �������� n ������Ԫ�أ�������ͷ���ĵ�����	
	LinkNode* p;
	int i;
	*LL = (LinkList) malloc (sizeof (LinkNode));
	(*LL)->next = NULL;    // �Ƚ���һ����ͷ���ĵ�����
	for (i = n; i > 0; --i) {
		p = (LinkNode*) malloc (sizeof (LinkNode));
		printf("������� %d ���������:\t", i);
		scanf("%d", &p->data);    // ����Ԫ��ֵ
		p->next = (*LL)->next;
		(*LL)->next = p;  // ����
	}
} // CreateLinkList

void PrintLinkList(LinkList LL) {
   int i=1;
   LinkNode* p=LL;
   if(GetLinkListLength(LL)==0){
		printf("����Ϊ�ձ�!\n"); return;
   }
   while (p->next) {
        p=p->next;
		//printf("[%d] %5d  %d ", i++,p->data,&p->data);
		printf("%5d->", p->data);
    }
   printf("\n");
} // PrintLinkList

void ReadLinkList(LinkList LL, char * fname){
	int i;
	FILE *pf;//FILE���͵�ָ�����pf
	ElemType x;

	pf= fopen(fname, "r");//���ļ�
	if(!pf){
		printf("���ļ�ʧ��!���ܸ��ļ�������\n");
		return;
	}
	//����ǰ��ȷ��˳����пռ���ô������
	//ͬʱ��ϵͳ��ǰֻ�������ļ��ж���������
	CreateLinkList(&LL, 0);

	for(i=1;!feof(pf);i++){//feof�ж�pfָ���Ƿ�����ļ���β
		fscanf(pf, "%d\t", &x);//��scanf�ȽϱȽ�
		printf("%d\t", x);
		InsertLinkListElem(LL, i, x, 0);
	}
	fclose(pf);//�ر��ļ�����fopen���ʹ��
}
int GetLinkListLength(LinkList LL){
	LinkNode* p;
	int n;
	p=LL->next;n=0;
	while(p){
		n++;
		p=p->next;
	}
	return n;
}
int LocateLinkListElem(LinkList LL, ElemType x){

	int i=1;
	LinkNode* p=LL->next;
	while (p) {
		if(x==p->data) return i;
		else
			i++;
		p=p->next;
    }
	return 0;//ʧ��
}

void SaveLinkList(LinkList LL, char * fname){
	int i;
	LinkNode* p = LL->next;
	FILE *pf;
	pf= fopen(fname, "w");
	if(!pf){
		printf("���������ļ�ʧ��!\n");
		return;
	}

	for(i=0;p;i++){
		if(i%10==0 && i!=0 )printf("\n");
			fprintf(pf, "%5d\t", p->data);//��printf�ȽϱȽ�
		p=p->next;
	}
	fclose(pf);
	printf("\n�رձ����ļ����Զ�����...\n");
	system(fname);//���ļ�
}

void EditLinkListElem(LinkList LL, int i, ElemType x){
	int j=1;
	LinkNode* p = LL->next;
	while(p && j<i){p=p->next;++j;}
	if ( !p || j>i ){ printf("������%d λ���ϲ�����Ԫ��", i);   return;}      
	p->data = x;  //  �޸ĵ� i ��Ԫ��
}
//�ȽϺ���
int ElemTypeCmp(ElemType a, ElemType b) {
	if(a==b)
		return 1;
	else
		return 0;
} 