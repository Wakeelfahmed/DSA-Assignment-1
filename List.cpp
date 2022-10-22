#include "List.h"
list::list() :head(0), tail(0) {}
Node* list::get_head() const { return head; }
Node* list::get_tail() const { return tail; }
void list::insert_beg(Account Account){
	Node* New_Node = new Node(Account);
	if (isEmpty())
		tail = New_Node;
	else
		New_Node->next = head;
		head = New_Node;
}
void list::insert_specfic_Position(int place, Account student) {}
void list::insert_after(Account old, Account student){}
void list::insert_end(Account student){}
void list::Display_list() const{}
bool list::isEmpty() const { if (head == NULL) return 1; return 0; }
int list::Number_of_Nodes() const {
	Node* loop = head;		int NumberofNodes = 0;
	while (loop != NULL)
	{
		NumberofNodes++;
		loop = loop->next;
	}
	return NumberofNodes;
}
void list::delete_Student(Account Value_to_delete){}