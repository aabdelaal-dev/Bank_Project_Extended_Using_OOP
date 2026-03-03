#pragma once

#include "clsScreen.h"
#include "clsClientListScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsTransactionsMenueScreen.h"
#include "clsManageUsersMenueScreen.h"
#include "Global.h"
#include "clsLoginScreen.h"
#include "clsLoginRegistersScreen.h"
#include "clsCurrencyExchangeMenueScreen.h"

class clsMainScreen : protected clsScreen
{
private:

	enum enMainMenueChoice {
		 eListClients  = 1, eAddNewClient          = 2,
		 eDeleteClient = 3, eUpdateClient		   = 4,
		 eFindClient   = 5, eShowTransactionsMenue = 6,
		 eManageUser   = 7, eLoginRegisters        = 8,
		 enCurrency    = 9, eExit                  = 10
	};

	static short _ReadMainMenueOption() {

		short Choice;

		cout << setw(37) << left << "" << "Choose what do you want to do [1 to 10]? ";
		
		Choice = clsInputValidate::ReadShortBetween(1, 10, "Enter Number Between [1 to 10]");

		return Choice;
	}

	static void _PerformMainMenueChoice(enMainMenueChoice enChoice) {

		switch (enChoice)
		{
		case clsMainScreen::eListClients:
		{
			system("cls");
			_ShowAllClientsScreen();
			_GoBackToMainMenue();
			break;
		}
		case clsMainScreen::eAddNewClient: {
			system("cls");
			_AddNewClientScreen();
			_GoBackToMainMenue();
			break;
		}
		case clsMainScreen::eDeleteClient: {

			system("cls");
			_DeleteClientScreen();
			_GoBackToMainMenue();

			break;
		}
		case clsMainScreen::eUpdateClient: {

			system("cls");
			_UpdateClientScreen();
			_GoBackToMainMenue();
			break;
		}
		case clsMainScreen::eFindClient: {

			system("cls");
			_FindClientScreen();
			_GoBackToMainMenue();

			break;
		}
		case clsMainScreen::eShowTransactionsMenue:
			system("cls");
			_ShowTransactionsMenueScreen();
			_GoBackToMainMenue();
			break;
		case clsMainScreen::eManageUser: {

			system("cls");
			_ShowManageUsersScreen();
			_GoBackToMainMenue();
			break;
		}
		case clsMainScreen::eLoginRegisters: {

			system("cls");
			_ShowLoginRegistersScreen();
			_GoBackToMainMenue();
			break;
		}
		case clsMainScreen::enCurrency: {

			system("cls");
			_ShowCurrencyExchangeScreen();
			_GoBackToMainMenue();
			break;
		}
		case clsMainScreen::eExit: {

			system("cls");
			_Logout();
			break;
		}
		}

	}

	static void _GoBackToMainMenue() {
		cout << "\n\tPress Any key to back to main menue.....";
		system("pause>0");
		ShowMainMenue();

	}

	static void _ShowAllClientsScreen() {

		clsCLientListScreen::ShowClientList();
	}

	static void _AddNewClientScreen() {
		//cout << "\nThis Screen for Add New client\n";
		clsAddNewClientScreen::ShowAddNewClientScreen();
		
	}

	static void _DeleteClientScreen() {
		
		clsDeleteClientScreen::ShowDeleteClientSceen();

	}
	
	static void _UpdateClientScreen() {
		//cout << "\nThis Screen for Update client\n";
		clsUpdateClientScreen::ShowUpdateClientScreen();
		
	}
	
	static void _FindClientScreen() {
		//cout << "\nThis Screen for Find client\n";
		clsFindClientScreen::ShowFindClientScreen();
	}

	static void _ShowTransactionsMenueScreen() {
		//cout << "\nThis is Transactions Menue Screen\n";

		clsTransactionsMenueScreen::ShowTransactionsMenue();
	}

	static void _ShowManageUsersScreen() {
		// cout << "\nThis is Manage Users Screen\n";
		clsManageUsersMenueScreen::ShowManageUsersScreen();
	}

	static void _Logout() {
		//cout << "\nThis is Exit Screen\n";

		CurrentUser = clsUser::Find("", "");

		//clsLoginScreen::_ShowLoginScreen();

	}

	static void _ShowLoginRegistersScreen() {
		 //cout << "\nlogin Registers screen will be here!\n";
		clsLoginRegistersScreen::_ShowLoginRegistersScreen();

	}

	static void _ShowCurrencyExchangeScreen() {

		//cout << "\nCurrency Exchange screen will be here!\n";
		clsCurrencyExchangeMenueScreen::ShowCurrencyExchangeMenueScreen();

	}
	void _ShowClientData(vector<clsBankClient> vClients) {

		for (clsBankClient& C : vClients)
		{
			cout << "| " << left << setw(15) << C.AccountNumber();
			cout << "| " << left << setw(20) << C.FullName();
			cout << "| " << left << setw(12) << C.Phone;
			cout << "| " << left << setw(20) << C.Email;
			cout << "| " << left << setw(10) << C.PinCode;
			cout << "| " << left << setw(12) << C.AccountBalance;
			cout << endl;
		}
	}


public:
	static void ShowMainMenue() {

		system("cls");
		clsScreen::_DrawScreenHeader("\t\tMain Screen");
		cout << setw(37) << left << "" << "==============================================\n";
		cout << setw(37) << left << "" << "\t\t\tMain Menue\n";
		cout << setw(37) << left << "" << "==============================================\n";
		cout << setw(37) << left << "" << "\t[1] Show Client List.\n";
		cout << setw(37) << left << "" << "\t[2] Add New Client.\n";
		cout << setw(37) << left << "" << "\t[3] Delete Client.\n";
		cout << setw(37) << left << "" << "\t[4] Update Client Info.\n";
		cout << setw(37) << left << "" << "\t[5] Find Client.\n";
		cout << setw(37) << left << "" << "\t[6] Transactions.\n";
		cout << setw(37) << left << "" << "\t[7] Manage Users.\n";
		cout << setw(37) << left << "" << "\t[8] Login Register.\n";
		cout << setw(37) << left << "" << "\t[9] Currency Exchange.\n";
		cout << setw(37) << left << "" << "\t[10] Logout.\n";
		cout << setw(37) << left << "" << "==============================================\n";
				
		_PerformMainMenueChoice((enMainMenueChoice)_ReadMainMenueOption());
	}


};
