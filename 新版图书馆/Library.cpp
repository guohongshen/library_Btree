#include"Library.h"

bool Library::read(BTree& y)
{
	cout << "\t\t��ʼ��ȡ......" << endl;
	char sign;//��־λ��$���飬%�����ģ�&��ԤԼ��
	Book* Book_temp = nullptr;//��������еġ�ĳһ���顱
	Appointment* Appointment_temp = nullptr;//��Զ��ĳһ����Ľ�����Ϣ��������һ��Ԫ��
	Borrow* Borrow_temp = nullptr;//��Զ��ǰ������С�ĳһ���顱��ԤԼ��Ϣ��������һ��Ԫ��
	/******/
	string Book_number_temp;//���
	string Book_name_temp;//����
	string Book_auther_temp;//����
	int Book_surplus_temp;//ʣ����
	int Book_total_temp;//�ܿ��
	/******/
	unsigned long long Borrow_ID_temp;//���������֤��
	string Borrow_name_temp;//����������
	string Borrow_Book_number_temp;//�������
	string Borrow_Book_name_temp;//��������
	//���Ŀ�ʼʱ�����£��ݶ��ɽ���1�£���
	int Borrow_year_temp;
	int Borrow_month_temp;
	int Borrow_day_temp;
	/******/
	unsigned long long Appointment_ID_temp;//���֤
	string Appointment_name_temp;//ԤԼ��
	string Appointment_number_temp;//ԤԼ���
	string Appointment_Book_name_temp;//ԤԼ����
	//ԤԼ��ʼʱ�����£�
	int Appointment_year_temp;
	int Appointment_month_temp;
	int Apppointment_day_temp;
	/******/

	ifstream inFile("Library.txt", ios_base::in);
	if (!inFile) {
		cout << "\t\tͼ��ݴ浵��ʧ��!�˳�����..." << endl;
		return false;
	}
	else if (inFile.eof()) {//��ע�⣺�������Ҫ�ٿ���
		cout << "\t\t�ļ�Ϊ�ա�" << endl;
		return false;
	}
	else {
		cout << "\t\t�ɹ���ͼ��ݴ浵..." << endl;
	}
	while (inFile.peek() != EOF)//��ע�⣺�������Ҫ�ٿ���
	{
		inFile >> sign;
		if (sign == '$') {//��
			inFile >> Book_number_temp;
			inFile >> Book_name_temp;
			inFile >> Book_auther_temp;
			inFile >> Book_surplus_temp;
			inFile >> Book_total_temp;
			Book_temp = new Book(Book_number_temp, Book_name_temp, Book_auther_temp, Book_surplus_temp, Book_total_temp);
			y.insert_page0(Book_number_temp, Book_temp);//����ż����Ӧ�Ĵ洢��ַ���뵽B���С�
			Appointment_temp = nullptr;//�ÿգ���������������жϲ��ܽ��С�
			Borrow_temp = nullptr;
		}
		else if (sign == '%') {//����
			inFile>>Borrow_ID_temp;//���������֤��
			inFile >> Borrow_name_temp;//����������
			inFile >> Borrow_Book_number_temp;//�������
			inFile >> Borrow_Book_name_temp;
			//���Ŀ�ʼʱ�����£��ݶ��ɽ���1�£���
			inFile >> Borrow_year_temp;
			inFile >> Borrow_month_temp;
			inFile >> Borrow_day_temp;
			if (Borrow_temp == nullptr) {//˵��֮ǰ���һ�ν������黹û���κν�����Ϣ
				Book_temp->Borrow_index = new Borrow(Borrow_ID_temp, Borrow_name_temp, Borrow_Book_number_temp, Borrow_Book_name_temp, Borrow_year_temp, Borrow_month_temp, Borrow_day_temp);
				Borrow_temp = Book_temp->Borrow_index;
			}
			else {//˵��֮ǰ���һ�ν��������н�����Ϣ
				Borrow_temp->next = new Borrow(Borrow_ID_temp, Borrow_name_temp, Borrow_Book_number_temp, Borrow_Book_name_temp, Borrow_year_temp, Borrow_month_temp, Borrow_day_temp);
				Borrow_temp = Borrow_temp->next;//��������β��
			}
		}
		else if (sign == '&') {//ԤԼ
			inFile >> Appointment_ID_temp;//���֤
			inFile >> Appointment_name_temp;//ԤԼ��
			inFile >> Appointment_number_temp;//ԤԼ���
			inFile >> Appointment_Book_name_temp;//ԤԼ����
			//ԤԼ��ʼʱ�����£�
			inFile >> Appointment_year_temp;
			inFile >> Appointment_month_temp;
			inFile >> Apppointment_day_temp;
			if (Appointment_temp == nullptr) {
				Book_temp->Appointment_index = new Appointment(Appointment_ID_temp, Appointment_name_temp, Appointment_number_temp, Appointment_Book_name_temp, Appointment_year_temp, Appointment_month_temp, Apppointment_day_temp);
				Appointment_temp = Book_temp->Appointment_index;
			}
			else {
				Appointment_temp->next = new Appointment(Appointment_ID_temp, Appointment_name_temp, Appointment_number_temp, Appointment_Book_name_temp, Appointment_year_temp, Appointment_month_temp, Apppointment_day_temp);
				Appointment_temp = Appointment_temp->next;
			}
		}
		else {//����
			cout << "�ļ������˳�......";
			exit(1);
		}
	}
	cout << endl;
	return true;
};
bool Library::borrow(BTree& y)
{
	int choose = -1;//���û������ı���
	string string_temp_0;//�����û��������ŵı���
	unsigned long long int_temp_0;//�����û���ID
	string string_temp_1;//�����û�������
	Book* Book_temp_0 = nullptr;//���յ�ַ�ı���
	Borrow* Borrow_temp_0 = nullptr;//����������Ϣ��ָ��
	cout << "��������Ҫ��ѯ����ţ�";
	cin >> string_temp_0;
	Book_temp_0 = y.search_return_index(string_temp_0);
	if (Book_temp_0 == nullptr) {
		cout << "��ѯʧ�ܣ������ڸ��飡";
		return false;
	}
	else {//�ҵ�����
		if (Book_temp_0->Book_surplus <= 0) {//�����޿��
			cout << "����̫���������ѱ��������Ƚ��꣡";
			return false;
		}
		else {//�����п��
			cout << "���롰1�����ɳɹ����ģ�";
			cin >> choose;
			if (choose == 1) {
				cout << "������Ҫ��¼����ظ�����Ϣ��" << endl;
				cout << "����������������";
				cin >> string_temp_1;
				cout << "�������������֤���룺";
				cin >> int_temp_0;
				time_t now = time(0);//��ȡ����
				struct tm ltm;//ʱ��ṹ��
				localtime_s(&ltm, &now);//ת����������
				cout <<"*"<< ltm.tm_year << endl;
				Borrow_temp_0 = Book_temp_0->Borrow_index;
				if (Borrow_temp_0 == nullptr) {
					Book_temp_0->Borrow_index = new Borrow(int_temp_0, string_temp_1, string_temp_0, Book_temp_0->Book_name, ltm.tm_year, ltm.tm_mon, ltm.tm_mday);
					Borrow_temp_0 = Book_temp_0->Borrow_index;
				}
				else {//��������н�����Ϣ���Ͳ��뵽��Ϣĩβ
					Borrow_temp_0 = Book_temp_0->Borrow_index;
					while (Borrow_temp_0->next != nullptr) {
						Borrow_temp_0 = Borrow_temp_0->next;
					}
					Borrow_temp_0->next = new Borrow(int_temp_0, string_temp_1, string_temp_0, Book_temp_0->Book_name, ltm.tm_year, ltm.tm_mon, ltm.tm_mday);
					Borrow_temp_0 = Borrow_temp_0->next;
				}
				Book_temp_0->Book_surplus--;//���¸���Ŀ��
				cout << "���ĳɹ���";
				cout << "�������ˡ�" << string_temp_1 << endl;
				cout << "�����֤���롿" << int_temp_0 << endl;
				cout << "������������" << Book_temp_0->Book_name << endl;
				cout << "������ʱ�䡿" << (1900 + ltm.tm_year) << "��" << 1 + ltm.tm_mon << "��" << ltm.tm_mday << "��" << endl;
				cout << "*******************************************************" << endl;
				cout << "��ܰ��ʾ������30�쵽�ݹ黹�����鼮�������������ٷ��1Ԫ/�죩��" << endl;
				return true;
			}
			else {
				cout << "����ʧ�ܣ������ԣ�";
				return false;
			}
		}
	}
};
bool Library::appointment(BTree& y)
{
	int choose = -1;//���û������ı���
	string string_temp_0;//�����û��������ŵı���
	unsigned long long int_temp_0;//�����û���ID
	string string_temp_1;//�����û�������
	Book* Book_temp = nullptr;//���յ�ַ�ı���
	Appointment* Appointment_temp_0 = nullptr;//����������Ϣ��ָ��
	cout << "��������Ҫ��ѯ����ţ�";
	cin >> string_temp_0;
	Book_temp = y.search_return_index(string_temp_0);
	if (Book_temp == nullptr) {
		cout << "��ѯʧ�ܣ������ڸ��飡";
		return false;
	}
	else {//�ҵ�����
		if (Book_temp->Book_surplus <= 0) {//�����޿��
			cout << "����̫���������ѱ��������Ƚ��꣡";
			return false;
		}
		else {//�����п��
			cout << "���롰1�����ɳɹ����ģ�";
			cin >> choose;
			if (choose == 1) {
				cout << "������Ҫ��¼����ظ�����Ϣ��" << endl;
				cout << "����������������";
				cin >> string_temp_1;
				cout << "�������������֤���룺";
				cin >> int_temp_0;
				time_t now = time(0);//��ȡ����
				struct tm ltm;//ʱ��ṹ��
				localtime_s(&ltm, &now);//ת����������
				Appointment_temp_0 = Book_temp->Appointment_index;
				if (Appointment_temp_0 == nullptr) {
					Book_temp->Appointment_index = new Appointment(int_temp_0, string_temp_1, string_temp_0, Book_temp->Book_name, ltm.tm_year, ltm.tm_mon, ltm.tm_mday);
					Appointment_temp_0 = Book_temp->Appointment_index;
				}
				else {//��������н�����Ϣ���Ͳ��뵽��Ϣĩβ
					Appointment_temp_0 = Book_temp->Appointment_index;
					while (Appointment_temp_0->next != nullptr) {
						Appointment_temp_0 = Appointment_temp_0->next;
					}
					Appointment_temp_0->next = new Appointment(int_temp_0, string_temp_1, string_temp_0, Book_temp->Book_name, ltm.tm_year, ltm.tm_mon, ltm.tm_mday);
					Appointment_temp_0 = Appointment_temp_0->next;
				}
				Book_temp->Book_surplus--;//���¸���Ŀ��
				cout << "ԤԼ�ɹ���";
				cout << "��ԤԼ�ˡ�" << string_temp_1 << endl;
				cout << "�����֤���롿" << int_temp_0 << endl;
				cout << "��ԤԼ������" << Book_temp->Book_name << endl;
				cout << "��ԤԼʱ�䡿" << (1900 + ltm.tm_year) << "��" << 1 + ltm.tm_mon << "��" << ltm.tm_mday << "��" << endl;
				cout << "*******************************************************" << endl;
				cout << "��ܰ��ʾ�������߸���������ȡ����ԤԼ�鼮������˴�ԤԼ����Ч��" << endl;
				return true;
			}
			else {
				cout << "ԤԼʧ�ܣ������ԣ�";
				return false;
			}
		}
	}
};
bool Library::take_book(BTree& y)
{
	short permission = 0;//�������������ֵ���鿴�Ƿ����ȡ�顣
	int timepass = 0;//����ʱ���ֵ���������ж��Ƿ����
	string book_number_temp;//��ʱ����������
	unsigned long long ID_temp;//�û������֤����
	Book* Book_temp = nullptr;//���յ�ַ�ı���
	Appointment* Appointment_temp_pr = nullptr;
	Appointment* Appointment_temp = nullptr;//����ԤԼ��Ϣ
	Borrow* Borrow_temp = nullptr;//����������Ϣ
	Appointment* delete_help = nullptr;//��æɾ��ĳ�����
	cout << "����������Ҫȡ����ţ�";
	cin >> book_number_temp;
	Book_temp = y.search_return_index(book_number_temp);
	if (Book_temp == nullptr) {
		cout << "δ������ȷ����ţ������ԣ�";
		return false;
	}
	else {
		cout << "�������������֤���룺";
		cin >> ID_temp;
		Appointment_temp_pr = Book_temp->Appointment_index;
		Appointment_temp = Book_temp->Appointment_index;
		while (Appointment_temp != nullptr) {
			if (Appointment_temp->Appointment_ID == ID_temp) {//�ҵ�ԤԼ��Ϣ�����ǲ鿴�Ƿ��ڣ�
				//time_t now = time(0);//��ȡ���ڵ�����
				//struct tm ltm;//ʱ��ṹ��
				//localtime_s(&ltm, &now);//ת����������
				time_t now = time(0);//��ȡ����
				struct tm ltm;//ʱ��ṹ��
				localtime_s(&ltm, &now);//ת����������
				if (ltm.tm_year = Appointment_temp->Appointment_year && ((ltm.tm_mon - Appointment_temp->Appointment_month) < 2) && (((ltm.tm_mon - Appointment_temp->Appointment_month) * 30) + ltm.tm_mday - Appointment_temp->Apppointment_day) < 8) {//���ʱ�䶼�Ϸ��Ļ����Ϳ���ȡ
					permission = 1;
					//���¾���ȡ��Ĺ��̣�
					cout << "���ҵ�ԤԼ��Ϣ......" << endl;
					cout << "����ȡ��......" << endl;
					//������ȡ�飺
					Borrow_temp = Book_temp->Borrow_index;
					ltm.tm_year = ltm.tm_year + 118;
					Book_temp->Borrow_index = new Borrow(Appointment_temp->Appointment_ID, Appointment_temp->Appointment_name, Appointment_temp->Appointment_number, Appointment_temp->Appointment_Book_name, ltm.tm_year, ltm.tm_mon, ltm.tm_mday);
					Book_temp->Borrow_index->next = Borrow_temp;//������
					//�����ǰ�ԤԼ��Ϣɾ����
					if (Appointment_temp->next != nullptr) {//��һ��ɾ�����
						Appointment_temp->Appointment_Book_name = Appointment_temp->next->Appointment_Book_name;
						Appointment_temp->Appointment_ID = Appointment_temp->next->Appointment_ID;
						Appointment_temp->Appointment_month = Appointment_temp->next->Appointment_month;
						Appointment_temp->Appointment_name = Appointment_temp->next->Appointment_name;
						Appointment_temp->Appointment_number = Appointment_temp->next->Appointment_number;
						Appointment_temp->Appointment_year = Appointment_temp->next->Appointment_year;
						Appointment_temp->Apppointment_day = Appointment_temp->next->Apppointment_day;
						delete_help = Appointment_temp->next;//ɾ��ָ���õ���Ҫɾ����ֵ
						Appointment_temp->next = Appointment_temp->next->next;//��ֵ����
						delete_help->next = nullptr;
						delete delete_help;
					}
					else {//�ڶ���ɾ�����
						if (Book_temp->Appointment_index == Appointment_temp) {
							delete_help = Appointment_temp;
							Book_temp->Appointment_index = nullptr;
							delete delete_help;
						}
						else {
							delete_help = Appointment_temp;
							Appointment_temp_pr->next = nullptr;
							delete delete_help;
						}
						//Appointment_temp_pr->next = nullptr;//ǰһ��ָ���ÿ�
						//delete_help = Appointment_temp;
						//delete delete_help;
					}
					cout << "ȡ��ɹ���" << endl;
					cout << "�����Դ��ߴ����ˣ�" << endl;
					return true;
				}
				else {
					permission = 0;
					if (Appointment_temp->next != nullptr) {//��һ��ɾ�����
						Appointment_temp->Appointment_Book_name = Appointment_temp->next->Appointment_Book_name;
						Appointment_temp->Appointment_ID = Appointment_temp->next->Appointment_ID;
						Appointment_temp->Appointment_month = Appointment_temp->next->Appointment_month;
						Appointment_temp->Appointment_name = Appointment_temp->next->Appointment_name;
						Appointment_temp->Appointment_number = Appointment_temp->next->Appointment_number;
						Appointment_temp->Appointment_year = Appointment_temp->next->Appointment_year;
						Appointment_temp->Apppointment_day = Appointment_temp->next->Apppointment_day;
						delete_help = Appointment_temp->next;//ɾ��ָ���õ���Ҫɾ����ֵ
						Appointment_temp->next = Appointment_temp->next->next;//��ֵ����
						delete_help->next = nullptr;
						delete delete_help;
					}
					else {//�ڶ���ɾ�����
						if (Book_temp->Appointment_index == Appointment_temp) {
							delete_help = Appointment_temp;
							Book_temp->Appointment_index = nullptr;
							delete delete_help;
						}
						else {
							delete_help = Appointment_temp;
							Appointment_temp_pr->next = nullptr;
							delete delete_help;
						}
					}
					Book_temp->Book_surplus++;//���Ȿ�����
				}
			}
			else {//ʲô������
				//permission = 0;
			}
			Appointment_temp_pr = Appointment_temp;
			Appointment_temp = Appointment_temp->next;//ѭ��
		}
		if (permission == 0) {//����δԤԼ�鼮����ȥȡ�飬һ�����ܳɹ���
			cout << "δ�ҵ���ص�ԤԼ��Ϣ ���� ��δ��ָ��������ȡ�������鼮�ѵ���ԤԼʧ��......" << endl;
			cout << "ȡ��ʧ��......" << endl;
			return false;
		}
	}
};
bool Library::return_book(BTree& y)
{
	short permission = 0;//�ж��Ƿ���Ի���
	int timepass = 0;//����ʱ���ֵ���������ж��Ƿ�������η���
	int money = 0;//����
	unsigned long long ID_temp;//�û������֤����
	string book_number_temp;//�����û���������
	Book* Book_temp = nullptr;//���յ�ַ�ı���
	Borrow* Borrow_temp_pr = nullptr;
	Borrow* Borrow_temp = nullptr;//����������Ϣ
	Borrow* delete_help = nullptr;//ɾ��ָ��
	cout << "�����������黹��ĺ��룺";
	cin >> book_number_temp;
	Book_temp = y.search_return_index(book_number_temp);
	if (Book_temp == nullptr) {
		cout << "δ������ȷ����ţ������ԣ�";
		return false;
	}
	else {
		cout << "�������������֤���룺";
		cin >> ID_temp;
		Borrow_temp_pr = Book_temp->Borrow_index;
		Borrow_temp = Book_temp->Borrow_index;
		while(Borrow_temp!=nullptr){
			if (Borrow_temp->Borrow_ID == ID_temp) {
				permission = 1;//�ҵ���Ϣ
				time_t now = time(0);//��ȡ���ڵ�����
				struct tm ltm;//ʱ��ṹ��
				localtime_s(&ltm, &now);//ת����������
				timepass = (ltm.tm_year - Borrow_temp->Borrow_year) * 365 - (ltm.tm_mon - Borrow_temp->Borrow_month) * 30 - ltm.tm_mday + Borrow_temp->Borrow_day;//�ܹ�����������
				money = timepass - 30;
				if (money > 0) {//��Ҫ���
					if (Borrow_temp->next != nullptr) {
						delete_help = Borrow_temp->next;
						Borrow_temp->Borrow_Book_name = delete_help->Borrow_Book_name;
						Borrow_temp->Borrow_Book_number = delete_help->Borrow_Book_number;
						Borrow_temp->Borrow_day = delete_help->Borrow_day;
						Borrow_temp->Borrow_ID = delete_help->Borrow_ID;
						Borrow_temp->Borrow_month = delete_help->Borrow_month;
						Borrow_temp->Borrow_name = delete_help->Borrow_name;
						Borrow_temp->Borrow_year = delete_help->Borrow_year;
						Borrow_temp->next = delete_help->next;
						delete_help->next = nullptr;
						delete delete_help;
					}
					else {
						if (Book_temp->Borrow_index == Borrow_temp) {
							delete_help = Borrow_temp;
							Book_temp->Borrow_index = nullptr;
							delete delete_help;
						}
						else {
							delete_help = Borrow_temp;
							Borrow_temp_pr->next = nullptr;
							delete delete_help;
						}
					}
					Book_temp->Book_surplus++;//�������
					cout << "�ѹ黹��" << endl;
					cout << "���������Ѿ����ڣ����Է��" << money << "Ԫ" << endl;
					cout << "�뵽��̨����֧��������" << endl;
					return true;
				}
				else {//���÷��
					if (Borrow_temp->next != nullptr) {
						delete_help = Borrow_temp->next;
						Borrow_temp->Borrow_Book_name = delete_help->Borrow_Book_name;
						Borrow_temp->Borrow_Book_number = delete_help->Borrow_Book_number;
						Borrow_temp->Borrow_day = delete_help->Borrow_day;
						Borrow_temp->Borrow_ID = delete_help->Borrow_ID;
						Borrow_temp->Borrow_month = delete_help->Borrow_month;
						Borrow_temp->Borrow_name = delete_help->Borrow_name;
						Borrow_temp->Borrow_year = delete_help->Borrow_year;
						Borrow_temp->next = delete_help->next;
						delete_help->next = nullptr;
						delete delete_help;
					}
					else {
						if (Book_temp->Borrow_index == Borrow_temp) {
							delete_help = Borrow_temp;
							Book_temp->Borrow_index = nullptr;
							delete delete_help;
						}
						else {
							delete_help = Borrow_temp;
							Borrow_temp_pr->next = nullptr;
							delete delete_help;
						}
					}
					Book_temp->Book_surplus++;//�������
					cout << "�ѳɹ��黹��" << endl;
					cout << "��ӭ�����ٴι��٣�" << endl;
					return true;
				}
			}
			else {//ʲôҲ����
			}
			Borrow_temp_pr = Borrow_temp;
			Borrow_temp = Borrow_temp->next;
		}
		if (permission == 0) {
			cout << "δ�ҵ������Ϣ������ʧ�ܣ������ԣ�" << endl;
			cout << "��˶���Ϣ���鿴�Ƿ��������" << endl;
			return false;
		}
	}
};
bool Library::throw_book(BTree& y)
{
	short permission = 0;//��־�Ƿ��������Ȿ��
	string book_number_temp;//���չ���Ա��������
	Book* Book_temp = nullptr;//���յ�ַ�ı���
	cout << "����������Ҫ��յ���ĺ��룺";
	cin >> book_number_temp;
	Book_temp = y.search_return_index(book_number_temp);
	if (Book_temp == nullptr) {
		cout << "δ������ȷ����ţ������ԣ�";
		return false;
	}
	else {
		if (Book_temp->Appointment_index == nullptr && Book_temp->Borrow_index == nullptr) {
			cout << "������ձ���......" << endl;
			y.delete_page00(book_number_temp);
			delete Book_temp;
			return true;
		}
		else {
			cout << "���ʧ�ܣ������治�㣡���н����������ԤԼ����";
			return false;
		}
	}
};
bool Library::add_book(BTree& y)
{
	short permission = 0;//��־�Ƿ���������Ȿ��
	string book_number_temp;//���չ���Ա��������
	Book* Book_temp = nullptr;//���յ�ַ�ı���
	cout << "����������Ҫ���ӵ���ĺ��룺";
	cin >> book_number_temp;
	Book_temp = y.search_return_index(book_number_temp);
	if (Book_temp == nullptr) {
		cout << "δ������ȷ����ţ������ԣ�";
		return false;
	}
	else {
		cout << "�����������......" << endl;
		Book_temp->Book_surplus++;
		Book_temp->Book_total++;
		cout << "���������" << endl;
		return true;
	}
};
bool Library::add_new_book(BTree& y)
{
	Book* Book_temp = nullptr;
	string Book_number_temp;//���
	string Book_name_temp;//����
	string Book_auther_temp;//����
	int Book_surplus_temp;//ʣ����
	int Book_total_temp;//�ܿ��
	cout << "��������Ҫ�����µ���ţ�";
	cin >> Book_number_temp;
	Book_temp = y.search_return_index(Book_number_temp);
	if (Book_temp != nullptr) {
		cout << "�����Ѵ��ڴ��飡";
		cout << "�����ԣ�";
		return false;
	}
	else {
		cout << "������������";
		cin >> Book_name_temp;
		cout << "���������ߣ�";
		cin >> Book_auther_temp;
		cout << "Ͷ��������";
		cin >> Book_total_temp;
		Book_surplus_temp = Book_total_temp;
		Book_temp = new Book(Book_number_temp, Book_name_temp, Book_auther_temp, Book_surplus_temp, Book_total_temp);
		y.insert_page0(Book_number_temp, Book_temp);
		Book_temp = nullptr;
		cout << "��ӳɹ���";
		return true;
	}
};
bool Library::browse_book(BTree& y)
{
	Book* Book_temp = nullptr;
	Borrow* Borrow_temp = nullptr;
	Appointment* Appointment_temp = nullptr;
	string Book_number_temp;
	cout << "��������Ҫ�鿴�������ţ�";
	cin >> Book_number_temp;
	Book_temp = y.search_return_index(Book_number_temp);
	if (Book_temp == nullptr) {
		cout << "���ݲ����ڴ��飡�����ԣ�";
		return false;
	}
	else {
		cout << "���£�" << endl;
		cout << "����š�" << Book_temp->Book_number << endl;
		cout << "��������" << Book_temp->Book_name << endl;
		cout << "�����ߡ�" << Book_temp->Book_auther << endl;
		cout << "���ֿ�桿" << Book_temp->Book_surplus <<"��"<< endl;
		cout << "���ܿ�桿" << Book_temp->Book_total <<"��"<< endl;
		Borrow_temp = Book_temp->Borrow_index;
		Appointment_temp = Book_temp->Appointment_index;
		if (Borrow_temp != nullptr) {
			cout << endl;
			cout << "������Ϣ���£�" << endl;
			while (Borrow_temp != nullptr) {
				cout << "�����������֤���롿" << Borrow_temp->Borrow_ID << endl;
				cout << "��������������" << Borrow_temp->Borrow_name << endl;
				cout << "���������ڡ�" << 1900 + Borrow_temp->Borrow_year << "��" << 1 + Borrow_temp->Borrow_month << "��" << Borrow_temp->Borrow_day << "��" << endl;
				cout << endl;
				Borrow_temp = Borrow_temp->next;
			}
		}
		else{}
		if (Appointment_temp != nullptr) {
			cout << endl;
			cout << "ԤԼ��Ϣ���£�" << endl;
			while (Appointment_temp != nullptr) {
				cout << "��ԤԼ�����֤���롿" << Appointment_temp->Appointment_ID << endl;
				cout << "��ԤԼ��������" << Appointment_temp->Appointment_name << endl;
				cout << "��ԤԼ���ڡ�" << 1900 + Appointment_temp->Appointment_year<<"��"<< 1 + Appointment_temp->Appointment_month <<"��"<< Appointment_temp->Apppointment_day<<"��" << endl;
				cout << endl;
				Appointment_temp = Appointment_temp->next;
			}
		}
		else{}
		return true;
	}
};