
//Library Files

#include<iostream>
#include<cstring>
#include<fstream>                        
#include <string>

using namespace std;

struct management
{
	int account_number;
	char name[50];
	char city[50];
	char state[50];
	int zip;
	char telephone_number[50];
	char account_balance[50];
	char last_payment_date[100];
};

//Function 1

void record_entry();
void AddRecordInFile(management object);

//Function 2

void display_particular_customer_record();

//Function 3

void delete_particular_customer_record();

//Function 4

void change_particular_customer_record();

//Function 5

void view_all_customers_list();

//Function 6

void balance_inquiry();

//Function 7

void deposit_amount();

//Function 8

void withdraw_amount();

//Function 9 

void transfer_amount_to_other_account();

//Funtion Token

string* getTokens(string line);

//Funtion PrintMenu

void print_menu();

//Main Function

void main()                               
{
	cout << endl;
	cout << endl;
	cout << "                    Welcome To Inventory System To Manage Customer Accounts                 " << endl;
	
	//Menu Printing

	print_menu();                         

}

//Funtion 1

//This Function Is Used For Record Entry

void record_entry()                      
{
	//Asking From User To Tell Number Of Customers 

	int cus_num;
	cout << "Enter The Number Of Customers You Want To Take Record From Them : ";
	cin >> cus_num;
	management* customer = new management[cus_num];
	
	for (int i = 0; i < cus_num; i++)
	{
		cout << "********************************************************************************************" << endl;
		cout << "                                  Enter " << i + 1 << " Customer Details :-" << endl;
		cout << "********************************************************************************************" << endl;
		cout << "Enter Account Number Of Customer = ";
		cin >> customer[i].account_number;
		cout << endl;
		cin.ignore();
		cout << "Enter The Name Of Customer = ";
		cin.getline(customer[i].name, 50);
		cout << endl;
		cout << "Enter City Of Customer = ";
		cin.getline(customer[i].city, 50);
		cout << endl;
		cout << "Enter State Of Customer = ";
		cin.getline(customer[i].state, 50);
		cout << endl;
		cout << "Enter Zip Code Of Customer = ";
		cin >> customer[i].zip;
		cout << endl;
		cin.ignore();
		cout << "Enter Telephone Number Of Customer = ";
		cin.getline(customer[i].telephone_number, 20);
		cout << endl;

		//Input Validation
		
		double UserBalance;
		do                                      
		{
			cout << "Enter Account Balance Of Customer = ";
			cin.getline(customer[i].account_balance, 50);
			UserBalance = stod(customer[i].account_balance);
			if (UserBalance < 0) 
			{
				cout << "Please Enter Positive Amount In Account Balance" << endl;
			}
		} while (UserBalance < 0);              
		cout << endl;
		cout << "Enter Last payment date Of Customer = ";
		cin.getline(customer[i].last_payment_date, 100);
		AddRecordInFile(customer[i]);
	}

	//Ask The User To Return To Main Menu

	cout << "Do You Want To Go Back To Menu (Y/N) : " << endl;
	char option;
	cin >> option;
	switch (option)
	{
	case 'y':
	case 'Y':
		print_menu();                           
		break;                              
	default:
		cout << endl;
		cout << "Thank You For Using Our System !" << endl;
	}
}

//Function 1

 //This Function Is Used For Record Entry In File

void AddRecordInFile(management object)         
{
	ofstream fout;
	string filename = "Record.txt";
	fout.open(filename, ios::app);
	fout << object.account_number << "," << object.name << "," << object.city << "," << object.state << "," << object.zip << "," << object.telephone_number << "," << object.account_balance << "," << object.last_payment_date;
	fout << endl;
	fout.close();
}

//Funtion 2

//This Function Is Used For Display Particular Customer Record By Entering Account Number

