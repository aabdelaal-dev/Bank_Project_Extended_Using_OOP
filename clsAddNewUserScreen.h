#pragma once
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"

class clsAddNewUserScreen : protected clsScreen 
{
private:
	
	static string _ReadNewUser(string Message) {
		string UserName;
		cout << Message;
		UserName = clsInputValidate::ReadString();
		return UserName;
	}

	static int _ReadUserPermessions() {

		char Answer = 'n';
		int Perm = 0;

		Answer = clsInputValidate::ReadAnswer("\nDo you want to give full access? y/n? ");

		if (Answer == 'y' || Answer == 'Y') {
			return -1;
		}

		cout << "\nDo you want to give access to: \n";

		Answer = clsInputValidate::ReadAnswer("\nShow client list? y/n ? ");
		if (Answer == 'y' || Answer == 'Y') {
			Perm += clsUser::enPermession::pShowClientList;
		}

		Answer = clsInputValidate::ReadAnswer("\nAdd new client? y/n ? ");
		if (Answer == 'y' || Answer == 'Y') {
			Perm += clsUser::enPermession::pAddNewClient;
		}

		Answer = clsInputValidate::ReadAnswer("\nDelete client? y/n ? ");
		if (Answer == 'y' || Answer == 'Y') {
			Perm += clsUser::enPermession::pDeleteClient;
		}

		Answer = clsInputValidate::ReadAnswer("\nUpdate client? y/n ? ");
		if (Answer == 'y' || Answer == 'Y') {
			Perm += clsUser::enPermession::pUpdateClient;
		}

		Answer = clsInputValidate::ReadAnswer("\nFind client? y/n ? ");
		if (Answer == 'y' || Answer == 'Y') {
			Perm += clsUser::enPermession::pFindClient;
		}

		Answer = clsInputValidate::ReadAnswer("\nTransactions client? y/n ? ");
		if (Answer == 'y' || Answer == 'Y') {
			Perm += clsUser::enPermession::pTransactions;
		}

		Answer = clsInputValidate::ReadAnswer("\nManage Users? y/n ? ");
		if (Answer == 'y' || Answer == 'Y') {
			Perm += clsUser::enPermession::pManageUsers;
		}

		Answer = clsInputValidate::ReadAnswer("\nLogin Registes? y/n ? ");
		if (Answer == 'y' || Answer == 'Y') {
			Perm += clsUser::enPermession::pLoginRegisters;
		}


		if (Perm == 255)
			return -1;

		return Perm;
	}

	static void _ReadUserInfo(clsUser &User) {

		cout << "\nEnter First Name: ";
		User.FirstName = clsInputValidate::ReadString();
		cout << "\nEnter Last Name: ";
		User.LastName = clsInputValidate::ReadString();
		cout << "\nEnter Email : ";
		User.Email = clsInputValidate::ReadString();
		cout << "\nEnter Phone: ";
		User.Phone = clsInputValidate::ReadString();
		cout << "\nEnter Password: ";
		User.Password = clsInputValidate::ReadString();
		cout << "\nEnter Permessions: ";
		User.Permessions = _ReadUserPermessions() ;
		
	}

	static void _PrintUser(clsUser User) {

		cout << "\nUser Card : \n";

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
	static void ShowAddNewUserScreen() {

		system("cls");

		clsScreen::_DrawScreenHeader("\tAdd New User Screen");

		string UserName; 
		UserName = _ReadNewUser("\nPlease Enter UserName? ");
		
		while (clsUser::IsUserExist(UserName)) {

			UserName = _ReadNewUser("\nUser Already Exist, Please Enter Another User? ");
		}
		
		clsUser User = clsUser::GetAddNewUserObject(UserName);
		
		_ReadUserInfo(User);

		clsUser::enSaveResult Result = User.Save();

		switch (Result)
		{
		case clsUser::svFaildEmptyObject:
		{
			cout << "\nFaild, Object is Empty. ";
			break;
		}
		case clsUser::svSucceded:
		{
			cout << "\nUser Added Successfully -)\n";
			_PrintUser(User);
			break;
		}
		case clsUser::svFialdUserExist:
		{
			cout << "Faild, User already exists -(\n";
			break;
		}
		}


	}

};

