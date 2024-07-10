#include "bank.h"

vector <string> SplitString(string Line, string delim)
{
    short pos = 0;
    string CurrentWord = "";
    vector <string> vStrings;

    while ((pos = Line.find(delim)) != string::npos)
    {
        CurrentWord = Line.substr(0, pos);

        if (CurrentWord != "")
        {
            vStrings.push_back(CurrentWord);
        }

        Line.erase(0, pos + delim.length());

    }

    if (Line != "")
    {
        vStrings.push_back(Line);
    }

    return vStrings;
}

vector <stClientData> ReadClientsFromFileIntoVector(string FileName)
{
    fstream MyFile;
    vector <stClientData> vClients;

    MyFile.open(FileName, ios::in);

    if (MyFile.is_open())
    {
        string Line;
        stClientData Client;
        while (getline(MyFile, Line))
        {
            Client = ConvertLineToRecord(Line, delim);

            vClients.push_back(Client);
        }

        MyFile.close();
    }

    return vClients;
}

void PrintClientRecord(stClientData Client)
{
    cout << "| " << left << setw(15) << Client.AccountNumber;
    cout << "| " << left << setw(10) << Client.PinCode;
    cout << "| " << left << setw(40) << Client.ClientName;
    cout << "| " << left << setw(12) << Client.Phone;
    cout << "| " << left << setw(12) << Client.Balance;
}

void PrintAllClientsData(vector <stClientData> vClients)
{
    system("cls");
    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).\n";
    cout << "------------------------------------------------------------------------------------------------------------" << endl;

    cout << "| " << left << setw(15) << "Account Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n------------------------------------------------------------------------------------------------------------" << endl;

    if (vClients.size() == 0)
        cout << "\n\t\t\t\t No clients available.\n";

    for (stClientData& Client : vClients)
    {
        PrintClientRecord(Client);
        cout << endl;
    }
    cout << "------------------------------------------------------------------------------------------------------------" << endl;


}

void ShowMainMenu()
{
    system("cls");
    cout << "====================================================" << endl;
    cout << "\t\t Main Menu Screen" << endl;
    cout << "====================================================" << endl;
    cout << "\t[1] Show Client List" << endl;
    cout << "\t[2] Add new client" << endl;
    cout << "\t[3] Delete client" << endl;
    cout << "\t[4] Update client info" << endl;
    cout << "\t[5] Find Client" << endl;
    cout << "\t[6] Transactions" << endl;
    cout << "\t[7] Exit" << endl;
    cout << "====================================================" << endl;
    ExecuteMenuChoice((enMenuChoices)GetMenuChoice());
}

short GetMenuChoice()
{
    short MenuNumber=0;
    cout << "Choose what do you want to do? [1 to 7]?\n";
    cin >> MenuNumber;

    return MenuNumber;
}

void ExecuteMenuChoice(enMenuChoices MenuChoice)
{
    vector <stClientData> vClients;
    stClientData Client;
    string AccNumber;

    switch (MenuChoice)
    {
    case enMenuChoices::ShowClients:

        vClients = ReadClientsFromFileIntoVector(FileName);
        PrintAllClientsData(vClients);
        ReturnToMainMenu();
        break;

    case enMenuChoices::AddClient:

        AddingClientsScreen();
        AddClients();
        ReturnToMainMenu();
        break;

    case enMenuChoices::DeleteClient:

        vClients = LoadClientsDataFromFile(FileName);
        DeleteClientsScreen();
        AccNumber = GetAccNumToSearch();
        DeleteClientByAccountNumber(AccNumber, vClients);
        ReturnToMainMenu();
        break;

    case enMenuChoices::UpdateClientInfo:

        vClients = LoadClientsDataFromFile(FileName);
        UpdateClientsScreen();
        AccNumber = GetAccNumToSearch();
        UpdateClientByAccountNumber(AccNumber, vClients);
        ReturnToMainMenu();
        break;

    case enMenuChoices::FindClient:

        vClients = LoadClientsDataFromFile(FileName);
        FindClientsScreen();
        AccNumber = GetAccNumToSearch();
        FindClientByAccountNumber(AccNumber, vClients, Client);
        ReturnToMainMenu();
        break;

    case enMenuChoices::Transactions:
        TransactionMenuScreen();

        break;

    case enMenuChoices::ExitMenu:

        ProgramEndScreen();
        break;
    }
}

