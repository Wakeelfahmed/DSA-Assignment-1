#include"List.h"
bool transfer(Account& source, Account& destination, long double amount)
{
	if (source.is_Active())
	{
		if (source.Suffient_Balance(amount))
		{
			source.set_balance((source.get_balance() - amount));
			destination.set_balance((destination.get_balance() + amount));
			return 1;
		}
		else
			cout << "Insufficient Balance" << endl; return 0;
	}
	else
		cout << "Inactive account" << endl; return 0;
}
void ExportAsReadable(list list) {
	ofstream Accoufile;
	Accoufile.open("AccountsDetails.txt");
	for (int i = 1; i <= list.Number_of_Nodes(); i++)
	{
		Accoufile << "Account \'" << i << "\' Details:\n";
		Accoufile << "AccountNo:" << list.get_Account_Node(i)->Account_Data.get_AccountNo() << endl;
		Accoufile << "Account Holder Name:" << list.get_Account_Node(i)->Account_Data.get_Account_Holder_Name() << endl;
		Accoufile << "Balance:Rs." << list.get_Account_Node(i)->Account_Data.get_balance() << "/-\n";
		if (list.get_Account_Node(i)->Account_Data.is_Active())
			Accoufile << "Active Status:Active\n";
		else
			Accoufile << "Active Status:Dormant\n";
		Accoufile << "Minimum Balance:Rs." << list.get_Account_Node(i)->Account_Data.get_minBalance() << "/-\n";
		if (list.get_Account_Node(i)->Account_Data.is_current_or_saving_accountType())
			Accoufile << "Account Type:Current Account" << endl;
		else
			Accoufile << "Account Type:Saving Account" << endl;
	}
	cout << "Data has been successfully exported\n";
}
void ExportAsBackup(list Account_List) {
	ofstream Accoufile;
	Accoufile.open("AccountsSeverDataBase.txt");
	Accoufile << "SeverFile";
	for (int i = 1; i <= Account_List.Number_of_Nodes(); i++)
	{
		Accoufile << endl << Account_List.get_Account_Node(i)->Account_Data.get_AccountNo() << endl;
		Accoufile << Account_List.get_Account_Node(i)->Account_Data.get_Account_Holder_Name() << endl;
		Accoufile << Account_List.get_Account_Node(i)->Account_Data.get_balance() << endl;
		if (Account_List.get_Account_Node(i)->Account_Data.is_Active())
			Accoufile << "Active\n";
		else
			Accoufile << "Dormant\n";
		Accoufile << Account_List.get_Account_Node(i)->Account_Data.get_minBalance() << endl;
		if (Account_List.get_Account_Node(i)->Account_Data.is_current_or_saving_accountType())
			Accoufile << "Current\n";
		else
			Accoufile << "Saving\n";
		Accoufile << Account_List.get_Account_Node(i)->Account_Data.getPIN();
	}
}
void validate_Input(int start, int& input, int end) {
	while (input < start || input > end)
		input = _getch() - '0';
}
void validate_Input(int& input, int numberofaccount, Account account[]) {
	while ((input > numberofaccount || input <= 0) || (account[input].get_AccountNo() == ""))
		input = _getch();
}
void FindAccount(list list, string Account_No) {
	Node* p = list.get_head();
	while (p != NULL)
	{
		if (p->Account_Data.get_AccountNo() == Account_No)
		{
			cout << "Your Account exists in Records";
		}
		p = p->next;
	}
}
Account A; //Global (class)Account Object array.
int UI_Input = 0, loop = 1, Input[2];
char PIN[5];
void read_and_store_accounts(list& Account_list)
{
	string FileCheck, AccountStatus, AccountType, Account_Num;
	char Name[100];  long double Balance;	int Minimum_Ba;
	bool isactive;
	ifstream AccoutFile("AccountsSeverDataBase.txt");
	if (!AccoutFile)
	{
		cout << "Sever File Missing" << endl;		return;
	}
	AccoutFile >> FileCheck;
	if (!(FileCheck == "SeverFile"))//correct file check (optional)
	{
		cout << "Incorrect or Corrupt Sever File\n";		return;
	}
	while (!AccoutFile.eof())
	{
		AccoutFile >> Account_Num >> Name >> Balance >> AccountStatus >> Minimum_Ba >> AccountType >> PIN;
		Account* Temp = new Account(Name, Account_Num, Balance, AccountStatus, Minimum_Ba, AccountType, PIN);//Parameterized Cons.
		Account_list.insert_end(*Temp);
		Temp->~Account();		delete Temp;	//freeup
	}
	cout << "Data has been successfully Imported\n";
	AccoutFile.close();
}
void Bank_Main_Menu() {
	cout << "Welcome to Bank Account Management System" << endl;
	cout << "0. Manage Account DataBase" << "\t1. Create a Account" << endl;
	UI_Input = _getch() - '0';
}
int main()
{
	list Account_List;
	long double Amount;
	char sure;
	Bank_Main_Menu();
	validate_Input(0, UI_Input, 1);//Input validation
	if (UI_Input == 0)
		validate_Input(0, UI_Input, 1);//Input validation
	while (UI_Input == 0 || UI_Input == 1 || UI_Input == 2 || UI_Input == 3 || UI_Input == 4 || UI_Input == 5)//Input 6 terminates this loop.
	{
		switch (UI_Input)
		{
		case 0://Database
		{
			system("CLS");
			cout << "0. Import\t1. Export As Readable\t2. Export As Backup\t3. Sort Accounts List\n";
			Input[0] = _getch() - '0';
			if (Input[0] == 0)
				read_and_store_accounts(Account_List);
			if (Input[0] == 1)			//else if (Input[0] == 1)
				ExportAsReadable(Account_List);
			else if (Input[0] == 2) {
				ExportAsBackup(Account_List);
				cout << "Data has been successfully exported\n";
			}
			else if (Input[0] == 3) {
				int i, j; int ans;
				for (i = 1; i <= Account_List.Number_of_Nodes(); i++)
					for (j = 1; j <= Account_List.Number_of_Nodes() - i; j++) {
						ans = strcmp(Account_List.get_Account_Node(j)->Account_Data.get_Account_Holder_Name(), Account_List.get_Account_Node(j + i)->Account_Data.get_Account_Holder_Name());
						if (ans == 1) {
							Account_List.insert_after(Account_List.get_Account_Node(j + 1)->Account_Data, Account_List.get_Account_Node(j)->Account_Data);
							if (i != Account_List.Number_of_Nodes())
								Account_List.delete_Account_Node_fr_list(Account_List.get_Account_Node(j)->Account_Data);
						}
					}
				cout << "\nSorted List:\n";
				Account_List.Display_list();
			}
			break;
		}
		case 1: //Create Account
		{
			system("CLS");
			cout << "# of Accounts:" << Account_List.Number_of_Nodes() << endl;
			A.Account_Creation();
			Account_List.insert_end(A);
			A.~Account();
			break;
		}//end of Case 1
		case 2: //Manage Accounts
		{
			system("CLS");
			cout << "Select Account To Manage" << endl;
			Account_List.Display_list();
			cout << "\n0. for Main Menu\n";
			Input[1] = _getch() - '0';
			validate_Input(0, Input[1], Account_List.Number_of_Nodes()); //Input validation
			if (Input[1] == 0)
				break;
			Account_List.Display_Node(Input[1]);
			if (!(Account_List.get_Account_Node(Input[1])->Account_Data.is_Active()))
			{
				cout << "0. Back Menu" << "\t1. Activate Account" << endl;
				Input[0] = _getch() - '0';
				validate_Input(0, Input[0], 1); //Input validation
				if (Input[0] == 1)
				{
					cout << "Desposit Amount to Activate Account:";
					cin >> Amount;
					Account_List.get_Account_Node(Input[1])->Account_Data.update_balance(Amount);
				}
			}
			else
			{
				cout << "0. Back To Menu" << " \t1. Reset PIN" << "\t2. Close Account" << endl;
				Input[0] = _getch() - '0';
				validate_Input(0, Input[0], 2); //Input validation
				if (Input[0] == 1)//Reset PIN
				{
					Account_List.get_Account_Node(Input[1])->Account_Data.set_PIN();
					cout << "New PIN is:" << Account_List.get_Account_Node(Input[1])->Account_Data.getPIN() << endl;	//To remove
				}
				if (Input[0] == 2) //Close Account
				{
					cout << "Are you sure you want to close your account?: Y. proceed\\N. stop:";
					sure = _getch();
					if (sure == 'Y' || sure == 'y') //Confirmation. close Account
					{
						Account_List.delete_Account_Node_fr_list(Account_List.get_Account_Node(Input[1])->Account_Data);//To Delete Node from list.
						ExportAsBackup(Account_List);
						cout << "Backup File has been successfully updated\n";
					}
				}
			}
			break;
		}//end of Case 2
		case 3: //Deposit Money
		{
			system("CLS");
			cout << "Select Account To Deposit Money Into" << endl;
			Account_List.Display_list();
			cout << "\n0. Cancel";
			Input[1] = _getch() - '0';
			validate_Input(0, Input[1], Account_List.Number_of_Nodes());
			if (Input[1] == 0)
				break;
			Account_List.get_Account_Node(Input[1])->Account_Data.Deposit();
			break;
		}//end of Case 3
		case 4: //Withdraw Money
		{
			system("CLS");
			cout << "Select Account To Withdraw Money From" << endl;
			Account_List.Display_list();
			Input[1] = _getch() - '0';
			validate_Input(1, Input[1], Account_List.Number_of_Nodes()); //Input validation
			Account_List.get_Account_Node(Input[1])->Account_Data.Withdraw();
			break;
		}
		case 5: //Transfer Money
		{
			system("CLS");
			cout << "Select Account To Transfer Funds FROM:" << endl;
			Account_List.Display_list();
			Input[0] = _getch() - '0';
			validate_Input(1, Input[0], Account_List.Number_of_Nodes()); //Input validation
			cout << "Enter the 4-digit PIN to perform Transaction:" << Account_List.get_Account_Node(Input[0])->Account_Data.getPIN() << endl;//REMOVE THIS
			for (loop = 0; loop < 4; loop++)
			{
				PIN[loop] = _getch();	//User Entering PIN
				while (PIN[loop] < 48 || PIN[loop] > 57) {
					if (PIN[loop] == 8)//Allow user to retype/backspace pin
					{
						if (loop >= 0) {
							cout << "\b \b";
							if (loop != 0)
								loop--;
						}
					}
					PIN[loop] = _getch();
				}
				cout << "*";
			}PIN[4] = '\0';
			if (!(strcmp(Account_List.get_Account_Node(Input[0])->Account_Data.getPIN(), PIN))) //PIN Matching
			{
				cout << "\nSelect Account To Transfer Amount TO:";
				Input[1] = _getch() - '0';	validate_Input(1, Input[1], Account_List.Number_of_Nodes());//Input validation
				cout << "Enter Amount To Transfer:";
				cin >> Amount;
				if (transfer(Account_List.get_Account_Node(Input[0])->Account_Data, Account_List.get_Account_Node(Input[1])->Account_Data, Amount)) //transfer() function returns bool(1/0).
					cout << "Transaction is Sucessful" << endl;
				else
					cout << "Transaction is unSuccessful" << endl;
			}
			else
				cout << "\nInvalid PIN";
			break;
		}
		}//End of switch Statement.
		cout << "\n0. Manage Account DataBase" << "\t1. Create Account\t";
		if (Account_List.Number_of_Nodes() >= 1)
		{
			cout << "2. Manage Accounts" << "\n3. Deposit Money\t"
				<< "\t4. Withdraw Money\t";
			if (Account_List.Number_of_Nodes() >= 2)
				cout << "5. Transfer Funds\n";
			cout << "6. Exit Program" << endl;
		}
		UI_Input = _getch() - '0';
		if (Account_List.Number_of_Nodes() == 0)
			validate_Input(0, UI_Input, 1);//Import and creation allowed only
		else if (Account_List.Number_of_Nodes() == 1)
			while (UI_Input < 0 || UI_Input == 5 || UI_Input > 6) //Can't Transfer
				UI_Input = _getch() - '0';
		else
			validate_Input(0, UI_Input, 6);//Input validation for all options

	}//End of While Loop controlling switch Statement.
}
