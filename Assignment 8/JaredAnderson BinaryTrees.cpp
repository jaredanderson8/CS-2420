// Copyright 2020, Bradley Peterson, Weber State University, all rights reserved. (11/20)

#include <iostream>
#include <string>
#include <stack>
#include <sstream>
#include <cmath>
#include <cstdio>

using std::stack;
using std::istringstream;
using std::ostringstream;
using std::string;
using std::cout;
using std::cerr;
using std::endl;
using std::pow;
using std::cin;

//******************
//The Node class
//******************
class Node {
	public:
		Node();
  		string data{""};
  		Node* left{ nullptr };
  		Node* right{ nullptr };
};

Node::Node()
{
	data = "";
	left = nullptr;
	right = nullptr;
}

class TreeParser
{
	private:
		stack<string> mathStack;
		double castStrToDouble(string const &s);
		string castDoubleToStr(const double d);
		void initialize();
		bool isDigit(char c);
		bool isOperator(char c);
		void processExpression (Node* p); //Assuming raw pointers, or you can use shared pointers
		void computeAnswer(Node* p); //Assuming raw pointers, or you can use shared pointers

		Node* root{nullptr};

		void inOrderTraversal(Node* p);
		void postOrderTraversal(Node* p);

		void PrintTree2(string prout[], int row, Node* p);
		

	protected:
		string expression;
		int position;
		int nodes;

	public:
		TreeParser();
		void displayParseTree();
		void processExpression(string &_expression);
		string computeAnswer();
		
		void PrintTree(Node* p);
};

void TreeParser::displayParseTree() 
{
	cout << "Roughly how the tree is laid out: " << endl;
	PrintTree(root);
	cout << "The expression seen using in-order traversal: "; 
	inOrderTraversal(root);
	cout << endl;
	cout << "The expression seen using post-order traversal: "; 
	postOrderTraversal(root);
	cout << endl;	
}

double TreeParser::castStrToDouble(const string &s) 
{
	istringstream iss(s);
	double x;
	iss >> x;
	return x;
} 

string TreeParser::castDoubleToStr(const double d) 
{
	ostringstream oss;
	oss << d;
	return oss.str();

} 

TreeParser::TreeParser() 
{
	initialize();
}

void TreeParser::initialize() {
	expression = "";
	position = 0;
	while (!mathStack.empty()) 
	{
		mathStack.pop();
	}
}

bool TreeParser::isDigit(char c)
{
	if(isdigit(c))
	{
		return true;
	}
	else
	{
		return false;
	}
	
}

bool TreeParser::isOperator(char c)
{
	if(c == '+' || c == '-' ||  c == '*' ||  c == '/' ||  c == '^')
	{
		return true;
	}
	else
	{
		return false;
	}
}

void TreeParser::processExpression(string &_expression)
{
	nodes = 0;
	if(_expression != "")
	{
		expression = _expression;
		cout << " " << endl;
		cout << expression << endl;
		position = 0;
		root = new Node;
		nodes++;
		processExpression(root);
	}
	else
	{
		cout << "expression is empty." << endl;
	}
	
}

void TreeParser::processExpression (Node* p)
{
	while (position < expression.length())
	{
		if(expression[position] == '(')
		{
			p->left = new Node;
			nodes++;
			position++;
			processExpression(p->left);
		}
		else if(isDigit(expression[position]) || expression[position] == '.')
		{
			string temp = "";

			while(isdigit(expression[position]) || expression[position] == '.')
			{
				temp += expression[position];
				position++;
			}

			p->data = temp;
			return;
		}
		else if(isOperator(expression[position]))
		{
			p->data = expression[position];
			p->right = new Node;

			nodes++;
			position++;

			processExpression(p->right);
		}
		else if(expression[position] == ')')
		{
			position++;
			return;
		}
		else if(expression[position] == ' ')
		{ 
			position++;
		}	
	}
}

string TreeParser::computeAnswer()
{
	computeAnswer(root);
	return mathStack.top();
}

void TreeParser::computeAnswer(Node* p)
{
	if(p)
	{
		computeAnswer(p->left);
		computeAnswer(p->right);

		if(isDigit(p->data[0]))
		{
			mathStack.push(p->data);
		}
		else if(isOperator(p->data[0]))
		{
			double A = std::stod(mathStack.top());
			mathStack.pop();
			double B = std::stod(mathStack.top());
			mathStack.pop();

			double answer;

			if(p->data == "+")
			{
				answer = A + B;
			}
			else if (p->data == "-")
			{
				answer = B - A;
			}
			else if (p->data == "*")
			{
				answer = A * B;
			}
			else if (p->data == "/")
			{
				answer = B / A;
			}
			else if (p->data == "^")
			{
				answer = pow(B,A);
			}
			mathStack.push(std::to_string(answer));
		}
	}
}

void TreeParser::inOrderTraversal(Node* p)
{
	if(p)
	{
		inOrderTraversal(p->left);
		cout << p->data << " ";
		inOrderTraversal(p->right);
	}
}

void TreeParser::postOrderTraversal(Node* p)
{
	if(p)
	{
		inOrderTraversal(p->left);
		inOrderTraversal(p->right);
		cout << p->data << " ";
	}
}

