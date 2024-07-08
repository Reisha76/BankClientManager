# BankClientManager

**BankClientManager** is a C++ application designed to manage bank client information efficiently. This project demonstrates fundamental file handling, data management, and a menu-driven user interface in C++.

## Features

- **Client Management**: Add, update, delete, and search for bank clients.
- **Transaction Management**: Deposit and withdraw money, and view total client balances.
- **Data Persistence**: Client information is stored and retrieved from a file.
- **User Interface**: Simple text-based menu for navigating different functionalities.

## Functionalities

1. **Show Client List**: Displays a list of all clients with their details.
2. **Add New Client**: Allows adding a new client to the database with validation to prevent duplicate account numbers.
3. **Delete Client**: Removes a client from the database by account number.
4. **Update Client Info**: Updates existing client details.
5. **Find Client**: Searches for a client by account number and displays their details.
6. **Transactions**:
   - **Deposit Money**: Deposits a specified amount into a client's account.
   - **Withdraw Money**: Withdraws a specified amount from a client's account, ensuring sufficient balance.
   - **Total Client Balance**: Displays the total balance across all clients.
7. **Exit**: Exits the application.

Note
This project focuses on the integration of various functions to manage bank client information. Validating correct inputs was not the main focus, so there might be some validation issues. Future improvements could include more robust input validation and error handling.

## File Descriptions

1. **BankMain.cpp**:
   - **Purpose**: Contains the `main` function, which serves as the entry point of the application.
   - **Responsibilities**:
     - Initializes the application.
     - Displays the main menu.
     - Handles user input for menu navigation.
     - Calls appropriate functions based on user selection.

2. **bank.h**:
   - **Purpose**: Header file that contains all necessary declarations and definitions.
   - **Contents**:
     - **Structs**: Definitions for data structures such as `stClientData`.
     - **Enums**: Enumerations for menu choices like `enMenuChoices` and `enTransactionMenuChoices`.
     - **Global Variables**: Declarations of global variables such as `FileName` and `delim`.
     - **Function Declarations**: Prototypes for all the functions used in the application.

3. **FuncDef.cpp**:
   - **Purpose**: Implements all the functions declared in `bank.h`.
   - **Contents**:
     - **Client Management Functions**: Implementations for adding, deleting, updating, and finding clients.
     - **Transaction Functions**: Implementations for deposit, withdrawal, and displaying total balances.
     - **Utility Functions**: Helper functions for reading from and writing to files, string manipulation, and user interface display.

## How to Use

1. **Clone the Repository**:
   ```sh
   git clone https://github.com/YourUsername/BankClientManager.git
   cd BankClientManager

2.**Compile the source code**:

```g++ BankMain.cpp FuncDef.cpp -o BankMain```

3.**Run the executable**:
```.\BankMain```

4.**Follow the On-Screen Instructions to navigate through the menu.**



