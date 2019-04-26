#include <iostream>
#include <cstdlib>
#include <string>
#include "Stack.h"
#include <cmath>
//Check for an operator sign.
bool isOperator(char op)
{
    if(op == '+' || op == '-' || op == '*' || op == '/'|| op == '^')
    {
      return true;
    }
    else
    {
      return false;
    }
}
bool isdigit(char c)
{
  if(c>='0'&&c<='9')
  {
    return true;
  }
  else
  {
    return false;
  }
}
int precedence(char charVal)
{
  switch (charVal)
  {
    case '+':
    case '-':  return 1;
    case '*':
    case '/': return 2;
    case '^': return 3;
    default: return -1;
  }
}

//Conversion between postfix and infix.
string InfixToPostfix(string infix)
{
    string postfix = ""; //Empty string.
    myStack<char> opStack;
    int opEmpty = 0;

    for (int i = 0; i<infix.length(); i++)
    {
        if(infix[i] == ' '); //If space, ignore.

        else if(isdigit(infix[i]) || infix[i] == '.')
        {
            postfix+=infix[i];
        }

        else if(isOperator(infix[i]))
                {
                    postfix+=' '; // SPACE

                    if(precedence(infix[i]) > precedence(opStack.top()))
                        opStack.push(infix[i]);
                    else
                    {
                        while(!opEmpty && precedence(opStack.top()) >= precedence(infix[i]))
                        {
                            postfix+=opStack.pop(&opEmpty); //Keep popping stack until the top's priority is < incoming op.
                            postfix+=' '; // SPACE
                        }

                        opStack.push(infix[i]);//Push incoming operator on stack.
                    }
                }
        else if(infix[i] == '(')
        {
            if(infix[i+1] == '-')
            {
                opStack.push(infix[i]);
                postfix+='0';
            }
            else opStack.push(infix[i]);
        }

        else if(infix[i] == ')')
        {
            while(opStack.top() != '(')
            {
                postfix+=' '; // SPACE
                postfix+=opStack.pop(&opEmpty);
            }

            opStack.pop(&opEmpty);
        }
    }

    while(!opEmpty)
    {
        postfix+=' '; // SPACE
        postfix+=opStack.pop(&opEmpty);
    }

    return postfix; //Complete postfix expression.
}

//Evaluation of the postfix expression and returning the final result.
double postfixEvaluation(string postfix)
{
    myStack<double> output;
    int empty = 0;
    double final, n = 0.0;
    string Temp = "";

    for (int i = 0; i<postfix.length(); i++)
    {
        if(isdigit(postfix[i]) || postfix[i] == '.')
        {
            Temp+=postfix[i];
        }

        else if(postfix[i] == ' ')
        {
            if(Temp.length() >= 1)
            {
                n = stod(Temp); //String to double conversion.
                output.push(n);
                Temp = "";      //Reset string.
            }

        }//End else if.

        else if(isOperator(postfix[i]))
        {
            double val1, val2, compute;

            val2 = output.pop(&empty); //First operand.

            val1 = output.pop(&empty); //Second operand.

            switch (postfix[i]) {
                case '+':
                    compute = (val1 + val2); break;

                case '-':
                    compute = (val1 - val2); break;

                case '*':
                    compute = (val1 * val2); break;

                case '/':
                    compute = (val1 / val2); break;
                case '^':
                    compute = pow(val1,val2); break;
                default:
                    break;
            }
            output.push(compute); //Push back calculation into stack.
        }
    }

    final = output.pop(&empty); //Final Answer.

    return final;
}

void Interface()
{
    cout<<" ___________________________________________________________________"<<endl;
    cout<<"|___________________________________________________________________|"<<endl;
    cout<<"|+|<<<<<<<<<<<<<<<<<<<<<SIMPLE CALCULATOR>>>>>>>>>>>>>>>>>>>>>>>>>|+|"<<endl;
    cout<<"|-|                      by: Aidan Aarts                          |-|"<<endl;
    cout<<"|/|_______________________________________________________________|/|"<<endl;
    cout<<"|*|      Please enter the expression you wish to evaluate         |*|"<<endl;
    cout<<"|+|                   Expressions may have:                       |+|"<<endl;
    cout<<"|-|                   -Addition / Subtraction                     |-|"<<endl;
    cout<<"|/|                   -Division / Multiplication                  |/|"<<endl;
    cout<<"|*|                   -Parenthesis / Exponents                    |*|"<<endl;
    cout<<"|(|                                                               |)|"<<endl;
    cout<<"|+|            ENTER Q TO QUIT THE CALCULATOR                     |+|"<<endl;
}

int main() {

    string input="";

    //User input prompt.
    Interface();

    while(input!="q")
    {
        cout<<"|-|                                                               |-|"<<endl;
        cout<<"|/|Enter: ";
        cout<<"                                                        |/|"<<endl;
        getline(cin,input); //Get input stream.

        string postfix = InfixToPostfix(input);
        if(input == "q") break;
        cout<<"|*|                                                               |*|"<<endl;
        cout<<"|^| ==>    "<<postfixEvaluation(postfix)<<"                                                      |^|"<<endl;
        cout<<"|+|                                                               |+|"<<endl;
    }

    cout<<"|-| << GOODBYE!                                                   |-|"<<endl;
    cout<<"|*|_______________________________________________________________|*|"<<endl;
    cout<<"|___________________________________________________________________|"<<endl;

    return 0; //Done.

}
