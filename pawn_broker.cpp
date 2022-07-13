#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<string.h>
#include<math.h>

using namespace std;

class CustomerData
{
	public: char name[50], address[100], description[150], item[10], amount[10], date[12];
	
};

CustomerData C[100], t;
char buffer[50], temp[50], loanid[100],temp1[50],buffer1[50];
int count = 0, i;
fstream fp1,fp2;
string settlestatus;
//char keyloanid[15],tempcount[50],tempname[50];

//PACK FUNCTION FOR WRITING CUSTOMERS ENTRY DATA
void pack(CustomerData d)
{
	string settleLoan = "NO";
	fp1.open("CustomerData.txt",ios::out | ios::app);
	fp2.open("settle_loan.txt",ios::out | ios::app);
	strcpy(buffer, d.name);
	strcat(buffer, "|");
	strcat(buffer, d.address);
	strcat(buffer, "|");
	strcat(buffer, d.item);
	strcat(buffer, "|");
	strcat(buffer, d.description);
	strcat(buffer, "|");
	strcat(buffer, d.amount);
	strcat(buffer, "|");
	strcat(buffer, d.date);
	strcat(buffer, "|");
	//cout<<buffer;
	fp1<<count<<"|"<<buffer<<endl; //for storing details in the 1st file
	fp2<<count<<"|"<<d.name<<"|"<<settleLoan<<"|"<<endl; //for storing id,name,loan status in the 2nd file.
	fp1.close();
	fp2.close();
}

// WRITE FUNCTION FOR ENTERING CUSTOMERS RECORD IN THE FILE.
void write()
{

	cout<<"Enter the customer name:\n";
	cin>>ws;
	cin.getline(t.name,100);
	cout<<"Enter the address:\n";
	cin.getline(t.address,100);
	cout<<"Enter the item name:\n";
	cin.getline(t.item,100);
	cout<<"Enter the description of item:\n";
	cin.getline(t.description,100);
	cout<<"Enter the amount:\n";
	cin.getline(t.amount,100);
	cout<<"Enter today's Date in the format DD/MM/YYYY:\n";
	cin.getline(t.date,100); 
	pack(t);
}


 
//NO USE for this function
void unpack()
{
	
	for(i = 0; i<count; i++)
	{
		fp1.getline(buffer,100);
		sscanf(buffer,"%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|",loanid,C[i].name,C[i].address,C[i].item,C[i].description,C[i].amount,C[i].date);
		cout<<buffer;
	}
	fp1.close();
}

//DISPLAY FUNCTION TO PRINT CUSTOMERS DATA FROM THE FIRST FILE.
void display()
{	
	fp1.open("CustomerData.txt", ios::in);
	if(count == 0 )
	{
		cout<<"\nNo Record\n";
		return;
	}
	cout<<"Customer Detail is:\n";
	cout<<"\nLOAN ID\t\t NAME \t\t ADDRESS\t\t ITEM\t\t DESCRIPTION\t\t AMOUNT\t\t DATE\n";
	for(i =0; i<count;i++)
	{
		fp1.getline(buffer,100);
		sscanf(buffer,"%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|",loanid,C[i].name,C[i].address,C[i].item,C[i].description,C[i].amount,C[i].date);
		//cout<<"\nLOAN ID\t\t NAME \t\t ADDRESS\t\t ITEM\t\t DESCRIPTION\t\t AMOUNT\t\t DATE\n";
		cout<<loanid<<"\t\t";
		cout<<C[i].name<<"\t\t"<<C[i].address<<"\t\t"<<C[i].item<<"\t\t\t"<<C[i].description<<"\t\t\t"<<C[i].amount<<"\t\t"<<C[i].date<<"\n";
	}
	fp1.close();
}