void display_particular_customer_record()    
{
	fstream file;
	string account_num;
	file.open("D:\\Semester 1\\Programming Fundamentals\\Programming Fundamentals Lab\\Pf lab 2nd Project\\Project2\\Project2\\Record.txt", ios::in);
	if (file.is_open())
	{
		string delimiter = ",";
		string fullfile;
		
		//Asking For Account Number

		cout << "Enter The Account Number For Search " << endl;
		cout << endl;
		cout << "Account Number = ";
		cin >> account_num;
		
		bool recordFound = false;
		while (getline(file, fullfile))
		{
			//To Get Tokens Of string

			int pos = 0;
			string token;
			pos = fullfile.find(delimiter);    
			token = fullfile.substr(0, pos);
			
			if (token == account_num)
			{
				string* object = getTokens(fullfile);
				recordFound = true;
				cout << endl;
				cout << "Customer Record Is :" << endl;
				cout << endl;
				cout << "         Account No : " << object[0] << endl;
				cout << "         Name : " << object[1] << endl;
				cout << "         City : " << object[2] << endl;
				cout << "         State : " << object[3] << endl;
				cout << "         Zip Code : " << object[4] << endl;
				cout << "         Telephone Number : " << object[5] << endl;
				cout << "         Account Balance : " << object[6] << endl;
				cout << "         Last Payment Date : " << object[7] << endl;
				cout << endl;
			}
		}
		if (recordFound == false)
		{
			cout << "Record Not Found" << endl;
		}
		file.close();
	}
	else
	{
		cout << "File Not Found" << endl;
	}

	//Ask The User To Return To Main Menu

	cout << "Do You Want To Go Back To Menu (Y/N) : " << endl;
	char option;
	cin >> option;
	switch (option)
	{
		case 'y':
		case 'Y':
			print_menu();         
			break;
		default:
			cout << endl;
			cout << "Thank You For Using Our System !" << endl;
	}
}

//Function 3

//This Function Is Used To Delete Particular Record By Entering Account Number

void delete_particular_customer_record()       
{
	fstream readFile;
	string account_num;
	readFile.open("D:\\Semester 1\\Programming Fundamentals\\Programming Fundamentals Lab\\Pf lab 2nd Project\\Project2\\Project2\\Record.txt", ios::in);
	ofstream writeFile;
	
	//Temporary File

	string filename = "Temporary.txt";        
	writeFile.open(filename, ios::app);
	
	bool accountFind = false;
	
	if (readFile.is_open())
	{
		//Searching By Account Number

		cout << "Enter The Account Number To Delete Record " << endl;
		cout << endl;
		cout << "Account Number = ";            
		cin >> account_num;
		
		string particular_line;
		while (getline(readFile, particular_line))
		{
			string* object = getTokens(particular_line);    
			if (object[0] == account_num)
			{
				accountFind = true;
				cout << "Record Deleted Successfully !" << endl;
				cout << endl;
				cout << "Customer Record Is :" << endl;
				cout << endl;
				cout << "         Account No : " << object[0] << endl;
				cout << "         Name : " << object[1] << endl;
				cout << "         City : " << object[2] << endl;
				cout << "         State : " << object[3] << endl;
				cout << "         Zip Code : " << object[4] << endl;
				cout << "         Telephone Number : " << object[5] << endl;
				cout << "         Account Balance : " << object[6] << endl;
				cout << "         Last Payment Date : " << object[7] << endl;
				cout << endl;
				cout << endl;
			}
			else
			{

				writeFile << particular_line;
				writeFile << endl;
			}
		}
		if (accountFind == false)
		{
			cout << "Record Not Found !" << endl;
			cout << endl;
		}
		readFile.close();

		//Remove File

		remove("Record.txt");
	}
	else
	{
		cout << "File Not Found" << endl;
		cout << endl;
	}
	writeFile.close();

	//Rename File

	rename("Temporary.txt", "Record.txt");

	//Ask The User To Return To Main Menu

	cout << "Do You Want To Go Back To Menu (Y/N) : " << endl;
	char option;
	cin >> option;
	switch (option)
	{
	case 'y':
	case 'Y':
		print_menu();               
		break;
	default:
		cout << endl;
		cout << "Thank You For Using Our System !" << endl;
	}
}

//Function 4

 //This Function Is Used To Change All Record Of A Particular Customer By Entering Account Number

