#include "bank.h"
UserData CurrentUser;

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
    cout << "\t[7] Manage Users" << endl;
    cout << "\t[8] Log out" << endl;
    cout << "====================================================" << endl;
    ExecuteMenuChoice((enMenuChoices)GetMenuChoice());
}

short GetMenuChoice()
{
    short MenuNumber = 0;
    cout << "Choose what do you want to do? [1 to 8]?\n";
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

        if (!CheckAccessPermission(enPermissions::pListClients))
        {
            ShowAccessDeniedScreen();
            ReturnToMainMenu();
        }

        vClients = ReadClientsFromFileIntoVector(FileName);
        PrintAllClientsData(vClients);
        ReturnToMainMenu();
        break;

    case enMenuChoices::AddClient:

        if (!CheckAccessPermission(enPermissions::pAddNewClient))
        {
            ShowAccessDeniedScreen();
            ReturnToMainMenu();
        }

        AddingClientsScreen();
        AddClients();
        ReturnToMainMenu();
        break;

    case enMenuChoices::DeleteClient:

        if (!CheckAccessPermission(enPermissions::pDeleteClient))
        {
            ShowAccessDeniedScreen();
            ReturnToMainMenu();
        }

        vClients = LoadClientsDataFromFile(FileName);
        DeleteClientsScreen();
        AccNumber = GetAccNumToSearch();
        DeleteClientByAccountNumber(AccNumber, vClients);
        ReturnToMainMenu();
        break;

    case enMenuChoices::UpdateClientInfo:

        if (!CheckAccessPermission(enPermissions::pUpdateClient))
        {
            ShowAccessDeniedScreen();
            ReturnToMainMenu();
        }

        vClients = LoadClientsDataFromFile(FileName);
        UpdateClientsScreen();
        AccNumber = GetAccNumToSearch();
        UpdateClientByAccountNumber(AccNumber, vClients);
        ReturnToMainMenu();
        break;

    case enMenuChoices::FindClient:

        if (!CheckAccessPermission(enPermissions::pFindClient))
        {
            ShowAccessDeniedScreen();
            ReturnToMainMenu();
        }

        vClients = LoadClientsDataFromFile(FileName);
        FindClientsScreen();
        AccNumber = GetAccNumToSearch();
        FindClientByAccountNumber(AccNumber, vClients, Client);
        ReturnToMainMenu();
        break;

    case enMenuChoices::Transactions:

        if (!CheckAccessPermission(enPermissions::pTransactions))
        {
            ShowAccessDeniedScreen();
            ReturnToMainMenu();
        }

        TransactionMenuScreen();
        break;

    case enMenuChoices::ManageUsers:

        if (!CheckAccessPermission(enPermissions::pManageUsers))
        {
            ShowAccessDeniedScreen();
            ReturnToMainMenu();
        }

        ShowManageUsersMenu();
        break;

    case enMenuChoices::LogOut:

        StartProgram();
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

bool MarkClientForDeleteByAccountNumber(string AccNumber, vector <stClientData>& vClients)
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
                DataLine = ConvertRecordToLine(C, delim);//omly write records that are NOT marked for deletion
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

/////////////////BANK EXTENSION//////////////////////

void LoginScreen()
{
    
    system("cls");
    cout << "----------------------------------------" << endl;
    cout << "\tLogin Screen " << endl;
    cout << "----------------------------------------" << endl;

}

void StartProgram()
{
    bool IsValidUser = true;

    do
    {
        string UserName, Password;
        LoginScreen();

        if (!IsValidUser)
            cout << "\nInvalid username/password!";

        cout << "\nEnter Username:";
        cin >> UserName;

        cout << "\nEnter Password:";
        cin >> Password;

        IsValidUser = CheckUserAndPass(UserName,Password,CurrentUser);

    } while (!IsValidUser);

    ShowMainMenu();
}

bool CheckUserAndPass(string UserName, string Password,UserData &CurrentUser)
{
    vector <UserData> vUserData;
    vUserData = LoadUsersDataIntoVector();

    for (UserData &FileUser : vUserData)
    {
        if (UserName == FileUser.UserName && Password == FileUser.Password)
        {
            CurrentUser = FileUser;
            return true;
        }

    }
    return false;
}

vector <UserData> LoadUsersDataIntoVector()
{
    fstream MyFile;
    vector <UserData> vUsers;

    MyFile.open(FileNameUser, ios::in);

    if (MyFile.is_open())
    {
        string Line;
        UserData User;
        while (getline(MyFile, Line))
        {
            User = ConvertUserLineToRecord(Line, delim);

            vUsers.push_back(User);
        }

        MyFile.close();
    }

    return vUsers;
}

UserData ConvertUserLineToRecord(string Line, string delim)
{
    UserData User;
    vector <string> vUserString;
    vUserString = SplitString(Line, delim);

    User.UserName = vUserString[0];
    User.Password = vUserString[1];
    User.UserPermissions = stoi(vUserString[2]);
    return User;
}

void ShowManageUsersMenu()
{
    system("cls");
    cout << "====================================================" << endl;
    cout << "\t\t Manage Users Menu Screen" << endl;
    cout << "====================================================" << endl;
    cout << "\t[1] List Users" << endl;
    cout << "\t[2] Add New User" << endl;
    cout << "\t[3] Delete User" << endl;
    cout << "\t[4] Update User" << endl;
    cout << "\t[5] Find User" << endl;
    cout << "\t[6] Main Menu" << endl;
    cout << "====================================================" << endl;
    ExecuteUsersMenuChoice((enUserMenuChoices)GetUserMenuChoice());
}

short GetUserMenuChoice()
{
    short MenuNumber = 0;
    cout << "Choose what do you want to do? [1 to 6]?\n";
    cin >> MenuNumber;

    return MenuNumber;
}

void ExecuteUsersMenuChoice(enUserMenuChoices UserMenuChoice)
{
    vector <UserData> vUsers;
    string UserName;
    UserData User;
    switch (UserMenuChoice)
    {
    case enUserMenuChoices::ListUsers:
         vUsers = LoadUsersDataIntoVector();
        PrintUserList(vUsers);
        ReturnToUsersMenu();
        break;
        
    case enUserMenuChoices::AddUser:
        AddingUsersScreen();
        AddUsers();
        ReturnToUsersMenu();
        break;

    case enUserMenuChoices::DeleteUser:
        vUsers = LoadUsersDataIntoVector();
        DeleteUsersScreen();
        UserName = GetUserNameToSearch();

        if (UserName == "Admin")
        {
            cout << "\nThis user cannot be deleted.\n";
            ReturnToUsersMenu();
        }

        DeleteUserByAccountNumber(UserName, vUsers);
        ReturnToUsersMenu();
        break;

    case enUserMenuChoices::UpdateUser:
        vUsers = LoadUsersDataIntoVector();
        UpdateUserScreen();
        UserName = GetUserNameToSearch();
        UpdateUserByUserName(UserName,vUsers);
        ReturnToUsersMenu();
        break;

    case enUserMenuChoices::FindUser:
        vUsers = LoadUsersDataIntoVector();
        FindUsersScreen();
        UserName = GetUserNameToSearch();
        FindUserByUserName(UserName, vUsers, User);
        ReturnToUsersMenu();

        break;

    case enUserMenuChoices::BackToMainMenu:
        ShowMainMenu();
        break;

    default:
        break;
    }
}

void PrintUserList(vector <UserData> vUsers)
{
    system("cls");
    cout << "\n\t\t\t\t\tUser List (" << vUsers.size() << ") User(s).\n";
    cout << "------------------------------------------------------------------------------------------------------------" << endl;

    cout << "| " << left << setw(15) << "UserName";
    cout << "| " << left << setw(10) << "Password";
    cout << "| " << left << setw(12) << "Permissions";
    cout << "\n------------------------------------------------------------------------------------------------------------" << endl;

    if (vUsers.size() == 0)
        cout << "\n\t\t\t\t No users available.\n";

    for (UserData& User : vUsers)
    {
        PrintUserRecord(User);
        cout << endl;
    }
    cout << "------------------------------------------------------------------------------------------------------------" << endl;
}

void PrintUserRecord(UserData User)
{
    cout << "| " << left << setw(15) << User.UserName;
    cout << "| " << left << setw(10) << User.Password;
    cout << "| " << left << setw(12) << User.UserPermissions;
}

void ReturnToUsersMenu()
{
    cout << "\n\nPress any key to return to User Management menu...";
    system("pause>0");
    ShowManageUsersMenu();
}

void FindUsersScreen()
{
    system("cls");
    cout << "----------------------------------------" << endl;
    cout << "\t Find users screen " << endl;
    cout << "----------------------------------------\n" << endl;
}

string GetUserNameToSearch()
{
    string UserName = "";
    cout << "Enter UserName: ";
    cin >> UserName;

    return UserName;
}

bool FindUserByUserName(string UserName, vector <UserData> vUsers, UserData& User)
{
    vUsers = LoadUsersDataIntoVector();

    for (UserData& U : vUsers)
    {
        if (UserName == U.UserName)
        {
            User = U;
            PrintUserCard(User);
            return true;
        }
    }
    cout << "User with account number (" << UserName << ") is not found!";
    return false;
}

void PrintUserCard(UserData User)
{
    cout << "\nThe following are the User details:\n\n";
    cout << "-------------------------------------\n";
    cout << "Username       : " << User.UserName << endl;
    cout << "Password       : " << User.Password << endl;
    cout << "Permissions    : " << User.UserPermissions << endl;
    cout << "-------------------------------------\n";
}

void AddingUsersScreen()
{
    system("cls");
    cout << "----------------------------------------" << endl;
    cout << "\t Add new User screen " << endl;
    cout << "----------------------------------------" << endl;
}

void AddUsers()
{
    char AddMore = 'Y';
    do
    {

        cout << "Adding new user:\n\n";

        AddNewUser();

        cout << "User added successfully, do you want to add another? Y/N ";
        cin >> AddMore;

    } while (toupper(AddMore) == 'Y');
}

void AddNewUser()
{
    UserData User;
    User = ReadNewUser();
    AddDataLineToFile(FileNameUser, ConvertUserRecordToLine(User, "#//#"));
}

UserData ReadNewUser()
{
    short PermsCounter = 0;

    UserData UserInput;
    vector <UserData> vUsers = LoadUsersDataIntoVector();

    cout << "Enter UserName: ";
    cin >> UserInput.UserName;

    for (UserData& User : vUsers)
    {
        while (UserInput.UserName == User.UserName)//CHecking if account number already exists in file or not
        {
            cout << "UserName already exists! Enter a valid username:\n";
            cin >> UserInput.UserName;
            cout << endl;
        }
    }

    cout << "Enter password: ";
    cin >> UserInput.Password;
    cin.ignore();
    
    UserInput.UserPermissions = ReadPermissionsToSet();

    return UserInput;
}

int ReadPermissionsToSet()
{
    int Permissions = 0;
    char Answer = 'n';

    cout << "\n Do you want to give full access? y/n? ";
    cin >> Answer;
    if (toupper(Answer) == 'Y')
        return -1;

    cout << "\nDo you want to give access to: ";

    cout << "\nShow client list? y/n?: ";
    cin >> Answer;
    if (toupper(Answer) == 'Y')
        Permissions+=enPermissions::pListClients;
    
    cout << "\nAdd new client? y/n?: ";
    cin >> Answer;
    if (toupper(Answer) == 'Y')
        Permissions += enPermissions::pAddNewClient;

    cout << "\nDelete client? y/n?: ";
    cin >> Answer;
    if (toupper(Answer) == 'Y')
        Permissions += enPermissions::pDeleteClient;

    cout << "\nUpdate client? y/n?: ";
    cin >> Answer;
    if (toupper(Answer) == 'Y')
        Permissions += enPermissions::pUpdateClient;

    cout << "\nFind client? y/n?: ";
    cin >> Answer;
    if (toupper(Answer) == 'Y')
        Permissions += enPermissions::pFindClient;

    cout << "\nTransactions? y/n?: ";
    cin >> Answer;
    if (toupper(Answer) == 'Y')
        Permissions += enPermissions::pTransactions;

    cout << "\nManage users? y/n?: ";
    cin >> Answer;
    if (toupper(Answer) == 'Y')
        Permissions += enPermissions::pManageUsers;

    return Permissions;
}

string ConvertUserRecordToLine(UserData User, string Separator)
{
    string UserRecord = "";

    UserRecord += User.UserName + Separator;
    UserRecord += User.Password + Separator;
    UserRecord += to_string(User.UserPermissions) + Separator;

    return UserRecord;
}

void UpdateUserScreen()
{
    system("cls");
    cout << "----------------------------------------" << endl;
    cout << "\t Update User screen " << endl;
    cout << "----------------------------------------\n" << endl;
}

bool UpdateUserByUserName(string UserName, vector <UserData>& vUsers)
{
    UserData User;
    char Answer = 'n';

    if (FindUserByUserName(UserName, vUsers, User))
    {
        //PrintClientCard(Client);

        cout << "\n\nAre you sure you want to update this User info? y/n? ";
        cin >> Answer;

        if (toupper(Answer)=='Y')
        {
            for (UserData& U : vUsers)
            {
                if (U.UserName == UserName)
                {
                    U = ChangeUserRecord(UserName);
                    break;
                }
            }
            SaveUsersDataToFile(FileNameUser, vUsers);
            cout << "\n\nUser info updated succesfully";
            return true;
        }
    }
    return false;
}

UserData ChangeUserRecord(string UserName)
{
    UserData User;

    User.UserName = UserName;

    cout << "\n\nEnter Password:\n";
    getline(cin >> ws, User.Password);

    User.UserPermissions=ReadPermissionsToSet();

    //Still must add permissions

    return User;
}

vector <UserData> SaveUsersDataToFile(string FileNameUser, vector <UserData> vUsers)
{
    fstream MyFile;
    MyFile.open(FileNameUser, ios::out);//overwrite

    string DataLine;

    if (MyFile.is_open())
    {
        for (UserData U: vUsers)
        {
            if (U.MarkUserForDeletion == false)
            {
                DataLine = ConvertUserRecordToLine(U, delim);//omly write records that are NOT marked for deletion
                MyFile << DataLine << endl;
            }
        }
        MyFile.close();
    }
    return vUsers;
}

void DeleteUsersScreen()
{
    system("cls");
    cout << "----------------------------------------" << endl;
    cout << "\t Delete Users screen " << endl;
    cout << "----------------------------------------\n" << endl;
}

bool MarkUserForDeleteByUserName(string UserName, vector <UserData>& vUsers)
{
    for (UserData& U : vUsers)
    {
        if (U.UserName == UserName)
        {
            U.MarkUserForDeletion = true;
            return true;
        }
    }
    return false;
}

bool DeleteUserByAccountNumber(string UserName, vector <UserData>& vUsers)
{
    UserData User;
    char Answer = 'n';

    if (FindUserByUserName(UserName, vUsers, User))
    {
        cout << "\n\nAre you sure yuu want to delete this User> y/n? ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            MarkUserForDeleteByUserName(UserName, vUsers);
            SaveUsersDataToFile(FileNameUser, vUsers);

            //refresh clients:
            vUsers = LoadUsersDataIntoVector();
            cout << "\n\nUser deleted succesfully";
            return true;
        }
    }
    return false;

}

void ShowAccessDeniedScreen()
{
    system("cls");
    cout << "\n----------------------\n";
    cout << "ACCESS DENIED\nYou do not have permissions for this action\nPlease contact your system administrator.";
    cout << "\n----------------------\n";
}

bool CheckAccessPermission(enPermissions Permission)
{
    if (CurrentUser.UserPermissions == enPermissions::eAll)
        return true;

    else if ((CurrentUser.UserPermissions & Permission) == Permission)
        return true;

    else
        return false;
}