//SERACHING DETAILS IN 1ST FILE.
void search()
{
	cout<<"Enter the loan id to search for\n";
	cin>>temp;
	fp1.open("CustomerData.txt", ios::in);
	for(i = 0; i<count; i++)
	{
		fp1.getline(buffer,100);
		sscanf(buffer,"%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|",loanid,C[i].name,C[i].address,C[i].item,C[i].description,C[i].amount,C[i].date);
		//cout<<buffer;
		
		if(strcmp(loanid,temp)==0)
		{
			cout<<"Record found!\n"<<C[i].name<<"\t\t"<<C[i].address<<"\t\t"<<C[i].item<<"\t\t\t"<<C[i].description<<"\t\t\t"<<C[i].amount<<"\t\t"<<C[i].date<<"\n";
			break;
		}
	}
		
		if(i == count)
		{
			cout<<"Loan Id not match, Record not found\n";
		}
	fp1.close();
}

//FOR CALCULATION OF LOAN
int countLeapYearDays(int date[])
{
	int year = date[2];
	int leapday = int(year/4);
	if (date[1] <= 2)
	{
		leapday = leapday - 1;
	}
	return leapday;
	
	
}
int calculateday(int date1[], int date2[])
{
	const int monthDays[12] = { 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 };
	long int dayCount1 = (date1[2] * 365);
   	dayCount1 += monthDays[date1[1]-1];
	dayCount1 += date1[0];
	dayCount1 += countLeapYearDays(date1);
	long int dayCount2 = (date2[2] * 365);
	dayCount2 += monthDays[date2[1]-1];
	dayCount2 += date2[0];
	dayCount2 += countLeapYearDays(date2);
	return ( abs(dayCount1 - dayCount2) );
		
}
void calculate_loan()
{
	search();
	int rate = 2;
	int principle;
	int loanDate[3],currentDate[3];
	cout<<"Enter loanDate:\n";
	for(int i = 0; i<3; i++)
	{
		cin>>loanDate[i];
	}
	cout<<"Enter currentDate:\n";
	for(int j=0; j<3; j++)
	{
		cin>>currentDate[j];
	}
	cout<<"Loan Date:";
	cout<<loanDate[0]<<"/"<<loanDate[1]<<"/"<<loanDate[2]<<"\n";
	cout<<"Current Date:";
	cout<<currentDate[0]<<"/"<<currentDate[1]<<"/"<<currentDate[2]<<"\n";
	int totaldays = calculateday(loanDate,currentDate);
	cout<<"Enter the principle Amount:\n";
	cin>>principle;
	float time = totaldays/365;
	float simpleIntreset = (principle*rate*time)/100;
	float Intreset = principle + simpleIntreset;
	cout<<"Total Intreset Rate:\n";
	cout<<Intreset<<"\n";
}

//FOR SETTLE LOAN IN SECOND FILE.
void settle_loan()
{
	cout<<"Enter the loan id to settle loan:\n";
	cin>>temp1;
	fp2.open("settle_loan.txt",ios::out);
	for(i = 0; i<count; i++)
	{
		fp2.getline(buffer1,100);
		sscanf(buffer1,"%[^|]|%[^|]|%s|",loanid,C[i].name,settlestatus);
		//cout<<buffer;
		
		if(strcmp(loanid,temp1)==0)
		{
			cout<<"Record found!\n"<<loanid<<"\t\t"<<C[i].name<<"\t\t"<<settlestatus<<"\n";
			settlestatus = "YES";
			break;
		}
	}
		
		if(i == count)
		{
			cout<<"Loan Id not match, Record not found\n";
		}
	fp2.close();
	
}

//MAIN PART(DRIVER CODE)
int main()
{
	int c;
	fp1.open("CustomerData.txt",ios::out);
	fp2.open("settle_loan.txt",ios::out);
	
	fp1.close();
	fp2.close();
	while(1)
	{
		cout<<"\n1.Enter new Customer Data:\n2. View all the Records of Customer\n3.Search for Customer Details:\n4.Calculate Loan:\n5.Settle Loan\n6.Exit";
		cout<<"\nEnter your choice\n";
		cin>>c;
		switch(c)
		{
			case 1: count++;
				//cout<<count;
				write();
				break;
			case 2: //unpack();
				display();
				break;
			case 3: //unpack();
				search();
				break;
			case 4: calculate_loan();
				break;
			case 5: settle_loan();
				break;
			default : exit(0);
		}
	}
	
	return 0;
}
	
