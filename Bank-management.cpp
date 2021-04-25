#include<bits/stdc++.h>
#include<ctype.h>
#include<stdio.h>
using namespace std;


//Main class
class account
{
	int acno;
	char name[50];
	int deposit;
	char type;
public:
	void create_account();	//function to get data from user
	void show_account();	//function to show data on screen
	void modify();   //function to get new data from user
	void dep(int);	//function to accept amount and add to balance amount
	void draw(int);	//function to accept amount and subtract from balance amount
	void report();	//function to show data in tabular format
	int retacno();	//function to return account number
	int retdeposit();	//function to return balance amount
	char rettype();	//function to return type of account
};      

void account::create_account()
{
	cout <<"Enter The account No.:";
	cin >>acno;
	cout <<"Enter The Name of The account Holder: ";
	cin >>name;
	cout <<"Enter Type of The account (C/S): ";
	cin >>type;
	type = toupper(type);
	cout <<"Enter initial amount to open account(>=500 for Saving and >=1000 for Current account): ";
	cin >>deposit;
	cout <<"\n\nAccount Created Successfully..." <<endl <<endl;
}

void account::show_account()
{
	cout <<"\nAccount No. : "<<acno;
	cout <<"\nAccount Holder Name: " <<name;
	cout <<"\nType of Account : "<<type;
	cout <<"\nBalance amount : "<<deposit;
    cout <<endl <<endl;
}


void account::modify()
{
	cout <<"The account No.: "<<acno <<endl;
	cout <<"Enter The Name of The account Holder : ";
	cin >>name;
	cout <<"Enter Type of The account (C/S) : ";
	cin >>type;
	type = toupper(type);
}



void account::dep(int x)
{
	deposit += x;
}

void account::draw(int x)
{
	deposit -= x;
}

void account::report()
{
	cout <<acno <<setw(10) <<" " <<name <<setw(10) <<" " <<type <<setw(8) <<deposit <<endl;
}

int account::retacno()
{
	return acno;
}

int account::retdeposit()
{
	return deposit;
}

char account::rettype()
{
	return type;
}

//Function write in file
void write_account()
{
	account ac;
	ofstream outFile;
	outFile.open("account.dat",ios::binary|ios::app);
	ac.create_account();
	outFile.write((char *) &ac, sizeof(account));
	outFile.close();
}

//Reads specific record from file
void display_sp(int n)
{
	account ac;
	int flag=0;
	ifstream inFile;
    inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout <<"File could not be open !! Press any Key...";
		return;
	}
	cout <<"\nBALANCE DETAILS\n";
    while(inFile.read((char *) &ac, sizeof(account)))
	{
		if(ac.retacno()==n)
		{
			ac.show_account();
			flag=1;
		}
	}
    inFile.close();
	if(flag == 0)
		cout<<"\n\nAccount number does not exist!";
}


//Modify an existing account
void modify_account(int n)
{
	int found=0;
	account ac;
	fstream File;
    File.open("account.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout <<"File could not be open !! Press any Key...";
		return;
	}
    while(File.read((char *) &ac, sizeof(account)) && found==0)
	{
		if(ac.retacno()==n)
		{
			ac.show_account();
			cout <<"\n\nEnter The New Details of account"<<endl;
			ac.modify();
			int pos=(-1)*sizeof(account);
			File.seekp(pos,ios::cur);
		    File.write((char *) &ac, sizeof(account));
		    cout <<"\n\nRecord Updated";
		    found=1;
		  }
	}
	File.close();
	if(found == 0)
		cout <<"\n\nRecord Not Found..." <<endl;
}

//Delete record from file
void delete_account(int n)
{
	account ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout <<"File could not be open !! Press any Key...";
		return;
	}
	outFile.open("Temp.dat",ios::binary);
	inFile.seekg(0,ios::beg);
	while(inFile.read((char *) &ac, sizeof(account)))
	{
		if(ac.retacno() != n)
		{
			outFile.write((char *) &ac, sizeof(account));
		}
	}
    inFile.close();
	outFile.close();
	remove("account.dat");
	rename("Temp.dat","account.dat");
	cout <<"\n\nRecord Deleted..." <<endl <<endl;
}

