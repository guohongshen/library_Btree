#include"struct.h"

//类命名方式：BTree
//函数命名方式：下划线式
struct BTree_Node {//B树结点的定义
	int key_number;//结点当前关键字个数
	KeyType key[m + 1];//关键字数组，key[0]未用。最多有m-1个关键字，key[m]缓冲。
	BTree_Node* parent;//双亲结点指针
	BTree_Node* childs[m + 1];//孩子结点指针数组,最多有m个孩子，childs[m]缓冲
	Book* index[m + 1];	/*Record*/
	BTree_Node() {//构造函数
		key_number = 0;
		parent = nullptr;
		for (int i = 0;i < m + 1;i++)
		{
			childs[i] = nullptr;
			index[i] = nullptr;
		}
	}
};
struct result {//B树的查找结果-结构体定义
	BTree_Node* got;//指向找到的索引结点（B树结点）
	int i;//1<=i<=m,在结点中的关键字位序
	int tag;//1：查找成功，0：查找失败
};
class BTree {
private:
	BTree_Node* BTree_Node_root;//索引树的根
	result answer;//查找所用的变量
public:
	BTree();
	~BTree() {};
	//搜索函数如下：
	int search_location(string& x, BTree_Node*& y);//得到位置
	void search(string& x);//搜索函数：（之所以用&，是因为这是用户输入的）
	Book* search_return_index(string& x);//搜索并返回索引地址的函数：纯粹是为了迎合Library类的需求。
	//插入函数如下：
	void insert_page0(string x, Book* y);//插入函数【CORRECT】
	void produce_new_root(BTree_Node* p, string x, BTree_Node* z, Book* book);
	void insert_page_1(string& x, BTree_Node*& y, int z, Book* v);//【CORRECT】
	void insert_page_2(BTree_Node*& y, int i, string& x, BTree_Node* v, Book* book);
	void insert_split(BTree_Node*& y, int center, BTree_Node*& z);
	//删除函数如下：
	void delete_page00(string x);//删除函数：和下后继函数功能一样，只不过需要参数而已。
	void delete_page0();//删除界面：调用delete_page1()函数
	void delete_page1(BTree_Node*& y, int i);//删除函数：调用删除所需的一系列函数，如下：
	void delete_successor(BTree_Node*& y, int i);//后继即位函数
	void delete_remove(BTree_Node*& y, int i);//删除处于关键字集合边缘的关键字的函数
	void delete_restore(BTree_Node*& y);//功能：由于刚刚对y做过最小关键字删除，此时关键字个数不足，B树需要调整。
	//打印函数如下：
	void print_page();
	void print(BTree_Node* y);
	void print_aoru_page();
	void print_aoru(BTree_Node* y,const int height);
	//退出并保存函数如下：
	bool keep_exit();
	bool write(BTree_Node* y,ofstream& outFile);
};