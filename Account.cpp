#include "Account.h"
Account::Account() :Name(""), Balance(0), isActive(0), Minimum_Balance(0), Account_Type('S'), PIN("0000") {}
Account::Account(char* Name, string Account_Num, long double Balance, string isActive, short Minimum_Balance, string accountType, char* PIN)//Parametrized Constructor
{
	strcpy_s(this->Name, Name);			this->Account_Num = Account_Num;		this->Balance = Balance;
	if (isActive == "Active")
		this->isActive = 1;
	else
		this->isActive = 0;
	if (accountType == "Saving")
		Account_Type = 'S';
	else
		Account_Type = 'C';
	this->Minimum_Balance = Minimum_Balance;
	strcpy_s(this->PIN, PIN);
}
void Account::Account_Creation() {
	srand(time(0));
	cout << "Account Creation" << endl
		<< "Note Minimum Balance limit: Current Account: Rs.5000/- \t Saving Account: Rs.1000/-";
	cout << "\nSelect Account Type" << endl;
	cout << "\'C\'. Current Account \n\'S\'. Saving Account" << endl;
	Account_Type = _getch();
	while (!(Account_Type == 's' || Account_Type == 'S' || Account_Type == 'C' || Account_Type == 'c'))
		Account_Type = _getch();
	if (is_current_or_saving_accountType())
		Minimum_Balance = 5000;
	else
		Minimum_Balance = 1000;
	cout << "AccountNo Assigned:";
	for (short i = 0; i < 10; i++)
	{
		short randomNum; char random;
		randomNum = rand() % 101;
		if (randomNum >= 50)
		{
			random = ((char)65 + rand() % 26);
			Account_Num = Account_Num + random;
			//Account_Num = Account_Num + ((char)65 + rand() % 26);
		}
		else {
			random = 48 + rand() % 10;
			Account_Num = Account_Num + random;
		}
	}
	cout << Account_Num;
	cout << "\nEnter Account Holder Name:";
	cin >> Name;
	cout << "Enter the Amount You Want To Add in account:";
	cin >> Balance;
	saving_dedution(Balance);
	set_PIN();
	cout << "PIN Assigned:" << PIN << endl;
}
void Account::set_PIN() {
	for (short i = 0; i < 4; i++)
		PIN[i] = 48 + rand() % 10;
	PIN[4] = '\0';
}
void Account::set_Name(char* NewName) { strcpy_s(Name, NewName); }
void Account::set_accountNo(string AccountNum) { this->Account_Num = AccountNum; }
void Account::set_balance(long double a) { Balance = a; }
void Account::update_balance(long double a) { Balance = Balance + a; }
void Account::setisActive(bool truefalse) { isActive = truefalse; }
void Account::set_MinBalance(short Minimum_Balance) { this->Minimum_Balance = Minimum_Balance; }
void Account::set_accountType(char ch) { Account_Type = ch; }
void Account::get() const
{
	cout << "\nACCOUNT DETAILS" << endl
		<< "AccountNo:" << Account_Num << endl
		<< "Account Holder Name:" << Name << endl
		<< "Balance:Rs." << Balance << "/-" << endl;
	if (is_Active())
		cout << "Account Status:Active" << endl;
	else
		cout << "Account Status:Dormant" << endl << "Please go to Account Management to active your account" << endl;
	cout << "Minimum Balance:Rs." << Minimum_Balance << "/-" << endl;
	if (is_current_or_saving_accountType())
		cout << "Account Type:Current Account" << endl;
	else
		cout << "Account Type:Saving Account" << endl;
}
string Account::get_AccountNo() const { return Account_Num; }
char* Account::get_Account_Holder_Name() { return Name; }
long double Account::get_balance()  const { return Balance; }
short Account::get_minBalance() {
	if (Account_Type == 'C' || Account_Type == 'c')
		Minimum_Balance = 5000;
	else if (Account_Type == 'S' || Account_Type == 's')
		Minimum_Balance = 1000;
	return Minimum_Balance;
}
bool Account::is_current_or_saving_accountType()  const {
	if (Account_Type == 'C' || Account_Type == 'c')
		return 1;
	else if (Account_Type == 'S' || Account_Type == 's')
		return 0;
}
void Account::Deposit() {
	long double Deposit_Amount = 0, SUM = 0;
	if (Balance >= Minimum_Balance)
	{
		cout << "Enter Amount to Deposit:";
		cin >> Deposit_Amount;
		SUM = Deposit_Amount + get_balance();
		set_balance(SUM);
		cout << "Transaction Successful !!" << endl;
	}
	else
		cout << "Transaction Failed !!" << endl << "Account is Dormant" << endl;
}
char* Account::getPIN() { return PIN; }
void Account::Withdraw()
{
	int Withdraw_Amount;
	if (Balance >= Minimum_Balance)
	{
		cout << "Enter the Amount to Withdraw:";
		cin >> Withdraw_Amount;
		if (Balance >= Withdraw_Amount)
		{
			Balance = Balance - Withdraw_Amount;
			cout << "Transaction Sucessful" << endl;
		}
		else
			cout << "Transaction failed!!" << endl << "Insuffient Balance" << endl;
	}
	else
		cout << "Transaction failed!!" << endl << "Account is Dormant" << endl;
}
bool Account::is_Active() const
{
	if (Balance >= Minimum_Balance)
		return true;
	else
		return false;
}
bool Account::Suffient_Balance(long double Amount)  const
{
	if (Balance >= Amount)
		return 1;
	else
		return 0;
}
void Account::saving_dedution(long double balance) {
	if (!is_current_or_saving_accountType())
	{
		Balance = (Balance - (balance * float(float(2.5) / 100)));
		cout << "2.5% of the amount has been deducted\nNew Balance is:" << Balance << endl;
	}
}
Account::~Account() {
	//isActive = 0; Balance = 0; Account_Num = ""; strcpy_s(Name, "");
} // Destructor
bool Account::operator==(Account Account_2) const
{
	if (Account_Num == Account_2.get_AccountNo()
		&& !strcmp(Name, Account_2.get_Account_Holder_Name())
		&& Account_Type == Account_2.Account_Type
		&& !strcmp(PIN, Account_2.getPIN())
		)
		return 1;
	return 0;
}
