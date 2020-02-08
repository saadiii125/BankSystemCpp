//***************************************************************
//                   HEADER FILE USED IN PROJECT
//****************************************************************
#include<string.h>
#include<string>
#include<iostream>
#include<fstream>
#include <stdexcept>
#include <windows.h>
#include<cctype>
#include<iomanip>
#include<conio.h>
using namespace std;

//***************************************************************
//                   CLASS USED IN PROJECT
//****************************************************************

class account
{
	int acno;
	char name[50];
	int deposit;
	char type;
public:
	void create_account();	//function to get data from user
	void show_account() const;	//function to show data on screen
	void modify();	//function to add new data
	void dep(int);	//function to accept amount and add to balance amount
	void draw(int);	//function to accept amount and subtract from balance amount
	void report() const;	//function to show data in tabular format
	int retacno() const;	//function to return account number
	int retdeposit() const;	//function to return balance amount
	char rettype() const;	//function to return type of account
};         //class ends here


void account::create_account()
{
	cout<<"\nEnter The account No. : ";
	cin>>acno;
	cout<<"\n\nEnter The Name of The account Holder : ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\nEnter Type of The account (C/S) : ";
	cin>>type;
	type=toupper(type);
	cout<<"\nEnter The Initial amount(>=500 for Saving and >=1000 for current ) : ";
	cin>>deposit;
	cout<<"\n\n\nAccount Created..";
}


void account::show_account() const
{
	cout<<"\nAccount No. : "<<acno;
	cout<<"\nAccount Holder Name : ";
	cout<<name;
	cout<<"\nType of Account : "<<type;
	cout<<"\nBalance amount : "<<deposit;
}


void account::modify()
{
	cout<<"\nAccount No. : "<<acno;
	cout<<"\nModify Account Holder Name : ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\nModify Type of Account : ";
	cin>>type;
	type=toupper(type);
	cout<<"\nModify Balance amount : ";
	cin>>deposit;
}

	
void account::dep(int x)
{
	deposit+=x;
}
	
void account::draw(int x)
{
	deposit-=x;
}
	
void account::report() const
{
	cout<<acno<<setw(10)<<" "<<name<<setw(10)<<" "<<type<<setw(6)<<deposit<<endl;
}
	
int account::retacno() const
{
	return acno;
}

int account::retdeposit() const
{
	return deposit;
}

char account::rettype() const
{
	return type;
}


//***************************************************************
//    	function declaration
//****************************************************************
void write_account();	//function to write record in binary file
void display_sp(int);	//function to display account details given by user
void modify_account(int);	//function to modify record of file
void delete_account(int);	//function to delete record of file
void display_all();		//function to display all account details
void deposit_withdraw(int, int); // function to desposit/withdraw amount for given account
void intro();	//introductory screen function
void entry();
string getpassword(const string& prompt = "Enter password> " );


//****************************************************************************
//					Login Class
//****************************************************************************

