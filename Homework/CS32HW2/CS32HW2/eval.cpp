#include <string>
#include <stack>

using namespace std;

int evaluate(string infix, string& postfix, bool& result)
{
	int countOpen = 0;
	int countClose = 0;
	for (int i = 0; i < infix.size(); i++)
	{
		if (infix[i] == '(')
			countOpen++;
		if (infix[i] == ')')
		{
			countClose++;
			if (countClose > countOpen)
			{
				return 1;
			}
		}
	}
	if (countClose != countOpen)
		return 1;

	if (infix == "")
		return 1;


	int check = 0;

	while (check < infix.size() && infix[check] == ' ')
	{
		check++;
	}

	if (infix[check] == '^' || infix[check] == '&' || infix[check] == ')')
		return 1;

	check = infix.size() - 1;

	while (check > 0 && infix[check] == ' ')
	{
		check--;
	}

	if (infix[check] == '^' || infix[check] == '&' || infix[check] == '!' || infix[check] == '(')
		return 1;


	postfix = "";
	stack<char> operatorStack;
	char previous = '.';
	for (int i = 0; i < infix.size(); i++)
	{
		switch (infix[i])
		{
		case ('T'):
		case ('F'):
			if (previous == 'T' || previous == 'F')
			{
				return 1;
			}
			postfix += infix[i];
			previous = infix[i];
			break;
		case('('):
			if (previous == 'T' || previous == ')' || previous == 'F')
			{
				return 1;
			}
			operatorStack.push(infix[i]);
			previous = infix[i];
			break;
		case(')'):
			if (previous == '(' || previous == '!' || previous == '&' || previous == '^')
			{
				return 1;
			}
			while (operatorStack.top() != '(')
			{
				postfix += operatorStack.top();
				operatorStack.pop();
			}
			operatorStack.pop();
			previous = infix[i];
			break;
		case('!'):
			if (previous == 'T' || previous == 'F' || previous == ')')
			{
				return 1;
			}
			while (!operatorStack.empty() && operatorStack.top() != '(' && operatorStack.top() != '^' && operatorStack.top() != '&')
			{
				postfix += operatorStack.top();
				operatorStack.pop();
			}
			operatorStack.push(infix[i]);
			previous = infix[i];
			break;
		case('&'):
			if (previous == '&' || previous == '^' || previous == '(' || previous == '!')
			{
				return 1;
			}
			while (!operatorStack.empty() && operatorStack.top() != '(' && operatorStack.top() != '^')
			{
				postfix += operatorStack.top();
				operatorStack.pop();
			}
			operatorStack.push(infix[i]);
			previous = infix[i];
			break;
		case('^'):
			if (previous == '&' || previous == '^' || previous == '(' || previous == '!')
			{
				return 1;
			}
			while (!operatorStack.empty() && operatorStack.top() != '(')
			{
				postfix += operatorStack.top();
				operatorStack.pop();
			}
			operatorStack.push(infix[i]);
			previous = infix[i];
			break;
		case(' '):
			break;
		default:
			return 1;
		}
	}
	while (!operatorStack.empty())
	{
		postfix += operatorStack.top();
		operatorStack.pop();
	}

	//Evaluation of postfix

	stack<char> solStack;
	for (int i = 0; i < postfix.size(); i++)
	{
		if (postfix[i] == 'T' || postfix[i] == 'F')
		{
			solStack.push(postfix[i]);
		}
		else if (postfix[i] == '!')
		{
			char operand1 = solStack.top();
			solStack.pop();
			if (operand1 == 'T')
			{
				solStack.push('F');
			}
			if (operand1 == 'F')
			{
				solStack.push('T');
			}
		}
		else
		{
			char operand1 = solStack.top();
			solStack.pop();
			char operand2 = solStack.top();
			solStack.pop();
			if ((postfix[i] == '&' && operand1 == 'T' && operand2 == 'T') || (postfix[i] == '^' && operand1 != operand2))
			{
				solStack.push('T');
			}
			else
			{
				solStack.push('F');
			}
		}
	}
	if (solStack.top() == 'T')
		result = true;
	if (solStack.top() == 'F')
		result = false;
	return 0;
}