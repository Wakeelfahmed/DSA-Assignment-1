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
void ExportAsReadable(Account A[], int num_of_Accounts) {
	ofstream Accoufile;
	Accoufile.open("AccountsDetails.txt");
	for (int i = 1; i <= num_of_Accounts; i++)
	{
		Accoufile << "Account \'" << i << "\' Details:\n";
		Accoufile << "AccountNo:" << A[i].get_AccountNo() << endl;
		Accoufile << "Account Holder Name:" << A[i].get_Account_Holder_Name() << endl;
		Accoufile << "Balance:Rs." << A[i].get_balance() << "/-\n";
		if (A[i].is_Active())
			Accoufile << "Active Status:Active\n";
		else
			Accoufile << "Active Status:Dormant\n";
		Accoufile << "Minimum Balance:Rs." << A[i].get_minBalance() << "/-\n";
		if (A[i].is_current_or_saving_accountType())
			Accoufile << "Account Type:Current Account" << endl;
		else
			Accoufile << "Account Type:Saving Account" << endl;
	}
	cout << "Data has been successfully exported\n";
}
void ExportAsBackup(Account A[], int num_of_Accounts) {
	ofstream Accoufile;
	Accoufile.open("AccountsSeverDataBase.txt");
	Accoufile << "SeverFile";
	for (int i = 1; i <= num_of_Accounts; i++)
	{
		Accoufile << endl << A[i].get_AccountNo() << endl;
		Accoufile << A[i].get_Account_Holder_Name() << endl;
		Accoufile << A[i].get_balance() << endl;
		if (A[i].is_Active())
			Accoufile << "Active\n";
		else
			Accoufile << "Dormant\n";
		Accoufile << A[i].get_minBalance() << endl;
		if (A[i].is_current_or_saving_accountType())
			Accoufile << "Current\n";
		else
			Accoufile << "Saving\n";
		Accoufile << A[i].getPIN();
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

list Account_List;
Account A[50]; //Global (class)Account Object array.
int UI_Input = 0, loop = 1, Input[2];
char PIN[5];
void Bank_Main_Menu() {
	cout << "Welcome to Bank Account Management System" << endl;
	cout << "0. Manage Account DataBase" << "\t1. Create a Account" << endl;
	UI_Input = _getch() - '0';
}
int main()
{
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
				A[0].read_and_store_accounts(A, No_of_AccountsCounter);
			else if (Input[0] == 1)
				ExportAsReadable(A, No_of_AccountsCounter);
			else if (Input[0] == 2)
				ExportAsBackup(A, No_of_AccountsCounter);
			break;
		}
		case 1: //Create Account
		{
			system("CLS");
			No_of_AccountsCounter++;
			cout << "# of As:" << No_of_AccountsCounter << endl;
			A[No_of_AccountsCounter].Account_Creation();
			break;
		}//end of Case 1
		case 2: //Manage Accounts
		{
			system("CLS");
			cout << "Select Account To Manage" << endl;
			cout << "Account exsiting:" << No_of_AccountsCounter << endl;
			for (loop = 1; loop <= No_of_AccountsCounter; loop++)
				cout << loop << "\. " << A[loop].get_Account_Holder_Name() << endl;
			cout << "0. for Main Menu\n";
			Input[1] = _getch() - '0';
			validate_Input(0, Input[1], No_of_AccountsCounter); //Input validation
			if (Input[1] == 0)
				break;
			A[Input[1]].get();
			if (!(A[Input[1]].is_Active()))
			{
				cout << "0. Back Menu" << "\t1. Activate Account" << endl;
				Input[0] = _getch() - '0';
				validate_Input(0, Input[0], 1); //Input validation
				if (Input[0] == 1)
				{
					cout << "Desposit Amount to Activate Account:";
					cin >> Amount;
					A[Input[1]].update_balance(Amount);
				}
			}
			else
			{
				cout << "0. Back To Menu" << " \t1. Reset PIN" << "\t2. Close Account" << endl;
				Input[0] = _getch() - '0';
				validate_Input(0, Input[0], 2); //Input validation
				if (Input[0] == 1)//Reset PIN
				{
					A[Input[1]].set_PIN();
					cout << "New PIN is:" << A[Input[1]].getPIN() << endl;	//To remove
				}
				if (Input[0] == 2) //Close Account
				{
					cout << "Are you sure you want to close your account?: Y. proceed\\N. stop:";
					sure = _getch();
					if (sure == 'Y' || sure == 'y') //Confirmation. close Account
					{
						A[Input[1]].~Account(); //To Delete an account.
						for (loop = Input[1]; loop < No_of_AccountsCounter; loop++)
						{
							cout << "\t loop is:" << loop << endl;
							A[loop] = A[loop + 1];
							cout << "A[loop] = A[loop + 1]\n";
							A[loop + 1].~Account(); //To Delete an account.
						}
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
			for (loop = 1; loop <= No_of_AccountsCounter; loop++)
				cout << loop << ". " << A[loop].get_Account_Holder_Name() << endl;
			cout << "0. Cancel";
			Input[1] = _getch() - '0';
			validate_Input(0, Input[1], No_of_AccountsCounter);
			if (Input[1] == 0)
				break;
			A[Input[1]].Deposit();
			break;
		}//end of Case 3
		case 4: //Withdraw Money
		{
			system("CLS");
			cout << "Select Account To Withdraw Money From" << endl;
			for (loop = 1; loop <= No_of_AccountsCounter; loop++)
				cout << loop << ". " << A[loop].get_Account_Holder_Name() << endl;
			Input[1] = _getch() - '0';
			validate_Input(1, Input[1], No_of_AccountsCounter); //Input validation
			A[Input[1]].Withdraw();
			break;
		}
		case 5: //Transfer Money
		{
			system("CLS");
			cout << "Select Account To Transfer Funds FROM:" << endl;
			for (loop = 1; loop <= No_of_AccountsCounter; loop++)
				cout << "\'" << loop << "\'. " << A[loop].get_Account_Holder_Name() << endl;
			Input[0] = _getch() - '0';
			validate_Input(1, Input[0], No_of_AccountsCounter); //Input validation
			cout << "Enter the 4-digit PIN. perform Transaction:" << A[Input[0]].getPIN();
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
			if (!(strcmp(A[Input[0]].getPIN(), PIN))) //PIN Matching
			{
				cout << "\nSelect Account To Transfer Amount TO:";
				Input[1] = _getch() - '0';	validate_Input(1, Input[1], No_of_AccountsCounter);//Input validation
				cout << "Enter Amount To Transfer:";
				cin >> Amount;
				if (transfer(A[Input[0]], A[Input[1]], Amount)) //transfer() function returns bool(1/0).
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