void change_particular_customer_record()       
{
	fstream file;
	string account_num;
	file.open("D:\\Semester 1\\Programming Fundamentals\\Programming Fundamentals Lab\\Pf lab 2nd Project\\Project2\\Project2\\Record.txt", ios::in);
	ofstream fout;
	
	//Temporary File

	string filename = "Temporary.txt";          
	fout.open(filename, ios::app);
	
	bool accountFind = false;
	
	if (file.is_open())
	{
		//Asking The Account Number

		cout << "Enter The Account Number To Change Record " << endl;
		cout << endl;
		cout << "Account Number = ";
		cin >> account_num;

		string delimiter = ",";
		string line;
		while (getline(file, line))
		{
			//To Get Tokens Of String

			string* object = getTokens(line);  
			if (object[0] == account_num)
			{
				accountFind = true;
				management customer;          

				//Input Again To Change The Record Of A Particular Customer

				cout << "Enter Customer Details To Be Changed :" << endl;
				cout << "********************************************************************************************" << endl;
				cout << "Enter The Name Of Customer = ";
				cin.getline(customer.name, 50);
				cout << endl;
				cout << "Enter City Of Customer = ";
				cin.getline(customer.city, 50);
				cout << endl;
				cout << "Enter State Of Customer = ";
				cin.getline(customer.state, 50);
				cout << endl;
				cout << "Enter Zip Code Of Customer = ";
				cin >> customer.zip;
				cout << endl;
				cin.ignore();
				cout << "Enter Telephone Number Of Customer = ";
				cin.getline(customer.telephone_number, 20);
				cout << endl;
				
				//Input Validation(Balance Should Be Positive)

				double UserBalance;
				do
				{
					cout << "Enter Account Balance Of Customer = ";
					cin.getline(customer.account_balance, 50);
					UserBalance = stod(customer.account_balance);
					if (UserBalance < 0)
					{
						cout << "Please enter positive amount in account balance" << endl;
					}
				} while (UserBalance < 0);
				cout << endl;
				cout << "Enter Last payment Date Of Customer = ";
				cin.getline(customer.last_payment_date, 100);
				cout << endl;
				cout << "Record Updated Successfully !" << endl;
				cout << endl;
				fout << customer.account_number << "," << customer.name << "," << customer.city << "," << customer.state << "," << customer.zip << "," << customer.telephone_number << "," << customer.account_balance << "," << customer.last_payment_date << endl;
			}
			else
			{
				fout << line;
				fout << endl;
			}
		}
		if (accountFind == false)
		{
			cout << "Record Not Found !" << endl;
			cout << endl;
		}
		file.close();
	
		//Remove File
		
		remove("Record.txt");
	}
	else
	{
		cout << "File Not Found" << endl;
		cout << endl;
	}
	fout.close();

	//Rename File

	rename("Temporary.txt", "Record.txt");

	//Ask The User To Return To Main Menu

	cout << "Do You Want To Go Back To Menu (Y/N) : " << endl;
	char option;
	cin >> option;
	switch (option)
	{
	case 'y':
	case 'Y':
		print_menu();                         
		break;
	default:
		cout << endl;
		cout << "Thank You For Using Our System !" << endl;
	}
}

//Function 5 

//This Function Is To Display All Records That Are In File

void view_all_customers_list()        
{
	int record = 1;
	fstream file;
	file.open("D:\\Semester 1\\Programming Fundamentals\\Programming Fundamentals Lab\\Pf lab 2nd Project\\Project2\\Project2\\Record.txt", ios::in);
	if (file.is_open())
	{
		string fullfile;
		while (getline(file, fullfile))
		{
			//To Get Tokens Of String

			string* object = getTokens(fullfile);        
			
			cout << "Customer Number " << record << " Record Is :" << endl;
			cout << endl;
			cout << "         Account No : " << object[0] << endl;
			cout << "         Name : " << object[1] << endl;
			cout << "         Account Balance : " << object[6] << endl;
			cout << endl;
			record++;
		}
		cout << endl << "Total Number Of Records In File Found Are : " << record - 1 << endl;
		file.close();
	}

	//Ask The User To Return To Main Menu

	cout << "Do You Want To Go Back To Menu (Y/N) : " << endl;
	char option;
	cin >> option;
	switch (option)
	{
	case 'y':
	case 'Y':
		print_menu();                                   
		break;
	default:
		cout << endl;
		cout << "Thank You For Using Our System !" << endl;
	}
}

//Function 6

//This Function Is Used For Balance Inquiry Of A Particular Customer By Entering Account Number

