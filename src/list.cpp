//*****************************************************************************************
//Program by: Adam LaFleur
//Date: Feburary 8, 2019
//Class: CS163 - Data Structures
//Program: #2
//File: list.cpp
//Purpose: The purpose of this program is to help the user recieve a message and process the
//message deciding whether to delete or respond to it later. The program also can access the
//top of the unresponed messages and access the front and back of the too respond messages. 
//list.cpp has the purpose of containing the algorithms that control the adding to the stack 
//of new messages, deciding whether to delete the message or send to to the add function for 
//the queue. There are algoritms to print the lists and grab the accessable data info for
//each list. Functions return 1 for success and 0 for failure
//*****************************************************************************************/
#include "list.h"
#include <iostream>
#include <cstring>

using namespace std;



//Initializes object, head is NULL, and rear is NULL; Empty Lists!
list::list()
{
	head = nullptr;
	rear = nullptr;
}



//deconstructs and deletes all data, makes a call to pop to empty the stack and makes a call to 
//dequeue to empty the queue. All sets head and rear to NULL
list::~list()
{
	while(head)
	{
		pop();
	}
	head = nullptr;

	while(rear)
	{
		dequeue();
	}
	rear = nullptr;	
}



//Copies the data from one struct entry to another. Uses two arguments, the first is the object
//to copy two and the second is the object to copy from.
int list::copyData(entry &set, const entry &to_add)
{
	set.sender = new char[strlen(to_add.sender) + 1];
	strcpy(set.sender, to_add.sender);
	set.subject = new char[strlen(to_add.subject) + 1];
	strcpy(set.subject, to_add.subject);
	set.date = new char[strlen(to_add.date) + 1];
	strcpy(set.date, to_add.date);
	set.message = new char[strlen(to_add.message) + 1];
	strcpy(set.message, to_add.message);
	return 1;
}



//Used to prevent repeated code, deallocated and delete memory for struct entries. Takes an entry argument
int list::deleteData(entry &toDel)
{
	if(toDel.sender)
	{
		delete [] toDel.sender;
		delete [] toDel.subject;
		delete [] toDel.date;
		delete [] toDel.message;
		return 1;
	}
	return 0;
}



//Sends struct entry to push and returns flag that push returns. Takes an entry argument
int list::receiveMessage(const entry &to_add)
{
	return push(to_add);
}



//grabs the top of the stack by calling peek, uses a pass by reference argument to send the 
//data back. 
int list::top(entry &send)
{
	return peek(send);
}



//Used to determine whether to delete a entry or send it to the queue. The functions takes in an
//int argument that contains either 1 which means to save or 0 which means to delete. Deleting
//just pops the stack, while saving peeks the stack, enqueues the queue with what was peeked, then
//pops the stack
int list::stack2queue(int delC)
{
	entry newEnt;
	if(delC == 0)
	{
		pop();
		return 1;
	}
	if(delC == 1)
	{
		peek(newEnt);
		enqueue(newEnt);
		pop();
		deleteData(newEnt);
		return 1;
	}
	return 0;
}



//Used to send back the visible front and back entries of the queue, takes two pass by reference 
//arguments
int list::fbSend(entry &front, entry &back)
{
	if(rear)
	{
		copyData(front, rear->next->data);
		copyData(back, rear->data);
		return 1;
	}
	return 0;
}



//Recursive print the stack, takes in a node argument, and an int argument to keep track of how
//many spots are filled in the array at each node
int list::printStack(sNode *& head, int num)
{
	if(!head) return 0;
	for(int i = num; i > 0; i--)
	{
		if(head->data[i-1].sender)
		{
			cout << "Sender: " << head->data[i-1].sender << endl;
			cout << "Subject: " << head->data[i-1].subject << endl;
			cout << "Date: " << head->data[i-1].date << endl;
			cout << "Message: " << head->data[i-1].message << endl;
			cout << endl;
		}
		num = MAX;
	}
	printStack(head->next, num);
	return 1;
}



//Wrapper function for function above, returns status of that function
int list::printStack()
{
	return printStack(head, top_index);
}



//Used to remove the top entry, if index is 0 then it deletes top node
int list::pop()
{
	sNode * ptr = nullptr;
	if(!head) return 0;
	if(head->data[top_index - 1].sender)
	{
		deleteData(head->data[top_index - 1]);
	}
	top_index--;
	if(top_index == 0)
	{
		if(head->next == nullptr)
		{
			delete [] head->data;
			delete head;
			head = nullptr;
		}
		else
		{
			ptr = head->next;
			delete [] head->data;
			delete head;
			head = ptr;
			top_index = MAX;
		}	
	}
	return 1;
}



//Adds a entry to the list, if head is null add node and entry, if the nodes
//array is full then add a new node and start filling that array, keeps repeating
int list::push(const entry &to_add)
{
	sNode * newNode;
	if(!head)
	{
		top_index = 0;
		head = new sNode;
		head->next = nullptr;
		head->data = new entry[MAX];
		copyData(head->data[top_index],to_add);
		top_index++;
		return 1;
	}
	if(top_index == MAX)
	{
		top_index = 0;
		newNode = new sNode;
		newNode->data = new entry[MAX];
		copyData(newNode->data[top_index], to_add);
		newNode->next = head;
		head = newNode;
		top_index++;
		return 1;
	}
	else
	{
		copyData(head->data[top_index], to_add);
		top_index++;
		return 1;
	}
	return 0;
}



//Used to grab the top of the stack, takes a pass by reference entry argument
int list::peek(entry &send)
{
	if(!head) return 0;
	if(top_index > 0)
	{
		copyData(send, head->data[top_index-1]);
	}
	return 1;
}



//Check to see if stack is empty
int list::sisEmpty()
{
	if(!head) return 0;
	return 1; 
}



//Add a entry to the queue, takes a pass by reference entry argument
int list::enqueue(const entry &to_add)
{
	int result = 0;
	qNode * newNode = new qNode;
	qNode * ptr = nullptr;
	newNode->next = nullptr;
	copyData(newNode->data, to_add);

	if(!rear)
	{
		rear = newNode;
		rear->next = rear;
		result = 1;
	}
	else
	{
		ptr = rear->next;
		rear->next = newNode;
		rear = rear->next;
		rear->next = ptr;
		result = 1;
	}
	return result;	
}



//Used to remove a entry from the queue
int list::dequeue()
{
	qNode * ptr = nullptr;
	if(!rear) return 0;
	if(rear->next == rear)
	{
		deleteData(rear->data);
		delete rear;
		rear = nullptr;
		return 1;
	}
	ptr = rear->next;
	rear->next = ptr->next;
	deleteData(ptr->data);
	delete ptr;
	return 1;
}



//Checks to see if queue is empty
int list::qisempty()
{
	if(!rear) return 0;
	return 1;
}



//Prints the content of the queue
int list::printQueue()
{
	if(!rear) return 0;
	qNode * curr = rear->next; //Access First node
	while(curr->next != rear->next) //Traverse list, and print
	{
		cout << "Sender: " << curr->data.sender << endl;
		cout << "Subject: " << curr->data.subject << endl;
		cout << "Date: " << curr->data.date << endl;
		cout << "Message: " << curr->data.message << endl;
		curr = curr->next;
	}
	//Prints rear node, couldn't print node using the code above
	cout << "Sender: " << curr->data.sender << endl;
	cout << "Subject: " << curr->data.subject << endl;
	cout << "Date: " << curr->data.date << endl;
	cout << "Message: " << curr->data.message << endl;

	return 1;
}
