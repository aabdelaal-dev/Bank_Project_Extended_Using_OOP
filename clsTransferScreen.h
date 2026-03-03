#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "Global.h"

class clsTransferScreen:private clsScreen
{
private:
	static void _PrintClientCard(clsBankClient Client) {

		cout << "\nClient Card: \n";
		cout << "\n------------------------\n";
		cout << "\nFull Name   : " << Client.FullName();
		cout << "\nAcc. Number : " << Client.AccountNumber();
		cout << "\nBalance     : " << Client.AccountBalance;
		cout << "\n------------------------\n";
	}

	static clsBankClient _ReadClient() {

		string AccountNumber;
		AccountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(AccountNumber))
		{

			cout << "\nClient does not exist, please enter another account number? ";
			AccountNumber = clsInputValidate::ReadString();
		}
		
		return clsBankClient::Find(AccountNumber);

	}

	static double _ReadAmount(clsBankClient SourceClient) {

		double Amount;

		cout << "\nEnter transfer amount? ";

		Amount = clsInputValidate::ReadIntNumber("\nInvalid Number, PLease enter amount? ");

		while (SourceClient.AccountBalance < Amount) {

			cout << "\nAmont exceded avalable amount, please enter another amount? ";
			Amount = clsInputValidate::ReadDblNumber("\nInvalid Number, PLease enter amount? ");
		}
		return Amount;
	}

public:
	static void ShowTransferScreen() {

		_DrawScreenHeader("\t\tTransfer Screen");

		string AccountNumber;

		int Amount;

		cout << "\nPlease enter the number you want to transfer from? ";

		clsBankClient SourceClient = _ReadClient();

		_PrintClientCard(SourceClient);

		cout << "\nPlease enter the number you want to transfer to? ";

		clsBankClient DistenationClient = _ReadClient();

		_PrintClientCard(DistenationClient);

		Amount = _ReadAmount(SourceClient);

		char Answer = clsInputValidate::ReadAnswer("\nAre you sure you want to perform this operation? y/n? ");

		if (Answer == 'y' || Answer == 'Y')
		{
			if (!(SourceClient.AccountNumber() == DistenationClient.AccountNumber())) {

				if (SourceClient.Transfer(Amount, DistenationClient, CurrentUser.UserName()))
				{
					cout << "\nTransfer Done Successfully -:)\n";
					_PrintClientCard(SourceClient);
					_PrintClientCard(DistenationClient);
				}
				else
					cout << "\nTransfer Faild!\n";
			}else
				cout << "\nYou cannont transfer to the same account.\n";
				
		}
		else {
			cout << "\nOperation was cancelled -:(\n";
		}

	}

};

