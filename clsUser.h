#pragma once
#include "clsPerson.h"
#include <vector>
#include<iostream>
#include <fstream>
#include "clsString.h"
#include "clsDate.h"
#include "clsUtil.h"


using namespace std;
class clsUser : public clsPerson
{

private:

	enum enMode {
		EmptyMode = 1, UpdateMode = 2, AddNewMode = 3
	};


	enMode _Mode;
	string _UserName;
	string _Password;
	int _Permessions = -1;

	bool _MarkForDelete = false;

	static clsUser _ConvertUserRecordToObject(string UserRecord) {

		vector<string> vUser = clsString::Split(UserRecord, "#//#");

		return clsUser(enMode::UpdateMode, vUser[0], vUser[1], vUser[2], vUser[3], vUser[4],
			clsUtil::DecryptText(vUser[5]), stoi(vUser[6]));

	}

	static vector<clsUser> _LoadUsersDataFromFile() {

		fstream UsersFile;
		string line;
		vector<clsUser> vUsers;
		UsersFile.open("Users.txt", ios::in);

		if (UsersFile.is_open()) {
			while (getline(UsersFile,line))
			{
				vUsers.push_back(_ConvertUserRecordToObject(line));
			}
		
		}
		UsersFile.close();
		return vUsers;

	}

	static string _ConvertUserObjectToLine(clsUser User) {
		string UserRecord= "";
		string Delim = "#//#";
		UserRecord += User.FirstName + Delim;
		UserRecord += User.LastName + Delim;
		UserRecord += User.Email + Delim;
		UserRecord += User.Phone + Delim;
		UserRecord += User.UserName() + Delim;
		UserRecord += clsUtil::EncreptText(User.Password) + Delim;
		UserRecord += to_string(User.Permessions);

		return UserRecord;
	}

	static void _SaveUsersDataToFile(vector<clsUser> vUsers) {
		
		fstream UsersFile;
		string line;


		UsersFile.open("Users.txt", ios::out);//overrite

		if (UsersFile.is_open())
		{
			for (clsUser& U : vUsers) {
				if (!U.MarkedForDeleted()) {
					line = _ConvertUserObjectToLine(U);
					UsersFile << line << endl;
				}
			}
		}
		UsersFile.close();

		
	}

	static void _AddUserDataLineToFile(string UserLine) {

		
		fstream UsersFile;

		UsersFile.open("Users.txt", ios::app);

		if (UsersFile.is_open())
		{
			UsersFile << UserLine << endl;
			UsersFile.close();
		}
	}