void balance_inquiry()                      
{
	fstream readFile;
	string account_num;
	readFile.open("D:\\Semester 1\\Programming Fundamentals\\Programming Fundamentals Lab\\Pf lab 2nd Project\\Project2\\Project2\\Record.txt", ios::in);
	
	bool account_find = false;
	
	if (readFile.is_open())
	{
		//Asking For Account Number

		cout << "Enter the Account Number To Check The Balance : " << endl;
		cout << endl;
		cout << "Account Number = ";                    
		cin >> account_num;
		cout << endl;
		
		string line;
		while (getline(readFile, line))
		{
			//To Get Tokens From String

			string* object = getTokens(line);
			
			if (object[0] == account_num)
			{
				account_find = true;
				cout << "Customer Name And Balance Is : " << endl;
				cout << endl;
				cout << "         Name : " << object[1] << endl;
				cout << "         Balance : " << object[6] << endl;
			}
		}
		if (account_find == false)
		{
			cout << "Record Not Found ! " << endl;
		}
		readFile.close();
	}
	else
	{
		cout << "File Not Found !" << endl;
	}

	//Asking To Return To Main Menu

	cout << "Do You Want To Go Back To Menu (Y/N) : " << endl;
	char option;
	cin >> option;
	switch (option)
	{
	case 'y':
	case 'Y':
		print_menu();
		break;
	default:
		cout << endl;
		cout << "Thank You For Using Our System !" << endl;
	}

}

//Function 7

//This Function Is Used To Deposit Amount In A Particular Account By Entering Account Number

void deposit_amount()
{
	fstream readFile;
	string account_num;
	readFile.open("D:\\Semester 1\\Programming Fundamentals\\Programming Fundamentals Lab\\Pf lab 2nd Project\\Project2\\Project2\\Record.txt", ios::in);
	ofstream writeFile;
	
	//Temporary File
	
	string filename = "Temporary.txt";
	writeFile.open(filename, ios::app);

	bool accountFind = false;
	
	if (readFile.is_open())
	{
		//Asking For Account Number

		cout << "Enter The Account Number In Which You Want To Deposit Amount " << endl;
		cout << endl;
		cout << "Account Number = ";
		cin >> account_num;
		cout << endl;

		string line;
		while (getline(readFile, line))
		{
			//To Get Tokens Of String

			string* object = getTokens(line);
			if (object[0] == account_num)
			{
				accountFind = true;
			
				//Input Validation(Amount Must Be Positive)

				char deposit_amount[50];
				double UserBalance;
				do
				{
					cout << "Enter the Amount You Want to Deposit = ";
					cin >> deposit_amount;
					UserBalance = stod(deposit_amount);
					if (UserBalance < 0)
					{
						cout << "Please Enter Positive Amount In Account Balance ! " << endl;
					}
				} while (UserBalance < 0);
				string balance = object[6];
				double NewBalance = stod(balance) + UserBalance;
				cout << "Amount Deposited Successfully ! " << endl;
				writeFile << object[0] << "," << object[1] << "," << object[2] << "," << object[3] << "," << object[4] << "," << object[5] << "," << NewBalance << "," << object[7] << endl;
			}
			else
			{
				writeFile << line;
				writeFile << endl;
			}
		}
		if (accountFind == false)
		{
			cout << "Record not found!" << endl;
		}
		readFile.close();
	
		//For Remove The File

		remove("Record.txt");
	}
	else
	{
		cout << "File Not Found ! " << endl;
	}
	writeFile.close();

	//For Rename The File

	rename("Temporary.txt", "Record.txt");

	//Asking To Return To Main Menu

	cout << "Do You Want To Go Back To Menu (Y/N) : " << endl;
	char option;
	cin >> option;
	switch (option)
	{
	case 'y':
	case 'Y':
		print_menu();
		break;
	default:
		cout << endl;
		cout << "Thank You For Using Our System !" << endl;
	}

}	

//Function 8

//This Function Is Used For Withdraw Amount From A Particular Customer Account By Entering Account Number

