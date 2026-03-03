#pragma once
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"
class clsCurrencyCalculatorScreen:private clsScreen
{

	static clsCurrency _ReadCurrency(string Msg) {

		string CurrencyCode;

		cout << Msg;

		CurrencyCode = clsInputValidate::ReadString();

		while (!clsCurrency::IsCurrencyExist(CurrencyCode))
		{
			cout << "\nCurrency does not exist, enter another one? \n";
			CurrencyCode = clsInputValidate::ReadString();
		}

		return  clsCurrency::FindByCode(CurrencyCode);

	}

	static void _PrintCurrencyCard(clsCurrency Currency, string Title = "currency calculation") {
		cout << "\n" << Title;
		cout << "\n_________________________\n";
		cout << "\nCountry   :" << Currency.Country();
		cout << "\nCode      :" << Currency.CurrencyName();
		cout << "\nName      :" << Currency.CurrencyCode();
		cout << "\nRate/(1$) :" << Currency.Rate();
		cout << "\n_________________________\n";
	}

	static float _ReadAmount() {

		cout << "\nEnter amount to exchange: ";

		float Amount = clsInputValidate::ReadFloatNumber();

		return Amount;

	}

	static void _PrintCalculationResult(float Amount, clsCurrency CurrencyFrom, clsCurrency CurrencyTo){
		
		_PrintCurrencyCard(CurrencyFrom, "Convert From: ");

		float AmountInUSD = CurrencyFrom.ConvertToUSD(Amount);

		cout << "\n" << Amount << " " << CurrencyFrom.CurrencyCode() << " = "
		   	 << AmountInUSD << " USD\n";

		if (CurrencyTo.CurrencyCode() == "USD")
			return;

		cout << "\nConverting From USD ";

		_PrintCurrencyCard(CurrencyTo, "To: ");

		float AmountFromUSD = CurrencyFrom.ConvertToAnotherCurrency(Amount, CurrencyTo);

		cout << "\n" << Amount << " " << CurrencyFrom.CurrencyCode() << " = "
			<< AmountFromUSD << " " << CurrencyFrom.CurrencyCode();

	}


public:
	static void ShowCurrencyCalculatorScreen() {

		char Continue = 'y';

		while (Continue == 'y' || Continue == 'Y')
		{
			system("cls");
			_DrawScreenHeader("\t   Currency Calculator Screen");

			clsCurrency CurrencyFrom = _ReadCurrency("\nEnter Currency1 Code? \n");

			clsCurrency CurrencyTo = _ReadCurrency("\nEnter Currency2 Code? \n");

			float Amount = _ReadAmount();

			_PrintCalculationResult(Amount, CurrencyFrom, CurrencyTo);

			cout << "\nDo you want to perform another calculation? y/n? ";
			cin >> Continue;

		}	
	}
};

