#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "clsString.h"
//#include <iomanip>

using namespace std;

class clsCurrency
{

private:

	enum enMode{ eEmptyMode = 0, eUpdateMode = 1};
	enMode _Mode;

	string _Country;
	string _CurrencyCode;
	string _CurrencyName;
	float _Rate;


	static clsCurrency _ConvertLineToCurrencyObject(string Line, string Delim = "#//#") {

		vector<string> vCurruncyData = clsString::Split(Line, Delim);

		return clsCurrency(enMode::eUpdateMode, vCurruncyData[0], vCurruncyData[1], vCurruncyData[2],
			stof(vCurruncyData[3]));
	}

	static vector<clsCurrency> _LoadCurrenciesDataFromFile() {

		vector<clsCurrency> vCurrunciesData;

		fstream File; 
		string Line;

		File.open("Currencies.txt", ios::in);// Read Only

		if (File.is_open()) {

			while (getline(File, Line))
			{
				vCurrunciesData.push_back(_ConvertLineToCurrencyObject(Line));
			}
		}
		File.close();

		return vCurrunciesData;
	}

	string _ConvertCurruncyObjectToLine(clsCurrency Curruncy, string Separator = "#//#") {

		string CurruncyRecord = "";

		CurruncyRecord += Curruncy.Country() + Separator;
		CurruncyRecord += Curruncy.CurrencyCode() + Separator;
		CurruncyRecord += Curruncy.CurrencyName() + Separator;
		CurruncyRecord += to_string(Curruncy.Rate());

		return CurruncyRecord;
	}

	void _SaveCurrunciesDataToFile(vector<clsCurrency> vCurrunciesData) {

		fstream File;
		string Line;
		File.open("Currencies.txt", ios::out);

		if (File.is_open()) {
			for (clsCurrency& C : vCurrunciesData) {
				Line = _ConvertCurruncyObjectToLine(C);
				File << Line << endl;
			}
		}
		File.close();

	}

	void _Update() {

		vector<clsCurrency> vCurrunciesData = _LoadCurrenciesDataFromFile();

		for (clsCurrency& C : vCurrunciesData)
		{
			if (C.CurrencyCode() == _CurrencyCode) {
				C = *this;
				//C.UpdateRate(_Rate); // circular refrence error
				break;
			}
		}

		_SaveCurrunciesDataToFile(vCurrunciesData);
	}

	static clsCurrency _GetEmptyCurruncyObject() {

		return clsCurrency(enMode::eEmptyMode, "", "", "", 0);
	}


public:

	clsCurrency(enMode Mode, string Country, string CurrencyCode, string CurrencyName, float Rate) {
		_Mode = Mode;
		_Country = Country;
		_CurrencyCode = CurrencyCode;
		_CurrencyName = CurrencyName;
		_Rate = Rate;
	}

	bool IsEmpty() {
		return _Mode == enMode::eEmptyMode;
	}

	string Country() {
		return _Country;
	}

	string CurrencyCode() {
		return _CurrencyCode;
	}

	string CurrencyName() {
		return _CurrencyName;
	}


	float Rate() {
		return _Rate;
	}

	void UpdateRate(float NewRate) {

		_Rate = NewRate;
		_Update();

	}

	static clsCurrency FindByCode(string CurrencyCode) {
		

		CurrencyCode = clsString::ToUpper(CurrencyCode);

		fstream File;

		File.open("Currencies.txt", ios::in); // read only

		if (File.is_open()) {
			string Line;

			while (getline(File, Line))
			{
				clsCurrency Currency = _ConvertLineToCurrencyObject(Line);
				if (clsString::ToUpper(Currency.CurrencyCode()) == CurrencyCode) {
					File.close();
					return Currency;
				}
			}
			File.close();
		}
		return _GetEmptyCurruncyObject();
		
	}

	static clsCurrency FindByCountry(string Country) {

		Country = clsString::ToUpper(Country);

		fstream File;

		File.open("Currencies.txt", ios::in); // read only

		if (File.is_open()) {
			string Line;

			while (getline(File, Line))
			{
				clsCurrency Currency = _ConvertLineToCurrencyObject(Line);
				if (clsString::ToUpper(Currency.Country()) == Country) {
					File.close();
					return Currency;
				}
			}
			File.close();
		}
		return _GetEmptyCurruncyObject();
	}

	static bool IsCurrencyExist(string CurrencyCode) {

		clsCurrency Currency = FindByCode(CurrencyCode);

		return (!Currency.IsEmpty());
	}

	static vector<clsCurrency> GetCurrunciesList() {

		return _LoadCurrenciesDataFromFile();
	}

	float ConvertToUSD(float Amount) {

		return (float)Amount / Rate();

	}

	float ConvertToAnotherCurrency(float Amount ,clsCurrency Currency2) {

		if (Currency2.CurrencyCode() == "USD") {
			return ConvertToUSD(Amount);
		}
		
		float CurrencyToUSD = ConvertToUSD(Amount);

		return CurrencyToUSD * Currency2.Rate();

	}

};

