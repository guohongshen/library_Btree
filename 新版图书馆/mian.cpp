#include"Library.h"

int main()
{
	cout << endl;
	cout << "\t\t��ӭ����ͼ���ϵͳ��" << endl;
	BTree H;
	Library R;
	char choose;
	R.read(H);
	while (1) {
		cout << endl;
		cout << endl;
		cout << "\t\t���������µİ�����ɲ�����" << endl;
		cout << endl;
		cout << "\t\t��1������" << endl;
		cout << "\t\t��2��ԤԼ" << endl;
		cout << "\t\t��3��ȡ��" << endl;
		cout << "\t\t��4������" << endl;
		cout << "\t\t��5�����ĳ����" << endl;
		cout << "\t\t��6������ĳ�����飨ͼ������д��飬ѡ�������������" << endl;
		cout << "\t\t��7������ĳ�����飨ͼ���Ŀǰδ�д��飩" << endl;
		cout << "\t\t��8���鿴ĳ�����״̬" << endl;
		cout << "\t\t��9�����뷨���" << endl;
		cout << "\t\t�����������˳�ϵͳ�������棩" << endl;
		cout << endl;
		cout << "\t\t���������";
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