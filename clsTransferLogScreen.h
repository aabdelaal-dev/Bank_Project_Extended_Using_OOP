#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"

class clsTransferLogScreen:private clsScreen
{

private:

	static void _PrintTransferLogRecord(clsBankClient::stTransferLogRecord Record)
	{

		cout << "\n" << setw(8) << left << "";
		cout << "| " << setw(28) << left << Record.DateTime;
		cout << "| " << setw(10) << left << Record.SourceClient;
		cout << "| " << setw(10) << left << Record.DistenationClient;
		cout << "| " << setw(10) << left << Record.Amount;
		cout << "| " << setw(12) << left << Record.SourceClientBalance;
		cout << "| " << setw(12) << left << Record.DistenationClientBalance;
		cout << "| " << setw(15) << left << Record.User;
		cout << endl;
	}
public:

	static void ShowTransferLogScreen() {

		vector <clsBankClient::stTransferLogRecord> vTransferLogList;
		vTransferLogList = clsBankClient::GetTransfereLogList();

		string SubTitle = "\t   (" + to_string(vTransferLogList.size()) + ") Transfer Log";

		_DrawScreenHeader("\t Transfer Log Screen", SubTitle);


		cout << setw(8) << left << "" << "\n\t______________________________________________________________________________________________________\n" << endl;

		cout << setw(8) << left << "";
		cout << "| " << setw(28) << left << "Date/Time";
		cout << "| " << setw(10) << left << "S.Acc";
		cout << "| " << setw(10) << left << "D.Acc";
		cout << "| " << setw(10) << left << "Amount";
		cout << "| " << setw(12) << left << "S.Balance";
		cout << "| " << setw(12) << left << "D.Balance";
		cout << "| " << setw(15) << left << "User";



		cout  << "\n\t______________________________________________________________________________________________________" << endl;

		if (vTransferLogList.size() == 0) {

			cout << setw(35) << left << "" << "\t\tThere is no Transfer Logs\n";
		}
		else
		{
			for (clsBankClient::stTransferLogRecord& R : vTransferLogList) {
				_PrintTransferLogRecord(R);
			}

		}

		
		cout << setw(8) << left << "" << "\n\t______________________________________________________________________________________________________\n\n" << endl;


	}
};