void ReturnToMainMenu()
{
    cout << "\n\nPress any key to return to main menu...";
    system("pause>0");
    ShowMainMenu();
}

stClientData ReadNewClient()
{
    stClientData ClientData;
    vector <stClientData> vClients = ReadClientsFromFileIntoVector(FileName);

    cout << "Enter account number: ";
    cin >> ClientData.AccountNumber;

    for (stClientData& Client : vClients)
    {
        while (ClientData.AccountNumber == Client.AccountNumber)//CHecking if account number already exists in file or not
        {
            cout << "Account number already exists! Enter a correct account number:\n";
            cin >> ClientData.AccountNumber;
            cout << endl;
        }
    }

    cout << "Enter PIN number: ";
    cin >> ClientData.PinCode;
    cin.ignore();

    cout << "Enter client name: ";
    getline(cin, ClientData.ClientName);

    cout << "Enter Phone number: ";
    cin >> ClientData.Phone;

    cout << "Enter Account balance: ";
    cin >> ClientData.Balance;

    return ClientData;
}

void AddDataLineToFile(string FileName, string stDataLine)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out | ios::app);

    if (MyFile.is_open())
    {
        MyFile << stDataLine << endl;

        MyFile.close();
    }
}

void AddNewClient()
{
    stClientData Client;
    Client = ReadNewClient();
    AddDataLineToFile(FileName, ConvertRecordToLine(Client, "#//#"));
}

void AddClients()
{
    char AddMore = 'Y';
    do
    {

        cout << "Adding new client:\n\n";

        AddNewClient();

        cout << "Client added successfully, do you want to add another? Y/N ";
        cin >> AddMore;

    } while (toupper(AddMore) == 'Y');
}

void AddingClientsScreen()
{
    system("cls");
    cout << "----------------------------------------" << endl;
    cout << "\t Add new clients screen " << endl;
    cout << "----------------------------------------" << endl;
}

void DeleteClientsScreen()
{
    system("cls");
    cout << "----------------------------------------" << endl;
    cout << "\t Delete clients screen " << endl;
    cout << "----------------------------------------\n" << endl;
}

void UpdateClientsScreen()
{
    system("cls");
    cout << "----------------------------------------" << endl;
    cout << "\t Update clients screen " << endl;
    cout << "----------------------------------------\n" << endl;
}

void FindClientsScreen()
{
    system("cls");
    cout << "----------------------------------------" << endl;
    cout << "\t Find clients screen " << endl;
    cout << "----------------------------------------\n" << endl;
}

string GetAccNumToSearch()
{
    string AccNumber = "";
    cout << "Enter account number: ";
    cin >> AccNumber;

    return AccNumber;
}

bool FindClientByAccountNumber(string AccNumber, vector <stClientData> vClients, stClientData& Client)
{
    vClients = LoadClientsDataFromFile(FileName);

    for (stClientData& C : vClients)
    {
        if (AccNumber == C.AccountNumber)
        {
            Client = C;
            PrintClientCard(Client);
            return true;
        }
    }
    cout << "Client with account number (" << AccNumber << ") is not found!";
    return false;
}

void PrintClientCard(stClientData Client)
{
    cout << "\nThe following are the client details:\n\n";
    cout << "-------------------------------------\n";
    cout << "Account Number : " << Client.AccountNumber << endl;
    cout << "Pin Code       : " << Client.PinCode << endl;
    cout << "Client Name    : " << Client.ClientName << endl;
    cout << "Phone          : " << Client.Phone << endl;
    cout << "Balance        : " << Client.Balance << endl;
    cout << "-------------------------------------\n";
}

vector <stClientData> LoadClientsDataFromFile(string FileName)
{
    fstream MyFile;
    vector <stClientData> vClients;

    MyFile.open(FileName, ios::in);

    if (MyFile.is_open())
    {
        string Line;
        stClientData Client;
        while (getline(MyFile, Line))
        {
            Client = ConvertLineToRecord(Line, delim);

            vClients.push_back(Client);
        }

        MyFile.close();
    }

    return vClients;
}

