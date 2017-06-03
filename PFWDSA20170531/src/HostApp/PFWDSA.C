/*
*�ļ���PFWDSA.C
*���ݣ�
* �������ļ���ʵ��PFWDSAϵͳ���ܵ�����ڡ�ͨ����̬�����lib��ʽ����������̬��BaseServices.lib��PluginManager.lib
* ��һ����̬��DSATestServices.dll��������ܡ�
*���ߣ�������
*����: 2012-09-10
*/


#include "include/Global.h"
#include "include/BaseServices.h"
#include "include/DSATestServices.h"

//ʹ��DSATestServices.lib�������ʽ���Ӷ�̬���ӿ�DSATestServices.dll
//����make.bat�ļ��е�linkѡ�������һ��д
//#pragma comment(lib, "bin/DSATestServices.lib")
//#pragma comment(lib, "lib/BaseServices.lib")
//#pragma comment(lib, "lib/PluginManager.lib")

//ģ���ʹ�õ�ȫ�ֱ���(PluginManage.obj,BaseServices.obj��PFWDSA.obj��
//ʹ��ԭ��Դ�ļ��ж��壬ͷ�ļ���extern��������)
int  nPlugins=0;//0��ʾû�в��
char pluginFolder[] = ".\\Plugins\\"; //����ļ���
char dataFolder[] = ".\\Data\\"; //��������ļ���
char tempFolder[] = ".\\Temp\\"; //ϵͳ�������ʱ�ļ���
int  PFWDSAruntimes = 1; //PFWDSA���д���,1�״�ʹ��

//�Զ����ѡ����������ʾ
void AutoRandDemo(void);//ʹ�ú��������裺1��,����

//1 main�����������Ĺ�����ManagerPlugin��AutoRandDemo��ChoicePluginʵ�ֵĹ����������ѡ�����Ȳ���
//2 ��дϵͳ���д�������ReadSysRunTimes��SaveSysRunTimes�ۼƸ�ϵͳ���д�������д����־�ļ�PFWDSA.log��
//3 ���ز������LoadPlugin�б���ʾ������Թ������������ѡ��������
//4 ��ʾPFWDSA���˵�
//5 ѭ��ִ�й���������Զ������ʾ��ѡ��������������ϵͳ���˳�ϵͳ
//6 ʹ��goto���,�ָ�ɾ��������б���ʾ�ҿ���
//7 �˳�ϵͳʹ��goto��䣬����ϵͳʹ�õ���Դ

int main(void){	
	char m=' ';
	ReadSysRunTimes();//ReadSysRunTimes��BaseServices.libģ����
	do{
		system("CLS");//����
		PrintPFWDSATextUI(3);//��BaseServices.libģ����,��ʾ������
		LoadPlugin();//��BaseServices.libģ����,���ز��
		while(m!='Q' || m!='q'){
			PrintPFWDSATextUI(3);//��ʾ������
			ShowPluginsIDName();//��BaseServices.libģ����,��ʾ����б�
			printf("\n\t\t   ================== ");
			printf("\n\t\t   |  PFWDSA���˵�  | ");
			printf("\n\t\t   ------------------ ");
			printf("\n\t\t   | [M/m] ������� | ");
			printf("\n\t\t   | [A/a] �����ʾ | ");
			printf("\n\t\t   | [C/c] ѡ���� | ");
			printf("\n\t\t   | [R/r] ����ϵͳ | ");
			printf("\n\t\t   | [Q/q] �˳�ϵͳ | ");
			printf("\n\t\t   ================== ");
			printf("\n\t\t\a   ������˵����ַ�:");
			flushall();//����C�������������printf������scanf֮�䣬��Ϊ�ַ�����ʱ!
			m=getchar();
			switch(m){//switch���
				case 'M':
				case 'm':
					ManagerPlugin();//ManagerPlugin��BaseServices.libģ����
					break;
				case 'A':
				case 'a':
					AutoRandDemo();//ʹ�ú��������裺3��,����,��Դ�ļ���
					break;
				case 'C':
				case 'c':
					ChoicePlugin();//ChoicePlugin��BaseServices.libģ����
					break;
				case 'Q':
				case 'q':
					goto EXITPFWDSA;//ʹ��goto��䣬�˳�ϵͳ
				case 'R':
				case 'r':
					goto RESTART;//ʹ��goto��䣬����ϵͳ
				default:
					system("CLS");
					PrintPFWDSATextUI(3);
					ShowPluginsIDName();
					printf("\n\t\a������Ч���������������˵����ַ�!");
					system("PAUSE");
					break;		
			}
		}
		RESTART:
			DestroyPlugin();//DestroyPlugin��BaseServices.libģ����
	}while(m == 'R' || m == 'r');
	EXITPFWDSA:
		DestroyPlugin();
	system("DEL /F /Q .\\Temp\\*.*");
	printf("\n\t\a ��Ȩ@������2012 GPL���� CZLDL@TOM.COM\n\n");
	SaveSysRunTimes();//SaveSysRunTimesBaseServices.libģ����
	system("PAUSE");
	return 0;
}

//1 �Զ����ѡ����ʾ
//2 ����PFWDSAƽ̨0����1����2�����ϲ�����ѡ����������ʾ
//3 û�в�����˳�
//4 1�������ֱ�����иò�����������ѡ��
//5 2�����ϲ��������RandInt���ѡ��һ�������ʾ��RandInt��DSATestServices.dllģ����
//6 ��ESC���˳�

void AutoRandDemo(void){ //ʹ�ú��������裺2��,����
	while(1){//����ѭ����ֱ���û���ESC��
		PrintPFWDSATextUI(1);
		ShowPluginsIDName();
		printf("\n\t1�����л���س�����ִ��,�ո���ֶμ�ʱ!\n");
		if(nPlugins<=0){//û�в��
			printf("\tPFWDSAƽ̨û�в��!\n");
			system("PAUSE");
			return;
		}
		else if(nPlugins==1){//1�������������else�ϲ�
			//TimeClock��DSATestServices.dllģ���ڣ������ṩ������û�ʹ��(API)��
			//��ͬ��BaseServices.libΪPFWDSA�����ר��
			if(TimeClock(100)==VK_ESCAPE){//10����
				printf("\n\t�˳������ʾ!\n");
				break;//����while
			}
			RunPlugin(0);//RunPlugin��BaseServices.libģ����
		}
		else{//2�����ϲ��
			if(TimeClock(1000)==VK_ESCAPE){//1000����Ϊ1��
				printf("\n\t�˳������ʾ!\n");
				break;
			}
			//RandInt��DSATestServices.dllģ���ڣ�����[0,nPlugins-1)����������
			RunPlugin(RandInt(0,nPlugins));
		}
	}
}