#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <cctype>
#include "bookstore.h"
using namespace std;
unsigned int T;
int main()
{
	System sys;
	char * password = new char[50];
	strcpy(password,(char *)"admin62951");	// �����޸����루���ã� 
	T = sys.random(password);				// �������벢����
	Host * ph = NULL;
	bool ishost = false;
	system("color 0A");						// �����ı��ͱ�����ɫ
	cout << "			    ���ڶ�ȡ�У����Ժ�";
	for (int i = 0; i < 3; i++)
	{
		Sleep(300);
		cout << ".";
	}
	Sleep(500);
	while (true)
	{
		try
		{
    		ph = sys.menu(ph,ishost);			// ��ʾ���˵���Ĭ��Ϊ�û����棩 
		}
		catch (int)
		{
			cout << "�����ѡ��Ƿ��������ԣ�";
			Sleep(1500);
			cin.sync();
  			cin.clear();
		}
		catch (char *)
		{
			cout << "�ļ���ȡ/����ʧ�ܣ������ԣ�";
			Sleep(1500);
			cin.sync();
  			cin.clear();
		}
		catch (...)
		{
			cout << "��������һ��δ֪��������Ϊ����������...";
			Sleep(1500);
			cin.sync();
			cin.clear();
		}
	}
	delete []password;
	return 0;
}
/***************************************

		��ɫ����
	0=��ɫ 1=��ɫ 2=��ɫ 3=����ɫ
	4=��ɫ 5=��ɫ 6=��ɫ 7=��ɫ
	8=��ɫ 9=����ɫ A=����ɫ B=��ǳ��ɫ
	C=����ɫ D=����ɫ E=����ɫ F=����ɫ

***************************************/
