/*
*�ļ���BaseServices.C
*���ݣ�
*  ���������ļ�PFWDSA.C�ṩ�������񡣾������LoadPlugin��ChoicePlugin��RunPlugin��ManagerPlugin��9������
*  PFWDSAƽ̨�Ĳ������ʵ�ֵ���DSAInterface����������gVersion��gInterfaceȫ�ֱ���
*  Ŀǰ��gInterface����չʾDLL����ȫ�ֱ����ļ���������ͨ��DLL�ڲ�Я���Ĳ���ӿڣ���֤�ò���Ƿ�ΪPFWDSA�Ĳ��
*  ��gVersion����ͨ��DLL�ڲ�Я���İ汾��Ϣ����֤�ò����PFWDSAҪ��Ĳ���İ汾�Ƿ����  
*  ���������幦�ܼ�����ʵ��
*
*  ����ʵ��ģ�黯��BaseServices.lib��PluginManager.lib��PFWDSA.exe���ĳ������Ŀ�����������ʾ
*  static��̬ȫ�ֱ�����externȫ�ֱ�����ʹ��
*���ߣ�������
*����: 2012-09-10
*/


#include "../include/Global.h"
#include "../include/BaseServices.h"
#include "../include/PluginManager.h"

//1 ����־�ļ��л�ȡϵͳ���д���
//2 �����PFWDSA.log��־�ļ�ʧ�ܣ���ϵͳ���д���PFWDSAruntimesΪ0
//3 ���򣬻��ʵ��ֵPFWDSAruntimes
void ReadSysRunTimes(void){
	char bufflog[50],tmplog[50];
	FILE *pf=fopen("PFWDSA.log", "r");//PFWDSA.logӲ���룬���������޳�ζ
	if(!pf){
		PFWDSAruntimes=0;	
	}
	else{
		do{
			fgets(bufflog,50,pf);
			strcpy(tmplog,bufflog);
		}while(fgets(bufflog,50,pf));
		PFWDSAruntimes=atoi(tmplog);//���д���
		fclose(pf);
	}
} 
//1 ����ϵͳ���д���
//2 �����PFWDSA.log��־�ļ�ʧ�ܣ��򷵻أ�����һ������ʧ�ܣ�
//3 ���򣬱������д��������н���ʱ�����ں�ʱ��
void SaveSysRunTimes(void){
	time_t datetime;
	FILE *pf=fopen("PFWDSA.log", "a");
	PFWDSAruntimes++;
	time(&datetime); 
	if(!pf){
		printf("����ϵͳ���д���[%d]ʧ��! \n",PFWDSAruntimes);
		return;	
	}
	else{
		//�����д��������н���ʱ�����ں�ʱ��д����־�ļ�PFWDSA.log��
		fprintf(pf, "%d %s", PFWDSAruntimes, asctime(localtime(&datetime)));
		fclose(pf);
	}
}

