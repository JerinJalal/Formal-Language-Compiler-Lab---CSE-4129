//Write a C/C++ program that reads a C source file containing single-line and multi-line comments,
//along with white spaces (extra spaces, tabs, and newline characters). As the first step toward
//compilation, your program should remove all comments and unnecessary white spaces without
//removing the spaces required for correct syntax, and write the filtered code to a new output file.
//The program must also display the contents of both the input and the output files on the console.


#include<iostream>
#include<fstream>
#include<string>
#include<vector>

using namespace std;
bool space =false;
bool comment=false;
//int lineNumber=1;


void code(string str)
{
    for(int i=0; i<str.size(); i++)
    {
        //multiline comment
        if(str[i]=='/' && str[i+1]=='*')
        {
            i++;
            comment=true;
            continue;
        }
        else if(comment && str[i]=='*' && str[i+1]=='/')
        {
            i++;
            comment=false;
            continue;
        }
        if(comment == true) continue;
        //single line comment
        if(str[i]=='/' && str[i+1]=='/')
        {
            return;
        }
        //space
        if(str[i]==' ')
        {
            if(space == true) continue;
            space=true;
        }
        else
        {
            space = false;
        }
        cout<<str[i];

    }
    if(space == false && comment==false)
    {
        space=true;
        cout<<' ';
        //cout<<endl;
    }

}

int main()
{
    freopen("input.cpp","r",stdin);
    cout<<"Input File: ....."<<endl;

    string st;
    vector <string> vec;

    while(getline(cin,st))
    {
        vec.push_back(st);
        cout<<st<<endl;
    }
    cout<<endl;

    cout<<"\nOutput:"<<endl;
    ofstream output("pout.cpp");

    for(auto st:vec)
    {
        if(st.empty())continue;
        //cout<<lineNumber<<" ";
        code(st);
        //lineNumber++;

    }

    output.close();
}
