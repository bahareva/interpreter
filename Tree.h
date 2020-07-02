#ifndef Tree_H
#define Tree_H

#include <iostream>
#include <string>
#include <vector>
#include <stack>
using namespace std;

struct Node
{
	string data;
	Node* left, * middle, * right;

	Node();
	Node(const string&, Node*, Node*, Node*);
};

class Position
{
public:
	Position(Node* _root);

	Position left() const;
	Position middle() const;
	Position right() const;
	string getData() const;
	bool empty() const;

private:
	Node* root;
};

class Tree
{
public:
	Tree();
	Tree(const Tree&);
	Tree& operator = (const Tree&);
	~Tree();

	Tree(const string&);
	Tree(const string&, const Tree&, const Tree&, const Tree&);
	Tree(const string&, Node*, Node*, Node*);
	Tree(vector<string>& );

	bool member(const string& x);
	void printTree();
	Position rootPos() const;

private:
	Node* root;

	Node* makeTree(vector<string>& v);
	Node* constructTreeByOperation(stack<Node*>&, stack<Node*>&);

	bool memberHelp(const string& x, Node* current);
	Node* copyHelper(Node* current);
	void deleteHelper(Node* current);
	void printTreeHelper(Node*);

	string getData(Node);
	vector<Node*> convert(vector<string>);
	int  getNumberOfChildren(Node* t);
};

#endif // !Tree_H