void TreeParser::PrintTree(Node* p)
{
	if(p == nullptr)
	{
		p = root;
	}

	int size = nodes + 2;

    std::string prout[size];
 
    int i = 0;
    while(i < size)
	{
		prout[i] = std::to_string(i) + ":--";
		//cout << prout[i] << endl;
		i++;
	}
	
	prout[0] += p->data;
	int row = 1;
	PrintTree2(prout, row, p);

	i = 0;
	while (i < size)
	{
		cout << prout[i] << endl;
		i++;

		string temp = std::to_string(i);
		temp.append(":--");
		if(prout[i].compare(temp) == 0)
		{
			break;
		}	
	}
}

void TreeParser::PrintTree2(string prout[], int row, Node* p)
{
	int i = 0;
	while (i < row)
	{
		int digits = 1;
		int number = i;
		do
		{
			number /= 10; 
			digits++;
		} 
		while (number!= 0);
		
		prout[i].insert(digits + 2, 2, ' ');
		i++;
	}
	
	if(p->left != nullptr)
	{
		prout[row] += "/   ";
		prout[row+1] += p->left->data;
		prout[row+1] += "   ";

		if(p->left->left != nullptr && p->left->right != nullptr)
		{
			PrintTree2(prout, row + 2, p->left);
		}
		else
		{
			prout[row+2] += "     ";
			prout[row+3] += "     ";
		}
	}
	else
	{
		cout << "test 1" << endl;
		prout[row] += "    ";
		prout[row+1] += "    ";
	}

	if(p->right != nullptr)
	{
		prout[row] += "\\  ";
		prout[row+1] += p->right->data;
		prout[row+1] += " ";

		if(p->right->left != nullptr && p->right->right != nullptr)
		{			
			PrintTree2(prout, row + 2, p->right);
		}
		else
		{
			prout[row+2] += "     ";
			prout[row+3] += "     ";
		}	
	}
	else
	{
		cout << "test 2" << endl;
		prout[row] += " ";
		prout[row+1] += " ";
	}
	
}

void pressEnterToContinue() 
{
	printf("Press Enter to continue\n");

	cin.get();
}

// Copyright 2019, Bradley Peterson, Weber State University, all rights reserved. (07/2020)

int main() {

	TreeParser *tp = new TreeParser;
	
	string expression = "(4+7)";
	tp->processExpression(expression);
	tp->displayParseTree();
	cout << "The result is: " << tp->computeAnswer() << endl; //Should display 11 as a double output
	
	expression = "(7-4)";
	tp->processExpression(expression);
	tp->displayParseTree();
	cout << "The result is: " << tp->computeAnswer() << endl; //Should display 3 as a double output

  	expression = "(9*5)";
  	tp->processExpression(expression);
 	tp->displayParseTree();
  	cout << "The result is: " << tp->computeAnswer() << endl; //Should display 45 as a double output

	expression = "(4^3)";
	tp->processExpression(expression);
	tp->displayParseTree();
	cout << "The result is: " << tp->computeAnswer() << endl; //Should display 64 as a double output

	expression = "((2-5)-5)";
	tp->processExpression(expression);
	tp->displayParseTree();
	cout << "The result is: " << tp->computeAnswer() << endl; //Should display -8 as a double output
	
	expression = "(5*(6/2))";
	tp->processExpression(expression);
	tp->displayParseTree();
	cout << "The result is: " << tp->computeAnswer() << endl; //Should display 15 as a double output
	
	expression = "((14 / 7) + (8 * 2))";
	tp->processExpression(expression);
	tp->displayParseTree();
	cout << "The result is: " << tp->computeAnswer() << endl; //Should display 18 as a double output

	expression = "(543+321)";
	tp->processExpression(expression);
	tp->displayParseTree();
	cout << "The result is: " << tp->computeAnswer() << endl; //Should display 864 as a double output

	expression = "(7.5-3.25)";
	tp->processExpression(expression);
	tp->displayParseTree();
	cout << "The result is: " << tp->computeAnswer() << endl; //Should display 4.25 as a double output

	expression = "(5 + (34 - (7 * (32 / (16 * 0.5)))))";
	tp->processExpression(expression);
	tp->displayParseTree();
	cout << "The result is: " << tp->computeAnswer() << endl; //Should display 11 as a double output

  	expression = "((5*(3+2))+(7*(4+6)))";
  	tp->processExpression(expression);
  	tp->displayParseTree();
  	cout << "The result is: " << tp->computeAnswer() << endl; //Should display 95 as a double output

	expression = "(((2+3)*4)+(7+(8/2)))";
	tp->processExpression(expression);
	tp->displayParseTree();
	cout << "The result is: " << tp->computeAnswer() << endl; //Should display 31 as a double output

	expression = "(((((3+12)-7)*120)/(2+3))^3)";
	tp->processExpression(expression);
	tp->displayParseTree();
	cout << "The result is: " << tp->computeAnswer() << endl; //Should display close to 7077888 as a double output 
                                                            //NOTE, it won't be exact, it will display as scientific notation!
	
	expression = "(((((9+(2*(110-(30/2))))*8)+1000)/2)+(((3^4)+1)/2))";
	tp->processExpression(expression);
	tp->displayParseTree();
	cout << "The result is: " << tp->computeAnswer() << endl; //Should display close to 1337 as a double/decimal output
	
	pressEnterToContinue();
	return 0;
}
