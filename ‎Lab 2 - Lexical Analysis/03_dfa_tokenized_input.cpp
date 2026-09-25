#include<iostream>
#include<fstream>
#include<string>
#include<cctype>

using namespace std;

// ---------- DFA for Number ----------

bool isNum(string s)
{
    if(s.empty())
    {
        return false;
    }

    int state = 0;

    // state 0 = start
    // state 1 = digits before decimal
    // state 2 = decimal point
    // state 3 = digits after decimal

    for(int i = 0; i < (int)s.length(); i++)
    {
        char ch = s[i];

        if(state == 0)
        {
            if(isdigit(ch))
                state = 1;
            else
                return false;
        }

        else if(state == 1)
        {
            if(isdigit(ch))
                state = 1;
            else if(ch == '.')
                state = 2;
            else
                return false;
        }

        else if(state == 2)
        {
            if(isdigit(ch))
                state = 3;
            else
                return false;
        }

        else if(state == 3)
        {
            if(isdigit(ch))
                state = 3;
            else
                return false;
        }
    }

    return state == 1 || state == 3;
}


// ---------- DFA for Identifier ----------

bool isId(string s)
{
    if(s.empty())
        return false;

    int state = 0;

    // state 0 = start
    // state 1 = valid identifier

    for(int i = 0; i < (int)s.length(); i++)
    {
        char ch = s[i];

        if(state == 0)
        {
            if(isalpha(ch) || ch == '_')
                state = 1;
            else
                return false;
        }

        else if(state == 1)
        {
            if(isalnum(ch) || ch == '_')
                continue;
            else
                return false;
        }
    }

    return state == 1;
}


// ---------- Main ----------

int main()
{
//    ifstream input("tokenized_input.cpp");
//
//    if(!input)
//    {
//        cout << "File could not be found" << endl;
//        return 0;
//    }

    string token;
    int n;

    cout << "Enter number of tokens: ";
    cin >> n;


   // while(input >> token)
     for(int i = 0; i < n; i++)
    {
        cout << "Enter token " << ": ";
        cin >> token;
        if(isNum(token))
        {
            cout << token << " -> Valid Number" << endl;
        }
        else if(isId(token))
        {
            cout << token << " -> Valid Identifier" << endl;
        }
        else
        {
            cout << token << " -> Invalid Token" << endl;
        }
    }

    //input.close();

    return 0;
}
