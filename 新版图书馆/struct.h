#ifndef _STRUCT_H
#define _STRUCT_H
using namespace std;
#include<string>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include<fstream>
#include<ctime>
#define KeyType string//没有使用
const int m = 4;//四阶B树

struct Borrow;
struct Appointment;
//结构体命名方式：首字母大写式
struct Book {//书结构体
	string Book_number;//书号
	string Book_name;//书名
	string Book_auther;//作者
	int Book_surplus;//剩余量
	int Book_total;//总库存
	Borrow* Borrow_index = nullptr;//借书信息索引
	Appointment* Appointment_index = nullptr;//预约信息索引
	//Book* next = nullptr;【注：感觉不要就可以，一切基于B树进行操作】
	Book(string Book_number_x, string Book_name_x, string Book_auther_x, int Book_surplus_x, int Book_total_x) {//构造函数
		Book_number = Book_number_x;
		Book_name = Book_name_x;
		Book_auther = Book_auther_x;
		Book_surplus = Book_surplus_x;
		Book_total = Book_total_x;
	};
};
struct Borrow {//借阅结构体
	unsigned long long Borrow_ID;//借书人身份证号
	string Borrow_name;//借书人姓名
	string Borrow_Book_number;//所借书号
	string Borrow_Book_name;
	//借阅开始时间如下（暂定可借阅1月）：
	int Borrow_year;
	int Borrow_month;
	int Borrow_day;
	//short Borrow_penalty;//罚款【注：不要了】
	//Book* Book_index = nullptr;//返回到书【注：感觉不需要】
	Borrow* next = nullptr;
	Borrow(unsigned long long Borrow_ID_x, string Borrow_name_x, string Borrow_Book_number_x,string Borrow_Book_name_x, int Borrow_year_x,int Borrow_month_x,int Borrow_day_x) {//构造函数
		Borrow_ID = Borrow_ID_x;
		Borrow_name = Borrow_name_x;
		Borrow_Book_number = Borrow_Book_number_x;
		Borrow_Book_name = Borrow_Book_name_x;
		Borrow_year = Borrow_year_x;
		Borrow_month = Borrow_month_x;
		Borrow_day = Borrow_day_x;
	}
};
struct Appointment {//预约结构体
	unsigned long long Appointment_ID;//身份证
	string Appointment_name;//预约人
	string Appointment_number;//预约书号
	string Appointment_Book_name;//预约书名
	//预约开始时间如下（如果某一用户从n时刻预约到一本书，那么他必须在七个工作日内取走它，否则一周后到期，此预约信息将被视为无效!）：
	int Appointment_year;
	int Appointment_month;
	int Apppointment_day;
	//Book* Book_index = nullptr;//返回到书【注：感觉不需要】
	Appointment* next = nullptr;
	Appointment(unsigned long long Appointment_ID_x, string Appointment_name_x, string Appointment_number_x, string Appointment_Book_name_x,int Appointment_year_x,int Appointment_month_x,int Appointment_day_x) {
		Appointment_ID = Appointment_ID_x;
		Appointment_name = Appointment_name_x;
		Appointment_number = Appointment_number_x;
		Appointment_Book_name = Appointment_Book_name_x;
		Appointment_year = Appointment_year_x;
		Appointment_month = Appointment_month_x;
		Apppointment_day = Appointment_day_x;
	}
};
#endif