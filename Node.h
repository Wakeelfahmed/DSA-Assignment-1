#pragma once
#include"Account.h"
class Node
{
public:
	Account Account_Data;
	Node* next;
	Node();
	Node(Account NewAccount);
};
