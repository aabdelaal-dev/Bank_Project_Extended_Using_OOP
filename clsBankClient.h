#pragma once
#include "clsPerson.h"
#include "clsString.h"
#include <fstream>
#include <string>
#include <vector>


class clsBankClient :
public clsPerson

{
private:
	string _AccountNumber;
	string _PinCode;
	double _AccountBalance;
    bool _MarkForDelete = false;
	
	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode  = 2 };
	enMode _Mode;

	static clsBankClient _ConvertLineToClientObject(string Line, string Separator ="#//#" ) {

		vector<string> vClientData;

		vClientData = clsString::Split(Line, Separator);

		return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2], vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));


	}

    static clsBankClient _GetEmptyClienObject() {
        return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }

    static string _ConvertClientDataToLine(clsBankClient Client, string Separator = "#//#") {

        string Line="";
        Line += Client.FirstName + "#//#";
        Line += Client.LastName + "#//#";
        Line += Client.Email + "#//#";
        Line += Client.Phone + "#//#";
        Line += Client._AccountNumber + "#//#";
        Line += Client._PinCode + "#//#";
        Line += to_string(Client._AccountBalance);

        return Line;

    }

    static void _SaveClientsDataToFile(vector<clsBankClient> vClients)
    {

        fstream cFile;
        cFile.open("Clients.txt", ios::out);//overrite

        if (cFile.is_open()) {
            string Line = "";
            for (clsBankClient& C : vClients)
            {
                if (!C.MarkedForDelete()) {

                     Line = _ConvertClientDataToLine(C);
                     cFile << Line << endl;
                }

            }
        }
        cFile.close();


    }

    static vector<clsBankClient>  _LoadClientsDataFromFile() {

        vector<clsBankClient> vClients;

        fstream cFile;
        cFile.open("Clients.txt", ios::in);

        if (cFile.is_open()) {
            string Line;
            
            while (getline(cFile, Line)) {

                clsBankClient Client1 = _ConvertLineToClientObject(Line);

                 vClients.push_back(Client1);
                
            }
            cFile.close();
           
        }

        return vClients;

    }

    static void _AddClientDataLineToFle(string ClientLine)
    {
        fstream cFile;
        cFile.open("Clients.txt", ios::app);

        if (cFile.is_open())
        {
            cFile << ClientLine << endl;
            cFile.close();

        }


    }

    void _Update() {

        vector<clsBankClient> vClients;

        vClients = _LoadClientsDataFromFile();

        for (clsBankClient& C : vClients)
        {
            if (C.AccountNumber() == this->AccountNumber()) {
                C = *this;
                break;
            }
        }
        _SaveClientsDataToFile(vClients);

    }

    void _AddNew() {

        _AddClientDataLineToFle(_ConvertClientDataToLine(*this));

    }

    string _PrepareTransferLogRecord(clsBankClient DistenationClient, double Amount, string UserName, string Separator = "#//#") {
        string TransRecord = "";

        TransRecord += clsDate::GetSystemDateTimeString() + Separator;
        TransRecord += this->AccountNumber() + Separator; // Acc. Number from
        TransRecord += DistenationClient.AccountNumber() + Separator;// Acc. Number from
        TransRecord += to_string(Amount) + Separator; // amount
        TransRecord += to_string(this->_AccountBalance) + Separator; // Acc. balance from 
        TransRecord += to_string(DistenationClient.AccountBalance) + Separator; // Acc. balance to
        TransRecord += UserName;

        return TransRecord;
    }

    void _RegisterTransferLog(clsBankClient DistenationClient, double Amount, string UserName) {


        string TransferRecord = _PrepareTransferLogRecord(DistenationClient, Amount, UserName);

        fstream file;

        file.open("TransferLog.txt", ios::out | ios::app);

        if (file.is_open()) {
            file << TransferRecord << endl;
            file.close();
        }

    }

    struct stTransferLogRecord;

    static stTransferLogRecord _ConvertTransferLogDataLineToRecord(string Line, string Delimiter = "#//#") {

        vector<string> TransferLog = clsString::Split(Line, Delimiter);

        stTransferLogRecord TransferLogRecord;
        TransferLogRecord.DateTime = TransferLog[0];
        TransferLogRecord.SourceClient = TransferLog[1];
        TransferLogRecord.DistenationClient = TransferLog[2];
        TransferLogRecord.Amount = stoi(TransferLog[3]);
        TransferLogRecord.SourceClientBalance = stoi(TransferLog[4]);
        TransferLogRecord.DistenationClientBalance = stoi(TransferLog[5]);
        TransferLogRecord.User = TransferLog[6];

        return TransferLogRecord;

    }

