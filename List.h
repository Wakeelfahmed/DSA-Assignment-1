#pragma once
#include"Node.h"
class list
{
private:
	Node* head;
	Node* tail;
public:
	list();
	Node* get_head() const;
	Node* get_tail() const;
	void insert_beg(Account NewAccount);
	void insert_specfic_Position(int place, Account NewAccount);
	void insert_after(Account oldAccount, Account NewAccount);
	void insert_end(Account NewAccount);
	void Display_list() const;
	bool isEmpty() const;
	int Number_of_Nodes() const;
	void delete_Account_Node_fr_list(Account Account_Pos_to_delete);
	//Account get_Accounts_Details(int Node_Position) {	}
	void Display_Node(int i) const;
	Node* get_Account_Node(int i) const;
};