class login
{
	private:
		char username[25],pass[25];
	public:
		void addUser();
		void validate();
};
void login::validate()
{
	login ln;
	string password;
	char pwd[15],user[25];
	cout<<"Please Enter Username : ";
	cin>>user;
	password=getpassword("Please Enter Password : ");
	strcpy(pwd, password.c_str());
	
	bool flag=false;
	ifstream inFile;
	inFile.open("login.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
    	while(inFile.read(reinterpret_cast<char *> (&ln), sizeof(login)))
	{
		if(strcmp(ln.username,user)==0 && strcmp(ln.pass,pwd)==0)
		{
			cout<<"\nLoginned Successfully...\n";
			getch();	
			flag=true;
			break;
		}
	}
    inFile.close();
	if(flag==false)
		{
		cout<<"\nYou Entered Incorrect Details...Please Login again...\n";
		getch();
		entry();
		}
	
	
}


void login::addUser()
{
	
	login ln;
	string password,password1;
	char pass1[15];
	cout<<"Please Enter Username : ";
	cin>>ln.username;
	password=getpassword("Please Enter Password : ");
	password1=getpassword("\nPlease Confirm Password : ");
	strcpy(ln.pass, password.c_str());
	strcpy(pass1, password1.c_str());
	if(1) //Condistion to check if user already exist or not
	{
	if(strcmp(ln.pass,pass1)==0)
	{
		ofstream outFile;
		outFile.open("login.dat",ios::binary|ios::app);
		
		outFile.write(reinterpret_cast<char *> (&ln), sizeof(login));
		outFile.close();
	
		cout<<"\nUser Registered Successfully...\n";
		getch();
		entry();
	}
	else
	{
		cout<<"\nPasswords don't Match...\n";
		getch();
		entry();
	}
	}
	else
	{
		cout<<"\nUser already exist...Please Login..\n";
		getch();
		entry();
	}
	
}


//***************************************************************
//    	THE MAIN FUNCTION OF PROGRAM
//****************************************************************

int main()
{
	char ch;
	int num;
	intro();
	entry();
	do
	{
		system("cls");
		cout<<"\n\n\n\tMAIN MENU";
		cout<<"\n\n\t[01]. NEW ACCOUNT";
		cout<<"\n\n\t[02]. DEPOSIT AMOUNT";
		cout<<"\n\n\t[03]. WITHDRAW AMOUNT";
		cout<<"\n\n\t[04]. BALANCE ENQUIRY";
		cout<<"\n\n\t[05]. ALL ACCOUNT HOLDER LIST";
		cout<<"\n\n\t[06]. CLOSE AN ACCOUNT";
		cout<<"\n\n\t[07]. MODIFY AN ACCOUNT";
		cout<<"\n\n\t[08]. EXIT";
		cout<<"\n\n\tSelect Your Option (1-8) ";
		cin>>ch;
		system("cls");
		switch(ch)
		{
		case '1':
			write_account();
			break;
		case '2':
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			deposit_withdraw(num, 1);
			break;
		case '3':
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			deposit_withdraw(num, 2);
			break;
		case '4': 
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			display_sp(num);
			break;
		case '5':
			display_all();
			break;
		case '6':
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			delete_account(num);
			break;
		 case '7':
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			modify_account(num);
			break;
		 case '8':
			cout<<"\n\n\tThanks for using bank record system";
			break;
		 default :cout<<"\a";
		}
		cin.ignore();
		cin.get();
    }while(ch!='8');
	return 0;
}


//***************************************************************
//    	function to write in file
//****************************************************************

void write_account()
{
	account ac;
	ofstream outFile;
	outFile.open("account.dat",ios::binary|ios::app);
	ac.create_account();
	outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
	outFile.close();
}

//***************************************************************
//    	function to read specific record from file
//****************************************************************

void display_sp(int n)
{
	account ac;
	bool flag=false;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\nBALANCE DETAILS\n";
    	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if(ac.retacno()==n)
		{
			ac.show_account();
			flag=true;
		}
	}
    inFile.close();
	if(flag==false)
		cout<<"\n\nAccount number does not exist";
}


//***************************************************************
//    	function to modify record of file
//****************************************************************

void modify_account(int n)
{
	bool found=false;
	account ac;
	fstream File;
    File.open("account.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.retacno()==n)
		{
			ac.show_account();
			cout<<"\n\nEnter The New Details of account"<<endl;
			ac.modify();
			int pos=(-1)*static_cast<int>(sizeof(account));
			File.seekp(pos,ios::cur);
		    File.write(reinterpret_cast<char *> (&ac), sizeof(account));
		    cout<<"\n\n\t Record Updated";
		    found=true;
		  }
	}
	File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
}

//***************************************************************
//    	function to delete record of file
//****************************************************************


void delete_account(int n)
{
	account ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	outFile.open("Temp.dat",ios::binary);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if(ac.retacno()!=n)
		{
			outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
		}
	}
    inFile.close();
	outFile.close();
	remove("account.dat");
	rename("Temp.dat","account.dat");
	cout<<"\n\n\tRecord Deleted ..";
}

