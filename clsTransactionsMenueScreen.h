#pragma once
#include "clsMainScreen.h"
#include "clsScreen.h"
#include "clsUtil.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalancesScreen.h"
#include "clsTransferScreen.h"
#include "clsTransferLogScreen.h"


using namespace std;

class clsTransactionsMenueScreen: protected clsScreen
{
	enum enTranactionsMenueChoice {eDeposit = 1, eWithdraw = 2, eTotalBalances = 3, eTransfer = 4,
		eTransferLog = 5 , eMainMenue = 6};

	static short _ReadTransactionMenueOption() {

		short Choice;

		cout << setw(37) << left << "" << "Choose what do you want to do [1 to 6]? ";

		Choice = clsInputValidate::ReadShortBetween(1, 6, "Enter Number Between [1 to 6]");

		return Choice;
	}

	static void _PerformTransactionsMenueChoice(enTranactionsMenueChoice enChoice) {

		switch (enChoice)
		{
		case clsTransactionsMenueScreen::eDeposit:
		{
			system("cls");
			_ShowDepositScreen();
			_GoBackToTransactionsMenue();
			break;
		}
		case clsTransactionsMenueScreen::eWithdraw:
		{
			system("cls");
			_ShowWithdrawScreen();
			_GoBackToTransactionsMenue();
			break;
		}
		case clsTransactionsMenueScreen::eTotalBalances:
		{

			system("cls");
			_ShowTotalBalancesScreen();
			_GoBackToTransactionsMenue();
			break;
		}
		case clsTransactionsMenueScreen::eTransfer:
		{

			system("cls");
			_ShowTransferScreen();
			_GoBackToTransactionsMenue();
			break;
		}
		case clsTransactionsMenueScreen::eTransferLog:
		{

			system("cls");
			_ShowTransferLogScreen();
			_GoBackToTransactionsMenue();
			break;
		}
		case clsTransactionsMenueScreen::eMainMenue:
		{
		
			
		}
		}

	}

	static void _ShowDepositScreen() {
		
		/*cout << "\nDeposit screen will be here!";*/
		clsDepositScreen::ShowDepositScreen();
		
	}
	static void _ShowWithdrawScreen() {
		//cout << "\nWithdraw screen will be here!";
		clsWithdrawScreen::ShowWithdrawScreen();
	}
	static void _ShowTotalBalancesScreen() {
		//cout << "\nTotal balances screen will be here!";
		clsTotalBalancesScreen::ShowTotalBalancesScreen();
	}

	static void _ShowTransferScreen() {
		
		//cout << "\nTransere screen will be here!";

		clsTransferScreen::ShowTransferScreen();
	}

	static void _ShowTransferLogScreen() {
		
		cout << "\nTransere log screen will be here!\n";
		clsTransferLogScreen::ShowTransferLogScreen();
	}

	static void _GoBackToTransactionsMenue() {
		cout << "\n\tPress any key to back to Transaction menue screen....";
		system("pause>0");
		ShowTransactionsMenue();
	}

public:
	static void ShowTransactionsMenue() {


		system("cls");

		if (!CheckAccessRights(clsUser::enPermession::pTransactions))
			return;

		clsScreen::_DrawScreenHeader("\tTransactions Menue");
		cout << setw(37) << left << "" << "==============================================\n";
		cout << setw(37) << left << "" << "\t\tTransactions Menue\n";
		cout << setw(37) << left << "" << "==============================================\n";
		cout << setw(37) << left << "" << "\t[1] Deposit\n";
		cout << setw(37) << left << "" << "\t[2] Withdraw\n";
		cout << setw(37) << left << "" << "\t[3] Total Balances\n";
		cout << setw(37) << left << "" << "\t[4] Transfer\n";
		cout << setw(37) << left << "" << "\t[5] Transfer Log\n";
		cout << setw(37) << left << "" << "\t[6] Main Menue\n";
	
		cout << setw(37) << left << "" << "==============================================\n";

		//short choice = clsTransactionsMenueScreen::_ReadTransactionMenueOption();

		_PerformTransactionsMenueChoice((enTranactionsMenueChoice)_ReadTransactionMenueOption());

	}

};

