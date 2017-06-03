/*
����������Ǵ��ļ���ȡ����ʽ���ݼ��𰸣���д������֤�ӷ���𰸽���Ƿ�һ�£���ν��Ԫ���ԣ�
�����������ͼ������ļ�顣�ص��Ƕ���ʽ���㣬ֻ���˼ӷ������м����ͳ˷�����д��
2012-10-24 ������
*/

#include"DSA04.h"


//��������
//////////////////////////////////////////////////
//�ж�e�Ƿ��ڶ���ʽp��(��Ҫ��ָ��)
int IsExistElem (polynomial *p, ElemType e){
	polynomial *h=p->next;
	while(h){
		if(h->data.expn == e.expn){
			/*printf("%dָ���Ѿ�����!\n", e.expn); */ return 1;
		}
		h=h->next;
	}
	return 0;//e.expn�����
}
//����β���룬��������������
int InsAfter( polynomial * p, ElemType e ) {
	polynomial * h, *s;
	if ( ! p )
		return 0;
	h=p;
	s = (polynomial*)malloc(sizeof(polynomial));
	s->data = e;
	while(h->next)
		h=h->next;
	h->next = s;
	s->next=NULL;	
	return 1;
}
//ѡ������ȷ������ʽ�ӷ����㣨�ڴ��������ɶ���ʽʱ����ָ����������
//������ѧϰ�ߣ����㷨��̲Ĳ�ͬ��Ӧע��AddPoly������
void SelectSortPoly(polynomial *p){
	ElemType e;
	polynomial * tmp1, *tmp2, *least;
	
	if (p)
        for (tmp1 = p; tmp1->next; tmp1 = tmp1->next) {
            for (tmp2 = tmp1->next, least = tmp1; tmp2; tmp2 = tmp2->next)
                if (tmp2->data.expn < least->data.expn)
                    least = tmp2;
				if (tmp1 != least){
					e = tmp1->data;
					tmp1 ->data = least->data;
					least->data = e;
				}
        }	
}
//��Ϊ�������룬��Ϊ���ļ��еĶ������ɶ���ʽ
//�ļ���д����������
int CreatePolynFromFile ( polynomial **p, char * filename) {
   // ����m���ϵ����ָ����������ʾһԪ����ʽ����������p
	int i, m, j;
	ElemType e;
	polynomial *h, *q;
	FILE *pf;
	pf=fopen(filename, "r");//���ļ�
	if(!pf){
		printf("������ʽ�����ļ�%sʧ��!\n", filename);
		exit(0);//stdlib.h
	}
	nPoly=0;
	for(j=0; !feof(pf); j++){
		nPoly++;
		p[j] = (polynomial*)malloc(sizeof(polynomial));
		p[j]->data.coef=0.0;
		p[j]->data.expn=-1;
		p[j]->next=NULL;

		h=p[j];

		fscanf(pf, "%d\n", &m);//��scanf�ȽϱȽ�
		for ( i=1; i<=m; ++i ) {  // �������� m ��������
			//printf("���������ʽ%d ���ϵ����ָ��(��ָ������):\t", i);
			fscanf (pf, "%f %d", &e.coef, &e.expn);
			if (!IsExistElem ( p[j], e) && e.coef!=0){   
				q = (polynomial*)malloc(sizeof(polynomial));
				q->data = e;
				q->next = NULL;
				h->next=q;
				h=q;				
			}
			else 
				printf("\n����ʽ%d ��ָ��%d�Ѿ����ڻ�ϵ��Ϊ0!\n", j, e.expn);
		}
		fscanf (pf, "\n");
		SelectSortPoly(p[j]);//ָ����������
	}
	fclose(pf);//�ر��ļ�
	return 1;//�ɹ�
} // CreatPolyn

//���ٺ���������ʱ�򶼱������ˣ�
void DestroyPoly(polynomial *p){
	polynomial *q = p;
	while(p->next){
		q = p->next;
		p->next=q->next;
		free(q);
	}
	free(p);
}
int cmp(ElemType e1, ElemType e2){
	if(e1.expn<e2.expn)
		return -1;
	else if(e1.expn>e2.expn)
		return 1;
	return 0;
}
// ������������ʽ�Ľ�㹹�ɡ��Ͷ���ʽ�� Pc = Pa��Pb����ָ������
int AddPoly ( polynomial **Pc, polynomial *Pa, polynomial *Pb) {
   
   ElemType e1, e2;
   polynomial *a, *b, *h;
   (*Pc) = (polynomial*)malloc(sizeof(polynomial));
   (*Pc)->data.coef=0.0;
   (*Pc)->data.expn=-1;
   (*Pc)->next=NULL;
   h = *Pc;

   a=Pa->next;b=Pb->next;
   while (a && b) {
	   e1=a->data;e2=b->data;
	   switch (cmp(e1, e2)) { 
			case 1: {  // ����ʽPb��ǰ����ָ��ֵС
				InsAfter (h, e2);			
				b=b->next;
				break;
			}
			case 0: {   // ���ߵ�ָ��ֵ���
				e1.coef= e1.coef + e2.coef ;
				if ( e1.coef != 0.0 ) 
					InsAfter(h, e1); 	
				a=a->next;b=b->next;
				break;
			}
			case -1: {  //����ʽPa�е�ǰ����ָ��ֵС
				InsAfter (h, e1);			
				a=a->next;
				break;
			}
		}
    }
   while(a){
	   InsAfter(h, a->data); 
	   a = a->next;
   }
   while(b){
	   InsAfter(h, b->data); 
	   b = b->next;
   }
   SelectSortPoly(h);//ָ����������
   return 1;
} // AddPoly

//��Ļ����
void PrintPolyn(polynomial *p){
	polynomial * t = p->next;
	if(!t){
		printf("0\n");return;
	}
	while(t){
		printf("%5.1fX^%d ", t->data.coef, t->data.expn);
		t=t->next;
		if(t)
			if(t->data.coef>0)
				printf("+");
			else if(t->data.coef< 0)
				printf(" ");
	}
	printf("\n");
}

//������ļ�
void SavePolyn(FILE *pf, polynomial *p){
	polynomial * t = p->next;
	if(!t){
		fprintf(pf, "0\n");return;
	}
	while(t){
		fprintf(pf, "%5.1fX^%d ", t->data.coef, t->data.expn);
		t=t->next;
		if(t)
			if(t->data.coef>0)
				fprintf(pf, "+");
			else if(t->data.coef< 0)
				fprintf(pf, " ");
	}
	fprintf(pf, "\n\n");
}

//����ʽ�жϣ���֤AddPoly��������ʹ��
int IsEqualPoly(polynomial *a, polynomial *b)
{
	polynomial * h1=a->next, * h2=b->next;
	while(h1 && h2){
		if(h1->data.coef == h2->data.coef && h1->data.expn == h2->data.expn){
			h1=h1->next;
			h2=h2->next;
		}
		else
			return 0;//����
	}
	if(!h1 && !h2)
		return 1;//���
	else
		return 0;//����
}