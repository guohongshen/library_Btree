#include"Library.h"

int main()
{
	cout << endl;
	cout << "\t\t欢迎来到图书馆系统！" << endl;
	BTree H;
	Library R;
	char choose;
	R.read(H);
	while (1) {
		cout << endl;
		cout << endl;
		cout << "\t\t请输入以下的按键完成操作：" << endl;
		cout << endl;
		cout << "\t\t【1】借阅" << endl;
		cout << "\t\t【2】预约" << endl;
		cout << "\t\t【3】取书" << endl;
		cout << "\t\t【4】还书" << endl;
		cout << "\t\t【5】清空某本书" << endl;
		cout << "\t\t【6】增添某本旧书（图书馆已有此书，选择可增加数量）" << endl;
		cout << "\t\t【7】增添某本新书（图书馆目前未有此书）" << endl;
		cout << "\t\t【8】查看某本书的状态" << endl;
		cout << "\t\t【9】凹入法输出" << endl;
		cout << "\t\t【其他键】退出系统（不保存）" << endl;
		cout << endl;
		cout << "\t\t请输入键：";
		cin >> choose;
		system("cls");
		switch (choose) {
		case '1': {
			R.borrow(H);
			break;
		}
		case '2': {
			R.appointment(H);
			break;
		}
		case '3': {
			R.take_book(H);
			break;
		}
		case '4': {
			R.return_book(H);
			break;
		}
		case '5':{
			R.throw_book(H);
			break;
		}
		case '6':{
			R.add_book(H);
			break;
		}
		case '7': {
			R.add_new_book(H);
			break;
		}
		case '8': {
			R.browse_book(H);
			break;
		}
		case '9': {
			H.print_aoru_page();
			break;
		}
		default: {
			return 0;
		}
		}
		system("pause");
		system("cls");
	}
	return 0;
};