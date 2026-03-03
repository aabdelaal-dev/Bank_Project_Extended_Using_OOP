#pragma once
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"

class clsUpdateUserScreen: private clsScreen
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

		Answer = clsInputValidate::ReadAnswer("\nManage Users? y/n ? ");
		if (Answer == 'y' || Answer == 'Y') {
			Perm += clsUser::enPermession::pLoginRegisters;
		}


		if (Perm == 255)
			return -1;

		return Perm;
	}

	static void _ReadUserInfo(clsUser& User) {

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
		User.Permessions = _ReadUserPermessions();

	}


public:

	static void _ShowUpdateUserScreen() {

		system("cls");

		clsScreen::_DrawScreenHeader("\t  Update User Screen");

		cout << "\nEnter UserName ? ";
		string UserName = clsInputValidate::ReadString();

		while (!clsUser::IsUserExist(UserName))
		{
			cout << "\nUser does not exist, enter another UserName? ";

			string UserName = clsInputValidate::ReadString();
		}

		clsUser User = clsUser::Find(UserName);

		_PrintUser(User);

		char Answer;
		Answer = clsInputValidate::ReadAnswer("\nAre you sure you want to Update this user? y/n ? ");

		if (Answer == 'y' || Answer == 'Y') {
			
			_ReadUserInfo(User);

			clsUser::enSaveResult Result = User.Save();

			switch (Result)
			{
			case clsUser::svFaildEmptyObject:
			{
				cout << "\nFaild to Update, Object is empty!";
				break;
			}
			case clsUser::svSucceded:
			{
				cout << "\nUser Updated Successfully -)";
				_PrintUser(User);
				break;
			}
			case clsUser::svFialdUserExist:
			{
				cout << "\nFaild to Update, User is Exist -(";
				break;
			}
			}

		}


	}
};

