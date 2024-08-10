#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;

//enum Permissions {FullPermissions=-1};

struct stClientData
{
    string AccountNumber;
    string PinCode;
    string ClientName;
    string Phone;
    double Balance;
    bool MarkClientForDeletion = false;
};

struct UserData     //new struct to hold user login info and perms
{
    string UserName;
    string Password;
    short UserPermissions;
    bool MarkUserForDeletion = false;
};

const string FileName = "Clients.txt";
const string FileNameUser = "Users.txt";
const string delim = "#//#";

enum enMenuChoices
{
    ShowClients = 1, AddClient = 2, DeleteClient = 3, UpdateClientInfo = 4, FindClient = 5, Transactions = 6, ManageUsers=7, LogOut=8
};

enum enTransactionMenuChoices
{
    Deposit=1, Withdraw=2, TotalBalance=3, MainMenu=4
};

enum enUserMenuChoices
{
    ListUsers=1, AddUser=2, DeleteUser=3, UpdateUser=4, FindUser=5, BackToMainMenu=6
};

enum enPermissions
{
    eAll = -1, pListClients = 1, pAddNewClient=2, pDeleteClient=4, pUpdateClient=8,
    pFindClient=16, pTransactions=32, pManageUsers=64
};

void PrintAllClientsData(vector <stClientData> vClients);
void PrintClientRecord(stClientData Client);
void PrintMainMenuOptions();
void ShowMainMenu();
short GetMenuChoice();
vector <string> SplitString(string Line, string delim);
stClientData ConvertLineToRecord(string Line, string delim);
void ExecuteMenuChoice(enMenuChoices MenuChoice);
void ReturnToMainMenu();
stClientData ReadNewClient();
void AddDataLineToFile(string FileName, string stDataLine);
void AddNewClient();
void AddClients();
void AddingClientsScreen();
void DeleteClientsScreen();
void FindClientsScreen();
string GetAccNumToSearch();
bool FindClientByAccountNumber(string AccNumber, vector <stClientData> vClients, stClientData& Client);
bool DeleteClientByAccountNumber(string AccountNumber, vector <stClientData>& vClients);
void PrintClientCard(stClientData Client);
vector <stClientData> LoadClientsDataFromFile(string FileName);
stClientData ConvertLineToRecord(string Line, string delim);
bool MarkClientForDeleteByAccountNumber(string AccNumber, vector <stClientData> &vClients);
string ConvertRecordToLine(stClientData Client, string delim);
bool DeleteClientByAccountNumber(string AccountNumber, vector <stClientData>& vClients);
vector <stClientData> SaveClientsDataToFile(string FileName, vector <stClientData> vClients);
stClientData ChangeClientRecord(string AccountNumber);
bool UpdateClientByAccountNumber(string AccountNumber, vector <stClientData>& vClients);
void UpdateClientsScreen();
void ProgramEndScreen();
void TransactionMenuScreen();
void TransactionsSwitchCase(enTransactionMenuChoices TransactionChoice);
bool DepositMoney();
bool WithdrawMoney();
void ReturnToTransactionMenu();
void DepositMoneyScreen();
void WithdrawMoneyScreen();
short GetTransMenuChoice();
void PrintBalancesList(vector <stClientData> vClients);
void PrintBalancesRecords(stClientData Client);
void ShowTotalBalance();
/////////////////BANK EXTENSION//////////////////////
void LoginScreen();
bool CheckUserAndPass(string UserName, string Password, UserData& CurrentUser);
vector <UserData> LoadUsersDataIntoVector();
UserData ConvertUserLineToRecord(string Line, string delim);
void StartProgram();
void ShowManageUsersMenu();
short GetUserMenuChoice();
void ExecuteUsersMenuChoice(enUserMenuChoices UserMenuChoice);
void PrintUserList(vector <UserData> vUsers);
void PrintUserRecord(UserData User);
void ReturnToUsersMenu();
void PrintUserRecord(UserData User);
void ReturnToUsersMenu();
void FindUsersScreen();
string GetUserNameToSearch();
bool FindUserByUserName(string UserName, vector <UserData> vUsers, UserData& User);
void PrintUserCard(UserData User);
void AddingUsersScreen();
void AddUsers();
void AddNewUser(); 
UserData ReadNewUser();
string ConvertUserRecordToLine(UserData User, string Separator);
void UpdateUserScreen();
bool UpdateUserByUserName(string UserName, vector <UserData>& vUsers);
UserData ChangeUserRecord(string UserName);
vector <UserData> SaveUsersDataToFile(string FileNameUser, vector <UserData> vUsers);
void DeleteUsersScreen();
bool MarkUserForDeleteByUserName(string UserName, vector <UserData>& vUsers);
bool DeleteUserByAccountNumber(string UserName, vector <UserData>& vUsers);
int ReadPermissionsToSet();
void ShowAccessDeniedScreen();
bool CheckAccessPermission(enPermissions Permission);