stClientData ConvertLineToRecord(string Line, string delim)
{
    stClientData Client;
    vector <string> vClientData;
    vClientData = SplitString(Line, delim);

    Client.AccountNumber = vClientData[0];
    Client.PinCode = vClientData[1];
    Client.ClientName = vClientData[2];
    Client.Phone = vClientData[3];
    Client.Balance = stod(vClientData[4]);

    return Client;
}

bool MarkClientForDeleteByAccountNumber(string AccNumber, vector <stClientData> &vClients)
{
    for (stClientData& C : vClients)
    {
        if (C.AccountNumber == AccNumber)
        {
            C.MarkClientForDeletion = true;
            return true;
        }
    }
    return false;
}

string ConvertRecordToLine(stClientData Client, string Separator)
{
    string ClientRecord = "";

    ClientRecord += Client.AccountNumber + Separator;
    ClientRecord += Client.PinCode + Separator;
    ClientRecord += Client.ClientName + Separator;
    ClientRecord += Client.Phone + Separator;
    ClientRecord += to_string(Client.Balance);

    return ClientRecord;
}

bool DeleteClientByAccountNumber(string AccountNumber, vector <stClientData>& vClients)
{
    stClientData Client;
    char Answer = 'n';

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        //PrintClientCard(Client);

        cout << "\n\nAre you sure yuu want to delete this client> y/n? ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
            SaveClientsDataToFile(FileName, vClients);

            //refresh clients:
            vClients = LoadClientsDataFromFile(FileName);
            cout << "\n\nClient deleted succesfully";
            return true;
        }
    }
        return false;

}

vector <stClientData> SaveClientsDataToFile(string FileName, vector <stClientData> vClients)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out);//overwrite

    string DataLine;

    if (MyFile.is_open())
    {
        for (stClientData C : vClients)
        {
            if (C.MarkClientForDeletion == false)
            {
                DataLine = ConvertRecordToLine(C,delim);//omly write records that are NOT marked for deletion
                MyFile << DataLine << endl;
            }
        }
        MyFile.close();
    }

    return vClients;
}

stClientData ChangeClientRecord(string AccountNumber)
{
    stClientData Client;

    Client.AccountNumber = AccountNumber;

    cout << "\n\nEnter PIN:\n";
    getline(cin >> ws, Client.PinCode);

    cout << "Enter name:\n";
    getline(cin, Client.ClientName);

    cout << "Enter phone:\n";
    getline(cin, Client.Phone);

    cout << "Enter account balance:\n";
    cin >> Client.Balance;

    return Client;
}

bool UpdateClientByAccountNumber(string AccountNumber, vector <stClientData>& vClients)
{
    stClientData Client;
    char Answer = 'n';

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        //PrintClientCard(Client);

        cout << "\n\nAre you sure yuu want to update this clients info? y/n? ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            for (stClientData& C : vClients)
            {
                if (C.AccountNumber == AccountNumber)
                {
                    C = ChangeClientRecord(AccountNumber);
                    break;
                }
            }
            SaveClientsDataToFile(FileName, vClients);
            cout << "\n\nClient info updated succesfully";
            return true;
        }
    }
        return false;
}

void ProgramEndScreen()
{
        system("cls");
        cout << "----------------------------------------" << endl;
        cout << "\t Program End :D " << endl;
        cout << "----------------------------------------" << endl;
}

void TransactionMenuScreen()
{
    system("cls");
    cout << "====================================================" << endl;
    cout << "\t\t Transactions Menu" << endl;
    cout << "====================================================" << endl;
    cout << "\t[1] Deposit" << endl;
    cout << "\t[2] Withdraw" << endl;
    cout << "\t[3] Total clients balance" << endl;
    cout << "\t[4] Return to Main Menu" << endl;
    cout << "====================================================" << endl;
    TransactionsSwitchCase((enTransactionMenuChoices)GetTransMenuChoice());
}

void TransactionsSwitchCase(enTransactionMenuChoices TransactionChoice)
{
    switch (TransactionChoice)
    {
    case enTransactionMenuChoices::Deposit:
        
        DepositMoneyScreen();
        DepositMoney();
        ReturnToTransactionMenu();
        break;

    case enTransactionMenuChoices::Withdraw:

        WithdrawMoneyScreen();
        WithdrawMoney();
        ReturnToTransactionMenu();
        break;

    case enTransactionMenuChoices::TotalBalance:

        ShowTotalBalance();
        ReturnToTransactionMenu();
        break;

    case enTransactionMenuChoices::MainMenu:

        ShowMainMenu();
        break;
    }
}

