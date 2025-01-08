# credence
Credence password manager

Code Design
Modular Components

    Main Program (main.cpp)
        Parse commands.
        Call respective modules.
    Command Parser (CommandParser.h/cpp)
        Parse and validate user inputs.
    Database Handler (DatabaseHandler.h/cpp)
        Interact with SQLite.
    Encryption Module (Encryption.h/cpp)
        Encrypt and decrypt passwords.
    Authentication Module (Authentication.h/cpp)
        Verify user has sudo access.
    Utility Module (Utils.h/cpp)
        Provide helper functions (e.g., hashing, input sanitization).

Step 1: Install Required Packages

Ensure you have the necessary tools installed.

sudo apt update
sudo apt install g++ sqlite3 libsqlite3-dev


Step 2: Compile the Code

Use the following g++ command to compile the program:

g++ main.cpp -o credence -lsqlite3

This will:

    Compile main.cpp and link the sqlite3 library.
    Produce an executable named credence.


Step 3: Run the Program

Run the program with sudo since it checks for sudo privileges:

sudo ./credence

Step 4: Test Use Cases

Here are some example scenarios to test the functionality.
1. Adding a Credential

> add facebook myuser mypassword

2. Listing Credentials

> list

Expected output:

App: facebook, Username: myuser, Password: mypassword

3. Removing a Credential

> remove facebook

4. Listing Credentials After Deletion

> list

Expected output:

(no output)

5. Exiting the Program

> exit
