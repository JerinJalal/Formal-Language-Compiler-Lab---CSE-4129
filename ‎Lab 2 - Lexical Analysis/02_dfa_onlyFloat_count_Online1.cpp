//
//    “Design a DFA that accepts only floating-point numbers and
//    counts the number of digits after the decimal point.”
//
//    For example:
//
//    12.34 → 2 digits
//
//    5.678 → 3 digits
//
//    10.5 → 1 digit
//
//    123 → Not a floating-point number

#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int countDecimalDigits(string s)
{
    int state = 0;
    int count = 0;

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
                return -1;
        }

        else if(state == 1)
        {
            if(isdigit(ch))
                state = 1;
            else if(ch == '.')
                state = 2;
            else
                return -1;
        }

        else if(state == 2)
        {
            if(isdigit(ch))
            {
                state = 3;
                count++;
            }
            else
                return -1;
        }

        else if(state == 3)
        {
            if(isdigit(ch))
            {
                count++;
                state = 3;
            }
            else
                return -1;
        }
    }

    // A valid floating-point number must end in state 3
    if(state == 3)
        return count;
    else
        return -1;
}

int main()
{
    string s;

    cout << "Enter a number: ";
    cin >> s;

    int result = countDecimalDigits(s);

    if(result == -1)
    {
        cout << "Not a floating-point number" << endl;
    }
    else
    {
        cout << result << " digits after decimal point" << endl;
    }

    return 0;
}
