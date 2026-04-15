

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include<fstream>



using namespace std;

const string ClientFileName = "Clients.txt";

void GotoBackMainMenuee();

enum enMainMennueOptions { ShowClientsList = 1, AddNewClientenum = 2, DeletClient = 3, UpdateClientInfo = 4, FindClient = 5, Exit = 6 };

void PerformMainMenuueOption(enMainMennueOptions MainMennueOption);


struct sClient
{
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	string AccountBalance;
	bool MarkForDelete = false;
	bool MarkForUpdate = false;

};

vector<sClient> LoadDateFromFileAsLineAndConvertToRecordInStructAfterThisStructInVector(string ClientFileNam);



string ReadAccountNumber()
{
    string AccountNumber;
    cout << "Please enter your Account Number \n";
    getline(cin>>ws, AccountNumber);

    return AccountNumber;
}


sClient ReadNewClient()
{
    vector< sClient> VClient = LoadDateFromFileAsLineAndConvertToRecordInStructAfterThisStructInVector(ClientFileName);
    sClient Client;
    cout << "Please enter your Account Number\n ";
    getline(cin >> ws, Client.AccountNumber); 
    cout << "Please enter your Pin Code\n";
    getline(cin, Client.PinCode);
    cout << "Please enter your Name\n ";
    getline(cin, Client.Name);
    cout << "Please enter your Phone\n";
    getline(cin, Client.Phone);
    cout << "Please enter your Account Balance \n";
    getline(cin, Client.AccountBalance);


    return Client;
}


vector<string>SplitString(string S1, string Delim = "#//#")
{
    short pos = 0;
    string Word;
    vector<string>vString;
    while ((pos = S1.find(Delim)) != std::string::npos)
    {

        Word = S1.substr(0, pos);
        if (Word != "")
        {
            vString.push_back(Word);

        }
        S1.erase(0, pos + Delim.length());
    }

    if (S1 != "")
    {
        vString.push_back(S1);
    }

    return vString;
}


string ConvertRecordToLine(sClient Client, string Seperator = "#//#")
{
    string StClientLine = "";
    StClientLine += Client.AccountNumber + Seperator;
    StClientLine += Client.PinCode + Seperator;
    StClientLine += Client.Name + Seperator;
    StClientLine += Client.Phone + Seperator;
    StClientLine += (Client.AccountBalance);



    return StClientLine;
}


sClient ConvertLineToRecordInStruct(string S1)//دا بقا هياخد السطر يحوله ل ريكورد والريكورد يحوله ل بيانات عميل وبيانات العميل تبق متخزنه كلها في استراكتشر
{
    vector<string>VSDataForClientWithoutOrderOrNamed;
    VSDataForClientWithoutOrderOrNamed = SplitString(S1);
    // احنا بق عاوزين نحول الداتا ال في الفيكتور الي ريكورد ل بيانات العميل مترتبه ومتسميه 

    sClient ClientData;//  دا بقا انت هتملي معلومات العميل في استراكشر عادي

    ClientData.AccountNumber = VSDataForClientWithoutOrderOrNamed[0];
    ClientData.PinCode = VSDataForClientWithoutOrderOrNamed[1];
    ClientData.Name = VSDataForClientWithoutOrderOrNamed[2];
    ClientData.Phone = VSDataForClientWithoutOrderOrNamed[3];
    ClientData.AccountBalance = VSDataForClientWithoutOrderOrNamed[4];

    return ClientData;
    //  يعني دا هيرجعلي معلومات العميل في استركشر
}


void AddDateLineToFile(string FileName, string stDataLine)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out | ios::app); // Write and don't delet origin
    if (MyFile.is_open())
    {
        MyFile << stDataLine << endl;
        MyFile.close();
    }

}

void AddNewClient()
{
    sClient Client;
    Client = ReadNewClient();
    AddDateLineToFile(ClientFileName, ConvertRecordToLine(Client));


}



vector<sClient> LoadDateFromFileAsLineAndConvertToRecordInStructAfterThisStructInVector(string ClientFileName)
{
    fstream MyFile;
    string Line;
    sClient ClientInStruct;
    vector<sClient>ClientInVectorAsStruct;
    MyFile.open(ClientFileName, ios::in); //ReadMode

    if (MyFile.is_open())
    {

        while (getline(MyFile, Line))// خلي بالك هيا my file NotFile Name
        {
            ClientInStruct = ConvertLineToRecordInStruct(Line);
            ClientInVectorAsStruct.push_back(ClientInStruct);

        }

        MyFile.close();
    }
    return ClientInVectorAsStruct;
}


