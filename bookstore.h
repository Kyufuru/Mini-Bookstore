using namespace std;
class B
{
	public:
		B();														// 初始化 
	protected:
		int num;													// 书籍编号
		string name;												// 书籍名称
		string sort;												// 书籍分类
		string author;												// 书籍作者
		int quantity;												// 书籍数量
		double price;												// 书籍价格 
		double origin;												// 书籍成本
		bool newbook;												// 是否新书(0:N 1:Y)
		double discount;											// 书籍折扣(0为不打折)
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
		void savebook(char * line);									// 保存书籍
		void Renum()												// 修改编号
		{
			cin >> num;
			if (num <= 0 || !cin) throw -1;
		}
		void Rename(){ cin >> name; }								// 修改书名
		void Reauthor(){ cin >> author; }							// 修改作者 
		void Resort(){ cin >> sort; }								// 修改类别 
		void Requantity()											// 修改数量
		{
			cin >> quantity;
			if (quantity < 0 || !cin) throw -1;
		}
		void Reprice()												// 修改价格
		{
			cin >> price;
			if (price <= 0 || !cin) throw -1;
		}
		void Reorigin()												// 修改成本
		{
			cin >> origin;
			if (origin <= 0 || !cin) throw -1;
		}
		void Renewbook()											// 修改新书
		{
			cin >> newbook;
			if (!cin) throw -1;
		}
		void Rediscount()											// 修改折扣
		{
			cin >> discount;
			if (discount >= 1 || discount < 0 || !cin) throw -1;
		}  															// 添加/修改/删除通知
		static void Reinform(char * info = (char *)""){ inf.assign(info); }
		int Getnum(){ return num; }									// 获得编号
		string Getsort(){ return sort;}								// 获得类别
		string Getname(){ return name; }							// 获得书名
		string Getauthor(){ return author; }						// 获得作者
		int Getquantity(int n = 0)									// 获得/累计数量 
		{
			quantity += n;
			return quantity;
		}
		double Getprice(){ return price; }							// 获得价格
		double Getorigin(){ return origin; }						// 获得成本
		bool Getnew(){ return newbook; }							// 获得新书
		double Getdiscount(){ return discount; }					// 获得折扣 
		static int Getcount(int n = 0)								// 获得/累计长度
		{
			count += n;
			return count;
		}
		static void Countzero(){ count = 0; }						// 长度归零
		static string Getinform(){ return inf; }					// 获得通知 
		friend istream & operator >>(istream & in, Host & h);
		friend ostream & operator <<(ostream & out, Host & h);
		friend bool operator ==(Host & ph, Host & nph);
	protected:
		static string inf;											// 通知
		static int count;											// 长度 
};
class System
{
	public:
		Host * menu(Host * ph = NULL, bool ishost = true);			// 主菜单界面(ishost判断是否为管理员)
		void showmenu(bool ishost);									// 显示主菜单界面 
		void info();												// 显示说明信息
		Host * check(Host * h, bool ishost = true);									// 检查书单是否为空
		Host * load(Host * ph, bool ishost = true);									// 加载书目
		void save(Host * ph, char * line = (char *)"SAVEBooklist(UTF-8).txt");		// 保存书目
		Host * view(Host * ph, bool ishost = true);									// 选择查看书单的方式
		Host * orderview(Host * ph, bool ishost = true);							// 按号排序并输出书单
		Host * sortview(Host * ph, bool ishost = true);								// 按类输出书单
		Host * nameview(Host * ph, bool ishost = true);								// 按名首字母输出书单 
		Host * search(Host * ph, bool ishost = true);								// 查询书籍子菜单
		Host * search(Host * ph, int num, bool ishost = true);						// 按号查询 
		Host * search(Host * ph, string namesort, int flag, bool ishost = true);	// 按名/类查询
		Host * search(Host * ph, bool isnew, bool ishost);							// 新书查询
		Host * search(Host * ph, double isdiscount, bool ishost); 					// 查看打折书籍
		// 注：为防止二义性，新书和打折书查询的函数参数ishost不设缺省值 
		void quit();																// 退出程序
		Host * addbook(Host * ph);									// 添加书籍
		Host * delbook(Host * ph);									// 删除书籍子菜单
		Host * del(Host * ph, int num);								// 按号删除书籍
		Host * del(Host * ph, string name);							// 按名删除书籍
		Host * reverse(Host * ph);									// 修改书籍
		void soldlist(Host * ph);									// 销售清单 
		Host * inform(Host * ph);									// 添加/修改/删除通知
		Host * buybook(Host * ph);									// 购买书籍
		bool login(string ac, bool ishost);							// 登录界面
		unsigned int random(char * password);						// 密码加密			 
};
