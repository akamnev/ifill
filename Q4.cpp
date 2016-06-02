#include <vector>
#include <iostream>

using namespace std;

typedef struct Node 
{
	int data;
	struct Node* next;
} Node;

void push(Node*& head_ref, int new_data)
{
    Node* new_node = new Node;
    new_node->data  = new_data;
    new_node->next = head_ref;
    head_ref = new_node;
}

void print_list(Node* root) 
{
	while (root) 
	{
		cout << root->data << " ";
	    root = root->next;
	}
	cout << endl;
}

Node* reverse(Node* root) 
{
	Node* new_root = 0;
	while (root) 
	{
		Node* next = root->next;
		root->next = new_root;
		new_root = root;
		root = next;
	}
	return new_root;
}

void merge(Node* root1, Node* root2)
{
	Node* new_root = root1;
	root1 = root1->next;
	
	while(root1 && root2 && root2 != root1)
	{
		new_root->next = root2;
		root2 = root2->next;
		new_root = new_root->next;
		new_root->next = root1;
		root1 = root1->next;
		new_root = new_root->next;
	}
	return;
}

inline int length(Node* root)
{
	int cnt = 0;
	while(root)
	{
		cnt++;
		root = root->next;
	}
	return cnt;
}

int main()
{
    cout << endl << "Question #4" << endl;
	Node* root1 = 0;
	for(int i = 9; i > 0; i--)
		push(root1, i);
	print_list(root1);

	int len = length(root1);
	Node* root2 = root1;
	for(int i = 0; i < len / 2; i++)
		root2 = root2->next;
	root2 = reverse(root2);

	merge(root1, root2);
	cout << "merge" << endl;
	print_list(root1);
	return 0;
}