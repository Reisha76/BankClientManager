# Bank Management System

This project is a comprehensive Bank Management System implemented in C++. It provides various functionalities to manage client accounts, handle transactions, and now, with the recent extension, includes an innovative user management and permissions system. The extension significantly enhances the project's functionality by introducing a detailed mechanism to manage users (e.g., admins and moderators) and control their access to different parts of the system.

## Features

### Core Features

- **Client Management:**
  - **Add New Clients:** Add new clients to the bank's database with account details such as account number, PIN code, client name, phone number, and account balance.
  - **Delete Clients:** Remove clients from the system.
  - **Update Client Information:** Modify existing client details.
  - **Find Clients:** Search for clients using their account number.
  - **List All Clients:** Display a comprehensive list of all clients with their details.

- **Transaction Management:**
  - **Deposit Money:** Deposit money into a client's account.
  - **Withdraw Money:** Withdraw money from a client's account, ensuring that the withdrawal amount does not exceed the available balance.
  - **Total Clients' Balance:** Display the total balance across all client accounts.

### New Features Added in the Extension

- **User Management Screen:**
  - **Add New Users:** Create new users who can be admins or moderators.
  - **Delete Users:** Remove existing users from the system.
  - **Update User Information:** Modify the details of existing users.
  - **Find Users:** Search for users using their username.
  - **List All Users:** Display a list of all users with their credentials and permissions.

- **Permissions System:**
  - The extension introduces a **permissions system** that allows the assignment of specific permissions to users. This system is innovative because it uses a **bitwise operator mechanism** to control access to various parts of the system.
  - **Permissions Assignation:** Each user can be assigned different permissions, which define what actions they are allowed to perform. For example, some users may only be able to view the client list, while others can add, delete, or update client information.
  - **Permission Levels:**
    - **Full Access:** Users with full access can perform all actions within the system. This is achieved by setting their permissions value to `-1`.
    - **Custom Permissions:** Permissions can be selectively granted for specific actions, such as listing clients, adding new clients, deleting clients, updating client information, finding clients, managing transactions, and managing users.

## How the Permissions System Works

The permissions system is based on a bitwise operation mechanism, which allows efficient and flexible control over user access:

- **Bitwise Permissions:** Each action in the system corresponds to a specific bit in a permissions integer. By using bitwise operations, the system can quickly determine whether a user has the required permission for a particular action.
- **Permission Values:** The system defines a set of enumerated permissions:
  - `pListClients = 1`
  - `pAddNewClient = 2`
  - `pDeleteClient = 4`
  - `pUpdateClient = 8`
  - `pFindClient = 16`
  - `pTransactions = 32`
  - `pManageUsers = 64`
  - **Full Access** is represented by setting the permissions value to `-1`, which allows the user to perform all actions in the system.

- **Efficiency and Performance:** The use of bitwise operations for checking permissions is not just a technical choice but a performance optimization. By leveraging bitwise checks, the system can validate a user's permissions with minimal computational overhead, saving significant time compared to traditional methods. This approach ensures that even with a large number of users and permissions, the system remains responsive and efficient. This is particularly beneficial in scenarios where multiple permission checks need to be performed rapidly, such as during login or when accessing various system functionalities.

This system allows the creation of highly granular permission profiles for each user, ensuring that access is precisely controlled and tailored to the needs of different roles within the bank system.

## How to Use

1. **Login:**
   - Start the program and log in using the username and password. User credentials and permissions will be validated during the login process.

2. **Main Menu:**
   - After logging in, users are presented with a main menu where they can choose various actions depending on their assigned permissions.

3. **User Management:**
   - Admin users can access the user management menu to add, delete, update, or find users, and set their permissions accordingly.

4. **Client Management:**
   - Depending on the permissions, users can manage client information, handle transactions, or view client data.

## Future Work

Further enhancements to the system could include more sophisticated roles and permission groups, integration with a database management system for persistent storage, and additional security features like password hashing and multi-factor authentication.

## Conclusion

This project demonstrates a comprehensive bank management system with an innovative extension that brings user management and a permissions system to the forefront. The bitwise operator-based permissions mechanism is particularly noteworthy, offering a powerful and flexible way to control user access within the system. This method not only simplifies the process of permissions validation but also significantly enhances the system's performance, making it scalable and efficient even as the user base grows.