void withdraw_amount()
{
	fstream readFile;
	string account_num;
	readFile.open("D:\\Semester 1\\Programming Fundamentals\\Programming Fundamentals Lab\\Pf lab 2nd Project\\Project2\\Project2\\Record.txt", ios::in);
	ofstream writeFile;

	//Temporary File
	
	string filename = "Temporary.txt";
	writeFile.open(filename, ios::app);
	
	bool accountFind = false;
	
	if (readFile.is_open())
	{
		//Asking For Account Number
			
		cout << "Enter The Account Number In Which You Want To Withdraw Amount " << endl;
		cout << endl;
		cout << "Account Number = ";
		cin >> account_num;
		cout << endl;
	
		string line;
		while (getline(readFile, line))
		{
			//To Get Tokens Of String

			string* object = getTokens(line);
			
			if (object[0] == account_num)
			{
				accountFind = true;
				bool check = true;
				
				//Here do-While Loop Is Used For Withdraw Amount Must be Smaller Than Current Balance
				//Input Must Be Positive

				char withdraw_amount[50];
				double extractAmount;
				do 
				{
					cout << "Enter the Amount You Want To Withdraw = ";
					cin>>withdraw_amount;
					extractAmount = stod(withdraw_amount);
					double prevBalance = stod(object[6]);
					if (extractAmount < 0 || extractAmount > prevBalance) 
					{
						check = false;
						if (extractAmount < 0) 
						{
							cout << "Please Enter Positive Amount." << endl;
						}
						if (extractAmount > prevBalance) 
						{
							cout << "You Do Not Have Sufficient Balance In Your Account ! " << endl;
							cout << endl;
							cout << "Your Current Balance Is : " << prevBalance << endl;
						}
					}
					else 
					{
						check = true;
					}	
				} while (check == false);

				double NewBalance = stod(object[6]) - extractAmount;
				cout << "Amount Withdraw Successfully ! " << endl;
				writeFile << object[0] << "," << object[1] << "," << object[2] << "," << object[3] << "," << object[4] << "," << object[5] << "," << NewBalance << "," << object[7] << endl;
			}
			else
			{
				writeFile << line;
				writeFile << endl;
			}
		}
		if (accountFind == false)
		{
			cout << "Record not found!" << endl;
		}
		readFile.close();
		
		//Remove File

		remove("Record.txt");
	}
	else
	{
		cout << "File Not Found ! " << endl;
	}
	writeFile.close();
	
	//Rename File
	
	rename("Temporary.txt", "Record.txt");
	
	//Asking To Return To Main Menu

	cout << "Do You Want To Go Back To Menu (Y/N) : " << endl;
	char option;
	cin >> option;
	switch (option)
	{
	case 'y':
	case 'Y':
		print_menu();
		break;
	default:
		cout << endl;
		cout << "Thank You For Using Our System !" << endl;
	}

}

//Funtion 9

//This Function Is Used For Transfer Amount To Other Account By Entering Two Account Numbers

