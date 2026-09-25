//    Write a C/C++ program to implement the following CFG and show respective outputs on console:
//    S → aA | bB | cdC
//    A → BC | xD | ε
//    B → pB | q
//    C → rC | s
//    D → tu | vD | ε
//
//    The program should prompt the user to input the number of strings to check.
//
//    Sample Input       Sample Output
//
//    10
//    aqs                Valid
//    apqrs              Valid
//    aqqrs              Valid
//    ax tu               Invalid
//    ax                 Valid
//    axtu               Valid
//    bq                 Valid
//    bpq                Valid
//    bppq                Valid
//    cds                Valid

#include<iostream>
#include<string>

using namespace std;

string str;
int i=0;
int l;
int f=1;

void S();
void A();
void B();
void C();
void D();

void S()
{
    //    S → aA | bB | cdC
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
    else if(str[i]=='c' && f && i+1<l && str[i+1]=='d')
    {
        i=i+2;
        C();
    }
    else
    {
        f=0;
    }
}
void A()
{
    //    A → BC | xD | ε
    if(str[i]=='x' && f && i<l)
    {
        i++;
        D();
    }
    else if((str[i] == 'p' || str[i] == 'q')&& f && i < l) // important because B has p,q terminals
    {
        B();
        C();
    }
    else
    {

    }
}
void B()
{
    //    B → pB | q
    if(str[i]=='p' && f && i<l)
    {
        i++;
        B();

    }
    else if(str[i]=='q' && i<l && f)
    {
        i++;
    }
    else
    {
        f=0;
    }
}
void C()
{
    //    C → rC | s
    if(str[i]=='r' && f && i<l)
    {
        i++;
        C();

    }
    else if(str[i]=='s' && i<l && f)
    {
        i++;
    }
    else
    {
        f=0;
    }

}
void D()
{
    //    D → tu | vD | ε
    if(str[i]=='t' && f && i+1<l && str[i+1]=='u')
    {
        i=i+2;
    }
    else if(str[i]=='v' && f && i<l)
    {
        i++;
        D();
    }
    else{

    }
}

int main()
{
    int n;
    cin>>n;

    cout<<"Sample Input \t\tSample Output \n";
    for(int k=0; k<n; k++)
    {
        cin>>str;
        i=0;
        l=str.length();
        f=1;

        S();
        cout<<str<<" \t\t\t ";
        if(f && i==l)
        {
            cout<<"   Valid \n";
        }
        else{
             cout<<"   Invalid \n";
        }
    }

    return 0;
}
