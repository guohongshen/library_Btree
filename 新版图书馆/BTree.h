#include"struct.h"

//��������ʽ��BTree
//����������ʽ���»���ʽ
struct BTree_Node {//B�����Ķ���
	int key_number;//��㵱ǰ�ؼ��ָ���
	KeyType key[m + 1];//�ؼ������飬key[0]δ�á������m-1���ؼ��֣�key[m]���塣
	BTree_Node* parent;//˫�׽��ָ��
	BTree_Node* childs[m + 1];//���ӽ��ָ������,�����m�����ӣ�childs[m]����
	Book* index[m + 1];	/*Record*/
	BTree_Node() {//���캯��
		key_number = 0;
		parent = nullptr;
		for (int i = 0;i < m + 1;i++)
		{
			childs[i] = nullptr;
			index[i] = nullptr;
		}
	}
};
struct result {//B���Ĳ��ҽ��-�ṹ�嶨��
	BTree_Node* got;//ָ���ҵ���������㣨B����㣩
	int i;//1<=i<=m,�ڽ���еĹؼ���λ��
	int tag;//1�����ҳɹ���0������ʧ��
};
class BTree {
private:
	BTree_Node* BTree_Node_root;//�������ĸ�
	result answer;//�������õı���
public:
	BTree();
	~BTree() {};
	//�����������£�
	int search_location(string& x, BTree_Node*& y);//�õ�λ��
	void search(string& x);//������������֮������&������Ϊ�����û�����ģ�
	Book* search_return_index(string& x);//����������������ַ�ĺ�����������Ϊ��ӭ��Library�������
	//���뺯�����£�
	void insert_page0(string x, Book* y);//���뺯����CORRECT��
	void produce_new_root(BTree_Node* p, string x, BTree_Node* z, Book* book);
	void insert_page_1(string& x, BTree_Node*& y, int z, Book* v);//��CORRECT��
	void insert_page_2(BTree_Node*& y, int i, string& x, BTree_Node* v, Book* book);
	void insert_split(BTree_Node*& y, int center, BTree_Node*& z);
	//ɾ���������£�
	void delete_page00(string x);//ɾ�����������º�̺�������һ����ֻ������Ҫ�������ѡ�
	void delete_page0();//ɾ�����棺����delete_page1()����
	void delete_page1(BTree_Node*& y, int i);//ɾ������������ɾ�������һϵ�к��������£�
	void delete_successor(BTree_Node*& y, int i);//��̼�λ����
	void delete_remove(BTree_Node*& y, int i);//ɾ�����ڹؼ��ּ��ϱ�Ե�Ĺؼ��ֵĺ���
	void delete_restore(BTree_Node*& y);//���ܣ����ڸոն�y������С�ؼ���ɾ������ʱ�ؼ��ָ������㣬B����Ҫ������
	//��ӡ�������£�
	void print_page();
	void print(BTree_Node* y);
	void print_aoru_page();
	void print_aoru(BTree_Node* y,const int height);
	//�˳������溯�����£�
	bool keep_exit();
	bool write(BTree_Node* y,ofstream& outFile);
};