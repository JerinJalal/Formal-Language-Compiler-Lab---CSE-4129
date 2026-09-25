//2. Write a C/C++ program to implement the following CFG and show respective outputs on console:
//
//        A→ Cy|q|pB
//        B→ Cuu | rs
//        C-> epsilon | m
//
//(The program prompts the user to input the number of strings to check.)
//
//Sample Input       Sample Output
//     8
//     q                 Valid
//    my                 Valid
//    y                  Valid
//    prs                Valid
//    puu                Valid
//    pmuu               Valid
//    cy                 Invalid
//    pruu               Invalid

#include<iostream>
#include<string>

using namespace std;

string str;
int i =0;
int l;
int f=1;

void A();
void B();
void C();

// A→ Cy|q|pB
void A()
{
    if(str[i]=='q' && f && i<l)
    {
        i++;
    }
    else if(str[i]=='p' && f && i<l)
    {
        i++;
        B();
    }
    else{
        C();
        if(str[i]=='y' && f && i<l)
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
    // B→ Cuu | rs
    if(str[i]=='r' && f && str[i+1]=='s' && i+1<l)
    {
        i=i+2;
    }
    else{
        C();
        if(str[i]=='u' && f && str[i+1]=='u' && i+1<l)
        {
            i=i+2;
        }
        else{
            f=0;
        }
    }

}
void C()
{
    // C-> epsilon | m

    if(str[i]=='m' && f && i<l)
    {
        i++;
    }
    else{
        //epsilon
    }
}



int main()
{
    int n;
    cout << "Sample Input\t\tSample Output" << endl;
    cin>>n;

    for(int k=0; k<n; k++)
    {
        cin>>str;

        i=0;
        l=str.length();
        f=1;

        A();
        cout<<str<<"\t\t\t";
        if(f && i==l)
        {
           cout<<"Valid \n";
        }
        else{
            cout<<"Invalid \n";
        }
    }

    return 0;

}
