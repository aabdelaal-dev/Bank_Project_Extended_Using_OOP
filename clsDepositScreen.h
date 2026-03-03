#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

class clsDepositScreen : protected clsScreen
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
	static void ShowDepositScreen() {
		system("cls");
		_DrawScreenHeader("\t\tDeposit Screen");

		string AccNumber = _ReadAccountNumber();
		double DepositeAmount = 0;
		clsBankClient Client = clsBankClient::Find(AccNumber);

		_PrintClientCard(Client);

		cout << "\nPlease Enter Deposite Amount? ";
		DepositeAmount = clsInputValidate::ReadDblNumber("Please Enter a valid Number? ");

		char Answer = 'n';

		cout << "\nAre you sure you want to perform this transaction? ";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{
			Client.Deposit(DepositeAmount);
			cout << "\nAmount Deposited Successfully.\n";
			cout << "\nNew Balance is = " << Client.AccountBalance;
		}


	}


};

