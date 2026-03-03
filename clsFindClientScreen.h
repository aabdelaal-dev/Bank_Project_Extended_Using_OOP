#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include <iostream>
using namespace std;

class clsFindClientScreen :protected clsScreen
{
private:
		static void _PrintClientCard(clsBankClient & Client) {
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


public:
	void static ShowFindClientScreen() {

		//system("cls");

		if (!CheckAccessRights(clsUser::enPermession::pFindClient))
			return;

		_DrawScreenHeader("\t  Find Client Screen");

		string AccountNumber;
		char Answer = 'n';

		do
		{
			cout << "\nPlease Enter Account Number To Find The Client? ";
			AccountNumber = clsInputValidate::ReadString();

			while (!clsBankClient::IsClientExist(AccountNumber)) {

				cout << "\nClient With Account Number " << AccountNumber << " not found, Please enter another one?  ";
				AccountNumber = clsInputValidate::ReadString();

			}

			clsBankClient Client = clsBankClient::Find(AccountNumber);


			if (!Client.IsEmpty()) {
				cout << "\nClient has Founded.\n";
			}
			else {
				cout << "\nClient wasnt found!\n";
			}

			_PrintClientCard(Client);

			cout << "\nDo You want to find another client? (y/n)? ";
			cin >> Answer;

		} while (Answer == 'y' || Answer == 'Y');

	}

};

