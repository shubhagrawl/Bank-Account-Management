//Run this code on an ide otherwise some parts of it will not work or work improperly
//If you have any suggestions then pls tell me by commenting
//Give a like if you like it :)
#include<iostream>
#include<fstream>
#include<cstdlib>

using namespace std;
//Main class
class account_query
{
private:
    char account_number[20];
    char firstName[10];
    char lastName[10];
    float total_Balance;
public: //Functions
    void read_data();
    void show_data();
    void write_rec();
    void read_rec();
    void search_rec();
    void edit_rec();
    void delete_rec();
}obj; // Defining an object to the class
void account_query::read_data()
{
    //taking input from the user
    cout<<"\nEnter Account Number: ";
    cin>>obj.account_number;
    cout<<"Enter First Name: ";
    cin>>obj.firstName;
    cout<<"Enter Last Name: ";
    cin>>obj.lastName;
    cout<<"Enter Balance: ";
    cin>>obj.total_Balance;
    cout<<endl;
}
void account_query::show_data()
{
    //Displaying the data entered by the user
    cout<<"Account Number: "<<obj.account_number<<endl;
    cout<<"First Name: "<<obj.firstName<<endl;
    cout<<"Last Name: "<<obj.lastName<<endl;
    cout<<"Current Balance: Rs.  "<<obj.total_Balance<<endl;
    cout<<"-------------------------------"<<endl;
}
void account_query::write_rec()
{
    //Writing data to the binary file
    ofstream outfile;
    outfile.open("record.bank", ios::binary|ios::app);
    read_data();
    outfile.write((char*)&obj , sizeof(obj));
    outfile.close();
}
void account_query::read_rec()
{
    //Reading data from the binary file
    ifstream infile;
    infile.open("record.bank", ios::binary);
    if(!infile) //Checking if the file is open
    {
        cout<<"Error in Opening! File Not Found!!"<<endl;
        return;
    }
    cout<<"\n****Data from file****"<<endl;
    while(!infile.eof())
    {
        //Conditional loop to check if any data in on the file
        if((infile.read((char*)&obj , sizeof(obj))) > 0)
           {
               show_data();
           }
    }
    infile.close();
}
void account_query::search_rec()
{
    //Searching record from the file
    int n;
    ifstream infile;
    infile.open("record.bank", ios::binary);
    if(!infile)
    {
        cout<<"\nError in opening! File Not Found!!"<<endl;
        return;
    }
    infile.seekg(0,ios::end); //Seeking to the last char of the file
    int count = infile.tellg()/sizeof(obj); //obtaining the no of objects
    cout<<"\n There are "<<count<<" record in the file";
    cout<<"\n Enter Record Number to Search: ";
    cin>>n;
    infile.seekg((n-1) * sizeof(obj));
    infile.read((char*)&obj , sizeof(obj));
    show_data();
}
void account_query::edit_rec()
{
    //Function to edit the records
    int n;
    fstream iofile;
    iofile.open("record.bank", ios::in|ios::binary);
    if(!iofile)
    {
        cout<<"\nError in opening! File Not Found!!"<<endl;
        return;
    }
    iofile.seekg(0, ios::end); // Seeking to the last char of the file
    int count = iofile.tellg()/sizeof(obj); //obtaining the size of the file
    cout<<"\n There are "<<count<<" record in the file";
    cout<<"\n Enter Record Number to edit: ";
    cin>>n;
    iofile.seekg((n-1) * sizeof(obj));
    iofile.read((char*)&obj , sizeof(obj));
    cout<<"Record "<<n<<" has following data"<<endl;
    show_data();
    iofile.close();
    iofile.open("record.bank", ios::out|ios::in|ios::binary);
    iofile.seekp((n-1) * sizeof(obj));
    cout<<"\nEnter data to Modify "<<endl;
    read_data();
    iofile.write((char*)&obj , sizeof(obj));
}
void account_query::delete_rec()
{
    //Function to delete any record
    int n;
    ifstream infile;
    infile.open("record.bank", ios::binary);
    if(!infile)
    {
        cout<<"\nError in opening! File Not Found!!"<<endl;
        return;
    }
    infile.seekg(0,ios::end); //Seeking to last character of file
    int count = infile.tellg()/sizeof(obj);
    cout<<"\n There are "<<count<<" record in the file";
    cout<<"\n Enter Record Number to Delete: ";
    cin>>n;
    fstream tmpfile; //Creating a temporary file
    tmpfile.open("tmpfile.bank", ios::out|ios::binary);
    infile.seekg(0); //Seeking to first char of file
    for(int i=0; i<count; i++)
    {
        infile.read((char*)&obj , sizeof(obj));
        if(i==(n-1))
            continue;
        tmpfile.write((char*)&obj , sizeof(obj));
    }
    infile.close();
    tmpfile.close();
    remove("record.bank");
    rename("tmpfile.bank", "record.bank");
}
int main()
{
    account_query A; //Object of the class
    int choice;
    cout<<"*** Bank Account Management System ***"<<endl;
    while(true)
    {
        cout<<"Select one option below ";
        cout<<"\n\t1-->Add record to file";
        cout<<"\n\t2-->Show record from file";
        cout<<"\n\t3-->Search Record from file";
        cout<<"\n\t4-->Update Record";
        cout<<"\n\t5-->Delete Record";
        cout<<"\n\t6-->Quit";
        cout<<"\nEnter your choice: ";
        cin>>choice;
        switch(choice)
        {
        case 1:
            A.write_rec();
            break;
        case 2:
            A.read_rec();
            break;
        case 3:
            A.search_rec();
            break;
        case 4:
            A.edit_rec();
            break;
        case 5:
            A.delete_rec();
            break;
        case 6:
            exit(0);
            break;
        default:
            cout<<"\nEnter correct choice";
            exit(0);
        }
    }
    system("pause");
    return 0;
}