void PrintClientCard(sClient Client)
{
    cout << "\n Following is Client Details :\n";
    cout << " " << setw(30) << "\nAccountNumber:" << Client.AccountNumber;
    cout << " " << setw(30) << "\nPinCode is   :" << Client.PinCode;
    cout << " " << setw(30) << "\nClientName   :" << Client.Name;
    cout << " " << setw(30) << "\nPhone        :" << Client.Phone;
    cout << " " << setw(30) << "\nBalance      :" << Client.AccountBalance;

}


bool FindClientByAccountNumber(string AccountNumber, vector< sClient> VClient, sClient& Client)
{
    AccountNumber = ReadAccountNumber();

    for (sClient C : VClient)
    {
        if (C.AccountNumber == AccountNumber)
        {
            Client = C;             //   خلي بالك بقا من الحته دا لازم تعرف متغير جديد يلف في الفيكتو وبعد كدا تعمل متغير تاني بيساوي القديم ويبق باي ريفرنس 
            return true;
        }


    }
    return false;

}



bool MarkClientForUpdateByAccountNumber(string AccountNumber, vector<sClient>& VClient)
{

    for (sClient& C : VClient)
    {
        if (C.AccountNumber == AccountNumber)
        {
            C.MarkForDelete = true;
            return true;
        }

    }
    return false;
}


bool MarkClientForDeletByAccountNumber(string AccountNumber, vector<sClient>& VClient)
{

    for (sClient& C : VClient)
    {
        if (C.AccountNumber == AccountNumber)
        {
            C.MarkForDelete = true;
            return true;
        }

    }
    return false;
}


vector<sClient>SaveClientDateToFile_Delete(string FileName, vector<sClient>VClient)
{
    fstream MyFile;
    string DataLine;
    MyFile.open(FileName, ios::out);//

    if (MyFile.is_open())
    {

        for (sClient& C : VClient)
        {

            if (C.MarkForDelete == false)
            {

                DataLine = ConvertRecordToLine(C);
                MyFile << DataLine << endl;
            }


        }
        MyFile.close();
    }


    return VClient;
}


vector<sClient>SaveClientDateToFile_Update(string FileName, vector<sClient>VClient)
{
    fstream MyFile;
    string DataLine;
    MyFile.open(FileName, ios::out);// بيمسح كل الداتا الموجوده في الفايل 

    if (MyFile.is_open())
    {

        for (sClient& C : VClient)
        {

            if (C.MarkForDelete == false)
            {

                DataLine = ConvertRecordToLine(C);
                MyFile << DataLine << endl;
            }
            else
            {

                cout << "\nPinCode is   :";
                getline(cin >> ws, C.PinCode);
                cout << "\nClientName   :";
                getline(cin, C.Name);
                cout << "\nPhone        :";
                getline(cin, C.Phone);
                cout << "\nBalance      :";
                getline(cin, C.AccountBalance);

                DataLine = ConvertRecordToLine(C);
                MyFile << DataLine << endl;


            }


        }
        MyFile.close();
    }


    return VClient;
}

short ReadMenuueOption()
{
    cout << "Please Chose what you want to do? [1 To 6]\n";
    short Choise = 0;
    cin >> Choise;
    return Choise;


}

void PrintClientRecord(sClient Client)
{

    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(10) << left << Client.PinCode;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.Phone;
    cout << "| " << setw(12) << left << Client.AccountBalance;

}


void ShowAllClientData()
{
    vector<sClient>vClients = LoadDateFromFileAsLineAndConvertToRecordInStructAfterThisStructInVector(ClientFileName);
    cout << "\n\t\t\t\t\t Client List(" << vClients.size() << ") Client((s).";
    cout <<
        "\n________________________________________________________________";
    cout << "___________________________________________________\n" << endl;

    cout << "| " << left << setw(15) << "AccountNumber";
    cout << "| " << left << setw(10) << "PinCode";
    cout << "| " << left << setw(40) << "ClientName";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout <<
        "\n________________________________________________________________";
    cout << "____________________________________________________\n" << endl;

    for (sClient Client : vClients)
    {
        PrintClientRecord(Client);
        cout << endl;
    }
    cout <<
        "\n________________________________________________________________";
    cout << "_________________________________________________________\n" << endl;


}



