#pragma once
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"

class clsFindUserScreen : private clsScreen
{

private:

	static void _PrintUser(clsUser User) {

		cout << "\nUser Card : ";
		cout << "\n_____________________________";
		cout << "\nFirst Name  : " << User.FirstName;
		cout << "\nLast Name   : " << User.LastName;
		cout << "\nFull Name   : " << User.FullName();
		cout << "\nEmail       : " << User.Email;
		cout << "\nPhone       : " << User.Phone;
		cout << "\nUserName    : " << User.UserName();
		cout << "\nPermessions : " << User.Permessions;
		cout << "\n_____________________________";

	}



public:

	static void _ShowFindUserScreen() {

		system("cls");

		clsScreen::_DrawScreenHeader("\t    Find User Screen");

		cout << "\nEnter UserName ? ";
		string UserName = clsInputValidate::ReadString();

		while (!clsUser::IsUserExist(UserName))
		{
			cout << "\nUser does not exist, enter another UserName? ";

			UserName = clsInputValidate::ReadString();
		}
		clsUser User = clsUser::Find(UserName);

		if (!User.IsEmpty())
			cout << "\nUser Found :-) \n";
		else
			cout << "\nUser Not Found :-( \n";


		_PrintUser(User);
		
	}
};

