/*
*�ļ���DSA02.C
*����ļ���ʵ��˳���б������в���
*���ߣ�������
*����: 2012-09-10
*/

#include "DSA02.h"

//ʹ�þ�̬����ʵ��˳���
void  InitSeqList( SeqListA SL,  int n)
{  
    int  i;
    for ( i=0; i<n ; i++){
	printf("������� %d ��Ԫ��: ",i);
        scanf("%d", &SL[i]);
    }
}
//ʹ�ö�̬����ʵ��˳���
void InitSeqList2( SeqList* SL ) {
	// ����һ���յ����Ա� 
	SL->data = (ElemType*) malloc (INITSIZE*sizeof (ElemType));
	SL->length = 0;
	SL->listsize = INITSIZE;
} // InitSeqList

//����ָ��Ϊ�����ģ�Ҳ���Է���һ��ָ��ĺ���
//SeqList* SL InitSeqList3( SeqList * SL)
//����ʵ������
void  InitSeqList3( SeqList ** SL){
	(*SL)->data = (ElemType*) malloc (INITSIZE*sizeof (ElemType));
	(*SL)->length = 0;
	(*SL)->listsize = INITSIZE;
}
//���ٲ����·���
void ClearSeqList( SeqList * SL){
	int i;
	if(SL->length==0){
		printf("˳���Ϊ�ձ�!\n");
		return;
	}
	else{
		printf("˳����������ݣ�Ĭ�ϱ��浽DSA021.tmp�ļ���[y/n]? \t");flushall();
		if(getchar()=='y'){
			SeqListSave(SL, ".\\Temp\\DSA021.tmp");
			system(".\\Temp\\DSA021.tmp");
			printf("\n�رձ����ļ����Զ�����...\n");
		}
		free(SL->data);//�ͷ�˳�����Ĵ洢���ݵĿռ�
		InitSeqList2(SL);//��Ҫ���³�ʼ��������˳���������Ϊ��ȷ��������
	}
}
int  SeqListInsert(SeqList *SL, int i, ElemType x, int speed)
{
	int j, ii;
	if (i<1 || i>SL->length+1){
		printf("iֵ�����\n");
		return 0;//ʧ��
	}
	if(SL->length==SL->listsize)
	{
		printf("˳����ռ䲻�㣡���ô洢�ռ�(����һ��Ԫ�ؿռ�)\n");
		SL->data=(ElemType*)realloc(SL->data, (SL->listsize + 1) * sizeof(ElemType));
		SL->listsize++;
	}
	for (j=SL->length-1; j>=i-1; j--){
		system("CLS");
		printf("������ʾ����������̣���%d λ���ϲ���%d Ԫ��...\n", i, x);
		SeqListPrint2(SL);
		SL->data[j+1]=SL->data[j];//����
		printf("���ں���%dԪ��%dλ��->%dλ��\n", SL->data[j], j+1, j+2 );
		Sleep(speed);
		
		for(ii=0;ii<SL->length;ii++){
			if(ii%10==0 && ii!=0 )printf("\n");
				if(ii==j)
					printf("%5d-> ", SL->data[ii]);
				else
					printf("%5d ", SL->data[ii]);
		}
		printf("%5d*", SL->data[SL->length]);
		Sleep(speed);
	}
	system("CLS");
	printf("�������!\n",i, x);
	SL->data[i-1] = x;
	SL->length++;// ���ȼ�1
	return 1;//�ɹ�
}

