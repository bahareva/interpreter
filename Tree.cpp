#include "Tree.h"
#include <cstring>
#include <cassert>
#include <stack>
#include "Parser.h"

Node::Node(const string& _data, Node* _left, Node* _middle, Node* _right)
	:data(_data), left(_left), middle(_middle), right(_right) {}

Node::Node() : data(""), left(NULL), middle(NULL), right(NULL)
{}


Tree::Tree()
{
	root = nullptr;
}

Tree::Tree(const string& x)
{
	root = new Node(x, nullptr, nullptr, nullptr);
}

Tree::Tree(const Tree& t)
{
	root = copyHelper(t.root);
}

Tree::~Tree()
{
	deleteHelper(root);
}

Tree& Tree::operator = (const Tree& t)
{
	if (this != &t)
	{
		deleteHelper(root);
		root = copyHelper(t.root);
	}
	return *this;
}

Tree::Tree(const string& rt, const Tree& left, const Tree& middle, const Tree& right)
{
	root = new Node(rt,
		copyHelper(left.root),
		copyHelper(middle.root),
		copyHelper(right.root));
}

Tree::Tree(const string& rt, Node* left, Node* middle, Node* right)
{
	root = new Node(rt, left, middle, right);
}

Tree::Tree(vector<string>& v)
{
	this->root = makeTree(v);
}

bool Tree::member(const string& x)
{
	return memberHelp(x, root);
}

void Tree::printTree()
{
	printTreeHelper(this->root);
}

string Tree::getData(Node t)
{
	return t.data;
}

bool Tree::memberHelp(const string& x, Node* current)
{
	if (current == nullptr)
	{
		return false;
	}

	return current->data == x ||
		memberHelp(x, current->left) ||
		memberHelp(x, current->right);
}

Node* Tree::copyHelper(Node* current)
{
	if (current == nullptr)
	{
		return nullptr;
	}

	return new Node(current->data,
		copyHelper(current->left),
		copyHelper(current->middle),
		copyHelper(current->right));
}

void Tree::deleteHelper(Node* current)
{
	if (current == nullptr)
	{
		return;
	}

	deleteHelper(current->left);
	deleteHelper(current->right);
	deleteHelper(current->middle);
	delete current;
}

vector<Node*> Tree::convert(vector<string> v)
{
	vector<Node*> result;
	for (int i = 0; i < v.size(); i++)
	{
		Node* node = new Node(v[i], nullptr, nullptr, nullptr);
		result.push_back(node);
	}
	return result;
}

Node* Tree::constructTreeByOperation(stack<Node*>& op, stack<Node*>& var)
{
	Node* x = op.top();
	int numberOfChildren = getNumberOfChildren(x);
	if (numberOfChildren == 1)
	{
		x->right = var.top();
		var.pop();
		op.pop();
		var.push(x);
	}
	if (numberOfChildren == 2)
	{
		x->right = var.top();
		var.pop();
		x->left = var.top();
		var.pop();
		op.pop();
		var.push(x);
	}
	if (numberOfChildren == 3)
	{
		x->right = var.top();
		var.pop();
		x->middle = var.top();
		var.pop();
		x->left = var.top();
		var.pop();
		op.pop();
		var.push(x);
	}
	return x;
}


int Tree::getNumberOfChildren(Node* t)
{
	Parser a;
	char data = t->data[0];

	if (t->data == "read" || t->data == "print")
	{
		return 1;
	}
	else if (a.isOperation(data))
	{
		return 2;
	}
	else
	{
		return 3;
	}
}

Node* Tree::makeTree(vector<string>& v)
{
	Node* tree = new Node();
	vector<Node*> vector = convert(v);
	stack<Node*> operations;
	stack<Node*> variables;

	Node* bottom = new Node("N", nullptr, nullptr, nullptr);
	operations.push(bottom);
	variables.push(bottom);

	Parser par;

	for (int i = 0; i < vector.size(); i++)
	{
		if (vector.size() == 1)
		{
			tree = vector[0];
		}
		else if (par.isLetter(vector[i]->data[0]) || par.isNumber(vector[i]->data[0]))
		{
			if (vector[i]->data == "print" || vector[i]->data == "read")
			{
				operations.push(vector[i]);
			}
			variables.push(vector[i]);
		}

		else if (vector[i]->data[0] == '[')
		{
			operations.push(vector[i]);
		}
		else if (vector[i]->data[0] == ']')
		{
			while (operations.top()->data != "N" && operations.top()->data != "[")
			{
				tree = constructTreeByOperation(operations, variables);
			}
			if (operations.top()->data == "[")
			{
				operations.pop();
			}
		}
		else if (vector[i]->data[0] == '(') {
			operations.push(vector[i]);
		}
		else if (vector[i]->data[0] == ')')
		{
			while (operations.top()->data != "N" && operations.top()->data != "(")
			{
				tree = constructTreeByOperation(operations, variables);
			}
			if (operations.top()->data == "(")
			{
				operations.pop();
			}
		}
		else {
			while (operations.top()->data != "N" && par.priority(vector[i]->data) <= par.priority(operations.top()->data))
			{
				tree = constructTreeByOperation(operations, variables);
			}
			operations.push(vector[i]);
		}
	}
	while (operations.top()->data != "N")
	{
		tree = constructTreeByOperation(operations, variables);
	}
	return tree;
}

void Tree::printTreeHelper(Node* n)
{
	if (n == NULL)
	{
		return;
	}
	else
	{
		cout << "Root Data: " << n->data << endl;
	}
	if (n->left != NULL)
	{
		cout << "Left children data: " << n->left->data << endl;
	}
	if (n->middle != NULL)
	{
		cout << "Middle children data: " << n->middle->data << endl;
	}
	if (n->right != NULL)
	{
		cout << "Right children data: " << n->right->data << endl;
	}

	printTreeHelper(n->left);
	printTreeHelper(n->middle);
	printTreeHelper(n->right);
}

Position Tree::rootPos() const
{
	return Position(root);
}

Position::Position(Node* _root) :root(_root)
{

}

Position Position::left() const
{
	assert(root != nullptr);
	return Position(root->left);
}

Position Position::middle() const
{
	assert(root != nullptr);
	return Position(root->middle);
}

Position Position::right() const
{
	assert(root != nullptr);
	return Position(root->right);
}

string Position::getData() const
{
	assert(root != nullptr);
	return root->data;
}

bool Position::empty() const
{
	return root == nullptr;
}

