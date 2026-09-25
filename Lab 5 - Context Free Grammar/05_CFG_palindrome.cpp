#include<iostream>
#include<string>

using namespace std;

string str;
int i = 0;
int l;
int f = 1;

void P();
void Q();
void R();

void P()
{
    // P -> eQ | Rr

    if(str[i]=='e' && f && i<l)
    {
        i++;
        Q();
    }
    else
    {
        R();

        if(str[i]=='r' && f && i<l)
        {
            i++;
        }
        else
        {
            f=0;
        }
    }
}

void Q()
{
    // Q -> tRm | np

    if(str[i]=='t' && f && i<l)
    {
        i++;
        R();

        if(str[i]=='m' && f && i<l)
        {
            i++;
        }
        else
        {
            f=0;
        }
    }
    else if(str[i]=='n' && i+1<l && str[i+1]=='p' && f)
    {
        i=i+2;
    }
    else
    {
        f=0;
    }
}

void R()
{
    // R -> f

    if(str[i]=='f' && f && i<l)
    {
        i++;
    }
    else
    {
        f=0;
    }
}

bool palindrome(int left, int right)
{
    if(left >= right)
    {
        return true;
    }

    if(str[left] != str[right])
    {
        return false;
    }

    return palindrome(left+1, right-1);
}

int main()
{
    int n;

    cout<<"No. of Inputs: ";
    cin>>n;

    for(int k=0; k<n; k++)
    {
        cout<<"Enter String: ";
        cin>>str;

        i=0;
        l=str.length();
        f=1;

        // CFG checking
        P();

        if(f && i==l)
        {
            cout<<"CFG: Accepted"<<endl;
        }
        else
        {
            cout<<"CFG: Rejected"<<endl;
        }

        // Palindrome checking
        if(palindrome(0, l-1))
        {
            cout<<"Palindrome"<<endl;
        }
        else
        {
            cout<<"Not Palindrome"<<endl;
        }

        cout<<endl;
    }

    return 0;
}
