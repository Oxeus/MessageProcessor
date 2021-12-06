//*****************************************************************************************
//Program by: Adam LaFleur
//Date: February 8, 2019
//Class: CS163 - Data Structures
//Program: #2
//File: main.cpp
//Purpose: The purpose of this program is to help the user recieve a message and process the 
//message deciding whether to delete or respond to it later. The program also can access the
//top of the unresponed messages and access the front and back of the too respond messages.
//main.cpp has the purpose of controlling the program and inputting data to be sent to the ADT
//*****************************************************************************************
#include <iostream>
#include <cstring>
#include "list.h"

using namespace std;



void print(const entry &pEntry);
void status(int num);
void del(entry &toDel);



// The purpose of main is the initialize and run the program, main has a menu that gives the user an
// option of what they want to do, the menu repeats until the user specifices when to stop. The 
// main program also creates a struct info, fills it, and then sends it to the adt, receieve message is
// specified. The user is given the options of adding a mesage, processing the message, viewing the most recent message,
// viewing the first and last message to respond to, printing the stack, printing the queue, and 
// finally quitting the program.
int main()
{
	entry insert, topL, front, back; //entry objects used to grab data from ADT
	list messages; //creates an ADT object that main can interact with
	int choice = 0, num = 0, delc = 0; //choice used to control which menu option selected, num is used to record ADT return values
	bool control = true; //Controls whether the program loops or not
	char sender[64], subject[64], date[64], message[128]; //Used to temporarily store user input until allocated and copied into the info struct

	cout << "----------------------------------------------" << endl;
        cout << "********** Program #1: Job Listings **********" << endl;
        cout << "----------------------------------------------" << endl;
	while(control)
	{
		num = 0;
		cout << "Please choose an option: " << endl;
		cout << "01. Add a Message." << endl;
		cout << "02. Process a message." << endl;
		cout << "03. View most recent message." << endl;
		cout << "04. View first and last message to respond to." << endl;
		cout << "05. Print All (Stack)(Test-Only)." << endl;
		cout << "06. Print All (Queue)(Test-Only)." << endl;
		cout << "07. Quit client program." << endl;
		cout << "----------------------------------------------" << endl;
		cout << "Please enter a choice: ";
		cin >> choice;
		cin.ignore();
		cout << endl;
		switch(choice)
		{
			case 1:
				cout << "Please enter name of sender (email address or phone number for text): ";
				cin.getline(sender, sizeof(sender));
				cout << "Please enter subject of message: ";
                                cin.getline(subject, sizeof(subject));
				cout << "Please enter date of message: ";
                                cin.getline(date, sizeof(date));
				cout << "Please enter the body of message: ";
                                cin.getline(message, sizeof(message));
				insert.sender = new char[strlen(sender) + 1];
				strcpy(insert.sender, sender);
				insert.subject = new char[strlen(subject) + 1];
                                strcpy(insert.subject, subject);
				insert.date = new char[strlen(date) + 1];
                                strcpy(insert.date, date);
				insert.message = new char[strlen(message) + 1];
                                strcpy(insert.message, message);
				num = messages.receiveMessage(insert);
				del(insert);
				status(num);
				break;
			case 2:
				num = messages.top(topL);
                                if(num)
                                {
					print(topL);
					del(topL);
					cout << endl << "What choice do you want to make (0 for delete, 1 for save): ";
					cin >> delc;
					num = messages.stack2queue(delc);
				}
				status(num);
				break;
			case 3:
				num = messages.top(topL);
				if(num)
				{
					cout << "Top" << endl;
					cout << "----------------------------------" << endl;
					print(topL);
					del(topL);
				}
				status(num);
				break;
			case 4:
				num = messages.fbSend(front, back);
				if(num)
				{
					cout << "Front" << endl;
					cout << "-----------------------------------" << endl;
					print(front);
                                        del(front);
					cout << endl;
					cout << "Back" << endl;
					cout << "-----------------------------------" << endl;
					print(back);
                                        del(back);
				}
				status(num);
				break;
			case 5:
				num = messages.printStack();
				status(num);
				break;
			case 6:
				num = messages.printQueue();
				status(num);
				break;
			case 7:
				control = false;
				break;
			default:
				cout << "Incorrect choice, please try again." << endl;
				break;
		}
	}
	return 0;
}



// The purpose of print is to print off the entry data that is returned back from the ADT
void print(const entry &pEntry)
{
	cout << "Sender: " << pEntry.sender << endl;
	cout << "Subject: " << pEntry.subject << endl;
	cout << "Date: " << pEntry.date << endl;
	cout << "Message: " << pEntry.message << endl;
}



// The purpose of del is to delete the temporary allocated memory of entry objects after
// they have been send to the ADT, a function was created so there would be no repeated code
void del(entry &toDel)
{
	delete [] toDel.sender;
	delete [] toDel.subject;
	delete [] toDel.date;
	delete [] toDel.message;
}



// The prupose of status is to display whether the action succeded or not. Status takes in
// an argument int num which is supplied from main, if the number supplied is 0 then
// Failure will be printed out, if 1 is supplied then Success will be printed out.
void status(int num)
{
	cout << endl;
	cout << "Status: ";
	if(num == 0)
	{
		cout << "Failure! / Empty List!" << endl;
	}
	if(num == 1)
	{
		cout << "Success!" << endl;
	}
	cout << endl;
}