//***************************************************************
//    	function to display all accounts deposit list
//****************************************************************

void display_all()
{
	account ac;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\n\n\t\tACCOUNT HOLDER LIST\n\n";
	cout<<"====================================================\n";
	cout<<"A/c no.      NAME           Type  Balance\n";
	cout<<"====================================================\n";
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		ac.report();
	}
	inFile.close();
}

//***************************************************************
//    	function to deposit and withdraw amounts
//****************************************************************

void deposit_withdraw(int n, int option)
{
	int amt;
	bool found=false;
	account ac;
	fstream File;
    File.open("account.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.retacno()==n)
		{
			ac.show_account();
			if(option==1)
			{
				cout<<"\n\n\tTO DEPOSITE AMOUNT ";
				cout<<"\n\nEnter The amount to be deposited";
				cin>>amt;
				ac.dep(amt);
			}
		    if(option==2)
			{
				cout<<"\n\n\tTO WITHDRAW AMOUNT ";
				cout<<"\n\nEnter The amount to be withdraw";
				cin>>amt;
				int bal=ac.retdeposit()-amt;
				if((bal<500 && ac.rettype()=='S') || (bal<1000 && ac.rettype()=='C'))
					cout<<"Insufficience balance";
				else
					ac.draw(amt);
		      }
			int pos=(-1)*static_cast<int>(sizeof(ac));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(account));
			cout<<"\n\n\t Record Updated";
			found=true;
	       }
         }
    File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
}


//***************************************************************
//    	INTRODUCTION FUNCTION
//****************************************************************

void intro()
{
	cout<<"\n\n\n\t\t\t\t\t  B A N K";
	cout<<"\n\n\t\t\t\t\tR E C O R D";
	cout<<"\n\n\t\t\t\t\tS Y S T E M";
	cout<<"\n\n\n\n\t\t\t\tMADE BY : Iqra Shahbaz 172123";
	cout<<"\n\n\t\t\t\tAir University, Multan Campus";
	cin.get();
}


//***************************************************************
//    	LOGIN FUNCTION
//****************************************************************


void entry()
{
	int ch;
	login user;
	system("CLS");
	cout<<"\n\n\n\n";
	cout<<"\t[1] Login \n";
	cout<<"\t[2] Register \n";
	cout<<"\t[3] Exit\n\t";
	cin>>ch;
	if(ch==1)
	{
		user.validate();
	}
	else if(ch==2)
	{
		user.addUser();
	}
	else if(ch==3)
	{
		cout<<"\nProgram is Exiting.\n";
		getch();
		exit(1);
	}
	else
	{
		cout<<"\nYou Entered Incorrect Option.\n";
		getch();
		exit(1);

	}
}

string getpassword( const string& prompt  )
  {
  string result;

  // Set the console mode to no-echo, not-line-buffered input
  DWORD mode, count;
  HANDLE ih = GetStdHandle( STD_INPUT_HANDLE  );
  HANDLE oh = GetStdHandle( STD_OUTPUT_HANDLE );
  if (!GetConsoleMode( ih, &mode ))
    throw runtime_error(
      "getpassword: You must be connected to a console to use this program.\n"
      );
  SetConsoleMode( ih, mode & ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT) );

  // Get the password string
  WriteConsoleA( oh, prompt.c_str(), prompt.length(), &count, NULL );
  char c;
  while (ReadConsoleA( ih, &c, 1, &count, NULL) && (c != '\r') && (c != '\n'))
    {
    if (c == '\b')
      {
      if (result.length())
        {
        WriteConsoleA( oh, "\b \b", 3, &count, NULL );
        result.erase( result.end() -1 );
        }
      }
    else
      {
      WriteConsoleA( oh, "*", 1, &count, NULL );
      result.push_back( c );
      }
    }

  // Restore the console mode
  SetConsoleMode( ih, mode );

  return result;
  }

//***************************************************************
//    			END OF PROJECT
//***************************************************************
