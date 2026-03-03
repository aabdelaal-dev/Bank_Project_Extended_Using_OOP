#pragma once

#include "clsScreen.h"
#include "clsUser.h"
#include "Global.h"
#include "clsMainScreen.h"
class clsLoginScreen : private clsScreen
{

private:

	static bool _Login() {

		bool LoginFaild = false;

		short LoginFaildCount = 0;
		
		string UserName, Password;
		do
		{
			if (LoginFaild) {
				LoginFaildCount++;
				cout << "\nInvalid UserName or Password, Please Enter Again: ";		
				cout << "\nYou have " << (3-LoginFaildCount) << " Tries to login.\n";
			}

			if (LoginFaildCount == 3) {
				cout << "\nYou are locked after 3 faild tries :-(\n";
				return false;
			}
			
			cout << "\nEnter UserName? ";
			cin >> UserName;

			cout << "\nEnter Password? ";
			cin >> Password;

			CurrentUser =  clsUser::Find(UserName, Password);
		
			LoginFaild = CurrentUser.IsEmpty();

		} while (LoginFaild);

		CurrentUser.RegisterLogIn();

		clsMainScreen::ShowMainMenue();

		return true;
	}

public:

	static bool _ShowLoginScreen() {
		system("cls");

		clsScreen::_DrawScreenHeader("\t\tLogin Screen");

		return _Login();

	}

};

