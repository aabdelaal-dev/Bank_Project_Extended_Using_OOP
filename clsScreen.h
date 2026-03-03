#pragma once
#include<iostream>
#include "Global.h"
#include "clsUser.h"
#include "clsDate.h"

using namespace std;
class clsScreen
{

protected:
	static void _DrawScreenHeader(string Title, string SubTitle = "") {

		cout << "\n\t\t\t\t\t_________________________________________\n";
		cout << "\n\t\t\t\t\t   "<<Title;
		if (SubTitle != "")
			cout << "\n\t\t\t\t\t   " << SubTitle;
		cout << "\n\t\t\t\t\t_________________________________________\n";

        cout << "\n\t\t\t\t\t User: " << CurrentUser.UserName();
        cout << "\n\t\t\t\t\t Date: " << clsDate::DateToString(clsDate::GetSystemDate()) << "\n" << endl;

	}

    static bool CheckAccessRights(clsUser::enPermession Prmessions)
    {

        if (!CurrentUser.CheckAccessPermission(Prmessions))
        {
            cout << "\t\t\t\t\t______________________________________";
            cout << "\n\n\t\t\t\t\t  Access Denied! Contact your Admin.";
            cout << "\n\t\t\t\t\t______________________________________\n\n";
            return false;
        }
        else
            return true;

    }


};

