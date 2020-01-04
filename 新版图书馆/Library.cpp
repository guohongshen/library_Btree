#include"Library.h"

bool Library::read(BTree& y)
{
	cout << "\t\t开始读取......" << endl;
	char sign;//标志位【$：书，%：借阅，&：预约】
	Book* Book_temp = nullptr;//后继语句的中的“某一本书”
	Appointment* Appointment_temp = nullptr;//永远是某一本书的借阅信息链表的最后一个元素
	Borrow* Borrow_temp = nullptr;//永远是前驱语句中“某一本书”的预约信息链表的最后一个元素
	/******/
	string Book_number_temp;//书号
	string Book_name_temp;//书名
	string Book_auther_temp;//作者
	int Book_surplus_temp;//剩余量
	int Book_total_temp;//总库存
	/******/
	unsigned long long Borrow_ID_temp;//借书人身份证号
	string Borrow_name_temp;//借书人姓名
	string Borrow_Book_number_temp;//所借书号
	string Borrow_Book_name_temp;//所借书名
	//借阅开始时间如下（暂定可借阅1月）：
	int Borrow_year_temp;
	int Borrow_month_temp;
	int Borrow_day_temp;
	/******/
	unsigned long long Appointment_ID_temp;//身份证
	string Appointment_name_temp;//预约人
	string Appointment_number_temp;//预约书号
	string Appointment_Book_name_temp;//预约书名
	//预约开始时间如下：
	int Appointment_year_temp;
	int Appointment_month_temp;
	int Apppointment_day_temp;
	/******/

	ifstream inFile("Library.txt", ios_base::in);
	if (!inFile) {
		cout << "\t\t图书馆存档打开失败!退出程序..." << endl;
		return false;
	}
	else if (inFile.eof()) {//【注意：这儿还需要再看】
		cout << "\t\t文件为空。" << endl;
		return false;
	}
	else {
		cout << "\t\t成功打开图书馆存档..." << endl;
	}
	while (inFile.peek() != EOF)//【注意：这儿还需要再看】
	{
		inFile >> sign;
		if (sign == '$') {//书
			inFile >> Book_number_temp;
			inFile >> Book_name_temp;
			inFile >> Book_auther_temp;
			inFile >> Book_surplus_temp;
			inFile >> Book_total_temp;
			Book_temp = new Book(Book_number_temp, Book_name_temp, Book_auther_temp, Book_surplus_temp, Book_total_temp);
			y.insert_page0(Book_number_temp, Book_temp);//将书号及其对应的存储地址插入到B树中。
			Appointment_temp = nullptr;//置空，这样下面的条件判断才能进行。
			Borrow_temp = nullptr;
		}
		else if (sign == '%') {//借阅
			inFile>>Borrow_ID_temp;//借书人身份证号
			inFile >> Borrow_name_temp;//借书人姓名
			inFile >> Borrow_Book_number_temp;//所借书号
			inFile >> Borrow_Book_name_temp;
			//借阅开始时间如下（暂定可借阅1月）：
			inFile >> Borrow_year_temp;
			inFile >> Borrow_month_temp;
			inFile >> Borrow_day_temp;
			if (Borrow_temp == nullptr) {//说明之前最后一次进来的书还没有任何借阅信息
				Book_temp->Borrow_index = new Borrow(Borrow_ID_temp, Borrow_name_temp, Borrow_Book_number_temp, Borrow_Book_name_temp, Borrow_year_temp, Borrow_month_temp, Borrow_day_temp);
				Borrow_temp = Book_temp->Borrow_index;
			}
			else {//说明之前最后一次进来的书有借阅信息
				Borrow_temp->next = new Borrow(Borrow_ID_temp, Borrow_name_temp, Borrow_Book_number_temp, Borrow_Book_name_temp, Borrow_year_temp, Borrow_month_temp, Borrow_day_temp);
				Borrow_temp = Borrow_temp->next;//更新链表尾部
			}
		}
		else if (sign == '&') {//预约
			inFile >> Appointment_ID_temp;//身份证
			inFile >> Appointment_name_temp;//预约人
			inFile >> Appointment_number_temp;//预约书号
			inFile >> Appointment_Book_name_temp;//预约书名
			//预约开始时间如下：
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
		else {//错误
			cout << "文件有误，退出......";
			exit(1);
		}
	}
	cout << endl;
	return true;
};
bool Library::borrow(BTree& y)
{
	int choose = -1;//和用户交互的变量
	string string_temp_0;//接收用户输入的书号的变量
	unsigned long long int_temp_0;//接收用户的ID
	string string_temp_1;//接收用户的名字
	Book* Book_temp_0 = nullptr;//接收地址的变量
	Borrow* Borrow_temp_0 = nullptr;//遍历借阅信息的指针
	cout << "请输入需要查询的书号：";
	cin >> string_temp_0;
	Book_temp_0 = y.search_return_index(string_temp_0);
	if (Book_temp_0 == nullptr) {
		cout << "查询失败，不存在该书！";
		return false;
	}
	else {//找到该书
		if (Book_temp_0->Book_surplus <= 0) {//该书无库存
			cout << "阁下太慢，该书已被别人抢先借完！";
			return false;
		}
		else {//该书有库存
			cout << "输入“1”即可成功借阅！";
			cin >> choose;
			if (choose == 1) {
				cout << "下面需要您录入相关个人信息：" << endl;
				cout << "请输入您的姓名：";
				cin >> string_temp_1;
				cout << "请输入您的身份证号码：";
				cin >> int_temp_0;
				time_t now = time(0);//获取秒数
				struct tm ltm;//时间结构体
				localtime_s(&ltm, &now);//转换成年月日
				cout <<"*"<< ltm.tm_year << endl;
				Borrow_temp_0 = Book_temp_0->Borrow_index;
				if (Borrow_temp_0 == nullptr) {
					Book_temp_0->Borrow_index = new Borrow(int_temp_0, string_temp_1, string_temp_0, Book_temp_0->Book_name, ltm.tm_year, ltm.tm_mon, ltm.tm_mday);
					Borrow_temp_0 = Book_temp_0->Borrow_index;
				}
				else {//如果该书有借阅信息，就插入到信息末尾
					Borrow_temp_0 = Book_temp_0->Borrow_index;
					while (Borrow_temp_0->next != nullptr) {
						Borrow_temp_0 = Borrow_temp_0->next;
					}
					Borrow_temp_0->next = new Borrow(int_temp_0, string_temp_1, string_temp_0, Book_temp_0->Book_name, ltm.tm_year, ltm.tm_mon, ltm.tm_mday);
					Borrow_temp_0 = Borrow_temp_0->next;
				}
				Book_temp_0->Book_surplus--;//更新该书的库存
				cout << "借阅成功！";
				cout << "【借阅人】" << string_temp_1 << endl;
				cout << "【身份证号码】" << int_temp_0 << endl;
				cout << "【借阅书名】" << Book_temp_0->Book_name << endl;
				cout << "【借阅时间】" << (1900 + ltm.tm_year) << "年" << 1 + ltm.tm_mon << "月" << ltm.tm_mday << "日" << endl;
				cout << "*******************************************************" << endl;
				cout << "温馨提示：请在30天到馆归还所借书籍！否则您将面临罚款（1元/天）！" << endl;
				return true;
			}
			else {
				cout << "借阅失败！请重试！";
				return false;
			}
		}
	}
};
bool Library::appointment(BTree& y)
{
	int choose = -1;//和用户交互的变量
	string string_temp_0;//接收用户输入的书号的变量
	unsigned long long int_temp_0;//接收用户的ID
	string string_temp_1;//接收用户的名字
	Book* Book_temp = nullptr;//接收地址的变量
	Appointment* Appointment_temp_0 = nullptr;//遍历借阅信息的指针
	cout << "请输入需要查询的书号：";
	cin >> string_temp_0;
	Book_temp = y.search_return_index(string_temp_0);
	if (Book_temp == nullptr) {
		cout << "查询失败，不存在该书！";
		return false;
	}
	else {//找到该书
		if (Book_temp->Book_surplus <= 0) {//该书无库存
			cout << "阁下太慢，该书已被别人抢先借完！";
			return false;
		}
		else {//该书有库存
			cout << "输入“1”即可成功借阅！";
			cin >> choose;
			if (choose == 1) {
				cout << "下面需要您录入相关个人信息：" << endl;
				cout << "请输入您的姓名：";
				cin >> string_temp_1;
				cout << "请输入您的身份证号码：";
				cin >> int_temp_0;
				time_t now = time(0);//获取秒数
				struct tm ltm;//时间结构体
				localtime_s(&ltm, &now);//转换成年月日
				Appointment_temp_0 = Book_temp->Appointment_index;
				if (Appointment_temp_0 == nullptr) {
					Book_temp->Appointment_index = new Appointment(int_temp_0, string_temp_1, string_temp_0, Book_temp->Book_name, ltm.tm_year, ltm.tm_mon, ltm.tm_mday);
					Appointment_temp_0 = Book_temp->Appointment_index;
				}
				else {//如果该书有借阅信息，就插入到信息末尾
					Appointment_temp_0 = Book_temp->Appointment_index;
					while (Appointment_temp_0->next != nullptr) {
						Appointment_temp_0 = Appointment_temp_0->next;
					}
					Appointment_temp_0->next = new Appointment(int_temp_0, string_temp_1, string_temp_0, Book_temp->Book_name, ltm.tm_year, ltm.tm_mon, ltm.tm_mday);
					Appointment_temp_0 = Appointment_temp_0->next;
				}
				Book_temp->Book_surplus--;//更新该书的库存
				cout << "预约成功！";
				cout << "【预约人】" << string_temp_1 << endl;
				cout << "【身份证号码】" << int_temp_0 << endl;
				cout << "【预约书名】" << Book_temp->Book_name << endl;
				cout << "【预约时间】" << (1900 + ltm.tm_year) << "年" << 1 + ltm.tm_mon << "月" << ltm.tm_mday << "日" << endl;
				cout << "*******************************************************" << endl;
				cout << "温馨提示：请在七个工作日内取走所预约书籍！否则此次预约将无效！" << endl;
				return true;
			}
			else {
				cout << "预约失败！请重试！";
				return false;
			}
		}
	}
};
bool Library::take_book(BTree& y)
{
	short permission = 0;//根据这个变量的值来查看是否可以取书。
	int timepass = 0;//储存时间差值，依次来判断是否过期
	string book_number_temp;//临时储存书的书号
	unsigned long long ID_temp;//用户的身份证号码
	Book* Book_temp = nullptr;//接收地址的变量
	Appointment* Appointment_temp_pr = nullptr;
	Appointment* Appointment_temp = nullptr;//遍历预约信息
	Borrow* Borrow_temp = nullptr;//遍历借阅信息
	Appointment* delete_help = nullptr;//帮忙删除某个结点
	cout << "请输入您需要取的书号：";
	cin >> book_number_temp;
	Book_temp = y.search_return_index(book_number_temp);
	if (Book_temp == nullptr) {
		cout << "未输入正确的书号！请重试！";
		return false;
	}
	else {
		cout << "请输入您的身份证号码：";
		cin >> ID_temp;
		Appointment_temp_pr = Book_temp->Appointment_index;
		Appointment_temp = Book_temp->Appointment_index;
		while (Appointment_temp != nullptr) {
			if (Appointment_temp->Appointment_ID == ID_temp) {//找到预约信息，于是查看是否到期：
				//time_t now = time(0);//获取现在的秒数
				//struct tm ltm;//时间结构体
				//localtime_s(&ltm, &now);//转换成年月日
				time_t now = time(0);//获取秒数
				struct tm ltm;//时间结构体
				localtime_s(&ltm, &now);//转换成年月日
				if (ltm.tm_year = Appointment_temp->Appointment_year && ((ltm.tm_mon - Appointment_temp->Appointment_month) < 2) && (((ltm.tm_mon - Appointment_temp->Appointment_month) * 30) + ltm.tm_mday - Appointment_temp->Apppointment_day) < 8) {//如果时间都合法的话，就可以取
					permission = 1;
					//以下就是取书的过程：
					cout << "已找到预约信息......" << endl;
					cout << "正在取书......" << endl;
					//以下是取书：
					Borrow_temp = Book_temp->Borrow_index;
					ltm.tm_year = ltm.tm_year + 118;
					Book_temp->Borrow_index = new Borrow(Appointment_temp->Appointment_ID, Appointment_temp->Appointment_name, Appointment_temp->Appointment_number, Appointment_temp->Appointment_Book_name, ltm.tm_year, ltm.tm_mon, ltm.tm_mday);
					Book_temp->Borrow_index->next = Borrow_temp;//连接上
					//下面是把预约信息删掉：
					if (Appointment_temp->next != nullptr) {//第一种删除情况
						Appointment_temp->Appointment_Book_name = Appointment_temp->next->Appointment_Book_name;
						Appointment_temp->Appointment_ID = Appointment_temp->next->Appointment_ID;
						Appointment_temp->Appointment_month = Appointment_temp->next->Appointment_month;
						Appointment_temp->Appointment_name = Appointment_temp->next->Appointment_name;
						Appointment_temp->Appointment_number = Appointment_temp->next->Appointment_number;
						Appointment_temp->Appointment_year = Appointment_temp->next->Appointment_year;
						Appointment_temp->Apppointment_day = Appointment_temp->next->Apppointment_day;
						delete_help = Appointment_temp->next;//删除指针拿到需要删除的值
						Appointment_temp->next = Appointment_temp->next->next;//赋值过来
						delete_help->next = nullptr;
						delete delete_help;
					}
					else {//第二种删除情况
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
						//Appointment_temp_pr->next = nullptr;//前一个指针置空
						//delete_help = Appointment_temp;
						//delete delete_help;
					}
					cout << "取书成功！" << endl;
					cout << "您可以带走此书了！" << endl;
					return true;
				}
				else {
					permission = 0;
					if (Appointment_temp->next != nullptr) {//第一种删除情况
						Appointment_temp->Appointment_Book_name = Appointment_temp->next->Appointment_Book_name;
						Appointment_temp->Appointment_ID = Appointment_temp->next->Appointment_ID;
						Appointment_temp->Appointment_month = Appointment_temp->next->Appointment_month;
						Appointment_temp->Appointment_name = Appointment_temp->next->Appointment_name;
						Appointment_temp->Appointment_number = Appointment_temp->next->Appointment_number;
						Appointment_temp->Appointment_year = Appointment_temp->next->Appointment_year;
						Appointment_temp->Apppointment_day = Appointment_temp->next->Apppointment_day;
						delete_help = Appointment_temp->next;//删除指针拿到需要删除的值
						Appointment_temp->next = Appointment_temp->next->next;//赋值过来
						delete_help->next = nullptr;
						delete delete_help;
					}
					else {//第二种删除情况
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
					Book_temp->Book_surplus++;//将这本书入库
				}
			}
			else {//什么都不做
				//permission = 0;
			}
			Appointment_temp_pr = Appointment_temp;
			Appointment_temp = Appointment_temp->next;//循环
		}
		if (permission == 0) {//此人未预约书籍反而去取书，一定不能成功。
			cout << "未找到相关的预约信息 或者 您未在指定期限内取走您的书籍已导致预约失败......" << endl;
			cout << "取书失败......" << endl;
			return false;
		}
	}
};
bool Library::return_book(BTree& y)
{
	short permission = 0;//判断是否可以还书
	int timepass = 0;//储存时间差值，依次来判断是否过期依次罚款
	int money = 0;//罚款
	unsigned long long ID_temp;//用户的身份证号码
	string book_number_temp;//接收用户输入的书号
	Book* Book_temp = nullptr;//接收地址的变量
	Borrow* Borrow_temp_pr = nullptr;
	Borrow* Borrow_temp = nullptr;//遍历借阅信息
	Borrow* delete_help = nullptr;//删除指针
	cout << "请输入您所归还书的号码：";
	cin >> book_number_temp;
	Book_temp = y.search_return_index(book_number_temp);
	if (Book_temp == nullptr) {
		cout << "未输入正确的书号！请重试！";
		return false;
	}
	else {
		cout << "请输入您的身份证号码：";
		cin >> ID_temp;
		Borrow_temp_pr = Book_temp->Borrow_index;
		Borrow_temp = Book_temp->Borrow_index;
		while(Borrow_temp!=nullptr){
			if (Borrow_temp->Borrow_ID == ID_temp) {
				permission = 1;//找到信息
				time_t now = time(0);//获取现在的秒数
				struct tm ltm;//时间结构体
				localtime_s(&ltm, &now);//转换成年月日
				timepass = (ltm.tm_year - Borrow_temp->Borrow_year) * 365 - (ltm.tm_mon - Borrow_temp->Borrow_month) * 30 - ltm.tm_mday + Borrow_temp->Borrow_day;//总共经历的天数
				money = timepass - 30;
				if (money > 0) {//需要罚款。
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
					Book_temp->Book_surplus++;//库存增加
					cout << "已归还！" << endl;
					cout << "但由于您已经逾期，所以罚款：" << money << "元" << endl;
					cout << "请到柜台办理支付手续！" << endl;
					return true;
				}
				else {//不用罚款。
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
					Book_temp->Book_surplus++;//库存增加
					cout << "已成功归还！" << endl;
					cout << "欢迎您的再次光临！" << endl;
					return true;
				}
			}
			else {//什么也不做
			}
			Borrow_temp_pr = Borrow_temp;
			Borrow_temp = Borrow_temp->next;
		}
		if (permission == 0) {
			cout << "未找到相关信息，操作失败！请重试！" << endl;
			cout << "请核对信息，查看是否输入错误！" << endl;
			return false;
		}
	}
};
bool Library::throw_book(BTree& y)
{
	short permission = 0;//标志是否可以清空这本书
	string book_number_temp;//接收管理员输入的书号
	Book* Book_temp = nullptr;//接收地址的变量
	cout << "请输入您需要清空的书的号码：";
	cin >> book_number_temp;
	Book_temp = y.search_return_index(book_number_temp);
	if (Book_temp == nullptr) {
		cout << "未输入正确的书号！请重试！";
		return false;
	}
	else {
		if (Book_temp->Appointment_index == nullptr && Book_temp->Borrow_index == nullptr) {
			cout << "正在清空本书......" << endl;
			y.delete_page00(book_number_temp);
			delete Book_temp;
			return true;
		}
		else {
			cout << "清库失败，此书库存不足！仍有借阅在外或者预约出！";
			return false;
		}
	}
};
bool Library::add_book(BTree& y)
{
	short permission = 0;//标志是否可以增加这本书
	string book_number_temp;//接收管理员输入的书号
	Book* Book_temp = nullptr;//接收地址的变量
	cout << "请输入您需要增加的书的号码：";
	cin >> book_number_temp;
	Book_temp = y.search_return_index(book_number_temp);
	if (Book_temp == nullptr) {
		cout << "未输入正确的书号！请重试！";
		return false;
	}
	else {
		cout << "正在完成增添......" << endl;
		Book_temp->Book_surplus++;
		Book_temp->Book_total++;
		cout << "已完成增添！" << endl;
		return true;
	}
};
bool Library::add_new_book(BTree& y)
{
	Book* Book_temp = nullptr;
	string Book_number_temp;//书号
	string Book_name_temp;//书名
	string Book_auther_temp;//作者
	int Book_surplus_temp;//剩余量
	int Book_total_temp;//总库存
	cout << "请输入需要增添新的书号：";
	cin >> Book_number_temp;
	Book_temp = y.search_return_index(Book_number_temp);
	if (Book_temp != nullptr) {
		cout << "本馆已存在此书！";
		cout << "请重试！";
		return false;
	}
	else {
		cout << "请输入书名：";
		cin >> Book_name_temp;
		cout << "请输入作者：";
		cin >> Book_auther_temp;
		cout << "投入总量：";
		cin >> Book_total_temp;
		Book_surplus_temp = Book_total_temp;
		Book_temp = new Book(Book_number_temp, Book_name_temp, Book_auther_temp, Book_surplus_temp, Book_total_temp);
		y.insert_page0(Book_number_temp, Book_temp);
		Book_temp = nullptr;
		cout << "添加成功！";
		return true;
	}
};
bool Library::browse_book(BTree& y)
{
	Book* Book_temp = nullptr;
	Borrow* Borrow_temp = nullptr;
	Appointment* Appointment_temp = nullptr;
	string Book_number_temp;
	cout << "请输入需要查看的书的书号：";
	cin >> Book_number_temp;
	Book_temp = y.search_return_index(Book_number_temp);
	if (Book_temp == nullptr) {
		cout << "本馆不存在此书！请重试！";
		return false;
	}
	else {
		cout << "如下：" << endl;
		cout << "【书号】" << Book_temp->Book_number << endl;
		cout << "【书名】" << Book_temp->Book_name << endl;
		cout << "【作者】" << Book_temp->Book_auther << endl;
		cout << "【现库存】" << Book_temp->Book_surplus <<"本"<< endl;
		cout << "【总库存】" << Book_temp->Book_total <<"本"<< endl;
		Borrow_temp = Book_temp->Borrow_index;
		Appointment_temp = Book_temp->Appointment_index;
		if (Borrow_temp != nullptr) {
			cout << endl;
			cout << "借阅信息如下：" << endl;
			while (Borrow_temp != nullptr) {
				cout << "【借书人身份证号码】" << Borrow_temp->Borrow_ID << endl;
				cout << "【借书人姓名】" << Borrow_temp->Borrow_name << endl;
				cout << "【借书日期】" << 1900 + Borrow_temp->Borrow_year << "年" << 1 + Borrow_temp->Borrow_month << "月" << Borrow_temp->Borrow_day << "日" << endl;
				cout << endl;
				Borrow_temp = Borrow_temp->next;
			}
		}
		else{}
		if (Appointment_temp != nullptr) {
			cout << endl;
			cout << "预约信息如下：" << endl;
			while (Appointment_temp != nullptr) {
				cout << "【预约人身份证号码】" << Appointment_temp->Appointment_ID << endl;
				cout << "【预约人姓名】" << Appointment_temp->Appointment_name << endl;
				cout << "【预约日期】" << 1900 + Appointment_temp->Appointment_year<<"年"<< 1 + Appointment_temp->Appointment_month <<"月"<< Appointment_temp->Apppointment_day<<"日" << endl;
				cout << endl;
				Appointment_temp = Appointment_temp->next;
			}
		}
		else{}
		return true;
	}
};