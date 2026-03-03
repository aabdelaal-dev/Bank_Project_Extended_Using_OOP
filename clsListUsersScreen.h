#pragma once

#include "clsScreen.h"
#include "clsUser.h"
#include <iomanip>

class clsListUsersScreen :protected clsScreen 
{

private:

	static void _PrintUserRecordLine(clsUser User) {

		cout << setw(8) << left << "";
		cout << "| " << setw(12) << left << User.UserName();
		cout << "| " << setw(25) << left << User.FullName();
		cout << "| " << setw(12) << left << User.Phone;
		cout << "| " << setw(20) << left << User.Email;
		cout << "| " << setw(10) << left << User.Password;
		cout << "| " << setw(12) << left << User.Permessions;

	}
public:
	static void ShowListUsersScreen() {

		system("cls");

		vector <clsUser> vUsers = clsUser::GetUsersList();

		string Title = "\t   List Users Screen";
		string SubTitel = "\t     (" + to_string(vUsers.size()) + ") User(s)";

		clsScreen::_DrawScreenHeader(Title,SubTitel);

		cout << setw(8) << left << "" << "\n\t______________________________________________________________________________________________________\n" << endl;

		cout << setw(8) << left << "";
		cout << "| " << setw(12) << left << "UserName";
		cout << "| " << setw(25) << left << "Full Name";
		cout << "| " << setw(12) << left << "Phone"; 
		cout << "| " << setw(20) << left << "Email"; 
		cout << "| " << setw(10) << left << "Password"; 
		cout << "| " << setw(12) << left << "Permessions";
			

		
		cout << setw(8) << left << "" << "\n\t______________________________________________________________________________________________________\n" << endl;

		if (vUsers.size() == 0) {
			cout << setw(35) << left << "" << "\t\tThere is no users exists!\n";
		}
		else {
			for (clsUser & U: vUsers)
			{
				_PrintUserRecordLine(U);
				cout << endl;
			}
		}
		cout <<setw(37) << left << "" << "\n\t______________________________________________________________________________________________________\n";

	}
};

