#pragma once
#include "clsScreen.h"
#include"clsCurrency.h"
#include "clsString.h"
class clsFindCurrencyScreen : private clsScreen
{
private:

	static clsCurrency _FindCurrency(short FindBy) {

		if (FindBy == 1) {
			string Code;
			cout << "\nPlease Enter Country Code? ";
			Code = clsString::ToUpper(clsInputValidate::ReadString());
						
			clsCurrency Currency = clsCurrency::FindByCode(Code);
			return Currency;

		}
		else {
			string Country;
			cout << "\nPlease Enter Country Name? ";
			Country = clsString::ToUpper(clsInputValidate::ReadString());

			clsCurrency Currency = clsCurrency::FindByCountry(Country);
			return Currency;

		}
	}

	static void _PrintCurrency(clsCurrency Currency) {
		cout << "\n_________________________\n";
		cout << "\nCountry   :" << Currency.Country();
		cout << "\nCode      :" << Currency.CurrencyName();
		cout << "\nName      :" << Currency.CurrencyCode();
		cout << "\nRate/(1$) :" << Currency.Rate();
		cout << "\n_________________________\n";
	}

public:
	static void ShowFindCurruncyScreen() {

		_DrawScreenHeader("\t  Find Curruncy Screen");
		short FindChoice;

		cout << "\nFind by: [1] Code or [2] Country ? ";
		FindChoice = clsInputValidate::ReadIntBetween(1, 2, "Invalid choice, Enter Number between [1-2]? ");

		clsCurrency Currency = _FindCurrency(FindChoice);

		if (Currency.IsEmpty())
			cout << "\Currency Not Found :-(\n";

		else {
			cout << "\Currency Found :-)\n";
			_PrintCurrency(Currency);
		}
	}

};

