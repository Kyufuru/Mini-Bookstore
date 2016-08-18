#include <iostream>
#include <iomanip>
#include <fstream> 
#include <cstdlib>
#include <cctype>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include "bookstore.h"
using namespace std;
string Host::inf = "";
int Host::count = 0;
const int MAXLEN = 256;
extern unsigned int T;
B::B()
{
	num = quantity = price = origin = discount = 0;
	name = sort = author = "无";
	newbook = false;
}
ostream & operator <<(ostream & out, Guest & g)
{
	out << fixed << setprecision(2)
		<< "编号：" << g.num << endl
		<< "名称：" << g.name;
	if (g.newbook == 1) cout << "【新】";
	out << endl
		<< "种类：" << g.sort << endl 
		<< "作者：" << g.author << endl << "数量：" << g.quantity << " 本" << endl 
		<< "价格：";
	if (g.discount != 0) out << g.price * g.discount << " 元【" << g.discount*10 << "折】";
	else out << g.price << " 元";
	out << endl;
	return out;
} 
void Host::savebook(char * line)								// 保存书籍
{
	if (Getquantity() == 0) return;
	ofstream fout(line,ios::app);
	fout << '\n'
		 << num << '\t' << newbook << '\t' << name << '\t'
		 << sort << '\t' << author << '\t' << quantity << '\t'
		 << price << '\t' << origin << '\t' << discount;
	if (fout.fail())
	{
		int n = num;
		throw n;
	}
	fout.close();
}
istream & operator >>(istream & in, Host & h)
{
	in >> h.num;
	if (h.num == 0) return in;
	in >> h.newbook >> h.name >> h.sort >> h.author
	   >> h.quantity >> h.price >> h.origin >> h.discount;
	if (in.fail() || h.num < 0 || h.quantity < 0 || h.price < 0 
				  || h.origin < 0 || h.discount < 0 || h.discount >= 1)
	{
		int n = h.num;
		throw n;
	}
	return in;
}
ostream & operator <<(ostream & out, Host & h)
{
	out << fixed << setprecision(2)
		<< "编号：" << h.num << endl
		<< "名称：" << h.name;
	if (h.newbook == 1) cout << "【新】";
	out	<< endl
		<< "种类：" << h.sort << endl 
		<< "作者：" << h.author << endl << "数量：" << h.quantity << " 本" << endl 
		<< "价格：";
	if (h.discount != 0) out << h.price * h.discount << " 元【" << h.discount*10 << "折】";
	else out << h.price << " 元";
	out << endl << "成本：" << h.origin << " 元" << endl;
	return out;	
}
bool operator ==(Host & ph, Host & nph)
{ return (ph.num == nph.num) && (ph.name == nph.name); }
void System::showmenu(bool ishost)
{
	system("cls");
	cout << endl;
	for (int i = 0; i < 79; i++) cout << "=";
	cout << endl << "+									      +"
		 << endl << "+		   	      欢迎进入书店管理系统			      +"
		 << endl << "+		   	       请选择你需要的功能			      +"
		 << endl << "+									      +"
		 << endl << "+		  1. 查看书籍清单              2. 查询书籍		      +";
	if (not ishost)
		cout << endl << "+		  3. 购买书籍	               4. 管理员登录		      +"
		 	 << endl << "+		  5. 退出系统		      				      +";
	else
		cout << endl << "+		  3. 载入书籍清单	       4. 添加书籍		      +"
			 << endl << "+		  5. 删除书籍	               6. 修改书籍信息		      +"
			 << endl << "+		  7. 查看销售与统计	       8. 添加/修改/删除通知          +"
			 << endl << "+		  9. 退出登录		      10. 退出系统                    +";
	cout << endl << "+									      +"
		 << endl << "+								       ver1.5 +" << endl;
  	for (int i = 0; i < 79; i++) cout << "=";
  	cout << endl;
  	for (int i = 0; i < 40; i++) cout << "=#";
}
Host * System::menu(Host * ph, bool ishost)					// 主菜单界面
{															// ishost判断是否为管理员，默认为true 
	while (true)
  	{
  		string info = ph[0].Getinform();
		showmenu(ishost);
		if (info != "")
		{
			cout << endl << info << endl << endl;
			for (int i = 0; i < 40; i++) cout << "=#";
		}
  		Host * cph = check(ph,ishost);
  		if (!ph && cph)
  		{
			ph = cph;
  			showmenu(ishost);
  			if (info != "")
			{
				cout << endl << info << endl << endl;
				for (int i = 0; i < 40; i++) cout << "=#";
			}
		}
  		cout << endl << "您的选择：";
  		int choice = 0;
  		cin.sync();											// 在输入前后最好都使用一次清空缓冲区的命令 
  		cin.clear();										// 以免缓冲区残留数据，造成循环 
  		cin >> choice;
  		cin.sync();
  		cin.clear();
  		if (not ishost)										// 用户界面 
  			switch (choice)
  			{
  				case 1:
				  	{
				  		ph = view(ph,ishost);				// 查看书单 
				  		break;
				  	}
				case 2:
					{
						ph = search(ph,ishost);				// 查询书籍 
						break;
					}
				case 3:
					{
						ph = buybook(ph);					// 购买书籍 
						break; 
					} 
				case 4:
					{
						ishost = login("admin",ishost);		// 登录界面 
						break; 
					} 
				case 5: quit();								// 退出系统 
				default: throw choice;
			}
		else												// 管理界面 
		  	switch (choice)
  			{
  				case 1:
					{
				  		ph = view(ph,ishost);				// 查看书单 
				  		break;
					}
				case 2:
					{
						ph = search(ph,ishost);				// 查询书籍 
						break;
					}
				case 3:
					{
						ph = load(ph);						// 加载书目文件 
						break;
					}
				case 4:
					{
						ph = addbook(ph);					// 添加书籍 
						break;
					}
				case 5:
					{
						ph = delbook(ph);					// 删除书籍 
						break;
					} 
  				case 6:
  					{
  						ph = reverse(ph);					// 修改书籍 
  						break;
					}
				case 7:
					{
						soldlist(ph);						// 销售清单与统计 
						break;
					} 
				case 8:
					{
						ph = inform(ph);					// 修改通知 
						break;
					}
				case 9:
					{
						cout << "\n您已成功退出登录！敲击任意键继续或返回";
						getch();
						cin.clear();
						cin.sync();
						ishost = false;
						break;
					}
				case 10: quit();							// 退出系统 
				default:
					{
						cout << "输入的选项非法，请重试！";
						Sleep(1500);
						cin.sync();
  						cin.clear();
  						break;
					}
			}
	}
	return ph;
}
Host * System::check(Host *ph, bool ishost)					// 检查书单是否为空，并返回书单指针 
{	
	Sleep(500);
	if (!ph)
	{
		cout << endl << "没有书单信息！";
		Sleep(1000);
		while (true)
		{
			try
			{
				if (ishost) cout << endl << "是否从文件载入书单？（Y/N）：";
				else return load(ph,ishost);
				char choice;
				cin >> choice;
				cin.sync();
  				cin.clear();
				switch (toupper(choice))
				{
					case 'Y': return load(ph,ishost);
					case 'N': return ph;
					default: throw choice;
				}
			}
			catch (...)
			{
				cout << "输入的选项非法，请重试！";
				Sleep(1500);
				cin.sync();
  				cin.clear();
			}
		}
	}
	else return ph; 
}
Host * System::load(Host * ph, bool ishost)					// 加载书目
{
	char * line = new char[MAXLEN];
	int n = 0;												// n记录文本行数
	ifstream fin;
	while(true)
	{
		if (not ishost)
		{
			strcpy(line,"Booklist(UTF-8).txt");
			fin.open(line);
			if (!line) throw line;
			if (fin.fail())
			{
				cout << "\n找不到“" << line << "”，返回主菜单";
				Sleep(1500);
				fin.close();
				return ph; 
			}
			else
			{
				cout << "\n正在自动加载默认书单...\n";
				Sleep(500);
				break;
			}
		}
		char choice;
		cout << "\n是否加载默认文件？（Y/N/E返回）：";
		cin >> choice;
		cin.clear();
		cin.sync();
		switch (toupper(choice))
		{
			case 'Y':
			{
				strcpy(line,"Booklist(UTF-8).txt");
				fin.open(line);
				if (!line) throw line;
				if (fin.fail())
				{
					cout << "\n找不到“" << line << "”，返回主菜单";
					Sleep(1500);
					fin.close();
					return ph; 
				}
				else break;
			} 
			case 'N':
				{
					while (true)
					{
						cout << "\n请输入你要读取的文件名（包括后缀，输入exit退出）：";
						cin.getline(line,MAXLEN);
						cin.clear();
						cin.sync();
						if (!strcmp(line, "exit") || !strcmp(line, "EXIT"))
						{
							delete []line;
							return ph;
						}
						else
						{
							fin.open(line);
							if (!line) throw line;
							if (fin.fail())
							{
								cout << "找不到“" << line << "”，请重试！";
								Sleep(1500);
								fin.close();
								continue;
							}
						}
						break;
					}
					break;
				}
			case 'E':
				{
					delete []line;
					return ph;
				}
			default: throw line;
		}
		break;
	}
	for (int i = 0; i < 5; i++) fin.getline(line,MAXLEN);	// 跳过前五行的项目说明信息
	while(!fin.eof())
	{ 
		fin.getline(line,MAXLEN);
		n++;
	}
	//cout << n << endl;									// 调试点 1 
	fin.seekg(0);
	fin.clear();
	if (ph != NULL)
	{
		ph[0].Countzero(); 
		delete []ph;										// 释放上次动态分配的空间
		Host * ph;
	}
	ph = new Host[n];
	for (int i = 0; i < 5; i++) fin.getline(line,MAXLEN);
	try
	{								
		for (int i = 0; i < n; i++)
		{
			fin >> ph[i];
			//cout << ph[i] << endl;						// 调试点 2 
			if (fin.fail()) throw i+1;
			fin.getline(line,MAXLEN);
		}
	}
	catch (int num)
	{
		cout << "数据格式错误！请检查您书单中编号为 " << num << " 的数据！";
		Sleep(1500);
		ph = NULL;
		fin.close();
		delete []line;
		return ph;
	}
	fin.close();
	delete []line; 
	cout << "载入书单成功！敲击任意键返回或继续（敲击v键查看书单）";
	if (toupper(getchar()) == 'V') view(ph);
	save(ph);
	return ph;
}
void System::save(Host * ph, char * line)					// 保存书目到文本 
{
	ofstream fout;
	if (!ph)
	{
		fout.open(line,ios::out);							// 书单为空则清空保存文件 
		if (!fout) throw line;
		cout << "\n书单已自动保存到“" << line << "”中，敲击任意键返回或继续";
		getch();
		cin.clear();
		cin.sync();
		return;
	}
	else
	{
		fout.open(line);
		if (!fout) throw line;
	}
	fout << "【使用说明】\n"
		 << "一、请按照“编号、新书、书籍名称、分类、作者、数量、价格、成本、折扣”"
		 << "的顺序输入数据，数据之间请用“Tab键”或“空格”隔开\n"
		 << "二、每项数据不得包含“空格”、“Tab键”和“Enter键”，"
		 << "若包含此类字符系统将会报错并指出错误所在书籍编号\n"
		 << "三、新书：是否为新书。“1”为是，“0”为否；折扣：“0”为不打折，折扣以0到1之间的小数表示\n"
		 << "编号\t新书\t书籍名称\t分类\t作者\t数量/本\t价格/元\t成本/元\t折扣";
	fout.close();
	try
	{
		for(int i = 0; i < ph[0].Getcount(); i++)
	 	{
			ph[i].savebook(line);
			//cout << ph[i];								// 调试点 3
		}
	}
	catch (int n)
	{
		cout << "数据格式错误！请检查您书单中编号为 " << n << " 的数据！";
		cin.clear();
		cin.sync();
		Sleep(1500);
		return;
	}
	cout << "\n书单已自动保存到“" << line << "”中，敲击任意键返回或继续";
	getch();
	cin.clear();
	cin.sync();
} 