bool DepositMoney()
{
    vector<stClientData> vClients = LoadClientsDataFromFile(FileName);
    stClientData Client;
    string AccNumber = GetAccNumToSearch();
    int Deposit;
    char ans;

    if (FindClientByAccountNumber(AccNumber, vClients, Client))
    {
            for (stClientData& C : vClients)
            {
                if (C.AccountNumber == AccNumber)
                {
                    cout << "\nEnter deposit amount: ";
                    cin >> Deposit;
                    cout << "\nAre you sure you want to perform this transaction? y/n: ";
                    cin >> ans;
                    if (toupper(ans) == 'Y')
                    {
                        C.Balance += Deposit;
                        cout << "\nAmount has been deposited succesfully.\n";
                        cout << "New client balance : " << C.Balance << endl;
                        SaveClientsDataToFile(FileName, vClients);
                        return true;
                    }
                    else
                        return false;
                }
            }

    }
        return false;
}

bool WithdrawMoney()
{
    vector<stClientData> vClients = LoadClientsDataFromFile(FileName);
    stClientData Client;
    string AccNumber = GetAccNumToSearch();
    int Withdraw;
    char ans;

    if (FindClientByAccountNumber(AccNumber, vClients, Client))
    {
        for (stClientData& C : vClients)
        {
            if (C.AccountNumber == AccNumber)
            {
                cout << "\nEnter withdraw amount: ";
                cin >> Withdraw;
                while (Withdraw > C.Balance)
                {
                    cout << "Withdraw amount exceeds balance, you can withdraw up to : " << C.Balance << endl;
                    cout << "Please enter another amount to withdraw: ";
                    cin >> Withdraw;
                }
                cout << "\nAre you sure you want to perform this transaction? y/n: ";
                cin >> ans;
                if (toupper(ans) == 'Y')
                {
                    Withdraw *= -1;
                    C.Balance += Withdraw;
                    cout << "\nAmount has been withdrawed succesfully.\n";
                    cout << "New client balance : " << C.Balance << endl;
                    SaveClientsDataToFile(FileName, vClients);
                    return true;
                }
                else
                    return false;
            }
        }

    }
        return false;
}

void ShowTotalBalance()
{
    vector <stClientData> vClients = LoadClientsDataFromFile(FileName);

    PrintBalancesList(vClients);
}

void ReturnToTransactionMenu()
{
    cout << "\n\nPress any key to return to Transaction Menu...";
    system("pause>0");
    TransactionMenuScreen();
}

void DepositMoneyScreen()
{
    system("cls");
    cout << "----------------------------------------" << endl;
    cout << "\t Deposit money screen " << endl;
    cout << "----------------------------------------\n" << endl;
}

void WithdrawMoneyScreen()
{
    system("cls");
    cout << "----------------------------------------" << endl;
    cout << "\t Withdraw money screen " << endl;
    cout << "----------------------------------------\n" << endl;
}

short GetTransMenuChoice()
{
    short MenuNumber = 0;
    cout << "Choose what do you want to do? [1 to 4]?\n";
    cin >> MenuNumber;

    return MenuNumber;
}

void PrintBalancesList(vector <stClientData> vClients)
{
    system("cls");
    float TotalBalance = 0;
    cout << "\n\t\t\t\t\tBalances List (" << vClients.size() << ") Client(s).\n";
    cout << "------------------------------------------------------------------------------------------------------------" << endl;

    cout << "| " << left << setw(15) << "Account Number";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n------------------------------------------------------------------------------------------------------------" << endl;

    if (vClients.size() == 0)
        cout << "\t\t\t\t No clients available.";

    for (stClientData& Client : vClients)
    {
        TotalBalance += Client.Balance;
        PrintBalancesRecords(Client);
        cout << endl;
    }
    cout << "------------------------------------------------------------------------------------------------------------" << endl;
    cout << "\t\t\t\t\t     Total balance : " << TotalBalance;
}

void PrintBalancesRecords(stClientData Client)
{
    cout << "| " << left << setw(15) << Client.AccountNumber;
    cout << "| " << left << setw(40) << Client.ClientName;
    cout << "| " << left << setw(12) << Client.Balance;
}
