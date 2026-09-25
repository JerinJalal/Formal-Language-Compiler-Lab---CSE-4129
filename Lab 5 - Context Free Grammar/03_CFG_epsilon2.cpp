//    Write a C/C++ program to implement the following CFG and show respective outputs on console:
//    S → aA | bB | c
//    A → Cd | ef
//    B → Cx | yz
//    C → ε | p
//
//    The program should prompt the user to input the number of strings to check.
//
//    Sample Input       Sample Output
//
//    8
//    c                  Valid
//    ad                 Valid
//    apd                Valid
//    aef                Valid
//    bx                 Valid
//    bpx                Valid
//    byz                Valid
//    ab                 Invalid

#include<iostream>
#include<string>

using namespace std;

string str;
int i=0,l,f=1;

void S();
void A();
void B();
void C();

void S()
{//    S → aA | bB | c
    if(str[i]=='a' && f && i<l)
    {
        i++;
        A();
    }
    else if(str[i]=='b' && f && i<l)
    {
        i++;
        B();
    }
    else if(str[i]=='c' && f && i<l)
    {
        i++;
    }
    else{
        f=0;
    }
}
void A()
{
    //    A → Cd | ef

    if(str[i]=='e' && str[i+1]=='f' && f && i+1<l)
    {
        i+=2;

    }
    else{
        C();
        if(str[i]=='d' && f && i<l)
        {
            i++;
        }
        else{
            f=0;
        }

    }

}
void B()
{
    //    B → Cx | yz
    if(str[i]=='y' && str[i+1]=='z' && f && i+1<l)
    {
        i=i+2;
    }
    else{
        C();
        if(str[i]=='x' && f && i<l)
        {
            i++;
        }
    }

}
void C()
{
    //    C → ε | p
    if(str[i]=='p' && f && i<l)
    {
        i++;
    }
    else{

    }
}

int main()
{
    int n;
    cin>>n;

    cout<< "Sample Input \t\t\t Sample Output \n";
    for(int k=0; k<n ; k++)
    {
        cin>>str;
        i=0;
        l=str.length();
        f=1;
        S();
        cout<<str<<" \t\t\t ";
        if(f && i==l)
        {
            cout<<" Valid \n";
        }
        else{
            cout<<" Invalid \n";
        }
    }
}