int  SeqListDelete(SeqList *SL, int i, ElemType* x, int speed)
{   
	int j, ii;
	if (i<1 || i>SL->length){
		printf("iֵ�����\n");
		return 0;
	}
	*x = SL->data[i-1];
	for (j=i; j<SL->length; j++){
		system("CLS");
		printf("������ʾɾ���������̣���%d λ����ɾ��%d Ԫ��...\n", i, *x);
		SeqListPrint2(SL);	
		SL->data[j-1]=SL->data[j];//ǰ��
		printf("����ǰ��%dԪ��%dλ��->%dλ��\n", SL->data[j], j+1, j );
		Sleep(speed);
		//SeqListPrint2(SL);
		for(ii=0;ii<SL->length;ii++){
			if(ii%10==0 && ii!=0 )printf("\n");
			if(ii==j)
				printf("  <-%5d ", SL->data[ii]);
			else
				printf(" %5d ", SL->data[ii]);
		}
		Sleep(speed);
		SeqListPrint2(SL);
	}
	system("CLS");
	printf("ɾ�����!\n",i, x);
	SL->length--;// ���ȼ�1
	return 1;	
}
int  SeqListEdit(SeqList *SL, int i, ElemType x)
{   
	if (i<1 || i>SL->length){
		printf("iֵ�����\n");
		return 0;
	}
	SL->data[i-1]=x;//�޸�ָ��λ���ϵ�����Ԫ��
	return 1;	
}
void ReadSeqList(SeqList *SL, char * fname){
	int i;
	FILE *pf;//FILE���͵�ָ�����pf
	ElemType x;

	system(fname);//���ļ�
	printf("\n�ر��ļ����Զ�����...\n");

	pf= fopen(fname, "r");//���ļ�
	if(!pf){
		printf("���ļ�ʧ��!���ܸ��ļ�������\n");
		return;
	}
	//����ǰ��ȷ��˳����пռ���ô������
	//ͬʱ��ϵͳ��ǰֻ�������ļ��ж���������
	InitSeqList2(SL);

	//���һ�е�ԭ��ܸ��ӣ�googleȥ��
	//��һ��\t,����дʱ�ĸ�ʽ��ȡ�����ɽ��
	for(i=1;!feof(pf);i++){//feof�ж�pfָ���Ƿ�����ļ���β

		fscanf(pf, "%d\t", &x);//��scanf�ȽϱȽ�
		SeqListInsert(SL, i, x, 0);
	}
	fclose(pf);//�ر��ļ�����fopen���ʹ��
}
void SeqListSave(SeqList *SL, char * fname){
	int i;
	FILE *pf;
	pf= fopen(fname, "w");
	if(!pf){
		printf("���������ļ�ʧ��!\n");
		return;
	}

	for(i=0;i<SL->length;i++){
		if(i%10==0 && i!=0 )printf("\n");
			fprintf(pf, "%5d\t", SL->data[i]);//��printf�ȽϱȽ�
	}
	//fprintf(pf, "%s ", "\n�رո��ļ����Զ����ص�ϵͳ...\n");
	fclose(pf);
	printf("\n�رձ����ļ����Զ�����...\n");
	system(fname);//���ļ�
}
void SeqListPrint(SeqListA SL, int n){
	int i;
	for(i=0;i<n;i++){
		if(i%10==0 && i!=0 )printf("\n");
			printf("%5d ", SL[i]);
	}
	printf("\n");
}
void SeqListPrint2(SeqList *SL){
	char p;
	int i=0;
	if(SL->length==0){
		printf("˳���Ϊ�ձ�!\n");
		return;
	}
	printf("������y/Y��ӡ˳���Ԫ�ص���ֵ�͵�ַ������ֱ�ӻس�������ӡ��ַ![y/n]?\n");
	flushall();
	if((p=getchar())=='y'|| (p=getchar())=='Y'){
		for(i=0;i<SL->length;i++){
			if(i%10==0 && i!=0 )printf("\n");
			printf("[%2.2d] %5d %10d  ",i+1, SL->data[i], &SL->data[i]);
		}
		printf("\n");
	}
	else{
		for(i=0;i<SL->length;i++){
			if(i%10==0 && i!=0 )printf("\n");
			printf("[%2.2d] %5d ",i+1, SL->data[i]);
		}
		printf("\n");
	}
}
//��[min, max]֮������1���������
ElemType RandElem(ElemType min, ElemType max){
	ElemType x;
	int minValue=min, maxValue=max;
	time_t tx;
	srand((unsigned) time(&tx));
	x = min+(int)max*(rand() % (maxValue-minValue+1))/max;
	return x;
}
//��[min, max]֮������n�������������
void RandArray(ElemType min, ElemType max, SeqListA SL, int n){
	int i;
	int minValue=min, maxValue=max;
	srand((unsigned) time(NULL));
	for(i=0;i<n;i++)
		SL[i] = min+(int)max*(rand() % (maxValue-minValue+1))/max;
}

int GetSeqListLength(SeqList *SL)
{
	int len;
	len = SL->length;
	return len;
}
int GetSeqListElem(SeqList *SL, int i, ElemType *x){
	if(i<1 || i>SL->length)
	{
		printf("iֵ�����\n");
		return 0;
	}
	*x = SL->data[i-1];

	return 1;
}

int LocateSeqListElem(SeqList *SL,  ElemType x){
	int i=0;
	while(i<SL->length+1){
		if(SL->data[i]==x)
			return i+1;
		else
			i++;
	}
	return 0;//˳�����û��x����Ԫ��
}
//�ȽϺ���
 int ElemTypeCmp(ElemType a, ElemType b) {
	 if(a==b)
		 return 1;
	 else
		 return 0;
 } 

int LocateSeqListElem2(SeqList *SL,  ElemType x, int(* Cmp)(ElemType a, ElemType b)){
	int i=0;
	while(i<SL->length){
		if(Cmp(SL->data[i],x)==1)
			return 1;
		i++;
	}
	return 0;
}
//P18��2.2
void MoveOddEven(SeqList *SL){

}
void UnionSeqList(SeqList *La, SeqList *Lb) {//merge
	int i, La_len, Lb_len, pos;
	ElemType x;
	La_len = GetSeqListLength(La);    // �����Ա��ĳ���
    	Lb_len = GetSeqListLength(Lb);   
	for (i = 1;  i <= Lb_len;  i++) {
		GetSeqListElem(Lb, i, &x); // ȡLb�е�i������Ԫ�ظ���x
		pos = LocateSeqListElem(La, x);
		if (pos>La_len || pos<1) 
			SeqListInsert(La, ++La_len, x, 100);// La�в����ں� x ��ͬ������Ԫ�أ������֮
	}
}

void UnionSeqList2(SeqList *La, SeqList *Lb) {//merge
	int i, La_len, Lb_len;
	ElemType x;

	InitSeqList2(La);
	La_len = GetSeqListLength(La);    // �����Ա��ĳ���
    	Lb_len = GetSeqListLength(Lb);   
	for (i = 1;  i <= Lb_len;  i++) {
		if(GetSeqListElem(Lb, i, &x)==1) // ȡLb�е�i������Ԫ�ظ���x
			if(LocateSeqListElem2(La, x, ElemTypeCmp)==0)
				SeqListInsert(La, ++La_len, x, 100);// La�в����ں� x ��ͬ������Ԫ�أ������֮
	}
}