	static clsUser _GetEmptyUserObject() {

		return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	void _Update() {

		vector<clsUser> vUsers = _LoadUsersDataFromFile();

		for (clsUser& U : vUsers) {

			if (U.UserName() == _UserName) {
				U = *this;
			}
		}

		_SaveUsersDataToFile(vUsers);

	}

	void _AddNew() {

		_AddUserDataLineToFile(_ConvertUserObjectToLine(*this));

	}


	string _PrepareLogInRecord(string Separator = "#//#") {

		string RecordLine = "";

		RecordLine += clsDate::GetSystemDateTimeString() + Separator;
		RecordLine += UserName() + Separator;
		RecordLine += clsUtil::EncreptText(Password)+Separator;
		RecordLine += to_string(Permessions);

		return
			RecordLine;
	}	
	
	struct stLoginRegisterRecord;

	static stLoginRegisterRecord _ConvertLoginRegisterLineToRecord(string line) {

		vector <string> rRecord = clsString::Split(line, "#//#");
		stLoginRegisterRecord stRegisterRecord;

		stRegisterRecord.DateTime = rRecord[0];
		stRegisterRecord.UserName = rRecord[1];
		stRegisterRecord.Password = clsUtil::DecryptText(rRecord[2]);
		stRegisterRecord.Permessions = stoi(rRecord[3]);

		return stRegisterRecord;

	}

	static vector<stLoginRegisterRecord> _LoadLoginRegistersDataFromFile() {

		vector<stLoginRegisterRecord> vLoginRegisters;

		fstream file;

		file.open("LoginRegisters.txt", ios::in);
		string line;
		if (file.is_open()) {
			while (getline(file, line))
			{
				vLoginRegisters.push_back(_ConvertLoginRegisterLineToRecord(line));
			}

		}
		file.close();

		return vLoginRegisters;

	}




public:

	static struct stLoginRegisterRecord
	{
		string DateTime;
		string UserName;
		string Password;
		short Permessions = 0;
	};

	enum enPermession
	{
		pAll = -1,
		pShowClientList = 1, pAddNewClient = 2,
		pDeleteClient = 4, pUpdateClient = 8,
		pFindClient = 16, pTransactions = 32,
		pManageUsers = 64 , pLoginRegisters = 128
	};

	clsUser(enMode Mode, string FirstName, string LastName, string Email, string Phone, string UserName, string Password, int Permessions) :

		clsPerson(FirstName, LastName, Email, Phone) {
		_Mode = Mode;
		_UserName = UserName;
		_Password = Password;
		_Permessions = Permessions;

	}

	bool IsEmpty() {
		return (_Mode == enMode::EmptyMode);
	}

	bool MarkedForDeleted() {
		return _MarkForDelete;
	}

	//void SetUserName(string UserName) {
	//	_UserName = UserName;
	//}

	string UserName() {
		return _UserName;
	}

	//_declspec(property(get = GetUserName, put = SetUserName)) string UserName;

	void SetPassword(string Password) {
		_Password = Password;
	}

	string GetPassword() {
		return _Password;
	}

	_declspec(property(get = GetPassword, put = SetPassword)) string Password;

	void SetPermessions(int Permessions) {
		_Permessions = Permessions;
	}

	int GetPermessions() {
		return _Permessions;
	}

	_declspec(property(get = GetPermessions, put = SetPermessions)) int Permessions;

	static clsUser Find(string UserName) {

		fstream UsersFile;
		UsersFile.open("Users.txt", ios::in);//read only
		string line;
		if (UsersFile.is_open()) {

			while (getline(UsersFile, line))
			{
				clsUser User = _ConvertUserRecordToObject(line);;
				if (User._UserName == UserName) {
					UsersFile.close();
					return User;
				}
			}
		}
		UsersFile.close();
		return _GetEmptyUserObject();
	}

	static clsUser Find(string UserName, string Password) {

		fstream UsersFile;
		UsersFile.open("Users.txt", ios::in);//read only
		string line;
		if (UsersFile.is_open()) {

			while (getline(UsersFile, line))
			{
				clsUser User = _ConvertUserRecordToObject(line);;
				if (User._UserName == UserName && User._Password == Password) {
					UsersFile.close();
					return User;
				}
			}
		}
		UsersFile.close();
		return _GetEmptyUserObject();
	}

	static bool IsUserExist(string UserName) {
		clsUser User = Find(UserName);

		return (!User.IsEmpty());
	}

	enum enSaveResult { svFaildEmptyObject = 0, svSucceded = 1, svFialdUserExist };

	enSaveResult Save() {
		switch (this->_Mode)
		{
		case enMode::UpdateMode:
		{
			_Update();
			return enSaveResult::svSucceded;
		}
		case enMode::AddNewMode:
		{
			if (IsUserExist(this->_UserName)) {
				return enSaveResult::svFialdUserExist;
			}
			else {
				_AddNew();
				_Mode = enMode::AddNewMode;
				return enSaveResult::svSucceded;
			}
		}
		case enMode::EmptyMode:
		{
			return enSaveResult::svFaildEmptyObject;
		}
		}
	}

	static vector<clsUser> GetUsersList() {
		return _LoadUsersDataFromFile();
	}

	bool Delete() {

		vector<clsUser> vUsers = _LoadUsersDataFromFile();

		for (clsUser& U : vUsers) {
			if (U.UserName() == _UserName) {
				U._MarkForDelete = true;				
			}
		}
		_SaveUsersDataToFile(vUsers);
		*this = _GetEmptyUserObject();
		return true;
	}

	static clsUser GetAddNewUserObject(string UserName) {

		clsUser User = _GetEmptyUserObject();

		User._UserName = UserName;

		User._Mode = enMode::AddNewMode;

		return User;
	}

	bool CheckAccessPermission(enPermession Permession) {

		if (this->Permessions == enPermession::pAll)
			return true;

		if ((this->_Permessions & Permession) == Permession)
			return true;
		else
			return false;

	}

	void RegisterLogIn() {
		string RegisterLine = _PrepareLogInRecord();

		fstream logFile;
		logFile.open("LoginRegisters.txt",  ios::app);

		if (logFile.is_open()) {

			logFile << RegisterLine << endl;
			logFile.close();
		}


	}

	static vector<stLoginRegisterRecord> GetLoginRegistersList() {

		return _LoadLoginRegistersDataFromFile();

	}
};
