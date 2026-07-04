# Bank Client Management System

A console-based banking application for managing client records using file storage.

## Background

This is one of my older handmade C++ console projects from my early coding days. I kept the old-school console style because it shows the stage I was at while learning, experimenting, and building everything manually.

## Project Type

- **Language:** C++
- **Application type:** Console application
- **Build system:** CMake
- **Storage:** Text file storage

## Features

- Display all registered bank clients in a formatted table
- Add new clients with account number, PIN code, name, phone number, and balance
- Prevent duplicated account numbers when adding clients
- Delete a client by account number after confirmation
- Update client information while keeping the same account number
- Find and display a specific client by account number
- Save all client data in a text file

## Data Storage

Client data is stored in `MMU.txt`. Each line represents one client using `/##/` as a separator.

Typical client record format:

```text
AccountNumber/##/PINCode/##/Name/##/Phone/##/Balance
```

## Project Structure

```text
Bank-Client-Management-System/
├── CMakeLists.txt
├── main.cpp
├── MMU.txt
└── README.md
```

## How to Build and Run

### Using CMake

```bash
mkdir build
cd build
cmake ..
cmake --build .
./bank_client_management
```

### Using g++ directly

```bash
g++ -std=c++17 main.cpp -o bank_client_management
./bank_client_management
```

Keep the `.txt` data file in the same directory as the executable when running the program.
