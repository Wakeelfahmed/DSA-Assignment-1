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
	void insert_beg(Account student);
	void insert_specfic_Position(int place, Account student);
	void insert_after(Account old, Account student);
	void insert_end(Account student);
	void Display_list() const;
	bool isEmpty() const;
	int Number_of_Nodes() const;
	void delete_Student(Account Value_to_delete);
};