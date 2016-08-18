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
	name = sort = author = "��";
	newbook = false;
}
ostream & operator <<(ostream & out, Guest & g)
{
	out << fixed << setprecision(2)
		<< "��ţ�" << g.num << endl
		<< "���ƣ�" << g.name;
	if (g.newbook == 1) cout << "���¡�";
	out << endl
		<< "���ࣺ" << g.sort << endl 
		<< "���ߣ�" << g.author << endl << "������" << g.quantity << " ��" << endl 
		<< "�۸�";
	if (g.discount != 0) out << g.price * g.discount << " Ԫ��" << g.discount*10 << "�ۡ�";
	else out << g.price << " Ԫ";
	out << endl;
	return out;
} 
void Host::savebook(char * line)								// �����鼮
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
		<< "��ţ�" << h.num << endl
		<< "���ƣ�" << h.name;
	if (h.newbook == 1) cout << "���¡�";
	out	<< endl
		<< "���ࣺ" << h.sort << endl 
		<< "���ߣ�" << h.author << endl << "������" << h.quantity << " ��" << endl 
		<< "�۸�";
	if (h.discount != 0) out << h.price * h.discount << " Ԫ��" << h.discount*10 << "�ۡ�";
	else out << h.price << " Ԫ";
	out << endl << "�ɱ���" << h.origin << " Ԫ" << endl;
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
		 << endl << "+		   	      ��ӭ����������ϵͳ			      +"
		 << endl << "+		   	       ��ѡ������Ҫ�Ĺ���			      +"
		 << endl << "+									      +"
		 << endl << "+		  1. �鿴�鼮�嵥              2. ��ѯ�鼮		      +";
	if (not ishost)
		cout << endl << "+		  3. �����鼮	               4. ����Ա��¼		      +"
		 	 << endl << "+		  5. �˳�ϵͳ		      				      +";
	else
		cout << endl << "+		  3. �����鼮�嵥	       4. ����鼮		      +"
			 << endl << "+		  5. ɾ���鼮	               6. �޸��鼮��Ϣ		      +"
			 << endl << "+		  7. �鿴������ͳ��	       8. ���/�޸�/ɾ��֪ͨ          +"
			 << endl << "+		  9. �˳���¼		      10. �˳�ϵͳ                    +";
	cout << endl << "+									      +"
		 << endl << "+								       ver1.5 +" << endl;
  	for (int i = 0; i < 79; i++) cout << "=";
  	cout << endl;
  	for (int i = 0; i < 40; i++) cout << "=#";
}
Host * System::menu(Host * ph, bool ishost)					// ���˵�����
{															// ishost�ж��Ƿ�Ϊ����Ա��Ĭ��Ϊtrue 
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
  		cout << endl << "����ѡ��";
  		int choice = 0;
  		cin.sync();											// ������ǰ����ö�ʹ��һ����ջ����������� 
  		cin.clear();										// ���⻺�����������ݣ����ѭ�� 
  		cin >> choice;
  		cin.sync();
  		cin.clear();
  		if (not ishost)										// �û����� 
  			switch (choice)
  			{
  				case 1:
				  	{
				  		ph = view(ph,ishost);				// �鿴�鵥 
				  		break;
				  	}
				case 2:
					{
						ph = search(ph,ishost);				// ��ѯ�鼮 
						break;
					}
				case 3:
					{
						ph = buybook(ph);					// �����鼮 
						break; 
					} 
				case 4:
					{
						ishost = login("admin",ishost);		// ��¼���� 
						break; 
					} 
				case 5: quit();								// �˳�ϵͳ 
				default: throw choice;
			}
		else												// ������� 
		  	switch (choice)
  			{
  				case 1:
					{
				  		ph = view(ph,ishost);				// �鿴�鵥 
				  		break;
					}
				case 2:
					{
						ph = search(ph,ishost);				// ��ѯ�鼮 
						break;
					}
				case 3:
					{
						ph = load(ph);						// ������Ŀ�ļ� 
						break;
					}
				case 4:
					{
						ph = addbook(ph);					// ����鼮 
						break;
					}
				case 5:
					{
						ph = delbook(ph);					// ɾ���鼮 
						break;
					} 
  				case 6:
  					{
  						ph = reverse(ph);					// �޸��鼮 
  						break;
					}
				case 7:
					{
						soldlist(ph);						// �����嵥��ͳ�� 
						break;
					} 
				case 8:
					{
						ph = inform(ph);					// �޸�֪ͨ 
						break;
					}
				case 9:
					{
						cout << "\n���ѳɹ��˳���¼���û�����������򷵻�";
						getch();
						cin.clear();
						cin.sync();
						ishost = false;
						break;
					}
				case 10: quit();							// �˳�ϵͳ 
				default:
					{
						cout << "�����ѡ��Ƿ��������ԣ�";
						Sleep(1500);
						cin.sync();
  						cin.clear();
  						break;
					}
			}
	}
	return ph;
}
Host * System::check(Host *ph, bool ishost)					// ����鵥�Ƿ�Ϊ�գ��������鵥ָ�� 
{	
	Sleep(500);
	if (!ph)
	{
		cout << endl << "û���鵥��Ϣ��";
		Sleep(1000);
		while (true)
		{
			try
			{
				if (ishost) cout << endl << "�Ƿ���ļ������鵥����Y/N����";
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
				cout << "�����ѡ��Ƿ��������ԣ�";
				Sleep(1500);
				cin.sync();
  				cin.clear();
			}
		}
	}
	else return ph; 
}
Host * System::load(Host * ph, bool ishost)					// ������Ŀ
{
	char * line = new char[MAXLEN];
	int n = 0;												// n��¼�ı�����
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
				cout << "\n�Ҳ�����" << line << "�����������˵�";
				Sleep(1500);
				fin.close();
				return ph; 
			}
			else
			{
				cout << "\n�����Զ�����Ĭ���鵥...\n";
				Sleep(500);
				break;
			}
		}
		char choice;
		cout << "\n�Ƿ����Ĭ���ļ�����Y/N/E���أ���";
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
					cout << "\n�Ҳ�����" << line << "�����������˵�";
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
						cout << "\n��������Ҫ��ȡ���ļ�����������׺������exit�˳�����";
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
								cout << "�Ҳ�����" << line << "���������ԣ�";
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
	for (int i = 0; i < 5; i++) fin.getline(line,MAXLEN);	// ����ǰ���е���Ŀ˵����Ϣ
	while(!fin.eof())
	{ 
		fin.getline(line,MAXLEN);
		n++;
	}
	//cout << n << endl;									// ���Ե� 1 
	fin.seekg(0);
	fin.clear();
	if (ph != NULL)
	{
		ph[0].Countzero(); 
		delete []ph;										// �ͷ��ϴζ�̬����Ŀռ�
		Host * ph;
	}
	ph = new Host[n];
	for (int i = 0; i < 5; i++) fin.getline(line,MAXLEN);
	try
	{								
		for (int i = 0; i < n; i++)
		{
			fin >> ph[i];
			//cout << ph[i] << endl;						// ���Ե� 2 
			if (fin.fail()) throw i+1;
			fin.getline(line,MAXLEN);
		}
	}
	catch (int num)
	{
		cout << "���ݸ�ʽ�����������鵥�б��Ϊ " << num << " �����ݣ�";
		Sleep(1500);
		ph = NULL;
		fin.close();
		delete []line;
		return ph;
	}
	fin.close();
	delete []line; 
	cout << "�����鵥�ɹ����û���������ػ�������û�v���鿴�鵥��";
	if (toupper(getchar()) == 'V') view(ph);
	save(ph);
	return ph;
}
void System::save(Host * ph, char * line)					// ������Ŀ���ı� 
{
	ofstream fout;
	if (!ph)
	{
		fout.open(line,ios::out);							// �鵥Ϊ������ձ����ļ� 
		if (!fout) throw line;
		cout << "\n�鵥���Զ����浽��" << line << "���У��û���������ػ����";
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
	fout << "��ʹ��˵����\n"
		 << "һ���밴�ա���š����顢�鼮���ơ����ࡢ���ߡ��������۸񡢳ɱ����ۿۡ�"
		 << "��˳���������ݣ�����֮�����á�Tab�����򡰿ո񡱸���\n"
		 << "����ÿ�����ݲ��ð������ո񡱡���Tab�����͡�Enter������"
		 << "�����������ַ�ϵͳ���ᱨ��ָ�����������鼮���\n"
		 << "�������飺�Ƿ�Ϊ���顣��1��Ϊ�ǣ���0��Ϊ���ۿۣ���0��Ϊ�����ۣ��ۿ���0��1֮���С����ʾ\n"
		 << "���\t����\t�鼮����\t����\t����\t����/��\t�۸�/Ԫ\t�ɱ�/Ԫ\t�ۿ�";
	fout.close();
	try
	{
		for(int i = 0; i < ph[0].Getcount(); i++)
	 	{
			ph[i].savebook(line);
			//cout << ph[i];								// ���Ե� 3
		}
	}
	catch (int n)
	{
		cout << "���ݸ�ʽ�����������鵥�б��Ϊ " << n << " �����ݣ�";
		cin.clear();
		cin.sync();
		Sleep(1500);
		return;
	}
	cout << "\n�鵥���Զ����浽��" << line << "���У��û���������ػ����";
	getch();
	cin.clear();
	cin.sync();
} 

Host * System::view(Host * ph, bool ishost)					// �鿴�鵥�Ӳ˵� 
{
	if(!check(ph,ishost)) return ph;
	cout << "-------------------------------------\n"
		 << "      ��ϣ�������ַ�ʽ�鿴�鵥��\n\n"
		 << "   1.�����˳��鿴  2.������鿴\n"
		 << "   3.������˳��鿴  4.�������˵�\n"
		 << "-------------------------------------\n";
	int choice;
	while (true)
	{
		cout << "\n����ѡ��"; 
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
			cout << "�����ѡ��Ƿ��������ԣ�";
			Sleep(1500);
		}
	}
}
Host * System::orderview(Host * ph, bool ishost)			// ������������鵥 
{
	if(!check(ph,ishost)) return ph; 
	Sleep(500);
	system("cls");
	Sleep(500);
	Host temp = ph[0];										// **�¶����ʼ����ʱ�򳤶Ȳ����ۼ�** 
	for (int i = 0; i < ph[0].Getcount()-1; i++) 			// �������� 
	{
		//cout << i << endl;								// ���Ե� 4 
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
	cout << "�û���������ػ����";
	getch();
	cin.sync();
	cin.clear();
	return ph;
}
Host * System::sortview(Host * ph, bool ishost)				// ��������鵥
{
	if(!check(ph,ishost)) return ph; 
	Sleep(500);
	system("cls");
	Sleep(1000);
	string sort[ph[0].Getcount()];							// ����鼮���� 
	for (int i = 0, j = 0; i < ph[0].Getcount() && j < ph[0].Getcount(); i++, j++)
	{														// �������� 
		sort[i] = ph[j].Getsort();
		for (int k = 0; k < i; k++)
			if (sort[k] == sort[i]) i--; 
	}
	int i = 0;
	while (sort[i] != "")									// ��������鵥 
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
	cout << "�û���������ػ����";
	getch();
	cin.sync();
	cin.clear();
	return ph;
}
Host * System::nameview(Host * ph, bool ishost)				// ��������ĸ���
{
	if(!check(ph,ishost)) return ph; 
	Sleep(500);
	system("cls");
	Sleep(1000);
	Host temp = ph[0];										// **�¶����ʼ����ʱ�򳤶Ȳ����ۼ�** 
	for (int i = 0; i < ph[0].Getcount()-1; i++) 			// �������� 
	{
		//cout << i << endl;								// ���Ե� 5 
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
	cout << "�û���������ػ����";
	getch();
	cin.sync();
	cin.clear();
	return ph;
} 
Host * System::search(Host * ph, bool ishost)				// ��ѯ�鼮�Ӳ˵�
{
	if(!check(ph,ishost)) return ph;
	orderview(ph);
	cout << "\n\n#X#X#X#X#X#X#X#X#X#X# ��ѡ���ѯ��ʽ #X#X#X#X#X#X#X#X#X#X#\n"
		 << "\n         1.����Ų���  2.����������  3.�����߲���"
		 << "\n   4.���������  5.�鿴����  6.�鿴������  7.�������˵�\n"
		 << "\n##########################################################\n";
	int choice;
	while (true)
	{
		cout << "\n����ѡ��"; 
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
						cout << "�������ţ�";
						cin >> num;
						cin.clear();
						cin.sync();
						ph = search(ph,num,ishost);
						return ph;
					}
				case 2:
					{
						string name;
						cout << "������������";
						cin >> name;
						cin.clear();
						cin.sync();
						ph = search(ph,name,1,ishost);
						return ph;
					}
				case 3:
					{
						string author;
						cout << "���������ߣ�";
						cin >> author;
						cin.clear();
						cin.sync();
						ph = search(ph,author,3,ishost);
						return ph;
					}
				case 4:
					{
						string sort;
						cout << "���������";
						cin >> sort;
						cin.clear();
						cin.sync();
						ph = search(ph,sort,2,ishost);
						return ph;
					}
				case 5:
					{
						ph = search(ph,true,ishost);		// �鿴���� 
						return ph;
					}
				case 6:
					{
						ph = search(ph,0.0,ishost);			// �鿴������ 
						return ph;
					}
				case 7: menu(ph,ishost); 
				default: throw choice;
			}
		}
		catch (int)
		{
			cout << "�����ѡ��Ƿ��������ԣ�";
			Sleep(1500);
		}
	}
}
Host * System::search(Host * ph, int num, bool ishost)		// ���Ų�ѯ
{
	if(!check(ph,ishost)) return ph;
	system("cls");
	Sleep(500);
	bool found = false;
	cout << "\n\t\t\t\t  �������\n\n";
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
	if (!found) cout << "\nû�з���Ҫ������������\n";
	Sleep(500);
	cout << "\n�û���������ػ����";
	getch();
	cin.clear();
	cin.sync();
	return ph;
} 
Host * System::search(Host * ph, string namesortauthor, int flag, bool ishost)
															// ����/��/���߲�ѯ
{
	if(!check(ph,ishost)) return ph;
	system("cls");
	Sleep(500);
	bool found = false;
	cout << "\n\t\t\t\t  �������\n\n";
	for (int i = 0; i < 79; i++) cout << "*";
	cout << endl;
	if (flag == 1)											// ������ѯ
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
	else if (flag == 2)										// �����ѯ
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
	else if (flag == 3)										// �����߲�ѯ
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
	if (!found) cout << "\nû�з���Ҫ������������\n";
	Sleep(500);
	cout << "\n�û���������ػ����";
	getch();
	cin.clear();
	cin.sync();
	return ph;
}
Host * System::search(Host * ph, bool isnew, bool ishost)	// �鿴����
{
	if(!check(ph,ishost)) return ph;
	system("cls");
	Sleep(500);
	bool found = false;
	cout << "\n\t\t\t\t  �������\n\n";
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
	else													// �鿴���飨Ԥ�����ܣ� 
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
	if (!found) cout << "\nû�з���Ҫ������������\n";
	Sleep(500);
	cout << "\n�û���������ػ����";
	getch();
	cin.clear();
	cin.sync();
	return ph;
}
Host * System::search(Host * ph, double isdiscount, bool ishost)
															// �鿴�����鼮 
{
	if(!check(ph,ishost)) return ph;
	system("cls");
	Sleep(500);
	bool found = false;
	cout << "\n\t\t\t\t  �������\n\n";
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
	else													// �鿴�������鼮��Ԥ�����ܣ� 
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
	if (!found) cout << "\nû�з���Ҫ������������\n";
	Sleep(500);
	cout << "\n�û���������ػ����";
	getch();
	cin.clear();
	cin.sync();
	return ph; 
}
Host * System::addbook(Host * ph)							// ����鼮
{
	if(!check(ph)) return ph;
	int length;
	Host * nph; 
	system("cls");
	Sleep(300);
	cout << "��ʹ��˵����\n"
	 	 << "һ���밴�ա���š����顢�鼮���ơ����ࡢ���ߡ��������۸񡢳ɱ����ۿۡ�\n"
	 	 << "    ��˳���������ݣ�����֮�����á�Tab�����򡰿ո񡱸���\n"
	 	 << "�������Ϊ0��ʾ�������\n"
	 	 << "�������飺�Ƿ�Ϊ���顣��1��Ϊ�ǣ���0��Ϊ���ۿۣ���0��Ϊ������\n"
		 << "    �ۿ���0��1֮���С����ʾ\n"
	 	 << "������������������������������������������������������������������������������\n"
		 << "���	����	�鼮����	����	����	����	�۸�	�ɱ�	�ۿ�\n";
	length = ph[0].Getcount();								// ����ԭ���� 
	while(true)
	{
		ph[0].Countzero();									// ���ȹ��������ۼ� 
		nph = new Host[length+1];
		for (int i = 0; i < length; i++)
		{	if (ph[i].Getnum() == ph[length-1].Getnum() && ph[i].Getname() != ph[length-1].Getname())
			{												// ����ظ���ͻ�쳣��� 
				cout << "������󣡲�ͬ�鼮���Ӧ��ͬ��������������鼮��\n";
				ph[0].Getcount(-1);							// ph��ֻ��length����λ�ڴ�ռ䣡 
				ph = del(ph,ph[length-1].Getname());
				ph[0].Getcount(1);							// ������ԭ(��Ϊ��del�������Ѿ�-1��)
				length--;									// ����ph���� 
				Sleep(1500);
			} 
			//cout << ph[i] << endl;						// ���Ե� 6 
			nph[i] = ph[i];
		}
		try
		{ cin >> nph[length]; }
		catch (int n)
		{
			cout << "���ݸ�ʽ�����������鵥�б��Ϊ " << n << " �����ݣ�";
			cin.clear();
			cin.sync();
			Sleep(1500);
			return ph;
		}
		cin.clear();
		cin.sync();
		if (nph[length].Getnum() == 0)
		{
			nph[length].Getcount(-1); 						// ����0ʱ�����ۼ�
			//cout << ph[0].Getcount() << endl;				// ���Ե� 7 
			break; 
		} 
		ph = nph;
		length = ph[0].Getcount();							// ����nph���� 
	}
	for (int i = 0; i < length; i++)
	{
		for (int j = i - 1; j >= 0; j--)					// ����ͬһ���� 
			if (nph[j] == nph[i])
			{
				nph[i].Getquantity(nph[j].Getquantity());	// �ۼ��鱾���� 
				nph = del(nph,nph[j].Getnum());
				length--;
			}
	}
	delete []ph;
	save(nph);
	return nph;
}
Host * System::delbook(Host * ph)							// ɾ���鼮�Ӳ˵� 
{
	if(!check(ph)) return ph;
	int length;
	Host * nph; 
	length = ph[0].Getcount();								// ����ԭ���� 
	orderview(ph);
	cout << "\n>>>>>>>> ��ѡ��ɾ����ʽ <<<<<<<<\n"
		 << "\n>  1.�����ɾ��  2.������ɾ��  <\n"
		 << "\n================================\n";
	int choice;
	while (true)
	{
		cout << "\n����ѡ��"; 
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
						cout << "�������ţ����������ûس����������0����ɾ������";
						while (true)
						{
							cin >> num;
							cin.clear();
							cin.sync();
							if (num == 0)
							{
								cout << "\nɾ���ɹ���";
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
						cout << "���������������������ûس����������0����ɾ������";
						cin >> name;
						cin.clear();
						cin.sync();
						if (name == "0")
							{
								cout << "\nɾ���ɹ���";
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
			cout << "�����ѡ��Ƿ��������ԣ�";
			Sleep(1500);
		}
	}
}
Host * System::del(Host * ph, int num)						// ����ɾ���鼮
{
	for (int i = 0; i < ph[0].Getcount(); i++)
	{
		if (num == ph[i].Getnum())
		{
			ph[0].Getcount(-1);
			if (ph[0].Getcount() == 0)						// ɾ���� 
			{
				cout << "\n�鵥��ȫ��ɾ����";
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
Host * System::del(Host * ph, string name)					// ����ɾ���鼮
{
	for (int i = 0; i < ph[0].Getcount(); i++)
		if (name == ph[i].Getname())
		{
			ph[0].Getcount(-1);
			if (ph[0].Getcount() == 0)						// ɾ���� 
			{
				cout << "\n�鵥��ȫ��ɾ����";
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
Host * System::reverse(Host * ph)							// �޸��鼮
{
	if(!search(ph)) return ph;
	int n;
	while (true)
	{
		cout << "\n��ȷ����������Ҫ�޸��鼮��Ӧ�ı�ţ�����0���أ���";
		bool found = false;
		cin >> n;
		cin.clear();
		cin.sync();
		if (n == 0) return ph; 
		for (int i = 0; i < ph[0].Getcount(); i++)
			if (ph[i].Getnum() == n)
			{
				n = i;										// ��¼������ڵ�λ�� 
				found = true;
			}
		if (!found)
		{
			cout << "û����֮��Ӧ���鼮���������������Ƿ���ȷ";
			Sleep(1000);
		}
		else break;
	}
	cout << "\n%%%%%%%%%%%%%%%%% �����޸���һ����Ϣ��%%%%%%%%%%%%%%%%%\n"
		 << "\n        1.���  2.����  3.���  4.����  5.����\n"
		 << "   6.�۸�  7.�ɱ�  8.����  9.�ۿ�  10.ȫ��  0.����\n"
		 << "\n%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n";
	int choice;
	while (true)
	{
		try
		{
			cout << "\n����ѡ��";
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
							cout << "�������µı�ţ�";
							ph[n].Renum();					// �����ĳ�0�൱��ɾ���鼮 
							if (ph[n].Getquantity() == 0) del(ph,n);
							cin.clear();
							cin.sync();
							for (int i = 0; i < ph[0].Getcount(); i++)
								if (ph[i].Getnum() == ph[n].Getnum() && ph[i].Getname() != ph[n].Getname())
								{							// ����ظ���ͻ�쳣���
									same = true;
									ph[n] = temp;
									cout << "������󣡲�ͬ�鼮���Ӧ��ͬ�����������룡\n";
									Sleep(1500);
								}
						}
						break;
					}
				case 2:
					{
						cout << "�������µ�������";
						ph[n].Rename();
						cin.clear();
						cin.sync();
						break;
					}
				case 3:
					{
						cout << "�������µ����";
						ph[n].Resort();
						cin.clear();
						cin.sync();
						break;
					}
				case 4:
					{
						cout << "�������µ����ߣ�";
						ph[n].Reauthor();
						cin.clear();
						cin.sync();
						break;
					}
				case 5:
					{
						cout << "�������µ�������";
						ph[n].Requantity();
						cin.clear();
						cin.sync();
						break;
					}
				case 6:
					{
						cout << "�������µļ۸�";
						ph[n].Reprice();
						cin.clear();
						cin.sync();
						break;
					}
				case 7:
					{
						double origin;
						cout << "�������µĳɱ���";
						cin >> origin;
						cin.clear();
						cin.sync();
						ph[n].Reorigin();
						break;
					}
				case 8:
					{
						cout << "�������������ã�1Ϊ���飬0Ϊ�����飩��";
						ph[n].Renewbook();
						cin.clear();
						cin.sync();
						break;
					} 
				case 9:
					{
						cout << "�������µ��ۿۣ���0-1֮���С����ʾ��0��ʾ�����ۣ���";
						ph[n].Rediscount();
						cin.clear();
						cin.sync();
						break;
					}
				case 10:
					{
						cout << "������������Ϣ(ȫΪ0ʱ����)\n"
							 << "\n������������������������������������������������������������������������������\n"
		 					 << "���	����	�鼮����	����	����	����	�۸�	�ɱ�	�ۿ�\n";
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
								{							// ����ظ���ͻ�쳣���
									same = true;
									ph[n] = temp;
									cout << "������󣡲�ͬ�鼮���Ӧ��ͬ�����������룡\n";
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
						cout << "\n�޸ĳɹ���";
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
			cout << "�����ѡ������ݷǷ��������ԣ�";
			cin.clear();
			cin.sync();
			Sleep(1500);
		}
	}
}
void System::soldlist(Host * ph)							// �鿴�����嵥�����
{
	if(!check(ph,true)) return;
	Host * sph = ph; 
	char line[MAXLEN];
	strcpy(line,"SAVEBooklist(UTF-8).txt");
	int n = 0, m = sph[0].Getcount();						// n��¼ԭʼ�ı�����, m��¼������Ŀ���� 
	ifstream fin;
	fin.open(line);
	if (fin.fail()) throw line;
	for (int i = 0; i < 5; i++) fin.getline(line,MAXLEN);	// ����ǰ���е���Ŀ˵����Ϣ
	while(!fin.eof())
	{
		fin.getline(line,MAXLEN);
		n++;
	}
	//cout << n << endl;									// ���Ե� 8 
	fin.seekg(0);
	fin.clear();
	ph = new Host[n];
	for (int i = 0; i < 5; i++) fin.getline(line,MAXLEN);
	try
	{								
		for (int i = 0; i < n; i++)
		{
			fin >> ph[i];
			//cout << ph[i] << endl;						// ���Ե� 9 
			if (fin.fail()) throw i+1;
			fin.getline(line,MAXLEN);
		}
	}
	catch (int num)
	{
		cout << "���ݸ�ʽ����������ԭʼ�����ļ��б��Ϊ " << num << " �����ݣ�";
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
	cout << "      $$$$$$$$$$$$$$$$$$$$$$$$$$$$  �����嵥  $$$$$$$$$$$$$$$$$$$$$$$$$$$$\n\n";
	bool found = false;
	double total = 0; 
	cout << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++) 
			if (ph[i].Getnum() == sph[j].Getnum()) ph[i].Getquantity(-sph[i].Getquantity());
		if (ph[i].Getquantity() == 0) continue;			// û����
		else
		{
			found = true;
			cout << "��ţ�" << ph[i].Getnum() << endl
				 << "���ƣ�" << ph[i].Getname() << endl
				 << "���ࣺ" << ph[i].Getsort() << endl
				 << "���ߣ�" << ph[i].Getauthor() << endl
				 << "������" << ph[i].Getquantity() << endl
				 << "������" << ph[i].Getprice() - ph[i].Getorigin() << endl
				 << "������" << ph[i].Getquantity() * (ph[i].Getprice() - ph[i].Getorigin()) << endl
				 << endl << "---------------------------------------\n\n";
			total += ph[i].Getquantity() * (ph[i].Getprice() - ph[i].Getorigin());
		}
	}
	ph[0].Countzero();
	ph[0].Getcount(m);
	if (not found)
	{
		cout << "\nû�б����۵��鼮��";
		cout << "\n�û�����������򷵻�"; 
		getch();
		cin.clear();
		cin.sync();
	}
	else
	{
		cout << "�ܼ�ӯ����" << total << endl;
		Sleep(500);
		save(ph,(char *)"SOLDBooklist(UTF-8).txt");
	}
	delete []ph;
}
Host * System::inform(Host * ph)							// ���/�޸�/ɾ��֪ͨ
{
	char * pc = new char[3*MAXLEN];
	cout << "\n�������µ�֪ͨ����'#'��������ֻ����'#'��ɾ��֪ͨ����\n";
	cin.getline(pc,3*MAXLEN,'#');
	cin.clear();
	cin.sync();
	ph[0].Reinform(pc);
	delete []pc;
	cout << "\n�޸ĳɹ���";
	save(ph);
	return ph;
}
Host * System::buybook(Host * ph)							// �����鼮 
{
	if(!search(ph,false)) return ph;
	int n;
	while (true)
	{
		cout << "\n��ȷ����������Ҫ�����鼮��Ӧ�ı�ţ�����0���أ���";
		bool found = false;
		cin >> n;
		cin.clear();
		cin.sync();
		if (n == 0) return ph; 
		for (int i = 0; i < ph[0].Getcount(); i++)
			if (ph[i].Getnum() == n)
			{
				n = i;										// ��¼������ڵ�λ�� 
				found = true;
			}
		if (!found)
		{
			cout << "û����֮��Ӧ���鼮���������������Ƿ���ȷ";
			Sleep(1000);
			continue;
		}
		else break;
	}
	int quantity;
	while (true)
	{
		cout << "\n����������Ҫ�����鼮�ı���������0���أ���";
		try
		{
			cin >> quantity;
			cin.sync();
			cin.clear();
			if (!cin || quantity > ph[n].Getquantity() || quantity < 0) throw quantity;
			ph[n].Getquantity(-quantity);
			if (ph[n].Getquantity() == 0) ph = del(ph,n+1);	// ɾ����Ҳ�б�ż��ѭ�� 
			break;
		}
		catch (int)
		{
			cout << "������ֵ�Ƿ�������������";
			Sleep(1500);
		}
	}
	cout << "����ɹ���"; 
	save(ph,(char *)"SOLDBooklist(UTF-8).txt");
	return ph;
}
bool System::login(string ac, bool ishost)		// ��½����ȡ�������ļ�У�����ж���ȷ�� 
{
	int times = 0;								// ��½���� 
	while (true)
	{
		Sleep(500);
		system("cls");
		Sleep(1000);
		char account[11], password[11];
		cout << "\n\n           ^^^^^^^^^^^^^^^^^^^^^ > ����Ա��½ < ^^^^^^^^^^^^^^^^^^^^^"
			 << "\n           |                                                        |"
			 << "\n           |     �����������˺������루������ʮλ������exit���أ�   |"
			 << "\n           |            ���˺�������ֻ����Ӣ����ĸ�����֣�          |"
			 << "\n           |                                                        |"
			 << "\n           vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv"
			 << "\n\n                              �˺ţ�";
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
			else if (c == '\b')					// �˸�
			{
				if (count == 0) continue;
				cout << "\b \b";
				count-=2;
			}
			else								// ������� 
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
			cout << "\n                              ���룺";
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
				cout << "\n                  ���ѳ������δ��¼�ɹ���ϵͳ���Զ��������˵���";
				Sleep(1500);
				return false;
			}
			else cout << "\n                �˺Ż������������������루ʣ���½������" 
				 	  << 5 - times << " �Σ�";
			Sleep(1000);
			cin.clear();
			cin.sync();
		}
	}
	cout << "\n                          ��½�ɹ����û�����������򷵻�";
	getch();
	ishost = true;
	cin.clear();
	cin.sync();
	return ishost;
}
unsigned int System::random(char * password)				// ������ܲ����� 
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
void System::quit()											// �˳����� 
{
	cout << "��л����ʹ�ã��ټ���";
	Sleep(1000);
	system("cls");
	exit(0);
}
