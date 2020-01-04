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
#define KeyType string//û��ʹ��
const int m = 4;//�Ľ�B��

struct Borrow;
struct Appointment;
//�ṹ��������ʽ������ĸ��дʽ
struct Book {//��ṹ��
	string Book_number;//���
	string Book_name;//����
	string Book_auther;//����
	int Book_surplus;//ʣ����
	int Book_total;//�ܿ��
	Borrow* Borrow_index = nullptr;//������Ϣ����
	Appointment* Appointment_index = nullptr;//ԤԼ��Ϣ����
	//Book* next = nullptr;��ע���о���Ҫ�Ϳ��ԣ�һ�л���B�����в�����
	Book(string Book_number_x, string Book_name_x, string Book_auther_x, int Book_surplus_x, int Book_total_x) {//���캯��
		Book_number = Book_number_x;
		Book_name = Book_name_x;
		Book_auther = Book_auther_x;
		Book_surplus = Book_surplus_x;
		Book_total = Book_total_x;
	};
};
struct Borrow {//���Ľṹ��
	unsigned long long Borrow_ID;//���������֤��
	string Borrow_name;//����������
	string Borrow_Book_number;//�������
	string Borrow_Book_name;
	//���Ŀ�ʼʱ�����£��ݶ��ɽ���1�£���
	int Borrow_year;
	int Borrow_month;
	int Borrow_day;
	//short Borrow_penalty;//���ע����Ҫ�ˡ�
	//Book* Book_index = nullptr;//���ص��顾ע���о�����Ҫ��
	Borrow* next = nullptr;
	Borrow(unsigned long long Borrow_ID_x, string Borrow_name_x, string Borrow_Book_number_x,string Borrow_Book_name_x, int Borrow_year_x,int Borrow_month_x,int Borrow_day_x) {//���캯��
		Borrow_ID = Borrow_ID_x;
		Borrow_name = Borrow_name_x;
		Borrow_Book_number = Borrow_Book_number_x;
		Borrow_Book_name = Borrow_Book_name_x;
		Borrow_year = Borrow_year_x;
		Borrow_month = Borrow_month_x;
		Borrow_day = Borrow_day_x;
	}
};
struct Appointment {//ԤԼ�ṹ��
	unsigned long long Appointment_ID;//���֤
	string Appointment_name;//ԤԼ��
	string Appointment_number;//ԤԼ���
	string Appointment_Book_name;//ԤԼ����
	//ԤԼ��ʼʱ�����£����ĳһ�û���nʱ��ԤԼ��һ���飬��ô���������߸���������ȡ����������һ�ܺ��ڣ���ԤԼ��Ϣ������Ϊ��Ч!����
	int Appointment_year;
	int Appointment_month;
	int Apppointment_day;
	//Book* Book_index = nullptr;//���ص��顾ע���о�����Ҫ��
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