void DleteClientAccountNumber()
{

    string AccountNumber;
    vector<sClient> VSClient = LoadDateFromFileAsLineAndConvertToRecordInStructAfterThisStructInVector(ClientFileName);

    sClient Client;
    char Answer = 'n';
    cout << "\n ________________________________________\n";
    cout << "\t delet Client Screan\n";
    cout << " ________________________________________\n";

    if (FindClientByAccountNumber(AccountNumber, VSClient, Client))
    {


        PrintClientCard(Client);
        cout << "\n\nAre tou sure to Delete this Client ? Y|N";
        cin >> Answer;

        if (Answer == 'Y' || Answer == 'y')
        {
            MarkClientForDeletByAccountNumber(AccountNumber, VSClient);

            SaveClientDateToFile_Delete(ClientFileName, VSClient);
            VSClient = LoadDateFromFileAsLineAndConvertToRecordInStructAfterThisStructInVector(ClientFileName);

            cout << "\n Client Is Deleted Successfully";
           

        }
    }
    else
    {

        cout << "\n Clients is not Found!";
      

    }


  

}


void UpdateClientAccountNumber()
{
    string AccountNumber;
    vector<sClient> VSClient = LoadDateFromFileAsLineAndConvertToRecordInStructAfterThisStructInVector(ClientFileName);
    sClient Client;
    char Answer = 'n';
    cout << "\n ________________________________________\n";
    cout << "\t update Client Screan\n";
    cout << " ________________________________________\n";

    if (FindClientByAccountNumber(AccountNumber, VSClient, Client))
    {


        PrintClientCard(Client);
        cout << "\n\nAre tou sure to Update this Client ? Y|N";
        cin >> Answer;

        if (Answer == 'Y' || Answer == 'y')
        {
            MarkClientForUpdateByAccountNumber(AccountNumber, VSClient);

            SaveClientDateToFile_Update(ClientFileName, VSClient);
            VSClient = LoadDateFromFileAsLineAndConvertToRecordInStructAfterThisStructInVector(ClientFileName);

            cout << "\n Client Is Update Successfully";
      

        }
    }
    else
    {

        cout << "\n Clients is not Found!";
     

    }
  
}


void AddClients()
{
    char AddMore = 'Y';
    do
    {
        system("cls");
        cout << "Adding New Client :\n\n";
        AddNewClient();
        cout << "\n Client Addining Successfully, Do you Want To Add More Clients ? Y|N?\n";
        cin >> AddMore;


    } while (toupper(AddMore) == 'Y');

}

void FindCkientByAccountNumberOrigin()
{
    vector<sClient> VSClient = LoadDateFromFileAsLineAndConvertToRecordInStructAfterThisStructInVector(ClientFileName);

    sClient Client;
    cout << "\n ________________________________________\n";
    cout << "\t Find Client Screan\n";
    cout << " ________________________________________\n";

    string AccountNumber = ReadAccountNumber();
    if (FindClientByAccountNumber(AccountNumber,VSClient, Client))
    {
        PrintClientCard(Client);

    }
    else
    {
        cout << "\n Client With Account Number (" << AccountNumber << ") Is Not Found !\n";
    }

}

void ShowEndScreen()
{

    cout << "\n ________________________________________\n";
    cout << "\t Program End\n";
    cout << " ________________________________________\n";
}


void PerformMainMenuueOption(enMainMennueOptions MainMennueOption)
{
    switch (MainMennueOption)
    {
    case ShowClientsList:
    {
        system("cls");
        ShowAllClientData();
        GotoBackMainMenuee();
        break;
    }

  
    case AddNewClientenum:
    {

        system("cls");
        AddClients();
        GotoBackMainMenuee();
        break;

    }
    
    case DeletClient:
    {


        system("cls");
        DleteClientAccountNumber();
            GotoBackMainMenuee();
        break;

    }
 
    case UpdateClientInfo:
    {


        system("cls");
        UpdateClientAccountNumber();
        GotoBackMainMenuee();
        break;

    }

    case FindClient:
    {


        system("cls");
        FindCkientByAccountNumberOrigin();
        GotoBackMainMenuee();
        break;

    }

    case Exit:
    {
        system("cls");

        ShowEndScreen();
        break;
    }
   
    default:
        cout << "Numer is wrong \n";
        break;
    }


}


void showMainMenueScrean()
{
    system("cls");
    cout << "========================================================================\n";
    cout << "\t\t\t Main Menue Screen \n";
    cout << "========================================================================\n";
    cout << "\t[1] Show Clients List .\n";
    cout << "\t[2] Add New Client .\n";
    cout << "\t[3] Delet Client .\n";
    cout << "\t[4] Update Client Info .\n";
    cout << "\t[5] Find Client.\n";
    cout << "\t[6] Exit .\n";
    cout << "======================================================================\n";

    PerformMainMenuueOption((enMainMennueOptions)ReadMenuueOption());
}


void GotoBackMainMenuee()
{
    cout << "\n\n Press any Key to go back to Main menue...";
    system("pause>0");

    showMainMenueScrean();
}


int main()
{
  
    showMainMenueScrean();
   
}