//Display all accounts diposite list
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
	cout <<"\n\n\t\tACCOUNT HOLDER LIST\n\n";
	cout <<"====================================================\n";
	cout <<"A/c no.      NAME           Type  Balance\n";
	cout <<"====================================================\n";
	while(inFile.read((char *) &ac, sizeof(account)))
	{
		ac.report();
	}
	inFile.close();
    cout <<endl <<endl;
}

//Deposite and Withdrawl amount
void deposit_withdraw(int n, int option)
{
	int amt;
	int found=0;
	account ac;
	fstream File;
    File.open("account.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout <<"File could not be open !! Press any Key...";
		return;
	}
    while(File.read((char *) &ac, sizeof(account)) && found==0)
	{
		if(ac.retacno()==n)
		{
			ac.show_account();
			if(option==1)
			{
				cout <<"\n\nTO DEPOSITE AMOUNT " <<endl;
				cout  <<"Enter The amount to be deposited:";
				cin >>amt;
				ac.dep(amt);
			}
		    if(option==2)
			{
				cout <<"\n\nTO WITHDRAW AMOUNT " <<endl;
				cout <<"Enter The amount to be withdraw: ";
				cin>>amt;
				int bal=ac.retdeposit()-amt;
				if((bal<500 && ac.rettype()=='S') || (bal<1000 && ac.rettype()=='C'))
					cout <<"Insufficience balance!";
				else
					ac.draw(amt);
		      }
			int pos=(-1)* sizeof(ac);
			File.seekp(pos,ios::cur);
			File.write((char *) &ac, sizeof(account));
			cout <<"\n\nRecord Updated" <<endl;
			found=1;
	       }
	 }
    File.close();
	if(found == 0)
		cout<<"\n\nRecord Not Found ";
}


//Introduction Function
void intro()
{
	cout <<"\t\t\t\t\t\t\t--------------BANK MANAGEMENT SYSTEM---------------" <<endl;
	cout <<"\t\t\t\t\t\t\tMADE BY: Tushar Lalawat" <<endl;
}

//Main function
int main()
{
	char ch;
	int num;
	//clrscr();
	intro();
	do
	{
		//clrscr();
        cout <<"\t\t\t\t\t\t\t***************************************************" <<endl<<endl;
		cout <<"\t\t\t\t\t\t\tMAIN MENU" <<endl;
		cout <<"\t\t\t\t\t\t\t01. OPEN NEW ACCOUNT" <<endl;
		cout <<"\t\t\t\t\t\t\t02. DEPOSIT AMOUNT" <<endl;
		cout <<"\t\t\t\t\t\t\t03. WITHDRAW AMOUNT" <<endl;
		cout <<"\t\t\t\t\t\t\t04. BALANCE ENQUIRY" <<endl;
		cout <<"\t\t\t\t\t\t\t05. ALL ACCOUNT HOLDER LIST" <<endl;
		cout <<"\t\t\t\t\t\t\t06. CLOSE AN ACCOUNT" <<endl;
		cout <<"\t\t\t\t\t\t\t07. MODIFY AN ACCOUNT" <<endl;
		cout <<"\t\t\t\t\t\t\t08. EXIT" <<endl;
        cout <<"\t\t\t\t\t\t\t***************************************************" <<endl;
		cout <<"\nCHOOSE YOUR OPTION: " <<" ";
		cin >>ch;
		//clrscr();
		switch(ch)
		{
		case '1':
			write_account();
			break;

		case '2':
			cout <<"Enter account No. : "; 
            cin >>num;
			deposit_withdraw(num, 1);
			break;

		case '3':
			cout <<"Enter account No. : "; 
            cin >>num;
			deposit_withdraw(num, 2);
			break;

		case '4':
			cout <<"Enter The account No. : "; 
            cin >>num;
			display_sp(num);
			break;

		case '5':
			display_all();
			break;

		case '6':
			cout <<"Enter account No. : "; 
            cin >>num;
			delete_account(num);
			break;

		 case '7':
			cout <<"Enter The account No. : "; cin>>num;
			modify_account(num);
			break;

		 case '8':
			cout <<"Thanks for using bank managemnt system!" <<endl;
			break;

		 default :
            cout <<"\a";
		}
		//getch();
    }while(ch != '8');
	return 0;
}
