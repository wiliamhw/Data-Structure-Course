#include<bits/stdc++.h>
using namespace std;

const int A = 10080;
const int B = 1100;
const int C = 11180;
const int D = 12280;

int change(char x) {
    if (x == 'A') return A;
    else if (x == 'B') return B;
    else if (x == 'C') return C;
    else return D;
}

int isoperand(char x) {
	if(x == '+' || x=='-'|| x=='*' || x=='/' || x==')' || x=='(')
		return 0;
	return 1;
}
 
int Pre(char x) {
	if(x == '+' || x == '-')
		return 1;
	if(x == '*' || x == '/')
		return 3;
	return 0;
}
 
int inFix(string exp) {
	stack<int> operandStack;
	stack<char> operatorStack;
	int i, x, y, z;
	i=0;
	while(exp[i]!='\0')
	{
		if(exp[i]==' ' || exp[i]==',') {
			i++;
			continue;
		}
 
		if(isoperand(exp[i])) {
			operandStack.push(change(exp[i++]));
		}

		else if(!isoperand(exp[i]) && operatorStack.empty())
			operatorStack.push(exp[i++]);
		else if(!isoperand(exp[i]) && !operatorStack.empty()) {
			if(exp[i]=='(')
				operatorStack.push(exp[i++]);
			else if(Pre(exp[i])>Pre(operatorStack.top()) && exp[i]!=')')
				operatorStack.push(exp[i++]);
			else if(exp[i]==')' && operatorStack.top() == '(') {
				operatorStack.pop();
				i++;
			}
 
			else {
				x = operandStack.top();
				operandStack.pop();
				y = operatorStack.top();
				operatorStack.pop();
				z = operandStack.top();
				operandStack.pop();
				if(y == '+') {
					operandStack.push(z+x);
                }
				else if(y == '-')
					operandStack.push(z-x);
				else if(y == '*')
					operandStack.push(x*z);
				else if(y == '/')
					operandStack.push(z/x);
			} 
		}
	}
	while(!operatorStack.empty()) {
		x = operandStack.top();
		operandStack.pop();
		y = operatorStack.top();
		operatorStack.pop();
		z = operandStack.top();
		operandStack.pop();
		if(y == '+') {
			operandStack.push(x+z);
        }
		else if(y == '-')
			operandStack.push(z-x);
		else if(y == '*')
			operandStack.push(x*z);
		else if(y == '/')
			operandStack.push(z/x);
	}
	return operandStack.top();
}

int mod(string num, int a)  { 
    // Initialize result 
    int res = 0; 
  
    // One by one process all digits of 'num' 
    for (int i = 0; i < num.length(); i++) 
         res = (res*10 + (int)num[i] - '0') %a; 
  
    return res; 
} 
  

int main(int argc, char const *argv[]) {
	string s, num, temp;
    int T, N;
    cin >> T;

    while (T-- > 0) {
        cin >> N;
        cin.ignore();
        getline(cin,s);
        num = to_string(inFix(s));
        temp = num;

        while (N-- > 1) {
            num = num + temp;
        }
        cout << mod(num, 3331) << endl; 
    }
	return 0;
}