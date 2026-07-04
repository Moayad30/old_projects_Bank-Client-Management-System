#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include <limits>
using  namespace std ;

void ClearScreen()
{
#ifdef _WIN32
    ClearScreen();
#else
    system("clear");
#endif
}

void PauseScreen()
{
    cout << "Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}


enum enWhatChoose {Show = 1 , Add = 2 , Delete = 3 , Update = 4 , Find = 5 , Exit = 6};

const string FileName = "MMU.txt" ;

struct stClients
{
    string AccountNumber ;
    string PINcode ;
    string Name ;
    string Phone ;
    double AccountBalance ;
    bool MarkIt = false ;
};

void HeaderMain()
{
    cout << "====================================================" << endl ;
    cout << "\t\tMain Menue Screen" << endl ;
    cout << "====================================================" << endl ;
}

vector <string> SplitLine(string Line, string separator = "/##/")
{
    vector <string> vString ;

    string s ;
    int pos = 0 ;
    while((pos = Line.find(separator)) != std::string::npos)
    {
        s = Line.substr(0 , pos) ;
        vString.push_back(s) ;
        Line.erase(0,pos + separator.length()) ;
    }
    vString.push_back(Line) ;
    return vString ;
}

stClients ConvertSplitToRecord(string line)
{
    stClients Client ;
    vector <string > vString = SplitLine(line) ;

    Client.AccountNumber = vString[0] ;
    Client.PINcode = vString[1] ;
    Client.Name = vString[2] ;
    Client.Phone = vString[3] ;
    Client.AccountBalance = stod(vString[4] );

    return Client ;
}

vector <stClients> LoadDataFormFile(string FileName)
{
    vector <stClients>  DataClients ;
    stClients Client ;

    fstream MyFile ;
    MyFile.open(FileName , ios::in);

    string line ;
    if(MyFile.is_open())
    {
        while (getline(MyFile , line))
        {
            Client = ConvertSplitToRecord(line) ;
            DataClients.push_back(Client) ;
        }
        MyFile.close() ;
    }
    return DataClients ;
}

void PrintDataForOneClient(stClients Client)
{
        cout << "| " << setw(15) << left << Client.AccountNumber;
        cout << "| " << setw(10) << left << Client.PINcode ;
        cout << "| " << setw(25) << left << Client.Name ;
        cout << "| " << setw(13) << left << Client.Phone ;
        cout << "| " << setw(15) << left << Client.AccountBalance ;
}

void PrintListDataClients(vector<stClients> DataClients)
{
    cout << "\t\t\tClient List (" << DataClients.size() << ") Client(s)." << endl ;
    cout << "__________________________________________________________________________________" << endl ;
    cout << "| " << setw(15) << left << "Account Number" ;
    cout << "| " << setw(10) << left << "Pin Code" ;
    cout << "| " << setw(25) << left << "Client Name" ;
    cout << "| " << setw(13) << left << "Phone" ;
    cout << "| " << setw(15) << left << "Balance" ;
    cout << "\n__________________________________________________________________________________" << endl ;

    if(DataClients.size() == 0)
        cout << "\t\t\t\tNo Clients Available In the System!";
    else
    for(stClients c : DataClients)
    {
        PrintDataForOneClient(c) ;
        cout << endl ;
    }
    cout << "\n__________________________________________________________________________________\n" << endl ;
}

bool IsFindClient(vector <stClients> & DataClients , string AccountNumber)
{
    for(stClients c : DataClients)
    {
        if (c.AccountNumber == AccountNumber)
        {

            return true;
        }
    }
    return false ;
}

bool FindClient(vector <stClients> & DataClients , string AccountNumber , stClients & Client)
{
    for(stClients c : DataClients)
    {
        if (c.AccountNumber == AccountNumber)
        {
            Client = c ;
            return true;
        }
    }
    return false ;
}

string ConvertRecordToLine(stClients client, string separator = "/##/")
{
    string line ;

    line += client.AccountNumber + separator ;
    line += client.PINcode + separator ;
    line += client.Name + separator ;
    line += client.Phone + separator ;
    line += to_string(client.AccountBalance)  ;

    return line ;
}

stClients ReadDatadClient(vector<stClients> & DataClients)
{
    stClients NewClient ;

    cout << "Enter Account Number? " ;
    getline(cin >> ws , NewClient.AccountNumber) ;

    if(IsFindClient(DataClients,NewClient.AccountNumber))
    {
         cout << "This Account Number [" << NewClient.AccountNumber << "]is already exist , enter another account?" << endl << endl ;
         getline(cin >> ws , NewClient.AccountNumber) ;
    }

    cout << "Enter PIN code? " ;
    cin >> NewClient.PINcode ;

    cout << "Enter Name? " ;
    cin >> NewClient.Name ;

    cout << "Enter Phone? " ;
    cin >> NewClient.Phone;

    cout << "Enter Balance? " ;
    cin >> NewClient.AccountBalance ;

    return NewClient ;

}

void AddClientToFile(string line)
{
    fstream MyFile ;
    MyFile.open(FileName , ios::out | ios::app) ;

    if(MyFile.is_open())
    {

        MyFile << line << endl ;

        MyFile.close() ;
    }
}

void AddOneClient(vector<stClients> & DataClients)
{
    stClients Client = ReadDatadClient(DataClients) ;

    AddClientToFile(ConvertRecordToLine(Client)) ;
    DataClients = LoadDataFormFile(FileName);
}

void AddNewClient(vector<stClients> & DataClients)
{
    char c = 'n' ;
    do
    {
        cout << "Adding New Client\n\n" ;

        AddOneClient(DataClients) ;

        cout  << "\nClient Added successfully, Do you want add more clients? [n/y]?" << endl ;
        cin >> c ;
    }
    while(c == 'y' || c == 'Y') ;
}

void showAddNewClientScreen(vector<stClients> & DataClients)
{
    cout << "\n-----------------------------------\n";
    cout << "\tAdd New Clients Screen";
    cout << "\n-----------------------------------\n";
    AddNewClient(DataClients) ;

}



void MarkClientToDelete(vector <stClients> & DataClients , string AccountNumber)
{
    for(stClients & c : DataClients)
    {
        if(c.AccountNumber == AccountNumber)
        {
            c.MarkIt = true ;
            return ;
        }
    }
}

void PrintClientCard(stClients Client)
{
    cout << "\nThe following are the client details:\n";
    cout << "-----------------------------------";
    cout << "\nAccout Number: " << Client.AccountNumber;
    cout << "\nPin Code     : " << Client.PINcode ;
    cout << "\nName         : " << Client.Name;
    cout << "\nPhone        : " << Client.Phone;
    cout << "\nAccount Balance: " << Client.AccountBalance;
    cout << "\n-----------------------------------\n";
}

void SaveChangesOnFile(vector <stClients> & DataClients)
{
    fstream MyFile ;
    string line ;
    MyFile.open(FileName , ios::out) ;

    if(MyFile.is_open())
    {
        for(stClients c : DataClients)
        {
            if(c.MarkIt == false)
            {
                line = ConvertRecordToLine(c) ;
                MyFile << line << endl ;
            }
        }
        DataClients = LoadDataFormFile(FileName) ;
        MyFile.close() ;
    }
}

string ReadClientAccountNumber()
{
    string AccountNumber ;
    cout << "Enter Account Number,please?" ;
    cin >> AccountNumber ;
    return AccountNumber ;
}

void DeleteClientByAccountNumber(string AccountNumber , vector <stClients> & DataClients)
{
    char Answer = 'n' ;
    stClients Client ;

    if(FindClient(DataClients, AccountNumber , Client))
    {
       PrintClientCard(Client) ;
       cout << "Are you sure you want to delete this client? [y/n]? " ;
       cin >> Answer;

       if(Answer == 'y' || Answer == 'Y')
       {
            MarkClientToDelete(DataClients,AccountNumber) ;
            SaveChangesOnFile(DataClients) ;

            DataClients = LoadDataFormFile(FileName) ;
            cout << "Client Deleted Successfully" << endl ;
       }

    }
    else
    {
        cout << "Client with Account Number [" << AccountNumber << "] is not found!" << endl ;
    }

}

void DeleteClient(vector <stClients> & DataClients)
{
    cout << "\n-----------------------------------\n";
    cout << "\tDelete Client Screen";
    cout << "\n-----------------------------------\n";

    string AccountNumber = ReadClientAccountNumber() ;
    DeleteClientByAccountNumber(AccountNumber , DataClients) ;
}

stClients ChangeInfoClient(string AccountNumber)
{
    stClients Client ;

    Client.AccountNumber = AccountNumber ;

    cout << "\nEnter PIN code? " ;
    cin >> Client.PINcode ;

    cout << "Enter Name? " ;
    cin >> Client.Name ;

    cout << "Enter Phone? " ;
    cin >> Client.Phone ;

    cout << "Enter Balance? " ;
    cin >> Client.AccountBalance;

    return Client ;
}

void UpdateClientByAccountNumber(string AccountNumber ,vector <stClients> & DataClients)
{
    char Answer = 'n' ;
    stClients Client ;
    if(FindClient(DataClients,AccountNumber , Client))
    {
        PrintClientCard(Client) ;

        cout << "Are you sure you want to update this client? [y/n]? " ;
        cin >> Answer;

        if(Answer == 'y' || Answer == 'Y')
        {
            for(stClients & c : DataClients)
            {
                if(c.AccountNumber == AccountNumber)
                {
                    c = ChangeInfoClient(AccountNumber) ;
                    break ;
                }
            }

            SaveChangesOnFile(DataClients) ;
            cout << "\nClient updated Successfully" << endl ;
        }

    }
    else
    {
        cout << "Client with Account Number [" << AccountNumber << "] is not found!" << endl ;
    }
}

void FindClientByAccountNumber(vector <stClients> & DataClients)
{

    cout << "\n-----------------------------------\n";
    cout << "\tFind Client Screen";
    cout << "\n-----------------------------------\n";

    string AccountNumber = ReadClientAccountNumber() ;

    stClients Client ;
    if(FindClient(DataClients , AccountNumber, Client))
    {
        PrintClientCard(Client) ;
    }
    else
    {
        cout << "\nClient with Account Number[" << AccountNumber << "] is not found!";
    }
}
void UpdateInfoClient(vector <stClients> & DataClients)
{
    cout << "\n-----------------------------------\n";
    cout << "\tUpdate Client Info Screen";
    cout << "\n-----------------------------------\n";

    string AccountNumber = ReadClientAccountNumber();
    UpdateClientByAccountNumber(AccountNumber , DataClients) ;

}
void ExitProgram()
{
    cout << "====================================================" << endl ;
    cout << "\t\tThe End :)" << endl ;
    cout << "====================================================" << endl ;
}
void ShowMainMenue() ;
void GoToMainScreen()
{
    cout << "\nPress any key to go Main Menu...\n\n" ;
    PauseScreen() ;
    ShowMainMenue() ;
}

void WhatIsChoice(enWhatChoose Answer , vector <stClients> & DataClients )
{
    switch (Answer)
    {
        case enWhatChoose::Show :
            ClearScreen() ;
            PrintListDataClients(DataClients) ;
            GoToMainScreen() ;
            break;

        case enWhatChoose::Add :
            ClearScreen() ;
            AddNewClient(DataClients) ;
            GoToMainScreen() ;
            break;

        case enWhatChoose::Delete :
            ClearScreen() ;
            DeleteClient(DataClients) ;
            GoToMainScreen() ;
            break;

        case enWhatChoose::Update :
            ClearScreen() ;
            UpdateInfoClient(DataClients) ;
            GoToMainScreen() ;
            break;

        case enWhatChoose::Find :
            ClearScreen() ;
            FindClientByAccountNumber(DataClients) ;
            GoToMainScreen() ;
            break;

        case enWhatChoose::Exit :
            ClearScreen() ;
            ExitProgram() ;
            break;
    }
}

int ReadChoice()
{
    int Answer ;
    cout << "Choose what do you want to do? [1 to 6]? " ;
    cin >> Answer ;
    return Answer ;
}

void ShowMainMenue()
{
        vector <stClients> DataClients = LoadDataFormFile(FileName);

        ClearScreen() ;
        HeaderMain() ;

        cout << "\t[1] Show Client List." << endl ;
        cout << "\t[2] Add New Client." << endl ;
        cout << "\t[3] Delete Client." << endl ;
        cout << "\t[4] Update Client." << endl ;
        cout << "\t[5] Find Client." << endl ;
        cout << "\t[6] Exit." << endl ;
        cout << "====================================================" << endl ;
        WhatIsChoice((enWhatChoose)ReadChoice() , DataClients) ;

}

int main()
{
    ShowMainMenue() ;

    return 0;
}
