#include <windows.h> 

#include "../include/DSATestServices.h"

//���ش�[min,max)֮���һ�����������
int RandInt(const int min, const int max)
{
	int i;
	time_t tx;	
	srand((unsigned) time(&tx));//srand������������������ĳ�ʼ������������Ϊ���������
	return min+(int)(rand() % (max-min));//α���������������
}

//��[min, max]֮������n�������������a
void RandIntArray(const int min, const int max, int a[], int n){
	int i;
	time_t tx;	
	srand((unsigned) time(&tx));
	for(i=0;i<n;i++)
		a[i] = min+(int)(rand() % (max-min+1));
}

// ���ش�[min,max)֮���һ�����������
double RandDouble(const double min, const double max){
	int i;
	time_t tx;	
	if(fabs(min-max)<1e-6){
		printf("�������!");
		return 0.0;
	}
	srand((unsigned) time(&tx));//srand������������������ĳ�ʼ������������Ϊ���������
	return min+rand() / (double)(RAND_MAX/(max-min));//α���������������
}

//��[min, max]֮������n�������������a
void RandDoubleArray(const double min, const double max, double a[], int n){
	int i;
	time_t tx;
	if(fabs(min-max)<1e-6){//
		printf("�������!");
		return;
	}	
	srand((unsigned) time(&tx));
	for(i=0;i<n;i++)
		a[i] = min+rand() / (double)(RAND_MAX/(max-min));
}

//ÿ�ε���update�������൱��ʱ�����1ms 
void UpdateTime(struct tms *t){
	(*t).milliseconds++; //1ms��λʱ���1  
	cnt++; 
	if ((*t).milliseconds==1000){ //��ʱ��1���λ 
		(*t).milliseconds=0;  
		(*t).seconds++;  
	}  
	if ((*t).seconds==60){ //��ʱ��1�ֽ�λ 
		(*t).seconds=0;  
		(*t).minutes++;  
	}  
	if ((*t).minutes==60){ //��ʱ��1Сʱ��λ
		(*t).minutes=0;  
		(*t).hours++;  
	}  
	if((*t).hours==24)
		(*t).hours=0;  
	Sleep(1);  //Sleep��windows�ṩ�ĺ�������������ͣ���򣬵�λ���룬�˴���ͣ1ms 
}  

//�˴������ʱ�����rΪ�س������У�һֱ��ͬһ�и���ʱ��
void DisplayTime(struct tms *t){    	 
	printf("\t%d:",(*t).hours);  
	printf("%d:",(*t).minutes);  
	printf("%d:",(*t).seconds); 
	printf("%d",(*t).milliseconds);
	printf("\t��ESC���˳�!\r");
}  

//��ʼ��ʱ��
void InitTime(){
	timec.hours=timec.minutes=timec.seconds=timec.milliseconds=0; 
} 

//��ʱ��ʱ���ӣ���0��ʱ��msecondsʱ�����ַ�'m'�����ո����ʾ�ֶμ�ʱ
char TimeClock(int mseconds)  
{ 
	char m;   
	InitTime(); 
	cnt = 0; 
	while(1){ 
		if(kbhit()) //�˴�����Ƿ��м������� 
		{ 
			m=getch();  
			if(m == '\r')  //1 ������ڻس�����ô��ʱ����������ѭ�� 
				break; 
			else if(m == ' '){  //2 ������ڿո���ʾ�˴μ�ʱ����ʼ����ʱ�� 
				tmpc = timec; //��¼��һ�μ�ʱ����� 
				InitTime(); 
				printf("\n"); 
			} 
			else if(m == VK_ESCAPE)//3 ESC��������ESC
				return m;
			else {//4 ������ 
				printf("�������,��֧������س������߿ո��ESC��!\n"); 
			}  
		} 
		UpdateTime(&timec);  //���¼�ʱ�� 
		if(timec.milliseconds>=mseconds-1)
			return 'm';
		DisplayTime(&timec); //��ʾ��ʱ��ʱ�� 
	} 
	return m;
}
//2013-03-11
void RandCharArray(char min, char max, char a[], int n){
	int i;
	char minValue=min, maxValue=max;
	srand((unsigned) time(NULL));
	for(i=0;i<n;i++)
		a[i] = minValue+(char)(rand() % (maxValue-minValue+1));
}
void PrintiArray(int a[], int n){
	int i=0;
	for(i=0;i<n;i++){
		if(i%10==0 && i!=0 )//10��������
			printf("\n");
		printf("%5d ", a[i]);//5λ������

	}
	printf("\n");
}
void PrintdArray(double a[], int n){
	int i=0;
	for(i=0;i<n;i++){
		if(i%10==0 && i!=0 )//10��������
			printf("\n");
		printf("%5.2f ", a[i]);//5λ������2λС��

	}
	printf("\n");
}
void PrintcArray(char a[], int n){
	int i=0;
	for(i=0;i<n;i++){
		if(i%10==0 && i!=0 )//10��������
			printf("\n");
		printf("%c ", a[i]);

	}
	printf("\n");
}
//ͨ�ñȽϺ���
 int ICmp(const void *a, const void *b) {
	 /*int *aa=(int *)a,*bb=(int *)b;
	 if(*aa > *bb)return 1; 
	 else if(*aa == *bb)return 0;
	 	else return -1;*/	 
	 return *(int *)a > *(int *)b ? 1 : -1;//��������д���������������	 
 } 
int CCmp( const void *a , const void *b )
{
	char *aa=(char *)a,*bb=(char *)b;
	if(*aa > *bb)return 1; 
	else if(*aa == *bb )return 0;
		else return -1;
	//return(*(char *)a-*(char *)b);//��������д���������������	 
}
 int DCmp(const void *a, const void *b) {
	 double *aa=(double *)a,*bb=(double *)b;
	 if(*aa > *bb)return 1; 
	 else if( fabs(*aa - *bb)<1e-6)return 0;
	 	else return -1;
	 //return *(double *)a > *(double *)b ? 1 : -1;//��������д���������������	 
 }
 int FCmp(const void *a, const void *b) {
	 float *aa=(float *)a,*bb=(float *)b;
	 if(*aa > *bb)return 1; 
	 else if(fabs(*aa - *bb)<1e-6)return 0;
	 	else return -1;
	 //return *(float *)a > *(float *)b ? 1 : -1;//��������д���������������	 
 }
//ͨ�ý�������
void VSwap(void * vp1, void *vp2, int size){
	char *buffer =(char*)malloc(sizeof(char)*size) ;
	memcpy(buffer, vp1, size);
	memcpy(vp1, vp2, size);
	memcpy(vp2, buffer, size);
	free(buffer);
}