/*
*�ļ���TestDSA01.C
*����ļ���ʵ��ͨ��ѡ������Ĳ����ļ���DSAInterface�ǲ���Ĺ��ص�
*���ߣ�������
*����: 2012-09-10
*/

#include "DSA01.h"

//const int N=1000;
#define N 1000
#define RANMIN 1
#define RANMAX 10000

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

void TestDSABubbleSort(void);
void TestDSASelectSort(void);
void TestDSASort(void);

void DSAInterface(void){
	char s;
	while(1){
		printf("\n\t��������ĸbð�� sѡ�� aͨ������ x�˳�:");flushall();
		scanf("%c", &s);
		switch(s)
		{
			case 'x':
				return;
			case 'b':
				TestDSABubbleSort();
				break;
			case 's':
				TestDSASelectSort();
				break;
			case 'a':
				TestDSASort();
				break;
			default:
				printf("\t������ĸ��Ч!");		
				break;			
		}
	}
}
void TestDSABubbleSort(void){
	int arr[N];
	clock_t start, finish;
	double duration;
	int i=0;
	RandIntArray(1,N, arr, N);
	for(i=0;i<N;i++){
		if(i%10==0 && i!=0)printf("\n");
		printf("%5d ", arr[i]);
	}
	printf("\n");
	start = clock();
	DSABubbleSort((void**)arr, N, sizeof(int), ICmp);
	finish = clock();
	duration = (double)(finish-start)/CLOCKS_PER_SEC;
	printf("\nDSABubbleSort RandIntArray[%d] time is %f second\n", N, duration);
	for(i=0;i<N;i++){
		if(i%10==0 && i!=0 )printf("\n");
		printf("%5d ", arr[i]);
	}
	printf("\nDSABubbleSort RandIntArray[%d] time is %f second\n", N, duration);
}
void TestDSASelectSort(void){
	int arr[N];
	clock_t start, finish;
	double duration;
	int i=0;
	RandIntArray(1,N, arr, N);
	for(i=0;i<N;i++){
		if(i%10==0 && i!=0)printf("\n");
		printf("%5d ", arr[i]);
	}
	printf("\n");
	start = clock();
	DSASelectSort((void**)arr, N, sizeof(int), ICmp);
	finish = clock();
	duration = (double)(finish-start)/CLOCKS_PER_SEC;
	printf("DSASelectSort RandIntArray[%d] time is %f second\n", N, duration);
	for(i=0;i<N;i++){
		if(i%10==0 && i!=0 )printf("\n");
		printf("%5d ", arr[i]);
	}
}
void TestDSASort(void){
	long i;
	FILE *pf;//�ļ��������
	int* tArray, *sArray;
  
	//_int64 dTime, dTime1, dTime2;
	unsigned dTime, dTime1, dTime2;
	LARGE_INTEGER m_nFreq;
    LARGE_INTEGER m_nBeginTime;
    LARGE_INTEGER nEndTime;


	int* iArray = (int*)malloc(sizeof(int)*N);
	double* dArray = (double*)malloc(sizeof(double)*N);
	char* cArray = (char*)malloc(sizeof(char)*N);

	RandIntArray(RANMIN, RANMAX, iArray, N);

	printf("SelectSort(iArray, N)����ǰ...\n");
	PrintiArray(iArray,N);
	QueryPerformanceFrequency(&m_nFreq); // ��ȡʱ������
    QueryPerformanceCounter(&m_nBeginTime); // ��ȡʱ�Ӽ���
	//SelectSort(iArray, N);
	//DSA_SelectSort((void**)iArray, N, "int", ICmp);
	DSASelectSort((void**)iArray, N, sizeof(int), ICmp);
	QueryPerformanceCounter(&nEndTime);
    dTime = (nEndTime.QuadPart-m_nBeginTime.QuadPart)*1000/m_nFreq.QuadPart;
	printf("SelectSort(iArray, N)�����...\n");
	PrintiArray(iArray,N);
	printf("ѡ�������ʱ%d ���룡\n",dTime);

	//////////////////////////////////////////////
	system("PAUSE");//��ͣ
	system("CLS");//����CLean Screen=>CLS
	printf("DSA_SelectSort((void**)dArray, N, \"double\", DCmp)����ǰ...\n");
	RandDoubleArray(3.14, 96.54, dArray, N);
	PrintdArray(dArray,N);
	//DSA_SelectSort((void**)dArray, N, "double", DCmp);
	DSASelectSort((void**)dArray, N, sizeof(double), DCmp);
	printf("DSA_SelectSort((void**)dArray, N, \"double\", DCmp)�����...\n");
	PrintdArray(dArray,N);

	system("PAUSE");
	system("CLS");
	printf("DSA_SelectSort(cArray, N);����ǰ...\n");
	RandCharArray('a', 'z', cArray, N);
	PrintcArray(cArray,N);
	//DSA_SelectSort((void**)cArray, N, "char", CCmp);
	DSASelectSort((void**)cArray, N, sizeof(char), CCmp);
	printf("DSA_SelectSort(cArray, N);�����...\n");
	PrintcArray(cArray,N);
	system("PAUSE");
	system("CLS");
	pf=fopen("Temp\\DSA011.tmp", "w");//���ļ�
	//i���е�С�������ֵʱ��Χ�ڣ�0xffffffffUL(16) 4294967295(10) Լ42�ڣ�
	//������Լ��㵽1,10,100,1000,1000,10000,10��,��100�����������ʱ�Ͳ��ܵ���
	//ͨ���Աȿ��Է���c���Ա�׼����Ŀ���������qsort��0.062������10��������
	//������д��DSA_SelectSort������Ҫ111.328�롣���У�ѡ������Ϊ��O��n2�� ����������
	//��ΪO��nlogn�����㷨����һ�У��������ѡ��
	fprintf(pf, "%8s %8s %8s %8s\n", "���ݹ�ģ", "ѡ������", "ð������", "��������");
	for(i=1;i<ULONG_MAX/10000;i*=10){

		tArray=(int*)malloc(sizeof(int)*i);
		sArray=(int*)malloc(sizeof(int)*i);
		RandIntArray(RANMIN, RANMAX, tArray, i);
		memcpy(sArray, tArray, sizeof(int)*i);

		QueryPerformanceCounter(&m_nBeginTime); // ��ȡʱ�Ӽ���
		DSASelectSort((void**)sArray, i, sizeof(int), ICmp);
		QueryPerformanceCounter(&nEndTime);
		dTime = (nEndTime.QuadPart-m_nBeginTime.QuadPart)*1000/m_nFreq.QuadPart;
		printf("%8d ������ѡ�������ʱ %8d ���룡\n", i, dTime);

		memcpy(sArray, tArray, sizeof(int)*i);

		QueryPerformanceCounter(&m_nBeginTime); // ��ȡʱ�Ӽ���
		DSABubbleSort((void**)sArray, i, sizeof(int), ICmp);
		QueryPerformanceCounter(&nEndTime);
		dTime1 = (nEndTime.QuadPart-m_nBeginTime.QuadPart)*1000/m_nFreq.QuadPart;
		printf("%8d ������ð�������ʱ %8d ���룡\n", i, dTime1);

		memcpy(sArray, tArray, sizeof(int)*i);	
		QueryPerformanceCounter(&m_nBeginTime); // ��ȡʱ�Ӽ���
		//qsort(sArray, i ,sizeof(int), ICmp);
		DSAQuickSort(sArray, i ,sizeof(int), ICmp);
		QueryPerformanceCounter(&nEndTime);
		dTime2 = (nEndTime.QuadPart-m_nBeginTime.QuadPart)*1000/m_nFreq.QuadPart;
		printf("%8d ���������������ʱ %8d ���룡\n\n", i, dTime2);
		
		fprintf(pf, "%8d %8d %8d %8d\n", i, dTime, dTime1, dTime2);
		free(tArray);//�ͷ���malloc����Ķ��ڴ�ռ�
		free(sArray);
	}
	fclose(pf);//�ر��ļ�
	system("Temp\\DSA011.tmp");

	free(iArray);
	free(dArray);
	free(cArray);
}