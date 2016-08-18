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
	strcpy(password,(char *)"admin62951");	// 这里修改密码（内置） 
	T = sys.random(password);				// 保存密码并加密
	Host * ph = NULL;
	bool ishost = false;
	system("color 0A");						// 更改文本和背景颜色
	cout << "			    正在读取中，请稍候";
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
    		ph = sys.menu(ph,ishost);			// 显示主菜单（默认为用户界面） 
		}
		catch (int)
		{
			cout << "输入的选项非法，请重试！";
			Sleep(1500);
			cin.sync();
  			cin.clear();
		}
		catch (char *)
		{
			cout << "文件读取/载入失败，请重试！";
			Sleep(1500);
			cin.sync();
  			cin.clear();
		}
		catch (...)
		{
			cout << "程序发生了一个未知错误，正在为您重启程序...";
			Sleep(1500);
			cin.sync();
			cin.clear();
		}
	}
	delete []password;
	return 0;
}
/***************************************

		颜色代码
	0=黑色 1=蓝色 2=绿色 3=湖蓝色
	4=红色 5=紫色 6=黄色 7=白色
	8=灰色 9=淡蓝色 A=淡绿色 B=淡浅绿色
	C=淡红色 D=淡紫色 E=淡黄色 F=亮白色

***************************************/
