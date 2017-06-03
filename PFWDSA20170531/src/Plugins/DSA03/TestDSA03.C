/*
*�ļ���TestDSA02.C
*����ļ���ʵ�������Ĳ����ļ���DSAInterface�ǲ���Ĺ��ص�
*���ߣ�������
*����: 2012-09-10
*/

#include "DSA03.h"

char gVersion[20];
char gInterface[20];
//�����Ϣ
BOOL APIENTRY DllMain( HANDLE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call){
		case DLL_PROCESS_ATTACH:
			strcpy(gVersion,"1.0.0");
			strcpy(gInterface,"DSAInterface");
			break;
		case DLL_THREAD_ATTACH:	
		case DLL_THREAD_DETACH:		
		case DLL_PROCESS_DETACH:	
			break;
    }
    return TRUE;
}
char* GetPluginVersion(){
	return gVersion;
}
char* GetPluginInterface(){
	return gInterface;
}
//�����ܵĽӿ�

char LinkListMenu(LinkList *LL);

void DSAInterface(void){

	char flag;
	LinkList LL;
	flag='b';
	CreateLinkList(&LL, 0);
	while(flag !='Q' && flag != 'q'){
		system("CLS");//����
		flag = LinkListMenu(&LL);//��������	
		system("PAUSE");//��ͣ
	}	
	ClearLinkList(&LL);//����
}

char LinkListMenu(LinkList *LL){

	int i, n, j, speed;
	ElemType x;
	char c, r;
	char fname[20];
	char tempFolder[100]=".\\Temp\\";

	printf("******************************** �������� ********************************\n\n");
	printf(" ��ʼ��������InitList��ʼ����[I/i]\n\n");
	printf(" ���ٲ�����Clear���ٱ�[C/c]��Quit�˳�[Q/q]\n\n");
	printf(" �����Ͳ�����Find����[F/f]��Save����[S/s]��Print��ӡ[P/p]\n\n");
	printf(" �ӹ��Ͳ�����Read��ȡ[R/r]��Add����[A/a]��Deleteɾ��[D/d]��Edit�༭[E/e]\n\n");
	printf("***************************************************************************\n\n");
	printf("���������ַ�ѡ�������Ĳ���:\t");flushall();
	c= getchar();
	switch(c){
		case 'I':
		case 'i':
			printf("���������ڵ������?\n");
			scanf("%d", &n);
			CreateLinkList(LL, n);
			printf("������%d���ڵ������!\n", n);
			break;
		case 'C':
		case 'c':
			ClearLinkList(LL);
			break;
		case 'R':
		case 'r':
			printf("���ļ���ȡ����������,�磺DSA031.tmp\t");
			scanf("%s", fname);
			strcat(tempFolder, fname);
			ReadLinkList(*LL,tempFolder);
			PrintLinkList(*LL);			
			break;
		case 'A':
		case 'a':
			if(GetLinkListLength(*LL)==0)
				i=1;
			else
				i = (int)RandElem(1, GetLinkListLength(*LL));
			printf("����[r]robot�Զ���ɡ�����,�˹�����...\n");	flushall();
			if((r=getchar())=='r'){
				printf("����������Ԫ�غͶ����ٶ���100����?\t");
				scanf("%d %d", &n, &speed);
				for(j=0;j<n-1;j++){
					x=RandElem(j, n);
					InsertLinkListElem(*LL, i, x, speed);
					i = (int)RandElem(1, GetLinkListLength(*LL));
				}
			}
			else{
				printf("�������λ�ú�Ԫ��(����Ϊ%d):\t",GetLinkListLength(*LL));
				scanf("%d %d", &i, &x);
			}
			printf("������LL��%dλ���ϲ���Ԫ�� %d :\n",i, x);
			InsertLinkListElem(*LL, i, x, speed);
			PrintLinkList(*LL);			
			break;
		case 'D':
		case 'd':
			PrintLinkList(*LL);	
			if(GetLinkListLength(*LL)==0)
				return 'q';
			printf("ɾ���ĸ�λ���ϵ�ʲô�ڵ�Ͷ����ٶ���100����?\t");
			scanf("%d %d %d", &i,  &x, &speed);
			if(DeleteLinkListElem(*LL, i, &x,speed))
				printf("������LL��%dλ����ɾ��Ԫ�� %d \n",i, x);
			else
				printf("ɾ��ʧ��!\n");
			break;
		case 'E':
		case 'e':
			if(GetLinkListLength(*LL)==0){
				printf("����Ϊ�ձ�������!\n");
				return 'q';
			}
			printf("�޸��ĸ�λ���ϵĽڵ�,������λ��:\t");
			scanf("%d", &i);
			if(	GetLinkListElem(*LL, i, &x) != 0){
				printf("����LL��%dλ����Ԫ�� %d ���޸�Ϊ:\t",i, x);
				scanf("%d", &x);
				EditLinkListElem(*LL, i, x);
				PrintLinkList(*LL);			
			}
			else
				printf("�޸�ʧ��!\n");
			break;
		case 'F':
		case 'f':			
			printf("�����ĸ��ڵ�(����λ��)? \t");
			scanf("%d", &x);
			if(	i=LocateLinkListElem(*LL, x) != 0)
				printf("����LL��%dλ����Ϊ���ҵ�Ԫ�� %d \n",i, x);
			else
				printf("����ʧ��!\n");
			break;
		case 'S':
		case 's':			
			printf("�����������ݵ��ļ���,�磺DSA031.tmp\t");
			scanf("%s", fname);
			strcat(tempFolder, fname);
			SaveLinkList(*LL, tempFolder);
			break;

		case 'P':
		case 'p':
			PrintLinkList(*LL);//��ӡ			
			break;
		case 'Q':
		case 'q':
			return c;//�˳����Ա�
		default:
			printf("�������������������ַ�,Q/q�˳�!\n");
			break;
	}
	return NULL;
}