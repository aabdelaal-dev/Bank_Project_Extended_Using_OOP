#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include <iomanip>
#include <string>
class clsTotalBalancesScreen : protected clsScreen
{
private :
	static void _PrintClientRecordBalanceLine(clsBankClient Client)
	{
		cout << setw(25) << left << "" << "| " << setw(15) << left << Client.AccountNumber();
		cout << "| " << setw(40) << left << Client.FullName();
		cout << "| " << setw(12) << left << Client.AccountBalance;
	}


public:
	static void ShowTotalBalancesScreen(){
		
		system("cls");
		vector <clsBankClient> vClients = clsBankClient::GetClientsList();
		int ClientsCount = vClients.size();
		string SubTittle = "\t\t(" + to_string(vClients.size()) + ") Client(s)";

		clsScreen::_DrawScreenHeader("\tBalance List Screen", SubTittle);


		cout << setw(25) << left << "" << "\n\t\t_______________________________________________________";
		cout << "__________________________\n" << endl;


		cout << setw(25) << left << "" << "| " << setw(15) << left << "Account Number" << "| " << setw(40) << left << "Client Name" << "| " << setw(12) << left << "Balance" ;


		cout << "\n\t\t_______________________________________________________";
		cout << "__________________________\n" << endl;


		if (vClients.size() == 0) {
			cout << "\t\t\t\t\t\tNo Clients Available";
		}
		else {
			for (clsBankClient& C : vClients) {
				_PrintClientRecordBalanceLine(C);
				cout << endl;
			}
		}
		cout << "\n\t\t_______________________________________________________";
		cout << "__________________________\n" << endl;


		double TotalBalances = clsBankClient::GetTotalBalances();

		cout << setw(8) <<left << "" << "\t\t\t\t\t\tTotal Balances = " << TotalBalances << endl;
		cout << setw(8) << left << "" << "\t\t\t\t  ( " << clsUtil::NumberToText(TotalBalances) << " )" << endl;

	}

};

