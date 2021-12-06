//*****************************************************************************************
//Program by: Adam LaFleur
//Date: February 8, 2019
//Class: CS163 - Data Structures
//Program: #2
//File: list.h
//Purpose: The purpose of this program is to help the user recieve a message and process the
//message deciding whether to delete or respond to it later. The program also can access the
//top of the unresponed messages and access the front and back of the too respond messages.
//list.h defines the ADT structure, also defines the struct info
//*****************************************************************************************

struct entry {
	char * sender;
	char * subject;
	char * date;
	char * message;
};

const int MAX = 5;

class list
{
	public:
		list();
		~list();
		int receiveMessage(const entry &to_add);
		int stack2queue(int delC);
		int top(entry &send);
		int fbSend(entry &front, entry &back);
		int printStack();
		int printQueue();
	
	private:
	struct sNode {
		entry * data;
		sNode * next;
	}; //Stack node Defined
	sNode * head; //Stack head
	int top_index;

	struct qNode {
		entry data;
		qNode * next;
	}; //Queue node Defined
	qNode * rear; //Queue rear
	
	int printStack(sNode *&head, int num);
	int copyData(entry &set, const entry &to_add);
	int deleteData(entry &toDel);
	
	int push(const entry &to_add);
	int peek(entry &send);
	int pop();
	int sisEmpty();;

	int enqueue(const entry &to_add);
	int dequeue();
	int qisempty();
};
