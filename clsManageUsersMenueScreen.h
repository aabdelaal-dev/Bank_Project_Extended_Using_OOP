#pragma once

#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsListUsersScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"

class clsManageUsersMenueScreen : protected clsScreen
{
private:
	enum enManageUsersMenue
	{
		eListUsers = 1, eAddNewUser = 2, eDeleteUser = 3, eUpdateUser = 4, eFindUser = 5, eBackToMainMenue
	}; 

	static void _PerformManageUsersMenueChoice(enManageUsersMenue enChoice) {


		switch (enChoice)
		{
		case clsManageUsersMenueScreen::eListUsers: {
			system("cls");
			_ShowListUsersScreen();
			_GoBackToManageUsersMenue();
			break;
		}
		case clsManageUsersMenueScreen::eAddNewUser:
		{
			system("cls");
			_ShowAddNewUserScreen();
			_GoBackToManageUsersMenue();
			break;
		}
		case clsManageUsersMenueScreen::eDeleteUser:
		{
			system("cls");
			_ShowDeleteUserScreen();
			_GoBackToManageUsersMenue();
			break;
		}
		case clsManageUsersMenueScreen::eUpdateUser:
		{
			system("cls");
			_ShowUpdateUserScreen();
			_GoBackToManageUsersMenue();
			break;
		}
		case clsManageUsersMenueScreen::eFindUser: {

			system("cls");
			_ShowFindUserScreen();
			_GoBackToManageUsersMenue();
			break;
		}
		case clsManageUsersMenueScreen::eBackToMainMenue:
		{
			break;
		}
		}

	}

	static void _ShowListUsersScreen() {
		//cout << "\n\tList Users Screen Will Be Here!";
		clsListUsersScreen::ShowListUsersScreen();
	}
	static void _ShowAddNewUserScreen() {
		//cout << "\n\tAdd New User Screen Will Be Here!";
		clsAddNewUserScreen::ShowAddNewUserScreen();
	}
	static void _ShowDeleteUserScreen() {
		//cout << "\n\tDelete User Screen Will Be Here!";

		clsDeleteUserScreen::_ShowDeleteUserScreen();
	}
	static void _ShowUpdateUserScreen() {
		//cout << "\n\tUpdate User Screen Will Be Here!";

		clsUpdateUserScreen::_ShowUpdateUserScreen();
	}
	static void _ShowFindUserScreen() {
		//cout << "\n\tFind User Screen Will Be Here!";
		clsFindUserScreen::_ShowFindUserScreen();
	}

	static void _GoBackToManageUsersMenue() {
		cout << "\n\n\nPress any key to back to Manage Users Screen.... ";
		system("pause>0");
		ShowManageUsersScreen();

	}
	

public:
	static void ShowManageUsersScreen() {

		system("cls");

		if (!CheckAccessRights(clsUser::enPermession::pManageUsers))
			return;

		clsScreen::_DrawScreenHeader("\t\tManage Users");
		cout << endl;
		cout << setw(37) << left << "" << "==============================================\n";
		cout << setw(37) << left << "" << "\t\tTransactions Menue\n";
		cout << setw(37) << left << "" << "==============================================\n";
		cout << setw(40) << left << "" << "[1] List Users.\n";
		cout << setw(40) << left << "" << "[2] Add New Users.\n";
		cout << setw(40) << left << "" << "[3] Delete Users.\n";
		cout << setw(40) << left << "" << "[4] Update Users.\n";
		cout << setw(40) << left << "" << "[5] Find Users.\n";
		cout << setw(40) << left << "" << "[6] Main Menue.\n";
		cout << setw(37) << left << "" << "==============================================\n";

		cout << setw(37) << left << "" << "Chose what do you want to do [1 - 6]? ";

		short Choice;
		Choice = clsInputValidate::ReadShortBetween(1, 6);

		_PerformManageUsersMenueChoice((enManageUsersMenue)Choice);


	}



};

