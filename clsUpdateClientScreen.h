#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "iostream"

class clsUpdateClientScreen : protected clsScreen
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

	static void _ReadClientInfo(clsBankClient& Client) {

		cout << "\nEnter First Name: ";
		Client.FirstName = clsInputValidate::ReadString();
		cout << "\nEnter Last Name: ";
		Client.LastName = clsInputValidate::ReadString();
		cout << "\nEnter Email: ";
		Client.Email = clsInputValidate::ReadString();
		cout << "\nEnter Phone Number: ";
		Client.Phone = clsInputValidate::ReadString();
		cout << "\nEnter Pin Code: ";
		Client.PinCode = clsInputValidate::ReadString();
		cout << "\nEnter Account Balance: ";
		Client.AccountBalance = clsInputValidate::ReadFloatNumber();


	}

public:
	static void ShowUpdateClientScreen() {

		if (!CheckAccessRights(clsUser::enPermession::pUpdateClient))
			return;

		clsScreen::_DrawScreenHeader("Update Client Screen");

		string AccountNumber = "";

		cout << "\nPlease Enter Account Number? ";

		AccountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(AccountNumber)) {
			cout << "\nClient dose not esist, Please enter another account number? ";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);

		_PrintClientCard(Client);

		cout << "\nAre you sure you want to update this client? (y/n)? ";
		char Answer = 'n';
		cin >> Answer;
		if (Answer == 'y'|| Answer == 'Y')
		{
			cout << "\n\nUpdate Client";
			cout << "\n___________________\n";

			_ReadClientInfo(Client);

			clsBankClient::enSaveResult SaveResult;

			SaveResult = Client.Save();
			switch (SaveResult)
			{
			case clsBankClient::svFaildEmptyObject:
				cout << "\nFaild to save because object is empty! ";
				_PrintClientCard(Client);
				break;
			case clsBankClient::svSucceded:
				cout << "\nClient saved successfully -)";
				_PrintClientCard(Client);
				break;
			case clsBankClient::svFialdClientExist:
				cout << "\nFaild to save object because it exists -(";
				break;
			default:
				break;
			}

		}
		 

	}



};


