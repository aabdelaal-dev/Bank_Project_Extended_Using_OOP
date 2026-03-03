#pragma once
#include <iostream>
#include <iomanip>
#include "clsBankClient.h"
#include "clsMainScreen.h"

class clsCLientListScreen:  protected clsScreen 
{
private:

	static void _PrintClientRecordLine(vector<clsBankClient> vClients) {

		for (clsBankClient& C : vClients)
		{
			cout << setw(8) << left << "" << "| " << left << setw(15) << C.AccountNumber();
			cout << "| " << left << setw(20) << C.FullName();
			cout << "| " << left << setw(12) << C.Phone;
			cout << "| " << left << setw(20) << C.Email;
			cout << "| " << left << setw(10) << C.PinCode;
			cout << "| " << left << setw(12) << C.AccountBalance;
			cout << endl;
		}
	}
public:
	static void ShowClientList(){

		if (!CheckAccessRights(clsUser::enPermession::pShowClientList))
			return;

		vector <clsBankClient> vClients = clsBankClient::GetClientsList();

		string Title = "\t   Client List Screen";
		string SubTitle = "\t     (" + to_string(vClients.size()) + ") Client(s)";

		_DrawScreenHeader(Title, SubTitle);

		if (vClients.size() > 0) {
			

			cout << setw(8) << left << "" <<
				"\n\t____________________________________________________________________________________________________________\n" << endl;
			cout << setw(8) << left << "" << "| " << left << setw(15) << "Account Number";
			cout << "| " << left << setw(20) << "Client Name";
			cout << "| " << left << setw(12) << "Phone";
			cout << "| " << left << setw(20) << "Email";
			cout << "| " << left << setw(10) << "Pin Code";
			cout << "| " << left << setw(12) << "Balance";
			cout << "\n";
			cout << setw(8) << left << "" << "____________________________________________________________________________________________________________\n";


			_PrintClientRecordLine(vClients);
			cout << setw(8) << left << "" << "\n\t____________________________________________________________________________________________________________\n"<<endl;
		}
		else {
			cout << "\n\t____________________________________________________________________________________________________________\n";
			cout << "\n" << setw(8) << left << "" << "\t\t\t\t\tThers is no Clients Exist!\t\t\t\t";
			cout << "\n\t____________________________________________________________________________________________________________\n" << endl;

		}

	}

};

