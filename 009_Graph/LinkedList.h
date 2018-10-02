#pragma once

struct Node
{
	struct Vertex* Data;
	Node* Next;
};

Node* CreateListNode(struct Vertex* newData);
void  DestoryListNode(Node* node);
void  AppendListNode(Node** head, Node* newNode);
void  InsertAfterListNode(Node** current, Node** newNode);
void  InsertNewListHead(Node** head, Node** newHead);
void  RemoveListNode(Node** head, Node** remove);
Node* GetListNodeAt(Node* head, int location);
int   GetListNodeCount(Node* head);