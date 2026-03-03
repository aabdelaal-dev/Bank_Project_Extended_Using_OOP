#pragma once
#include "clsScreen.h"
#include "clsUser.h"
class clsDeleteUserScreen : private clsScreen
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

	static void _ShowDeleteUserScreen() {

		system("cls");

		clsScreen::_DrawScreenHeader("\t  Delete User Screen");

		cout << "\nEnter UserName ? ";
		string UserName = clsInputValidate::ReadString();

		while (!clsUser::IsUserExist(UserName))
		{
			cout << "\nUser does not exist, enter another UserName? ";

			string UserName = clsInputValidate::ReadString();
		}

		clsUser UserForDelete = clsUser::Find(UserName);

		_PrintUser(UserForDelete);

		char Answer;
		Answer = clsInputValidate::ReadAnswer("\nAre you sure you want to delete this user? y/n ? ");

		if (Answer == 'y' || Answer == 'Y') {

			if (UserForDelete.Delete()) {
			
				cout << "\n\nUser Deleted Succesfuly -)";
				_PrintUser(UserForDelete);

			}
			else
				cout << "\nUser does not deleted successfully -( ";

		}
		

	}
};