//0 һ��������ٰ���dll��txt�����ļ���dll�Ƕ����ƴ����ִ���壬txt���ı����������ļ���û��txt�ļ��������ʹ�ã���ϵͳҪ��
//  �����Ϣ�걸�����ڲ����������ɸ���ܡ����û�л�ò��������Ϣ�����������Ϊ�գ�����������Կ��Բ�ѯ������
//1 PFWDSA��ܼ��ز��:���ĺ�������ϵͳԤ��Plugins�ļ����е�ÿ�����
//  ����dll��txt�ļ������ļ���������ȫ�ֱ���DSAPlugin���飬�Թ�ʹ��
//2 Լ���������չ��Ϊdll�������ִ�Сд��
//3 ��ϵͳָ����binĿ¼��Plugins�ļ��б������в���ļ�
//4 ����Win32API����FindFirstFile������һ������ļ�
//5 ���FindFirstFile����ֵΪ�Ƿ��ģ����϶�PFWDSAƽ̨û�в����������PluginManageģ����InsertPlugin����������
//6 ���򣬴�ӡPFWDSA���ı�������3��PrintPFWDSATextUI��
//7       ѭ����������dll����ļ�
//8       ����Win32API����LoadLibrary����dll����ļ�
//9       ����Win32API����GetProcAddress����PFUNCPlugTxt���ͺ���ָ��GetPluginInterface����ò�������Ĳ���ӿ�
//10      ����GetProcAddress����PFUNCPlugTxt���ͺ���ָ��GetPluginVersion����ò�������Ĳ���汾��Ϣ
//11	  ͨ��GetPluginTxt������ò����Ϣtxt�ļ����ݣ���������ͬ����txt�ļ���	      
//12      ��GetPluginTxt�������txt�ļ�ʧ�ܣ������SetPluginTxt����������10����Ϣ
//13      �ɹ����ز������dll��txt�ļ���nPlugins����1
//14 ÿ���������Ϣ���洢��ȫ�ֱ���DSAPlugin������
void LoadPlugin(void){
	HANDLE hFile;
	HMODULE hm;
	PFUNCPlugInfo pluginfo;//PFUNCPlugInfo���͵Ĳ����Ϣ����
	WIN32_FIND_DATA FileData;
	int i;
	char dllname[100];
	char temp[100];
	strcpy(dllname,pluginFolder);
	strcpy(temp,pluginFolder);
	strcat(temp, "*.dll");//Ӳ����.dll
	i=0;
	//���ָ��Ŀ¼��ָ����ʽ��dll����ļ��ĵ�һ���ļ�
	hFile = FindFirstFile(temp,  &FileData);

	if (hFile==INVALID_HANDLE_VALUE) {
        	printf("\n\tPFWDSAƽ̨û�в��!\n");
		InsertPlugin();//�����µĲ��
	}
	else{
		PrintPFWDSATextUI(3);//��ӡPFWDSA���ı�������
		while (1){
			strcat(dllname, FileData.cFileName);
			hm = LoadLibrary(dllname);//Win32API����dll����ļ�
			if ( !hm )
				printf("\t���ز��ʧ��!\n");
			else{
				DSAPlugin[i].id=(DWORD)hm;
				//GetProcAddress������ò�������Ĳ���ӿ�����
				pluginfo = (PFUNCPlugInfo)GetProcAddress(hm, "GetPluginInterface");
				if (pluginfo != NULL)
					strcpy(DSAPlugin[i].iPlugin,pluginfo());
				else{
					printf("\t����ӿڵ���������!�ò������PFWDSA�Ĳ��,��������!\n");
					break;
				}
				//��ò�������Ĳ���汾
				pluginfo = (PFUNCPlugInfo)GetProcAddress(hm, "GetPluginVersion");
				if (pluginfo != NULL)
					strcpy(DSAPlugin[i].version,pluginfo());
				else{
					printf("\t����汾����������!�ò���汾����PFWDSA����,��������!\n");
					break;
				}
				if(GetPluginTxt(dllname,i)==-1){
					if(SetPluginTxt(dllname,i)==-1){
						printf("\t����%s�������txt�ļ�ʧ��!\n",dllname);
						break;
					}
				}
				i++;
			}
			//�����һ��dll����ļ�
			if (!FindNextFile(hFile, &FileData)) 
                		break;
			strcpy(dllname,pluginFolder);
		}
		nPlugins=i;
		FindClose(hFile);//�ͷŲ����ļ����
	}
	ShowPluginsIDName();//��ʾ�����ź�����
}
//1 ��ʾ�����ź�����
void ShowPluginsIDName(void){
	int i;
	printf("\n\n\t\t     PFWDSA����б�[%2.2d]   \n", nPlugins);
	printf("\t\t===========================\n");
 	printf("\t\t| ���       ����         |\n");
   	printf("\t\t---------------------------\n");
	for(i=0;i<nPlugins;i++){
		printf("\t\t| [%2d]    %-12s    |\n", i, DSAPlugin[i].name);
	}
  	printf("\t\t===========================\n");
}
//1 ѡ����������ʾ
//2 ���PFWDSAƽ̨�޲������ò��뺯��InsertPlugin���ز��
//3 ����ѭ������ѡ������ʾ��ֱ����y��Y�˳�
//4    PFWDSA���ı�������2����ʾ�����ź�����
//5    �������ѡ����
//6        ���Ϊ-1�˳����ѡ��
//7        �����[0��nPlugins)��Ч��Χ�����RunPlugin������ʾid���
//8        �����Ч�򱨸沢ѯ���Ƿ����ѡ��ͬ���������y��Y�����������˳�
void ChoicePlugin(void){
	char c = 'n';
	int id = 0;	
	if(nPlugins<=0){
		printf ("\n\tPFWDSAƽ̨û�в��!\n");
		InsertPlugin();
	}
	else{
		do{	
			PrintPFWDSATextUI(2);
			ShowPluginsIDName();
			printf("\n\t������[���]ѡ����([-1]����):");
			scanf("%d", &id);
			if(id==-1){
				printf("\n\t�˳����ѡ��!\n");
				return;
			}
			else if(id>=0 && id < nPlugins){
					RunPlugin(id);
					printf("\n\tѡ��ͬ�����[y/n]?(�س�����):");
					flushall();
					scanf("%c", &c);	
				}
				else{
					printf("\t���������[%d]������Ч��Χ[0,%d]!\n", id, nPlugins-1);
					printf("\n\t����ѡ��ͬ�����[y/n]?(�س�����):");
					flushall();
					scanf("%c", &c);
				}

		}while(c == 'Y' || c == 'y');
	}
}
//1 ���в��
//2 ѭ�����в������ʾĳ���������ʱѯ������y��Y������������˳�
//3 PFWDSA���ı�������2������Win32API����GetProcAddress����PFUNC���ͺ���ָ��DSAInterface������ӿ�
//4 ע���������������������
void  RunPlugin(int id){
	char cont;
	PFUNC pFunc;
	do{
		pFunc = (PFUNC)GetProcAddress((HINSTANCE)DSAPlugin[id].id, DSAPlugin[id].iPlugin);		
		if (pFunc != NULL)
			pFunc();		
		printf("\n\t��������[%s]�����[y/n]?(�س�����):",DSAPlugin[id].name);
		while (getchar() != '\n')
			;//���������������
		scanf("%c", &cont);
	}while(cont == 'Y' || cont == 'y');
}

