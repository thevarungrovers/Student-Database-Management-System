#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<conio.h>
#include<iomanip>
using namespace std;

int main(){
	FILE *fp, *ft;
	char another, choice;
	
	struct student {
		char first_name[50],last_name[50];
		char course[100];
		int section;
	};
	
	struct student e;
	
	char xfirst_name[50],xlast_name[50]; // temporary variables
	long int recsize;
	
	fp = fopen("user.txt","rb+");
	
	if(fp == NULL)
	{
		fp = fopen("users.txt","wb+");
		if(fp == NULL)
		{
		puts("\n\tConnot open file");
		return 0;
		}
	}
	
	recsize = sizeof(e);
	
	while(1)
	{
		system("CLS");
		top : 
		cout<< "\t\t-----STUDENT DATABASE MANAGEMENT SYSTEM-----";
		cout<<"\n\n\n\n";
		cout<<"\n\t\t\t1.Add Records";
		cout<<"\n\t\t\t2.List Records";
		cout<<"\n\t\t\t3.Modify Records";
		cout<<"\n\t\t\t4.Delete Records";
		cout<<"\n\t\t\t5.Exit";
		cout<<"\n\n";
		cout<<"\t\t\tSelect your choice : ";
		fflush(stdin);
		choice = getche();
		
		switch(choice)
		{
			case '1' :
				fseek(fp,0,SEEK_END);
				another = 'Y';
				while(another == 'Y' || another == 'y')
				{
					system("CLS");
					cout<<"\n\n\n\tEnter first name : ";
					cin>>e.first_name;
					cout<<"\n\tEnter last name : ";
					cin>>e.last_name;
					cout<<"\n\tENter course name : ";
					cin>>e.course;
					cout<<"\n\tEnter section : ";
					cin>>e.section;
					
					fwrite(&e, recsize,1,fp);
					cout<<"\n\n Add another record : ";
					fflush(stdin);
					another = getche();
				}
				break;
				
			case '2' :
				system("CLS");
				rewind(fp);
				cout<<"--- View the records in the database ---";
				cout<<"\n";
				while(fread(&e, recsize, 1, fp) == 1)
				{
					cout<<"\n";
					cout<<"\n"<<e.first_name<<setw(10)<<e.last_name;
					cout<<"\n";
					cout<<"\n"<<e.course<<setw(10)<<e.section;
				}
				cout<<"\n\n";
				system("pause");
				break;
				
			case '3' :
				system("CLS");
				another = 'Y';
				while(another == 'Y' || another == 'y')
				{
					cout<<"\nEnter the last name of the student : ";
					cin>>xlast_name;
					
					rewind(fp);
					while(fread(&e, recsize, 1, fp) == 0)
					{
						if(strcmp(e.last_name, xlast_name) == 0)
						{
							cout<<"\nEnter the new first name : ";
							cin>>e.first_name;
							cout<<"\nEnter the new last name : ";
							cin>>e.last_name;
							cout<<"\nEnter the new course : ";
							cin>>e.course;
							cout<<"\nEnter the new section : ";
							cin>>e.section;
							
							fseek(fp, -recsize, SEEK_CUR);
							fwrite(&e, recsize, 1, fp);
							break;
						}
						else
						{
							cout<<"\nRecord not found..";
						}
					}
					cout<<"\n Modify Another record (Y/N) ";
					fflush(stdin);
					another = getchar();
				}
				break;
			
			case '4' :
				system("CLS");
				another = 'Y';
				while(another == 'Y' || another == 'y')
				{
					cout<<"\nEnter the last name of the student to delete the record : ";
					cin>>xlast_name;
					
					ft = fopen("temp.txt","wb");
					
					rewind(fp);
					
					while(fread(&e, recsize, 1, fp) == 1)
					{
						if(strcmp(e.last_name, xlast_name) != 0)
						{
							fwrite(&e, recsize, 1, ft);
						}
					}
					fclose(fp);
					fclose(ft);
					remove("users.txt");
					rename("temp.txt","users.txt");
					
					fp = fopen("users.txt","rb+");
					
					cout<<"\nDelete Another Record (Y/N) ";
					fflush(stdin);
					another = getchar();	
				}
				break;
				
			case '5' :
				fclose(fp);
				cout<<"\n\n\t\tTHANK YOU FOR USING THIS SOFTWARE\n\n\n";
				exit(0);
				break;
				
			default : cout<<"\nEnter Valid Number(1-5)";
				goto top;
		}
	}
	
	system("pause");
	return 0;
}
