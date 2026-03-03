#pragma once
#include"clsScreen.h"
#include "clsInputValidate.h"
#include "clsCurrenciesListScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateCurrencyRateScreen.h"
#include "clsCurrencyCalculatorScreen.h"
class clsCurrencyExchangeMenueScreen: private clsScreen
{
private:
	enum enCurrunciesMainMnueOption
	{
		cListCurruncies     = 1,
		cFindCurruncy       = 2,
		cUpdateRate         = 3,
		cCurruncyCalculator = 4,
		cMainMenue          = 5
	};

	static void _PerformCurrencyExchangeMenueChoice(enCurrunciesMainMnueOption enChoice) {

		switch (enChoice)
		{
		case clsCurrencyExchangeMenueScreen::cListCurruncies:
		{
			system("cls");
			_ShowListCurrunciesScreen();
			_GoBackToCurruncyExchangeMenueScreen();
			break;
		}
		case clsCurrencyExchangeMenueScreen::cFindCurruncy:
		{
			system("cls");
			_ShowFindCurruncyScreen();
			_GoBackToCurruncyExchangeMenueScreen();
			break;
		}
		case clsCurrencyExchangeMenueScreen::cUpdateRate:
		{
			system("cls");
			_ShowUpdateRateScreen();
			_GoBackToCurruncyExchangeMenueScreen();
			break;
		}
		case clsCurrencyExchangeMenueScreen::cCurruncyCalculator:
		{
			system("cls");
			_ShowCurruncyCalculatorScreen();
			_GoBackToCurruncyExchangeMenueScreen();
			break;
		}
		case clsCurrencyExchangeMenueScreen::cMainMenue:
		{
			break;
		}
		}

	}

	static void _ShowListCurrunciesScreen() {
		//cout << "\nList Curruncies Screen Will Be Here!\n";
		clsCurrenciesListScreen::_ShowCurrunciesListScreen();
	}

	static void _ShowFindCurruncyScreen() {
		//cout << "\nFind Curruncy Screen Will Be Here!\n";
		clsFindCurrencyScreen::ShowFindCurruncyScreen();
	}
	

	static void _ShowUpdateRateScreen() {
		//cout << "\nUpdate Rate Screen Will Be Here!\n";
		clsUpdateCurrencyRateScreen::_ShowUpdateCurrencyRateScreen();
	}
	
	static void _ShowCurruncyCalculatorScreen() {
		//cout << "\nCurruncy Calculator Screen Will Be Here!\n";
		clsCurrencyCalculatorScreen::ShowCurrencyCalculatorScreen();
	}


	static void _GoBackToCurruncyExchangeMenueScreen() {

		cout << "\n\tPress any key to back to curruncy Exchange menue screen.....";
		system("pause>0");
		ShowCurrencyExchangeMenueScreen();
	}


public:
	static void ShowCurrencyExchangeMenueScreen() {
		system("cls");
		_DrawScreenHeader("   Currency Exchange Main Screen");

		cout << endl;
		cout << setw(37) << left << "" << "==============================================\n";
		cout << setw(37) << left << "" << "\t\t Currency Exchange Menue\n";
		cout << setw(37) << left << "" << "==============================================\n";
		cout << setw(40) << left << "" << "[1] List Curruncies.\n";
		cout << setw(40) << left << "" << "[2] Find Curruncy.\n";
		cout << setw(40) << left << "" << "[3] Update Rate.\n";
		cout << setw(40) << left << "" << "[4] Curruncy Calculator.\n";
		cout << setw(40) << left << "" << "[5] Main Menue.\n";
		cout << setw(37) << left << "" << "==============================================\n";

		cout << setw(37) << left << "" << "Chose what do you want to do [1 - 5]? ";

		_PerformCurrencyExchangeMenueChoice((enCurrunciesMainMnueOption)clsInputValidate::ReadIntBetween(1, 5, "Invalid Choice, Enter Number Between[1-5]? "));

	}

};

