/*
*�ļ���DSA03.H
*����ļ���ʵ��������ͷ�ļ�
*���ߣ�������
*����: 2012-09-10
*/
#ifndef DSA03_H
#define DSA03_H

#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>
#include<math.h>

extern char gVersion[20];
extern char* GetPluginVersion(void);
extern char gInterface[20];
extern char* GetPluginInterface(void);

typedef  int ElemType;
typedef struct  LinkNode {
      ElemType      data;  // ������
      struct LinkNode   *next;  // ָ����
   } LinkNode, *LinkList;  

//�꺯��
#define ROUND(val) (int)(val+0.5) 
int ElemTypeCmp(ElemType a, ElemType b);

ElemType RandElem(ElemType min, ElemType max);

void PrintLinkList(LinkList LL);
void CreateLinkList(LinkList * LL, int n);
void ClearLinkList(LinkList * LL);
int DeleteLinkListElem(LinkList LL, int i, ElemType *x, int) ;
int InsertLinkListElem(LinkList LL, int i, ElemType x, int) ;
int GetLinkListElem(LinkList LL, int i, ElemType *x);
int GetLinkListLength(LinkList LL);

void ReadLinkList(LinkList LL, char * fname);
void SaveLinkList(LinkList LL, char * fname);

int LocateLinkListElem(LinkList LL, ElemType x);
void EditLinkListElem(LinkList LL, int, ElemType x);

#endif