void transfer_amount_to_other_account()
{
	fstream file;
	string account_num1;
	string account_num2;
	string firstUserBalance, secondUserBalance;
	file.open("D:\\Semester 1\\Programming Fundamentals\\Programming Fundamentals Lab\\Pf lab 2nd Project\\Project2\\Project2\\Record.txt", ios::in);
	string filename = "Temporary.txt";
	bool first_account_find = false;
	bool second_account_find = false;
	if (file.is_open())
	{
		//Asking For Two Account Numbers

		cout << "Enter Account Number From Which You Want To Transfer " << endl;
		cout << endl;
		cout << "Account Number = ";
		cin >> account_num1;
		cout << "Enter Account Number In Which You Want To Deposit " << endl;
		cout << endl;
		cout << "Account Number = ";
		cin >> account_num2;
		
		string line;
		while (getline(file, line))
		{
			//To Get Tokens Of String

			string* object = getTokens(line);
			string accountNUmber = object[0];
			if (object[0] == account_num1)
			{
				first_account_find = true;
				string balance = object[6];
				firstUserBalance = balance;
				//firstUserBalance = &balance[0];
			}
			if (object[0] == account_num2)
			{
				second_account_find = true;
				string balance = object[6];
				secondUserBalance = balance;
				//secondUserBalance = &balance[0];
			}
		}
		file.close();
	}
	if (first_account_find == true && second_account_find == true)
	{
		bool check = true;
		char amount_to_transfer[50];
		double extractAmount;
		do 
		{
			cout << "Enter Amount To Transfer:" << endl;
			cin>>amount_to_transfer;
			extractAmount = stod(amount_to_transfer);
			double prevBalance = stod(firstUserBalance);
			if (extractAmount < 0 || extractAmount > prevBalance) 
			{
				check = false;
				if (extractAmount < 0) 
				{
					//Amount Should Be Positive

					cout << "Only Positive Amount Is Allowed ! " << endl;
					cout << endl;
				}
				else if (extractAmount > prevBalance) 
				{
					//Amount Should Be less Than Current Balance

					cout << "You Do Not Have Sufficient Balance In Your Account ! " << endl;
					cout << endl;
					cout << "Your Current Balance Is: " << prevBalance << endl;
				}
			}
			else
			{
				check = true;
			}
		} while (check == false);

		double firtPersonCurentBalance = stod(firstUserBalance) - extractAmount;
		double secondPersonCuurentBalance = stod(secondUserBalance) + extractAmount;
		fstream file;
		string recordFile = "D:\\Semester 1\\Programming Fundamentals\\Programming Fundamentals Lab\\Pf lab 2nd Project\\Project2\\Project2\\Record.txt";
		file.open(recordFile, ios::in);
		ofstream fout;
		string filename = "Temporary.txt";
		string line;
		fout.open(filename, ios::app);
		if (file.is_open())
		{
			while (getline(file, line))
			{
				string* object = getTokens(line);
				if (object[0] == account_num1)
				{
					//write first user updated record in file
					
					fout << object[0] << "," << object[1] << "," << object[2] << "," << object[3] << "," << object[4] << "," << object[5] << "," << firtPersonCurentBalance << "," << object[7] << endl;
				}
				else if (object[0] == account_num2)
				{
					//write second user updated record in file
					
					fout << object[0] << "," << object[1] << "," << object[2] << "," << object[3] << "," << object[4] << "," << object[5] << "," << secondPersonCuurentBalance << "," << object[7] << endl;
				}
				else
				{
					fout << line;
					fout << endl;
				}
			}
			file.close();
			remove("Record.txt");
		}
		fout.close();
		rename("Temporary.txt", "Record.txt");
	}
	else
	{
		if ((second_account_find == false) && (first_account_find == false))
		{
			cout << "Both Accounts Not Found" << endl;
		}
		else if ((second_account_find == false) || (first_account_find == false))
		{
			if (second_account_find == false)
			{
				cout << "Second Account Not Found" << endl;
			}
			else if (first_account_find == false)
			{
				cout << "First Account Not Found" << endl;
			}
		}
	}

	//Asking The User To Return To Main Menu

	cout << "Do You Want To Go Back To Menu (Y/N) : " << endl;
	char option;
	cin >> option;
	switch (option)
	{
	case 'y':
	case 'Y':
		print_menu();
		break;
	default:
		cout << endl;
		cout << "Thank You For Using Our System !" << endl;
	}

}

//Function Token

string* getTokens(string line)
{
	string delimiter = ",";
	string* object = new string[8];
	int pos = 0;
	string token;
	int i = 0;
	while ((pos = line.find(delimiter)) != string::npos)
	{
		token = line.substr(0, pos);
		object[i] = token;
		i++;
		line.erase(0, pos + delimiter.length());
	}
	object[i] = line;
	return object;
}

//Function PrintMenu

void print_menu()
{

	cout << "********************************************************************************************" << endl;
	cout << "                                              Menu                                          " << endl;
	cout << "********************************************************************************************" << endl;
	cout << "Press 1 For Enter New Record " << endl;
	cout << "Press 2 For Seacrch A Particular Customer Record " << endl;
	cout << "Press 3 For Delete A Particular Customer Record " << endl;
	cout << "Press 4 For Change A Particular Customer Record " << endl;
	cout << "Press 5 For View All Customer Record " << endl;
	cout << "Press 6 For Balance Inquiry " << endl;
	cout << "Press 7 For Deposit Amount " << endl;
	cout << "Press 8 For Withdraw Amount " << endl;
	cout << "Press 9 For Transfer Amount To Other Account " << endl;
	cout << "Press 10 For Exit From Menu " << endl;
	cout << "********************************************************************************************" << endl;
	cout << endl;
	int option;
	cout << "Enter Your Choice = ";
	cin >> option;
	cout << endl;
	switch (option)
	{
	case 1:
		record_entry();
		break;
	case 2:
		display_particular_customer_record();
		break;
	case 3:
		delete_particular_customer_record();
		break;
	case 4:
		change_particular_customer_record();
		break;
	case 5:
		view_all_customers_list();
		break;
	case 6:
		balance_inquiry();
		break;
	case 7:
		deposit_amount();
		break;
	case 8:
		withdraw_amount();
		break;
	case 9:
		transfer_amount_to_other_account();
		break;
	case 10:
		cout << "Thank You For Using Our System !" << endl;
		exit(0);
	default:
		cout << "Invalid Choice !" << endl;
	}
	cout << endl;
}