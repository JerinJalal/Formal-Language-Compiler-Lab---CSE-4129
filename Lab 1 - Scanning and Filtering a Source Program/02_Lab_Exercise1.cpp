//1. Write a program to print the header files used in a source program.
#include<iostream>
#include<fstream>
#include <string>
using namespace std;

int main()
{
    freopen("input_exercise1.cpp","r",stdin);
    string st;

    while(getline(cin,st)){
        if(st.find("#include") != string::npos)
        {
            st.erase(0, st.find('<') + 1);
            st.erase(st.find('>'));
            cout << st << endl;
        }
    }
}
