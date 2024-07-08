#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;

struct stClientData
{
    string AccountNumber;
    string PinCode;
    string ClientName;
    string Phone;
    double Balance;
    bool MarkClientForDeletion = false;
};

const string FileName = "Clients.txt";
const string delim = "#//#";

enum enMenuChoices
{
    ShowClients = 1, AddClient = 2, DeleteClient = 3, UpdateClientInfo = 4, FindClient = 5, Transactions = 6, ExitMenu=7
};

enum enTransactionMenuChoices
{
    Deposit=1, Withdraw=2, TotalBalance=3, MainMenu=4
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