Host * System::view(Host * ph, bool ishost)					// 查看书单子菜单 
{
	if(!check(ph,ishost)) return ph;
	cout << "-------------------------------------\n"
		 << "      您希望以哪种方式查看书单？\n\n"
		 << "   1.按编号顺序查看  2.按分类查看\n"
		 << "   3.按书名顺序查看  4.返回主菜单\n"
		 << "-------------------------------------\n";
	int choice;
	while (true)
	{
		cout << "\n您的选择："; 
		cin >> choice;
		cin.clear();
		cin.sync();
		try
		{
			switch (choice)
			{
				case 1: return orderview(ph, ishost);
				case 2: return sortview(ph, ishost);
				case 3: return nameview(ph, ishost);
				case 4: return ph;
				default: throw choice;
			}
		}
		catch (int)
		{
			cout << "输入的选项非法，请重试！";
			Sleep(1500);
		}
	}
}
Host * System::orderview(Host * ph, bool ishost)			// 按号排序并输出书单 
{
	if(!check(ph,ishost)) return ph; 
	Sleep(500);
	system("cls");
	Sleep(500);
	Host temp = ph[0];										// **新对象初始化的时候长度不会累加** 
	for (int i = 0; i < ph[0].Getcount()-1; i++) 			// 插入排序 
	{
		//cout << i << endl;								// 调试点 4 
		temp = ph[i+1];
		for (int j = i; j >=0; j--)
			if (ph[j].Getnum() > temp.Getnum())
			{
				ph[j+1] = ph[j];
				ph[j] = temp;
			}
			else break;
	}
	cout << "-------------------------\n\n";
	for (int i = 0; i < ph[0].Getcount(); i++)
	{
		if (ph[i].Getquantity() == 0) continue;
		if (ishost) cout << ph[i];
		else
		{
			Guest * gph = ph;
			cout << gph[i];
		}
		cout << "\n-------------------------\n\n";
	}
	Sleep(500);
	cout << "敲击任意键返回或继续";
	getch();
	cin.sync();
	cin.clear();
	return ph;
}
Host * System::sortview(Host * ph, bool ishost)				// 按类输出书单
{
	if(!check(ph,ishost)) return ph; 
	Sleep(500);
	system("cls");
	Sleep(1000);
	string sort[ph[0].Getcount()];							// 存放书籍种类 
	for (int i = 0, j = 0; i < ph[0].Getcount() && j < ph[0].Getcount(); i++, j++)
	{														// 整合类型 
		sort[i] = ph[j].Getsort();
		for (int k = 0; k < i; k++)
			if (sort[k] == sort[i]) i--; 
	}
	int i = 0;
	while (sort[i] != "")									// 按类输出书单 
	{
		cout << "-------------- "<< sort[i] <<" --------------\n\n";
		for(int j = 0; j < ph[0].Getcount(); j++)
		{
			if (ph[i].Getquantity() == 0) continue;
			if (sort[i] == ph[j].Getsort())
				if (ishost) cout << ph[j] << endl;
				else
				{
					Guest * gph = ph;
					cout << gph[j] << endl;
				}
		}
		i++;
	}
	Sleep(500);
	cout << "敲击任意键返回或继续";
	getch();
	cin.sync();
	cin.clear();
	return ph;
}
Host * System::nameview(Host * ph, bool ishost)				// 按名首字母输出
{
	if(!check(ph,ishost)) return ph; 
	Sleep(500);
	system("cls");
	Sleep(1000);
	Host temp = ph[0];										// **新对象初始化的时候长度不会累加** 
	for (int i = 0; i < ph[0].Getcount()-1; i++) 			// 插入排序 
	{
		//cout << i << endl;								// 调试点 5 
		temp = ph[i+1];
		for (int j = i; j >=0; j--)
			if (ph[j].Getname() > temp.Getname())
			{
				ph[j+1] = ph[j];
				ph[j] = temp;
			}
			else break;
	}
	cout << "-------------------------\n\n";
	for (int i = 0; i < ph[0].Getcount(); i++)
	{
		if (ph[i].Getquantity() == 0) continue;
		if (ishost) cout << ph[i];
		else
		{
			Guest * gph = ph;
			cout << gph[i];
		}
		cout << "\n-------------------------\n\n";
	}
	Sleep(500);
	cout << "敲击任意键返回或继续";
	getch();
	cin.sync();
	cin.clear();
	return ph;
} 
Host * System::search(Host * ph, bool ishost)				// 查询书籍子菜单
{
	if(!check(ph,ishost)) return ph;
	orderview(ph);
	cout << "\n\n#X#X#X#X#X#X#X#X#X#X# 请选择查询方式 #X#X#X#X#X#X#X#X#X#X#\n"
		 << "\n         1.按编号查找  2.按书名查找  3.按作者查找"
		 << "\n   4.按种类查找  5.查看新书  6.查看打折书  7.返回主菜单\n"
		 << "\n##########################################################\n";
	int choice;
	while (true)
	{
		cout << "\n您的选择："; 
		cin >> choice;
		cin.clear();
		cin.sync();
		try
		{
			switch (choice)
			{
				case 1:
					{
						int num;
						cout << "请输入编号：";
						cin >> num;
						cin.clear();
						cin.sync();
						ph = search(ph,num,ishost);
						return ph;
					}
				case 2:
					{
						string name;
						cout << "请输入书名：";
						cin >> name;
						cin.clear();
						cin.sync();
						ph = search(ph,name,1,ishost);
						return ph;
					}
				case 3:
					{
						string author;
						cout << "请输入作者：";
						cin >> author;
						cin.clear();
						cin.sync();
						ph = search(ph,author,3,ishost);
						return ph;
					}
				case 4:
					{
						string sort;
						cout << "请输入类别：";
						cin >> sort;
						cin.clear();
						cin.sync();
						ph = search(ph,sort,2,ishost);
						return ph;
					}
				case 5:
					{
						ph = search(ph,true,ishost);		// 查看新书 
						return ph;
					}
				case 6:
					{
						ph = search(ph,0.0,ishost);			// 查看打折书 
						return ph;
					}
				case 7: menu(ph,ishost); 
				default: throw choice;
			}
		}
		catch (int)
		{
			cout << "输入的选项非法，请重试！";
			Sleep(1500);
		}
	}
}
Host * System::search(Host * ph, int num, bool ishost)		// 按号查询
{
	if(!check(ph,ishost)) return ph;
	system("cls");
	Sleep(500);
	bool found = false;
	cout << "\n\t\t\t\t  搜索结果\n\n";
	for (int i = 0; i < 79; i++) cout << "*";
	cout << endl;
	for (int i = 0; i < ph[0].Getcount(); i++)
	{
		if (ph[i].Getquantity() == 0) continue;
		if (num == ph[i].Getnum())
		{
			found = true;
			if (ishost) cout << endl << ph[i] << endl;
			else
			{
				Guest * gph = ph;
				cout << endl << gph[i] << endl;
			}
			cout << "-------------------------------------\n";
		}
	}
	if (!found) cout << "\n没有符合要求的搜索结果！\n";
	Sleep(500);
	cout << "\n敲击任意键返回或继续";
	getch();
	cin.clear();
	cin.sync();
	return ph;
} 
Host * System::search(Host * ph, string namesortauthor, int flag, bool ishost)
															// 按名/类/作者查询
{
	if(!check(ph,ishost)) return ph;
	system("cls");
	Sleep(500);
	bool found = false;
	cout << "\n\t\t\t\t  搜索结果\n\n";
	for (int i = 0; i < 79; i++) cout << "*";
	cout << endl;
	if (flag == 1)											// 按名查询
	{
		for (int i = 0; i < ph[0].Getcount(); i++)
		{
			if (ph[i].Getquantity() == 0) continue;
			if (namesortauthor == ph[i].Getname())
			{
				found = true;
				if (ishost) cout << endl << ph[i] << endl;
				else
				{
					Guest * gph = ph;
					cout << endl << gph[i] << endl;
				}
				cout << "-------------------------------------\n";
			}
		}
	}
	else if (flag == 2)										// 按类查询
	{
		for (int i = 0; i < ph[0].Getcount(); i++)
		{
			if (ph[i].Getquantity() == 0) continue;
			if (namesortauthor == ph[i].Getsort())
			{
				found = true;
				if (ishost) cout << endl << ph[i] << endl;
				else
				{
					Guest * gph = ph;
					cout << endl << gph[i] << endl;
				}
				cout << "-------------------------------------\n";
			}
		}
	}
	else if (flag == 3)										// 按作者查询
	{
		for (int i = 0; i < ph[0].Getcount(); i++)
		{
			if (ph[i].Getquantity() == 0) continue;
			if (namesortauthor == ph[i].Getauthor())
			{
				found = true;
				if (ishost) cout << endl << ph[i] << endl;
				else
				{
					Guest * gph = ph;
					cout << endl << gph[i] << endl;
				}
				cout << "-------------------------------------\n";
			}
		}
	}
	if (!found) cout << "\n没有符合要求的搜索结果！\n";
	Sleep(500);
	cout << "\n敲击任意键返回或继续";
	getch();
	cin.clear();
	cin.sync();
	return ph;
}
Host * System::search(Host * ph, bool isnew, bool ishost)	// 查看新书
{
	if(!check(ph,ishost)) return ph;
	system("cls");
	Sleep(500);
	bool found = false;
	cout << "\n\t\t\t\t  搜索结果\n\n";
	for (int i = 0; i < 79; i++) cout << "*";
	cout << endl;
	if (isnew)
	{
		for (int i = 0; i < ph[0].Getcount(); i++)
		{
			if (ph[i].Getquantity() == 0) continue;
			if (ph[i].Getnew())
			{
				found = true;
				if (ishost) cout << endl << ph[i] << endl;
				else
				{
					Guest * gph = ph;
					cout << endl << gph[i] << endl;
				}
				cout << "-------------------------------------\n";
			}
		}
	}
	else													// 查看旧书（预留功能） 
	{
		for (int i = 0; i < ph[0].Getcount(); i++)
		{
			if (ph[i].Getquantity() == 0) continue;
			if (!ph[i].Getnew())
			{
				found = true;
				if (ishost) cout << endl << ph[i] << endl;
				else
				{
					Guest * gph = ph;
					cout << endl << gph[i] << endl;
				}
				cout << "-------------------------------------\n";
			}
		}
	}
	if (!found) cout << "\n没有符合要求的搜索结果！\n";
	Sleep(500);
	cout << "\n敲击任意键返回或继续";
	getch();
	cin.clear();
	cin.sync();
	return ph;
}
Host * System::search(Host * ph, double isdiscount, bool ishost)
															// 查看打折书籍 
{
	if(!check(ph,ishost)) return ph;
	system("cls");
	Sleep(500);
	bool found = false;
	cout << "\n\t\t\t\t  搜索结果\n\n";
	for (int i = 0; i < 79; i++) cout << "*";
	cout << endl;
	if (isdiscount != 0)
	{
		for (int i = 0; i < ph[0].Getcount(); i++)
		{
			if (ph[i].Getquantity() == 0) continue;
			if (ph[i].Getdiscount() != 0)
			{
				found = true;
				if (ishost) cout << endl << ph[i] << endl;
				else
				{
					Guest * gph = ph;
					cout << endl << gph[i] << endl;
				}
				cout << "-------------------------------------\n";
			}
		}
	}
	else													// 查看不打折书籍（预留功能） 
	{
		for (int i = 0; i < sizeof(ph); i++)
		{
			if (ph[i].Getquantity() == 0) continue;
			if (!ph[i].Getdiscount() == 0)
			{
				found = true;
				if (ishost) cout << endl << ph[i] << endl;
				else
				{
					Guest * gph = ph;
					cout << endl << gph[i] << endl;
				}
				cout << "-------------------------------------\n";
			}
		}
	}
	if (!found) cout << "\n没有符合要求的搜索结果！\n";
	Sleep(500);
	cout << "\n敲击任意键返回或继续";
	getch();
	cin.clear();
	cin.sync();
	return ph; 
}
Host * System::addbook(Host * ph)							// 添加书籍
{
	if(!check(ph)) return ph;
	int length;
	Host * nph; 
	system("cls");
	Sleep(300);
	cout << "【使用说明】\n"
	 	 << "一、请按照“编号、新书、书籍名称、分类、作者、数量、价格、成本、折扣”\n"
	 	 << "    的顺序输入数据，数据之间请用“Tab键”或“空格”隔开\n"
	 	 << "二、编号为0表示输入结束\n"
	 	 << "三、新书：是否为新书。“1”为是，“0”为否；折扣：“0”为不打折\n"
		 << "    折扣以0到1之间的小数表示\n"
	 	 << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n"
		 << "编号	新书	书籍名称	分类	作者	数量	价格	成本	折扣\n";
	length = ph[0].Getcount();								// 保存原长度 
	while(true)
	{
		ph[0].Countzero();									// 长度归零重新累加 
		nph = new Host[length+1];
		for (int i = 0; i < length; i++)
		{	if (ph[i].Getnum() == ph[length-1].Getnum() && ph[i].Getname() != ph[length-1].Getname())
			{												// 编号重复冲突异常检测 
				cout << "输入错误！不同书籍编号应不同，请重新输入该书籍！\n";
				ph[0].Getcount(-1);							// ph里只有length个单位内存空间！ 
				ph = del(ph,ph[length-1].Getname());
				ph[0].Getcount(1);							// 计数还原(因为在del函数里已经-1了)
				length--;									// 更新ph长度 
				Sleep(1500);
			} 
			//cout << ph[i] << endl;						// 调试点 6 
			nph[i] = ph[i];
		}
		try
		{ cin >> nph[length]; }
		catch (int n)
		{
			cout << "数据格式错误！请检查您书单中编号为 " << n << " 的数据！";
			cin.clear();
			cin.sync();
			Sleep(1500);
			return ph;
		}
		cin.clear();
		cin.sync();
		if (nph[length].Getnum() == 0)
		{
			nph[length].Getcount(-1); 						// 输入0时撤销累加
			//cout << ph[0].Getcount() << endl;				// 调试点 7 
			break; 
		} 
		ph = nph;
		length = ph[0].Getcount();							// 更新nph长度 
	}
	for (int i = 0; i < length; i++)
	{
		for (int j = i - 1; j >= 0; j--)					// 整合同一本书 
			if (nph[j] == nph[i])
			{
				nph[i].Getquantity(nph[j].Getquantity());	// 累加书本数量 
				nph = del(nph,nph[j].Getnum());
				length--;
			}
	}
	delete []ph;
	save(nph);
	return nph;
}
Host * System::delbook(Host * ph)							// 删除书籍子菜单 
{
	if(!check(ph)) return ph;
	int length;
	Host * nph; 
	length = ph[0].Getcount();								// 保存原长度 
	orderview(ph);
	cout << "\n>>>>>>>> 请选择删除方式 <<<<<<<<\n"
		 << "\n>  1.按编号删除  2.按书名删除  <\n"
		 << "\n================================\n";
	int choice;
	while (true)
	{
		cout << "\n您的选择："; 
		cin >> choice;
		cin.clear();
		cin.sync();
		try
		{
			switch (choice)
			{
				case 1:
					{
						int num;
						cout << "请输入编号（多个编号请用回车间隔，输入0结束删除）：";
						while (true)
						{
							cin >> num;
							cin.clear();
							cin.sync();
							if (num == 0)
							{
								cout << "\n删除成功！";
								cin.clear();
								cin.sync();
								save(ph); 
								return ph;
							}
							ph = del(ph,num);
							if (ph == NULL) return ph;
						}
					}
				case 2:
					{
						string name;
						cout << "请输入书名（多个编号请用回车间隔，输入0结束删除）：";
						cin >> name;
						cin.clear();
						cin.sync();
						if (name == "0")
							{
								cout << "\n删除成功！";
								cin.clear();
								cin.sync();
								save(ph);
								return ph;
							}
						ph = del(ph,name);
						if (ph == NULL) return ph;
					}
				default: throw choice;
			}
		}
		catch (int)
		{
			cout << "输入的选项非法，请重试！";
			Sleep(1500);
		}
	}
}
Host * System::del(Host * ph, int num)						// 按号删除书籍
{
	for (int i = 0; i < ph[0].Getcount(); i++)
	{
		if (num == ph[i].Getnum())
		{
			ph[0].Getcount(-1);
			if (ph[0].Getcount() == 0)						// 删光了 
			{
				cout << "\n书单已全部删除！";
				cin.clear();
				cin.sync();
				delete []ph;
				Host * ph = NULL;
				save(ph);
				return ph;
			}			
			ph[i] = ph[ph[0].Getcount()];
		}
	} 
	int length = ph[0].Getcount();
	ph[0].Countzero();
	Host * nph = new Host[length];
	for (int i = 0; i < nph[0].Getcount(); i++) nph[i] = ph[i];
	delete []ph;
	return nph;
}
Host * System::del(Host * ph, string name)					// 按名删除书籍
{
	for (int i = 0; i < ph[0].Getcount(); i++)
		if (name == ph[i].Getname())
		{
			ph[0].Getcount(-1);
			if (ph[0].Getcount() == 0)						// 删光了 
			{
				cout << "\n书单已全部删除！";
				cin.clear();
				cin.sync();
				delete []ph;
				Host * ph = NULL;
				save(ph);
				return ph;
			}			
			ph[i] = ph[ph[0].Getcount()];
		}
	int length = ph[0].Getcount();
	ph[0].Countzero();
	Host * nph = new Host[length];
	for (int i = 0; i < nph[0].Getcount(); i++) nph[i] = ph[i];
	delete []ph;
	save(nph);
	return nph;
}
Host * System::reverse(Host * ph)							// 修改书籍
{
	if(!search(ph)) return ph;
	int n;
	while (true)
	{
		cout << "\n请确认输入您需要修改书籍对应的编号（输入0返回）：";
		bool found = false;
		cin >> n;
		cin.clear();
		cin.sync();
		if (n == 0) return ph; 
		for (int i = 0; i < ph[0].Getcount(); i++)
			if (ph[i].Getnum() == n)
			{
				n = i;										// 记录编号所在的位置 
				found = true;
			}
		if (!found)
		{
			cout << "没有与之对应的书籍！请检查您的输入是否正确";
			Sleep(1000);
		}
		else break;
	}
	cout << "\n%%%%%%%%%%%%%%%%% 您想修改哪一项信息？%%%%%%%%%%%%%%%%%\n"
		 << "\n        1.编号  2.书名  3.类别  4.作者  5.数量\n"
		 << "   6.价格  7.成本  8.新书  9.折扣  10.全部  0.返回\n"
		 << "\n%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n";
	int choice;
	while (true)
	{
		try
		{
			cout << "\n您的选择：";
			cin >> choice;
			if (!cin) throw choice;
			cin.clear();
			cin.sync();
			switch (choice)
			{
				case 1:
					{
						Host temp = ph[n];
						bool same = true;
						while (same)
						{
							same = false;
							cout << "请输入新的编号：";
							ph[n].Renum();					// 数量改成0相当于删除书籍 
							if (ph[n].Getquantity() == 0) del(ph,n);
							cin.clear();
							cin.sync();
							for (int i = 0; i < ph[0].Getcount(); i++)
								if (ph[i].Getnum() == ph[n].Getnum() && ph[i].Getname() != ph[n].Getname())
								{							// 编号重复冲突异常检测
									same = true;
									ph[n] = temp;
									cout << "输入错误！不同书籍编号应不同，请重新输入！\n";
									Sleep(1500);
								}
						}
						break;
					}
				case 2:
					{
						cout << "请输入新的书名：";
						ph[n].Rename();
						cin.clear();
						cin.sync();
						break;
					}
				case 3:
					{
						cout << "请输入新的类别：";
						ph[n].Resort();
						cin.clear();
						cin.sync();
						break;
					}
				case 4:
					{
						cout << "请输入新的作者：";
						ph[n].Reauthor();
						cin.clear();
						cin.sync();
						break;
					}
				case 5:
					{
						cout << "请输入新的数量：";
						ph[n].Requantity();
						cin.clear();
						cin.sync();
						break;
					}
				case 6:
					{
						cout << "请输入新的价格：";
						ph[n].Reprice();
						cin.clear();
						cin.sync();
						break;
					}
				case 7:
					{
						double origin;
						cout << "请输入新的成本：";
						cin >> origin;
						cin.clear();
						cin.sync();
						ph[n].Reorigin();
						break;
					}
				case 8:
					{
						cout << "请输入新书设置（1为新书，0为非新书）：";
						ph[n].Renewbook();
						cin.clear();
						cin.sync();
						break;
					} 
				case 9:
					{
						cout << "请输入新的折扣（以0-1之间的小数表示，0表示不打折）：";
						ph[n].Rediscount();
						cin.clear();
						cin.sync();
						break;
					}
				case 10:
					{
						cout << "请输入新书信息(全为0时返回)\n"
							 << "\n■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n"
		 					 << "编号	新书	书籍名称	分类	作者	数量	价格	成本	折扣\n";
						Host temp = ph[n];
						bool same = true;
						while (same)
						{
							same = false;
							cin >> ph[n];
							cin.clear();
							cin.sync();
							for (int i = 0; i < ph[0].Getcount(); i++)
								if (ph[i].Getnum() == ph[n].Getnum() && ph[i].Getname() != ph[n].Getname())
								{							// 编号重复冲突异常检测
									same = true;
									ph[n] = temp;
									cout << "输入错误！不同书籍编号应不同，请重新输入！\n";
									Sleep(1500);
								}
							if (ph[n].Getnum() == 0)
							{
								ph[n] = temp;
								break;
							}
						}
						break;
					}
				case 0:
					{
						cout << "\n修改成功！";
						cin.clear();
						cin.sync();
						save(ph);
						return ph;
					}
				default: throw choice;
			}
		}
		catch (int)
		{
			cout << "输入的选项或数据非法，请重试！";
			cin.clear();
			cin.sync();
			Sleep(1500);
		}
	}
}
void System::soldlist(Host * ph)							// 查看销售清单与汇总
{
	if(!check(ph,true)) return;
	Host * sph = ph; 
	char line[MAXLEN];
	strcpy(line,"SAVEBooklist(UTF-8).txt");
	int n = 0, m = sph[0].Getcount();						// n记录原始文本行数, m记录销售书目条数 
	ifstream fin;
	fin.open(line);
	if (fin.fail()) throw line;
	for (int i = 0; i < 5; i++) fin.getline(line,MAXLEN);	// 跳过前五行的项目说明信息
	while(!fin.eof())
	{
		fin.getline(line,MAXLEN);
		n++;
	}
	//cout << n << endl;									// 调试点 8 
	fin.seekg(0);
	fin.clear();
	ph = new Host[n];
	for (int i = 0; i < 5; i++) fin.getline(line,MAXLEN);
	try
	{								
		for (int i = 0; i < n; i++)
		{
			fin >> ph[i];
			//cout << ph[i] << endl;						// 调试点 9 
			if (fin.fail()) throw i+1;
			fin.getline(line,MAXLEN);
		}
	}
	catch (int num)
	{
		cout << "数据格式错误！请检查您原始数据文件中编号为 " << num << " 的数据！";
		Sleep(1500);
		ph = NULL;
		fin.close();
		delete []ph;
		return;
	}
	fin.close();
	Sleep(300);
	system("cls");
	Sleep(1000);
	cout << "      $$$$$$$$$$$$$$$$$$$$$$$$$$$$  销售清单  $$$$$$$$$$$$$$$$$$$$$$$$$$$$\n\n";
	bool found = false;
	double total = 0; 
	cout << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++) 
			if (ph[i].Getnum() == sph[j].Getnum()) ph[i].Getquantity(-sph[i].Getquantity());
		if (ph[i].Getquantity() == 0) continue;			// 没人买
		else
		{
			found = true;
			cout << "编号：" << ph[i].Getnum() << endl
				 << "名称：" << ph[i].Getname() << endl
				 << "种类：" << ph[i].Getsort() << endl
				 << "作者：" << ph[i].Getauthor() << endl
				 << "销量：" << ph[i].Getquantity() << endl
				 << "单利：" << ph[i].Getprice() - ph[i].Getorigin() << endl
				 << "总利：" << ph[i].Getquantity() * (ph[i].Getprice() - ph[i].Getorigin()) << endl
				 << endl << "---------------------------------------\n\n";
			total += ph[i].Getquantity() * (ph[i].Getprice() - ph[i].Getorigin());
		}
	}
	ph[0].Countzero();
	ph[0].Getcount(m);
	if (not found)
	{
		cout << "\n没有被销售的书籍！";
		cout << "\n敲击任意键继续或返回"; 
		getch();
		cin.clear();
		cin.sync();
	}
	else
	{
		cout << "总计盈利：" << total << endl;
		Sleep(500);
		save(ph,(char *)"SOLDBooklist(UTF-8).txt");
	}
	delete []ph;
}
Host * System::inform(Host * ph)							// 添加/修改/删除通知
{
	char * pc = new char[3*MAXLEN];
	cout << "\n请输入新的通知（按'#'键结束，只输入'#'键删除通知）：\n";
	cin.getline(pc,3*MAXLEN,'#');
	cin.clear();
	cin.sync();
	ph[0].Reinform(pc);
	delete []pc;
	cout << "\n修改成功！";
	save(ph);
	return ph;
}
Host * System::buybook(Host * ph)							// 购买书籍 
{
	if(!search(ph,false)) return ph;
	int n;
	while (true)
	{
		cout << "\n请确认输入您需要购买书籍对应的编号（输入0返回）：";
		bool found = false;
		cin >> n;
		cin.clear();
		cin.sync();
		if (n == 0) return ph; 
		for (int i = 0; i < ph[0].Getcount(); i++)
			if (ph[i].Getnum() == n)
			{
				n = i;										// 记录编号所在的位置 
				found = true;
			}
		if (!found)
		{
			cout << "没有与之对应的书籍！请检查您的输入是否正确";
			Sleep(1000);
			continue;
		}
		else break;
	}
	int quantity;
	while (true)
	{
		cout << "\n请输入您需要购买书籍的本数（输入0返回）：";
		try
		{
			cin >> quantity;
			cin.sync();
			cin.clear();
			if (!cin || quantity > ph[n].Getquantity() || quantity < 0) throw quantity;
			ph[n].Getquantity(-quantity);
			if (ph[n].Getquantity() == 0) ph = del(ph,n+1);	// 删除中也有编号检测循环 
			break;
		}
		catch (int)
		{
			cout << "输入数值非法！请重新输入";
			Sleep(1500);
		}
	}
	cout << "购买成功！"; 
	save(ph,(char *)"SOLDBooklist(UTF-8).txt");
	return ph;
}
bool System::login(string ac, bool ishost)		// 登陆，读取二进制文件校验码判断正确性 
{
	int times = 0;								// 登陆次数 
	while (true)
	{
		Sleep(500);
		system("cls");
		Sleep(1000);
		char account[11], password[11];
		cout << "\n\n           ^^^^^^^^^^^^^^^^^^^^^ > 管理员登陆 < ^^^^^^^^^^^^^^^^^^^^^"
			 << "\n           |                                                        |"
			 << "\n           |     请输入您的账号与密码（不超过十位，输入exit返回）   |"
			 << "\n           |            （账号与密码只允许英文字母和数字）          |"
			 << "\n           |                                                        |"
			 << "\n           vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv"
			 << "\n\n                              账号：";
		char c;
		int count = 0;
		while (true)
		{
			c = getch();
			cin.clear();
			cin.sync();
			if (c != '\r' && c != '\t' && c != '\b')
			{
				if (count >= 10 || c == ' ' || !isalnum(c)) continue;
				account[count] = c;
				cout << account[count];
			}
			else if (c == '\b')					// 退格
			{
				if (count == 0) continue;
				cout << "\b \b";
				count-=2;
			}
			else								// 输入结束 
			{
				account[5] = '\0';
				break;
			}
			count++;
		}
		cin.clear();
		cin.sync();
		char * pe = new char[5];
		for (int i = 0; i < 4; i++) pe[i] = account[i];
		pe[4] = '\0';
		if (!strcmp(pe,"exit") || !strcmp(pe,"EXIT"))
		{
			delete []pe;
			return ishost;
		}
		delete []pe;
		try
		{
			cout << "\n                              密码：";
			count = 0;
			while (true)
			{
				c = getch();
				cin.clear();
				cin.sync();
				if (c != '\r' && c != '\t' && c != '\b')
				{
				if (count >= 10 || c == ' ' || !isalnum(c)) continue;
					password[count] = c;
					cout << "*";
				}
				else if (c == '\b')
				{
					if (count == 0) continue;
					cout << "\b \b";
					count-=2;
				}
				else
				{
					password[10] = '\0';
					break;
				}
				count++;
			}
			fstream bin("data.dat",ios::in|ios::binary);
			if (!bin) throw password;
			char * ps = new char[11];
			count = 0;
			for (int i = 0; i < 10; i++)
			{
				if (i % 2 == 0) count = i*i+3*i-4;
				else count = 2*i*i-3*i+1;
				bin.read(&ps[i],sizeof(char));
				ps[i] -= (T % 51) + count;
			}
			bin.close();
			ps[10] = '\0';
			if (strcmp(ps,password) || strcmp(account,ac.c_str())) throw -1;
			else
			{
				delete []ps;
				break;
			}
		}
		catch (int)
		{
			times++;
			if (times == 5)
			{
				cout << "\n                  您已超过五次未登录成功，系统将自动返回主菜单！";
				Sleep(1500);
				return false;
			}
			else cout << "\n                账号或密码有误！请重新输入（剩余登陆次数：" 
				 	  << 5 - times << " 次）";
			Sleep(1000);
			cin.clear();
			cin.sync();
		}
	}
	cout << "\n                          登陆成功！敲击任意键继续或返回";
	getch();
	ishost = true;
	cin.clear();
	cin.sync();
	return ishost;
}
unsigned int System::random(char * password)				// 密码加密并保存 
{
	int count = 0;
	T = time(NULL); 
	fstream bout("data.dat",ios::out|ios::binary);
	for (int i = 0; i < strlen(password); i++)
	{
		if (i % 2 == 0) count = i*i+3*i-4;
		else count = 2*i*i-3*i+1;
		password[i] += (T % 51) + count;
		bout.write(&password[i],sizeof(char));
	}
	bout.close();
	return T;
} 
void System::quit()											// 退出程序 
{
	cout << "感谢您的使用，再见！";
	Sleep(1000);
	system("cls");
	exit(0);
}
