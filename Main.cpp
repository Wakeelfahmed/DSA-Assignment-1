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
	cout << "Data has been successfully exported\n";
}
void validate_Input(int start, int& input, int end) {
	while (input < start || input > end)
		input = _getch() - '0';
}
void validate_Input(int& input, int numberofaccount, Account account[]) {
	while ((input > numberofaccount || input <= 0) || (account[input].get_AccountNo() == ""))
		input = _getch();
}
void Display_HeadTail(list list) {
	cout << "Head:" << list.get_head()->Account_Data.get_Account_Holder_Name() << "\t\tTail:" << list.get_tail()->Account_Data.get_Account_Holder_Name();
}
Account A; //Global (class)Account Object array.
int UI_Input = 0, loop = 1, Input[2];
char PIN[5];
void read_and_store_accounts(list& Account_list, int& AccountCounter)
{
	string FileCheck, AccountStatus, AccountType, Account_Num;
	char Name[100];  long double Balance;	int Minimum_Ba;
	bool isactive;
	ifstream AccoutFile("AccountsSeverDataBase.txt");
	if (!AccoutFile)
	{
		cout << "Sever File Missing" << endl;
		return;
	}
	AccoutFile >> FileCheck;
	if (!(FileCheck == "SeverFile"))
	{
		cout << "Incorrect or Corrupt Sever File\n";
		return;
	}
	while (!AccoutFile.eof())
	{
		AccountCounter++; cout << "Reading Account #:" << AccountCounter; cout << "\nRead\n";
		AccoutFile >> Account_Num >> Name >> Balance >> AccountStatus >> Minimum_Ba >> AccountType >> PIN;

		Account Temp(Name, Account_Num, Balance, AccountStatus, Minimum_Ba, AccountType, PIN);
		/*if (AccountStatus == "Active")
			Temp.setisActive(1);
		else
			Temp.setisActive(0);*/
		/*if (AccountType == "Saving")
			Temp.set_accountType('S');
		else
			Temp.set_accountType('C');*/
		//Temp.set_Name(Name); Temp.set_accountNo(Account_Num); Temp.set_balance(Balance);
		//Temp.set_MinBalance(Minimum_Ba);
		Account_list.insert_end(Temp);
		//Temp.~Account();
		cout << "# of Nodes:" << Account_list.Number_of_Nodes();
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
	int static No_of_AccountsCounter = 0;
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
			cout << "0. Import\t1. Export As Readable\t2. Export As Backup\n";
			Input[0] = _getch() - '0';
			if (Input[0] == 0)
				read_and_store_accounts(Account_List, No_of_AccountsCounter);
			if (Input[0] == 1)			//else if (Input[0] == 1)
				ExportAsReadable(Account_List);
			else if (Input[0] == 2)
				ExportAsBackup(Account_List);
			break;
		}
		case 1: //Create Account
		{
			system("CLS");
			No_of_AccountsCounter++;
			cout << "# of Accounts:" << No_of_AccountsCounter << endl;
			A.Account_Creation();
			Account_List.insert_end(A);
			Display_HeadTail(Account_List);
			A.~Account();
			break;
		}//end of Case 1
		case 2: //Manage Accounts
		{	//Node* Account;
			system("CLS");
			cout << "Select Account To Manage" << endl;
			cout << "Account exsiting:" << No_of_AccountsCounter << endl;
			//for (loop = 1; loop <= No_of_AccountsCounter; loop++)	//cout << loop << "\. " << A[loop].get_Account_Holder_Name() << endl;
			Account_List.Display_list();
			cout << "0. for Main Menu\n";
			Input[1] = _getch() - '0';
			validate_Input(0, Input[1], No_of_AccountsCounter); //Input validation
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
						//Account_List.get_Account_Node(Input[1])->Account_Data.~Account(); //To Delete an account.
						//Account_List.get_Account_Node(Input[1]);
						Account_List.delete_Account_Node_fr_list(Account_List.get_Account_Node(Input[1])->Account_Data);//To Delete Node from list.
						No_of_AccountsCounter--;
					}
				}
			}
			break;
		}//end of Case 2
		case 3: //Deposit Money
		{
			system("CLS");
			cout << "Select Account To Deposit Money Into" << endl;
			//for (loop = 1; loop <= No_of_AccountsCounter; loop++)
				//cout << loop << ". " << A[loop].get_Account_Holder_Name() << endl;
			cout << "0. Cancel";
			Account_List.Display_list();
			Input[1] = _getch() - '0';
			validate_Input(0, Input[1], No_of_AccountsCounter);
			if (Input[1] == 0)
				break;
			Account_List.get_Account_Node(Input[1])->Account_Data.Deposit();
			//A[Input[1]].Deposit();
			break;
		}//end of Case 3
		case 4: //Withdraw Money
		{
			system("CLS");
			cout << "Select Account To Withdraw Money From" << endl;
			//for (loop = 1; loop <= No_of_AccountsCounter; loop++)
				//cout << loop << ". " << A[loop].get_Account_Holder_Name() << endl;
			Account_List.Display_list();
			Input[1] = _getch() - '0';
			validate_Input(1, Input[1], No_of_AccountsCounter); //Input validation
			Account_List.get_Account_Node(Input[1])->Account_Data.Withdraw();
			//A[Input[1]].Withdraw();

			break;
		}
		case 5: //Transfer Money
		{
			system("CLS");
			cout << "Select Account To Transfer Funds FROM:" << endl;
			//for (loop = 1; loop <= No_of_AccountsCounter; loop++)
				//cout << "\'" << loop << "\'. " << A[loop].get_Account_Holder_Name() << endl;
			Account_List.Display_list();
			Input[0] = _getch() - '0';
			validate_Input(1, Input[0], No_of_AccountsCounter); //Input validation
			cout << "Enter the 4-digit PIN. perform Transaction:" << Account_List.get_Account_Node(Input[0])->Account_Data.getPIN();//REMOVE THIS
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
			if (!(strcmp(Account_List.get_Account_Node(Input[0])->Account_Data.getPIN(), PIN))) //PIN Matching//			if (!(strcmp(A[Input[0]].getPIN(), PIN))) //PIN Matching
			{
				cout << "\nSelect Account To Transfer Amount TO:";
				Input[1] = _getch() - '0';	validate_Input(1, Input[1], No_of_AccountsCounter);//Input validation
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
		if (No_of_AccountsCounter >= 1)
		{
			cout << "2. Manage Accounts" << "\n3. Deposit Money\t"
				<< "\t4. Withdraw Money\t";
			if (No_of_AccountsCounter >= 2)
				cout << "5. Transfer Funds\n";

			cout << "6. Exit Program" << endl;
		}
		UI_Input = _getch() - '0';
		if (No_of_AccountsCounter == 0)
			validate_Input(0, UI_Input, 1);//Import and creation allowed only
		else if (No_of_AccountsCounter >= 1)
			if (No_of_AccountsCounter < 2)
				while (UI_Input < 0 || UI_Input == 5 || UI_Input > 6) //Can't Transfer
					UI_Input = _getch() - '0';
			else
				validate_Input(0, UI_Input, 6);//Input validation for all options

	}//End of While Loop controlling switch Statement.
}