//1 ���ٲ�������ʹ���ڴ桢��Դ�����ͷ�
//2 �����LoadLibrary����������FreeLibrary�ͷŲ��dll��Դ
void DestroyPlugin(void){
	int i;
	for (i=0; DSAPlugin[i].id!=0; i++)
		FreeLibrary((HMODULE)DSAPlugin[i].id);
}
//1 ������������롢ɾ������ѯ��
//2 PFWDSA���ı�������0
//3 ѡ������ɾ�����ѯ������˳����в���
void ManagerPlugin(void){
	char m;
	while(1){
		system("CLS");
		PrintPFWDSATextUI(0);
		ShowPluginsIDName();
		printf("\n\t������[i]���� [d]ɾ�� [r]��ѯ [q]�˳�:");
		flushall();
		scanf("%c",&m);
		switch(m){
		case 'i':case 'I':
			InsertPlugin();
			break;
		case 'd':case 'D':
			DeletePlugin();
			break;
		case 'r':case 'R':
			RetrievePlugin();
			break;
		case 'q':case 'Q':
			printf("\n\t�˳��������!\n");
			return;
		default:
			printf("\t������Ч����������!", m);
			break;
		}
		system("PAUSE");
	}
}
//1 PFWDSA���ı�������
//2 PFWDSA�Ľ����Ϊ0���������1�����ʾ��2ѡ������������������ֽ���
void PrintPFWDSATextUI(int i){
	system("CLS");
	printf("\n\t=================================================");
	printf("\n\t|����DLL�����ܵġ����ݽṹ���㷨��ʵ����ʾƽ̨|");
	printf("\n\t|         �汾V1.0.0 ��ʹ��[%5.5d]��!           |",PFWDSAruntimes);
	printf("\n\t|    �����ݽṹ��(C���԰�)(��2��)�̲Ĳο�����   |");
	printf("\n\t| ����ƽ  ������ ����  �廪��ѧ������,2012��3�� |");
	printf("\n\t-------------------------------------------------");
	if(i==0)
		printf("\n\t|              PFWDSA�������ģ��               |");
	else if(i==1)
		printf("\n\t|              PFWDSA�����ʾģ��               |");
	else if(i==2)
		printf("\n\t|              PFWDSAѡ����ģ��               |");
	else 
		printf("\n\t|                PFWDSA������                   |");	
	printf("\n\t=================================================\n");	
}