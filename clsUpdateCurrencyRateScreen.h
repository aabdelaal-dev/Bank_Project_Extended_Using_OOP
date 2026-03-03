#pragma once
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"
class clsUpdateCurrencyRateScreen : private clsScreen
{

private:

	static void _PrintCurrencyCard(clsCurrency Currency) {
		cout << "\nCurrency Card: \n";
		cout << "\n_________________________\n";
		cout << "\nCountry   :" << Currency.Country();
		cout << "\nCode      :" << Currency.CurrencyName();
		cout << "\nName      :" << Currency.CurrencyCode();
		cout << "\nRate/(1$) :" << Currency.Rate();
		cout << "\n_________________________\n";
	}

public:
	static void _ShowUpdateCurrencyRateScreen() {

		_DrawScreenHeader("\t Update Currency Rate Screen");

		string Code;
		cout << "Please Enter Currency Code? ";
		Code = clsString::ToUpper(clsInputValidate::ReadString());

		while (!clsCurrency::IsCurrencyExist(Code))
		{
			cout << "Currency is not Exist, Please Enter Currency Code? ";
			Code = clsString::ToUpper(clsInputValidate::ReadString());
		}

		clsCurrency Currency = clsCurrency::FindByCode(Code);
		_PrintCurrencyCard(Currency); 

		short Answer = 'n';
		Answer = clsInputValidate::ReadAnswer("\nAre you sure you want to update rate of this currency? ");

		if (Answer == 'Y' || Answer == 'y')
		{
			cout << "\nUpdate Currency Rate: \n";
			cout << "\n_________________________\n";
			cout << "\nEnter New Rate: ";

			float NewRate = clsInputValidate::ReadFloatNumber();

			Currency.UpdateRate(NewRate);
			cout << "\nCurrency Rate Updated Successfully :-)\n";

			_PrintCurrencyCard(Currency);
		}
		else
		{
			cout << "\nCurrency Rate does not updated :-(\n";

		}





	}
};

