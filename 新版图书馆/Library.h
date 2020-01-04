#include"BTree.h"

class Library {//图书管理类
private:
	//Book* Book_root = nullptr;【基于B树，不需要另外的类】
	//Appointment* Appointment_root = nullptr;【注：废弃】
	//Borrow* Borrow_root = nullptr;【注：废弃】
public:
	Library() {};
	~Library() {};//
	bool read(BTree& y);//读文件
	bool borrow(BTree& y);//借书
	bool appointment(BTree& y);//预约
	bool take_book(BTree& y);//取书
	bool return_book(BTree& y);//还书
	bool throw_book(BTree& y);//清除某一本书
	bool add_book(BTree& y);//增加一本已有的书
	bool add_new_book(BTree& y);//增加一套本馆没有的书
	bool browse_book(BTree& y);//查看某一本书的状态
};