public:

	clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone, string AccountNumber, string PinCode, float AccountBalance) :clsPerson(FirstName, LastName, Email, Phone) {

		_Mode = Mode;
		_AccountNumber = AccountNumber;
        _PinCode = PinCode;
		_AccountBalance = AccountBalance;
	}

    struct stTransferLogRecord
    {
        string DateTime;
        string SourceClient;
        string DistenationClient;
        double Amount;
        double SourceClientBalance;
        double DistenationClientBalance;
        string User;
    };

    bool IsEmpty() {
        return (this->_Mode == enMode::EmptyMode);
    }

    //Read Only Prop
    string AccountNumber()
    {
        return _AccountNumber;
    }

    //Set Prop
    void SetPinCode(string PinCode)
    {
        _PinCode = PinCode;
    }
    //Get Prop
    string GetPinCode()
    {
        return _PinCode;
    }
    __declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;


    //Set Prop
    void SetAccountBalance(float AccountBalance)
    {
        _AccountBalance = AccountBalance;
    }
    //Get Prop
    float GetAccountBalance()
    {
        return _AccountBalance;
    }
    __declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;

    //no UI Related Code Inside Object.
   /* void Print()
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << FirstName;
        cout << "\nLastName    : " << LastName;
        cout << "\nFull Name   : " << FullName();
        cout << "\nEmail       : " << Email;
        cout << "\nPhone       : " << Phone;
        cout << "\nAcc. Number : " << _AccountNumber;
        cout << "\nPassword    : " << _PinCode;
        cout << "\nBalance     : " << _AccountBalance;
        cout << "\n___________________\n";

    }*/

    static clsBankClient Find(string AccountNumber) {

        fstream ClientFile;

        ClientFile.open("Clients.txt",ios::in);//read mode

        if (ClientFile.is_open()) {

            string Line;
            while (getline(ClientFile, Line)) {

                clsBankClient Client = _ConvertLineToClientObject(Line);

                if (Client.AccountNumber() == AccountNumber) {
                    ClientFile.close();
                    return Client;

                }

            }
            ClientFile.close();
            return _GetEmptyClienObject();

        }

    }

    static clsBankClient Find(string AccountNumber, string PinCode) {

        fstream ClientsFile ;

        vector<clsBankClient> vBankClients;
        
        ClientsFile.open("Clients.txt", ios::in);//read mode
    
        if (ClientsFile.is_open()) {

            string Line;
            while (getline(ClientsFile,Line))
            {
                clsBankClient Client = _ConvertLineToClientObject(Line);
                if (Client.AccountNumber() == AccountNumber && Client.PinCode == PinCode) {

                    ClientsFile.close();
                    return Client;

                }
                vBankClients.push_back(Client);
            }
            ClientsFile.close();

        }
        return _GetEmptyClienObject();

    }

    static bool IsClientExist(string AccountNumber) {

        clsBankClient Client = clsBankClient::Find(AccountNumber);

        return (!Client.IsEmpty());
    }

    enum enSaveResult { svFaildEmptyObject = 0, svSucceded=1, svFialdClientExist };

    enSaveResult Save() {

        switch (_Mode)
        {
        case enMode::UpdateMode:
        {
            _Update();
            return enSaveResult::svSucceded;

        }
        case enMode::AddNewMode:

        {
             if (IsClientExist(this->AccountNumber()))
			    return enSaveResult::svFialdClientExist;
             else {
                _AddNew();
                _Mode = enMode::UpdateMode;
                return enSaveResult::svSucceded;

             }
        }

        case enMode::EmptyMode:
            if(IsEmpty())
                return enSaveResult::svFaildEmptyObject;
        }

    }

    static clsBankClient GetAddNewClientObject(string AccountNumber) {

        clsBankClient NewClient =  _GetEmptyClienObject();

        NewClient._AccountNumber = AccountNumber;

        NewClient._Mode = enMode::AddNewMode;

        return NewClient;
    }

    bool MarkedForDelete() {
		return _MarkForDelete;
	}

    bool Delete() {

        vector<clsBankClient> vClients = _LoadClientsDataFromFile();
        for (clsBankClient& C : vClients) {
            if (C.AccountNumber() == this->_AccountNumber) {

                C._MarkForDelete = true;
                break;
            }
        }

        _SaveClientsDataToFile(vClients);

        *this = _GetEmptyClienObject();

        return true;
    }
    

    static vector<clsBankClient> GetClientsList() {

        return _LoadClientsDataFromFile();
    }


    static double GetTotalBalances() {

        vector <clsBankClient> vClients = _LoadClientsDataFromFile();

        double TotalBalances = 0;

        for (clsBankClient& C : vClients) {
            TotalBalances += C.AccountBalance;
        }

        return TotalBalances;
    }

    void Deposit(double Amount) {
        _AccountBalance += Amount;
        Save();
    }

    bool Withdraw(double Amount) {

        if (Amount > _AccountBalance) {
            return false;
        }
        else {
            _AccountBalance -= Amount;
            Save();
        }        
        return true;
    }

    bool Transfer(double Amount, clsBankClient& DistenationClient, string UserName) {
        
        if (DistenationClient.AccountNumber() == this->_AccountNumber)
            return false;

        if (this->Withdraw(Amount)) {
            DistenationClient.Deposit(Amount);
            _RegisterTransferLog(DistenationClient, Amount, UserName);
            return true;
        }
        return false;
    }


    static vector<stTransferLogRecord> GetTransfereLogList() {

        fstream file;
        string line;
        //vector<string> TransferLogs;
        vector<stTransferLogRecord> vTransferLogRecords;

        file.open("TransferLog.txt", ios::in ); // read only

        if (file.is_open()) {

            while (getline(file,line))
            {
                vTransferLogRecords.push_back(_ConvertTransferLogDataLineToRecord(line));
            }
        }
        file.close();

        return vTransferLogRecords;
    }

};

