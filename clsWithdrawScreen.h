#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
class clsWithdrawScreen : protected clsScreen
{

private:
	static void _PrintClientCard(clsBankClient& Client) {
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << Client.FirstName;
		cout << "\nLastName    : " << Client.LastName;
		cout << "\nFull Name   : " << Client.FullName();
		cout << "\nEmail       : " << Client.Email;
		cout << "\nPhone       : " << Client.Phone;
		cout << "\nAcc. Number : " << Client.AccountNumber();
		cout << "\nPassword    : " << Client.PinCode;
		cout << "\nBalance     : " << Client.AccountBalance;
		cout << "\n___________________\n";
	}

	static string _ReadAccountNumber() {

		string AccNumber;
		cout << "\nPlease Enter Account Number? ";
		AccNumber = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(AccNumber))
		{
			cout << "\nClient With [" << AccNumber << "] is not Exist!";

			cout << "\nPlease Enter Account Number? ";
			AccNumber = clsInputValidate::ReadString();
		}

		return AccNumber;

	}

public:
	static void ShowWithdrawScreen() {
		system("cls");
		clsScreen::_DrawScreenHeader("\t\tWithdraw Screen");

		double Amount=0;
		char Answer = 'n';
		string AccNumber = _ReadAccountNumber();

		clsBankClient Client = clsBankClient::Find(AccNumber);

		_PrintClientCard(Client);

		cout << "\nPlease Enter Withdraw Amount? ";

		Amount = clsInputValidate::ReadDblNumber("Please Enter a Valid Number? ");

		cout << "\nAre you sure you want to perform this transaction? ";

		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{
			if (Client.Withdraw(Amount)) {

				cout << "\nAmount Withdrawd Successfully.\n";
				cout << "\nNew balance is = " << Client.AccountBalance;

			}
			else {
				cout << "\nFaild, the amount exeded account balance.\n";
				cout << "\nAmount to withdraw is: "<<Amount;
				cout << "\nAccount balance is   : " << Client.AccountBalance;
			}

		}
		else
		{
			cout << "\nOperation was cancelled!";
		}
		
	}

};

