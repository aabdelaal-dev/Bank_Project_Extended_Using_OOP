#pragma once
#include"clsScreen.h"
#include "clsUser.h"

class clsLoginRegistersScreen : private clsScreen
{

private:


	static void _PrintLoginRegisterRecord(clsUser::stLoginRegisterRecord RegisterRecord) {
		
		cout << setw(8) << left << "";
		cout << "| " << setw(35) << left << RegisterRecord.DateTime;
		cout << "| " << setw(20) << left << RegisterRecord.UserName;
		cout << "| " << setw(20) << left << RegisterRecord.Password;
		cout << "| " << setw(15) << left << to_string(RegisterRecord.Permessions) << endl;

	}

public:

	static void _ShowLoginRegistersScreen() {

		if (!clsScreen::CheckAccessRights(clsUser::enPermession::pLoginRegisters)) {
			return;
		}

		vector <clsUser::stLoginRegisterRecord>  vLoginRegisters = clsUser::GetLoginRegistersList();

		string SubTitle = "\t      (" + to_string(vLoginRegisters.size()) + ") Record(s).";

		_DrawScreenHeader("\tLogin Registers List Screen", SubTitle);


		cout << setw(8) << left << "" << "\n\t______________________________________________________________________________________________________\n" << endl;

		cout << setw(8) << left << "";
		cout << "| " << setw(35) << left << "Date/Time";
		cout << "| " << setw(20) << left << "UserName";
		cout << "| " << setw(20) << left << "Password";
		cout << "| " << setw(15) << left << "Permessions";



		cout << setw(8) << left << "" << "\n\t______________________________________________________________________________________________________\n\n" << endl;


		if (vLoginRegisters.size() == 0) {
			cout << setw(35) << left << "" << "\t\tThere is no Login Registers!\n";
		}
		else {
			for (clsUser::stLoginRegisterRecord& Reg : vLoginRegisters) {
				_PrintLoginRegisterRecord(Reg);
			}
		}

		cout << setw(8) << left << "" << "\n\t______________________________________________________________________________________________________\n\n" << endl;

	}
};

