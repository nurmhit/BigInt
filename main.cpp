#include "biginteger.h"
#include <stack>

using namespace std;

bool is_operator(char c)
{
    if(c == '+' || c == '-' || c == '*' || c == '/' || c == '%')
        return true;
    return false;
}

bool is_low(char c)
{
    return (c == '+' || c == '-');
}

bool is_higher(char c, char d)
{
    if(!is_low(c) && is_low(d))
        return true;
    return false;
}

BigInteger calculate(vector <string> &data)
{
    stack <BigInteger> c;
    for(auto elem: data)
    {
        if(is_operator(elem[elem.length()-1]))
        {
            BigInteger b = c.top();
            c.pop();
            BigInteger a = c.top();
            c.pop();
            if(elem[0] == '+')
                c.push(a + b);
            else if(elem[0] == '-')
                c.push(a - b);
            else if(elem[0] == '*')
                c.push(a * b);
            else if(elem[0] == '/')
                c.push(a / b);
            else if(elem[0] == '%')
                c.push(a % b);
        }
        else
            c.push(elem);

    }
    return c.top();
}

BigInteger result(string &s, int &cur_pos)
{
    stack <BigInteger> c;
    stack <char> ops;
    vector <string> all;
    while(cur_pos < s.length())
    {
        if(s[cur_pos] == ' ')
        {
            cur_pos++;
        }
        else if(s[cur_pos] == '(')
        {
            cur_pos++;
            all.push_back(result(s, cur_pos).toString());
        }
        else if(s[cur_pos] == ')')
        {
            cur_pos++;
            break;
        }
        else if(s[cur_pos] == '-' && all.empty())
        {
            string st;
            cur_pos++;
            while(s[cur_pos] >= '0' && s[cur_pos] <= '9')
            {
                st += s[cur_pos];
                cur_pos++;
            }
            all.push_back('-' + st);
        }
        else if(is_operator(s[cur_pos]))
        {
            if(ops.empty() || is_higher(s[cur_pos], ops.top()))
                ops.push(s[cur_pos]);
            else{
                while(!ops.empty() && !is_higher(s[cur_pos], ops.top()))
                {
                    string operation;
                    operation += ops.top();
                    all.push_back(operation);
                    ops.pop();
                }
                ops.push(s[cur_pos]);
            }
            cur_pos++;
        }
        else
        {
            string st;
            while(s[cur_pos] >= '0' && s[cur_pos] <= '9')
            {
                st += s[cur_pos];
                cur_pos++;
            }
            all.push_back(st);
        }
    }
    while(!ops.empty())
    {
        string operation;
        operation += ops.top();
        all.push_back(operation);
        ops.pop();
    }
    return calculate(all);
}

int main() {
    string input;
    getline(cin, input);
    int pos = 0;
    cout << result(input, pos) << endl;
    return 0;
}