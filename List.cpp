#include "List.h"
list::list() :head(NULL), tail(NULL) {}
Node* list::get_head() const { return head; }
Node* list::get_tail() const { return tail; }
bool list::isEmpty() const {
	if (
		head == NULL) return 1; return 0;
}
void list::insert_beg(Account Account) {
	Node* New_Node = new Node(Account);
	if (isEmpty())
		tail = New_Node;
	else
		New_Node->next = head;
	head = New_Node;
}
void list::insert_specfic_Position(int place, Account student) {}
void list::insert_after(Account old, Account student) {}
void list::insert_end(Account Account) {
	Node* New_Node = new Node(Account);
	if (isEmpty())
		head = New_Node;
	else
		tail->next = New_Node;
	tail = New_Node;
}
void list::Display_list() const {
	Node* loop = head;
	int count = 1;
	while (loop != NULL)
	{
		cout << count << ". " << loop->Account_Data.get_Account_Holder_Name() << endl;
		loop = loop->next;
		count++;
	}
}
int list::Number_of_Nodes() const {
	Node* loop = head;		int NumberofNodes = 0;
	while (loop != NULL)
	{
		NumberofNodes++;
		loop = loop->next;
	}
	return NumberofNodes;
}
void list::delete_Account_Node_fr_list(Account Value_to_delete) {
	if (isEmpty()) {
		cout << "List is Empty\n"; return;
	}
	else if (!Search_in_List(Value_to_delete, *this)) {
		cout << "Not found in list\n"; return;
	}
	Node* p = head;
	Node* Temp;
	if (Value_to_delete == head->Data) {
		Temp = p;
		head = p->next;
		delete Temp;
		return;
	}
	while (p != NULL)
	{
		if (p->next->Data == Value_to_delete)
		{
			cout << "abr\n";
			Temp = p->next;
			p->next = p->next->next;
			delete Temp;
			if ((p->next == NULL))
				tail = p;
			return;
		}
		p = p->next;
	}
}

void list::Display_Node(int i) const {
	Node* loop = head;
	int count = 1;
	while (loop != NULL)
	{
		if (count == i) {
			loop->Account_Data.get();	return;
		}
		count++;
		loop = loop->next;
	}
}
Node* list::get_Account_Node(int i) const {
	Node* loop = head;
	int count = 1;
	while (loop != NULL)
	{
		if (count == i) {
			return loop;
		}
		count++;
		loop = loop->next;
	}
}

