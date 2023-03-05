#pragma once
#include<string>
#include<string.h>
#include<ctime>
#include<iostream>
#include<conio.h>
#include<string.h>
#include<fstream>
//#include"List.h"
using namespace std;
class Account
{
private:
	char Name[100];			//Account Holder Name
	string Account_Num;		//Account Number
	long double Balance;	//Total Balance in the account
	bool isActive;			//True if the account is active else false
	short Minimum_Balance;	//Minimum balance that must be maintained
	char Account_Type;		//'S' for saving and 'C' for current 
	char PIN[5];
public:
	Account();//Default Constructor
	Account(char*, string, long double, string, short, string, char*);//Parametrized Constructor
	void Account_Creation();
	void set_PIN();
	void set_Name(char *);
	void set_accountNo(string AccountNum);
	void set_balance(long double a);
	void update_balance(long double a);
	void setisActive(bool truefalse);
	void set_MinBalance(short Minimum_Balance);
	void set_accountType(char);
	void get() const;
	string get_AccountNo() const;
	char* get_Account_Holder_Name();
	long double get_balance() const;
	short get_minBalance();
	bool is_current_or_saving_accountType() const;
	void Deposit();
	char* getPIN();
	void Withdraw();
	bool is_Active() const;
	bool Suffient_Balance(long double Amount) const;
	~Account();//Destructor
	void saving_dedution(long double balance);
	//void read_and_store_accounts(list AccountArray, int& AccountCounter);
	bool operator==(Account Student_2) const;
}; //End of class

