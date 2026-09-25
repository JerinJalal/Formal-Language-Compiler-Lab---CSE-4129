#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

int main()
{
    freopen("input.cpp","r",stdin);

    string st;
    vector<string> vec;

    while(getline(cin,st))
    {
        int linenumber;
        cout<<linenumber<<' ';
        vec.push_back(st);
        cout<<st;
        cout<<endl;
        linenumber++;
    }
}
