//1. Write a C/C++ program that takes a C source code file that is already formatted without any extra spaces or comments.
//   Extract all string literals (text enclosed in " ") along with their line numbers and print them on the console.
//
//Note: Line numbers are not provided in the input. You may still receive partial marks if you print the string literals without the line numbers.
//Sample Input (qa_input.cpp)
//int x = 5;
//printf("Set B");
//int z = 0; printf("CSE 4130");
//printf("Lab Final");
//
//
//Output
//2. Set B
//4. CSE 4130
//5. Lab Final
//Total String Literals = 3

#include<iostream>
#include<fstream>
#include<string>
#include<vector>

using namespace std;

int main()
{
    freopen("string_literal_extractor_input.cpp","r",stdin);
    string st;

    int lineNumbers = 1;
    int total_literals = 0;

    while(getline(cin,st))
    {
        if(st.find("printf") != string::npos)
        {
            st.erase(0,st.find('"')+1);
            st.erase(st.find('"'));
            cout<<lineNumbers<<' ';
            cout<<st<<endl;
            total_literals++;
        }
        lineNumbers++;

    }
    cout<<"Total String Literals: "<<total_literals<<endl;

    return 0;what


}
// Another Approach
//
//#include<iostream>
//#include<string>
//
//using namespace std;
//
//int main()
//{
//    freopen("qa_input.cpp", "r", stdin);
//
//    string st;
//    int lineNumbers = 1;
//    int total_literals = 0;
//
//    while(getline(cin, st))
//    {
//        int start = st.find('"');
//
//        if(start != string::npos)
//        {
//            int end = st.find('"', start + 1);
//
//            string str = st.substr(start + 1, end - start - 1);
//
//            cout << lineNumbers << ". " << str << endl;
//
//            total_literals++;
//        }
//
//        lineNumbers++;
//    }
//
//    cout << "Total String Literals = " << total_literals << endl;
//
//    return 0;
//}
