#pragma once
#include "clsCurrency.h"
#include "clsScreen.h"

class clsCurrenciesListScreen: private clsScreen
{

private:

	static void _PrintCurruncyRecordLine(clsCurrency Currency ) {


		cout << setw(8) << left << "";
		cout << "| " << setw(35) << left << Currency.Country();
		cout << "| " << setw(10) << left << Currency.CurrencyCode();
		cout << "| " << setw(40) << left << Currency.CurrencyName();
		cout << "| " << setw(15) << left << Currency.Rate();
		cout << endl;

	}
public:
	static void _ShowCurrunciesListScreen() {

		vector<clsCurrency> vCurrencies = clsCurrency::GetCurrunciesList();

		string Title = "\t   Curruncies List Screen";
		string SubTitle = "\t    (" + to_string(vCurrencies.size()) + ") Curruncy";

		_DrawScreenHeader(Title, SubTitle);

		cout << "\n\t________________________________________________________________________________________________________\n" << endl;

		cout << setw(8) << left << "";
		cout << "| " << setw(35) << left << "Country";
		cout << "| " << setw(10) << left << "Code";
		cout << "| " << setw(40) << left << "Name";
		cout << "| " << setw(15) << left << "Rate/(1$)";

		cout << "\n\t________________________________________________________________________________________________________\n" << endl;

		if (vCurrencies.size() == 0)
		{
			cout << "\n\t\t\t\t\tThere is no Curruncies Avalable :-(\n";
		}
		else
		{
			for (clsCurrency& C : vCurrencies)
			{
				_PrintCurruncyRecordLine(C);
			}
		}

		cout << "\n\t________________________________________________________________________________________________________\n" << endl;
	}

};

