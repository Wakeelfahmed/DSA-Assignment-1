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
void list::insert_specfic_Position(short place, Account Account) {
	short position_count = 1;
	if (place > Number_of_Nodes()) {
		cout << "List has less nodes than the place, Node CAN't be inserted!!\n";
		return;
	}
	Node* NewNode = new Node(Account);
	Node* p = head;
	while (p != NULL)
	{
		if (place == 1) {
			insert_beg(Account);
			return;
		}
		else if (place == Number_of_Nodes()) {
			insert_end(Account);
			return;
		}
		else if (position_count == place - 1 && place != 0) {
			NewNode->next = p->next;
			p->next = NewNode;
			return;
		}
		p = p->next;		//move to next node
		position_count++;
	}
}
void list::insert_after(Account PreviousAcc, Account NewAcc) {
	if (isEmpty())
	{
		cout << "List is empty";
		return;
	}
	Node* p = head;
	short position_count = 1;
	while (p != NULL)
	{
		if (p->Account_Data == PreviousAcc)
		{
			Node* NewNode = new Node(NewAcc);
			if (position_count == Number_of_Nodes()) {
				p->next = NewNode;
				tail = NewNode;
				//insert_end(newvalue);
			}
			else
			{
				NewNode->next = p->next;
				p->next = NewNode;
				//insert_specfic_Position(position_count, newvalue);
			}
			return;
		}
		p = p->next;
		position_count++;
	}
}
void list::insert_end(Account Account) {
	Node* New_Node = new Node(Account);
	New_Node->Account_Data = Account;
	if (isEmpty())
		head = New_Node;
	else
		tail->next = New_Node;
	tail = New_Node;
}
void list::Display_list() const {
	Node* loop = head;
	short count = 1;
	while (loop != NULL)
	{
		cout << count << ". " << loop->Account_Data.get_Account_Holder_Name() << endl;
		loop = loop->next;
		count++;
	}
}
short list::Number_of_Nodes() const {
	Node* loop = head;		short NumberofNodes = 0;
	while (loop != NULL)
	{
		NumberofNodes++;
		loop = loop->next;
	}
	return NumberofNodes;
}
short Search_in_List(Account Account_to_search, list list) {
	Node* p = list.get_head();
	short count = 1;
	while (p != NULL)
	{
		if (Account_to_search == p->Account_Data)
			return count;
		p = p->next;
		count++;
	}
	return 0;
}
void list::delete_Account_Node_fr_list(Account Account_to_delete) {
	if (isEmpty()) {
		cout << "List is Empty\n"; return;
	}
	else if (!Search_in_List(Account_to_delete, *this)) {
		cout << "Not found in list\n"; return;
	}
	Node* p = head;
	Node* Temp;
	if (Account_to_delete == head->Account_Data) {
		Temp = p;
		head = p->next;
		delete Temp;
		return;
	}
	while (p != NULL)
	{
		if (p->next->Account_Data == Account_to_delete)
		{
			Temp = p->next;
			p->next = p->next->next;
			Temp->Account_Data.~Account();
			delete Temp;
			if ((p->next == NULL))
				tail = p;
			return;
		}
		p = p->next;
	}
}\
void list::Display_Node(short i) const {
	Node* loop = head;
	short count = 1;
	while (loop != NULL)
	{
		if (count == i) {
			loop->Account_Data.get();	return;
		}
		count++;
		loop = loop->next;
	}
}
Node* list::get_Account_Node(short i) const {
	Node* loop = head;
	short count = 1;
	while (loop != NULL)
	{
		if (count == i) {
			return loop;
		}
		count++;
		loop = loop->next;
	}
}