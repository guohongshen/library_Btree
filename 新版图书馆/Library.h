#include"BTree.h"

class Library {//ͼ�������
private:
	//Book* Book_root = nullptr;������B��������Ҫ������ࡿ
	//Appointment* Appointment_root = nullptr;��ע��������
	//Borrow* Borrow_root = nullptr;��ע��������
public:
	Library() {};
	~Library() {};//
	bool read(BTree& y);//���ļ�
	bool borrow(BTree& y);//����
	bool appointment(BTree& y);//ԤԼ
	bool take_book(BTree& y);//ȡ��
	bool return_book(BTree& y);//����
	bool throw_book(BTree& y);//���ĳһ����
	bool add_book(BTree& y);//����һ�����е���
	bool add_new_book(BTree& y);//����һ�ױ���û�е���
	bool browse_book(BTree& y);//�鿴ĳһ�����״̬
};