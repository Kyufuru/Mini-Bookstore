using namespace std;
class B
{
	public:
		B();														// ��ʼ�� 
	protected:
		int num;													// �鼮���
		string name;												// �鼮����
		string sort;												// �鼮����
		string author;												// �鼮����
		int quantity;												// �鼮����
		double price;												// �鼮�۸� 
		double origin;												// �鼮�ɱ�
		bool newbook;												// �Ƿ�����(0:N 1:Y)
		double discount;											// �鼮�ۿ�(0Ϊ������)
};
class Guest: public B
{
	public:
		friend ostream & operator <<(ostream & out, Guest & g); 
};
class Host: public Guest 
{
	public:
		Host(){ count++; } 
		void savebook(char * line);									// �����鼮
		void Renum()												// �޸ı��
		{
			cin >> num;
			if (num <= 0 || !cin) throw -1;
		}
		void Rename(){ cin >> name; }								// �޸�����
		void Reauthor(){ cin >> author; }							// �޸����� 
		void Resort(){ cin >> sort; }								// �޸���� 
		void Requantity()											// �޸�����
		{
			cin >> quantity;
			if (quantity < 0 || !cin) throw -1;
		}
		void Reprice()												// �޸ļ۸�
		{
			cin >> price;
			if (price <= 0 || !cin) throw -1;
		}
		void Reorigin()												// �޸ĳɱ�
		{
			cin >> origin;
			if (origin <= 0 || !cin) throw -1;
		}
		void Renewbook()											// �޸�����
		{
			cin >> newbook;
			if (!cin) throw -1;
		}
		void Rediscount()											// �޸��ۿ�
		{
			cin >> discount;
			if (discount >= 1 || discount < 0 || !cin) throw -1;
		}  															// ���/�޸�/ɾ��֪ͨ
		static void Reinform(char * info = (char *)""){ inf.assign(info); }
		int Getnum(){ return num; }									// ��ñ��
		string Getsort(){ return sort;}								// ������
		string Getname(){ return name; }							// �������
		string Getauthor(){ return author; }						// �������
		int Getquantity(int n = 0)									// ���/�ۼ����� 
		{
			quantity += n;
			return quantity;
		}
		double Getprice(){ return price; }							// ��ü۸�
		double Getorigin(){ return origin; }						// ��óɱ�
		bool Getnew(){ return newbook; }							// �������
		double Getdiscount(){ return discount; }					// ����ۿ� 
		static int Getcount(int n = 0)								// ���/�ۼƳ���
		{
			count += n;
			return count;
		}
		static void Countzero(){ count = 0; }						// ���ȹ���
		static string Getinform(){ return inf; }					// ���֪ͨ 
		friend istream & operator >>(istream & in, Host & h);
		friend ostream & operator <<(ostream & out, Host & h);
		friend bool operator ==(Host & ph, Host & nph);
	protected:
		static string inf;											// ֪ͨ
		static int count;											// ���� 
};
class System
{
	public:
		Host * menu(Host * ph = NULL, bool ishost = true);			// ���˵�����(ishost�ж��Ƿ�Ϊ����Ա)
		void showmenu(bool ishost);									// ��ʾ���˵����� 
		void info();												// ��ʾ˵����Ϣ
		Host * check(Host * h, bool ishost = true);									// ����鵥�Ƿ�Ϊ��
		Host * load(Host * ph, bool ishost = true);									// ������Ŀ
		void save(Host * ph, char * line = (char *)"SAVEBooklist(UTF-8).txt");		// ������Ŀ
		Host * view(Host * ph, bool ishost = true);									// ѡ��鿴�鵥�ķ�ʽ
		Host * orderview(Host * ph, bool ishost = true);							// ������������鵥
		Host * sortview(Host * ph, bool ishost = true);								// ��������鵥
		Host * nameview(Host * ph, bool ishost = true);								// ��������ĸ����鵥 
		Host * search(Host * ph, bool ishost = true);								// ��ѯ�鼮�Ӳ˵�
		Host * search(Host * ph, int num, bool ishost = true);						// ���Ų�ѯ 
		Host * search(Host * ph, string namesort, int flag, bool ishost = true);	// ����/���ѯ
		Host * search(Host * ph, bool isnew, bool ishost);							// �����ѯ
		Host * search(Host * ph, double isdiscount, bool ishost); 					// �鿴�����鼮
		// ע��Ϊ��ֹ�����ԣ�����ʹ������ѯ�ĺ�������ishost����ȱʡֵ 
		void quit();																// �˳�����
		Host * addbook(Host * ph);									// ����鼮
		Host * delbook(Host * ph);									// ɾ���鼮�Ӳ˵�
		Host * del(Host * ph, int num);								// ����ɾ���鼮
		Host * del(Host * ph, string name);							// ����ɾ���鼮
		Host * reverse(Host * ph);									// �޸��鼮
		void soldlist(Host * ph);									// �����嵥 
		Host * inform(Host * ph);									// ���/�޸�/ɾ��֪ͨ
		Host * buybook(Host * ph);									// �����鼮
		bool login(string ac, bool ishost);							// ��¼����
		unsigned int random(char * password);						// �������			 
};
