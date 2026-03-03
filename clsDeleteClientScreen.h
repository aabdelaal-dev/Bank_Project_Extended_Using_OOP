#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "iostream"
using namespace std;
class clsDeleteClientScreen : protected clsScreen
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

public:
	static void ShowDeleteClientSceen() {

		if (!CheckAccessRights(clsUser::enPermession::pDeleteClient))
			return;


		_DrawScreenHeader("\tDelete Client Screen");

		string AccountNumber = "";

		cout << "\nPlease Enter Account Number You Want to Delete? ";
		AccountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nAccount Number Not Found Please Enter Another Account Number? ";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);

		_PrintClientCard(Client);

		cout << "\nAre You Sure you want to delete this Client? (y/n)? ";
		char Answer = 'n';

		cin >> Answer;

		if(Answer == 'y' || Answer == 'Y') {

			if (Client.Delete()) {
				
				cout << "\nClient Deleted Successfully. ";
				_PrintClientCard(Client);
			}
		}
		else {
			cout << "\nClient Was not deleted ^_^ .";
		}

	}
	

};

