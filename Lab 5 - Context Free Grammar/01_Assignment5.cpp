#include <iostream>
#include <string>
#include <vector>
#include <cctype>
using namespace std;

//Tokenizer
vector<string> tokens;
int pos; // current position in tokens

bool isID(const string &t)
{
    return t.size() == 1 && t[0] >= 'a' && t[0] <= 'e';
}

bool isNUM(const string &t)
{
    return (t.size() == 1 && t[0] >= '0' && t[0] <= '9');
}

// Break the input string into tokens: +, -, *, /, (, ), single letters a-e, single digits
bool tokenize(const string &input)
{
    tokens.clear();
    for (size_t i = 0; i < input.size(); i++)
    {
        char c = input[i];
        if (isspace(c)) continue;

        if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')')
        {
            tokens.push_back(string(1, c));
        }
        else if ((c >= 'a' && c <= 'e') || (c >= '0' && c <= '9') )
        {
            tokens.push_back(string(1, c));
        }
        else
        {
            // Unknown character -> invalid input (not part of the alphabet)
            return false;
        }
    }
    return true;
}

// Exp -> Term + Term | Term - Term | Term
// Recursive Descent Parser
bool parseExp();   // forward declaration

// <Factor> -> ( <Exp> ) | ID | NUM
bool parseFactor()
{
    if (pos >= (int)tokens.size()) return false;

    if (tokens[pos] == "(")
    {
        int saved = pos;
        pos++; // consume '('
        if (parseExp() && pos < (int)tokens.size() && tokens[pos] == ")")
        {
            pos++; // consume ')'
            return true;
        }
        pos = saved; // backtrack
        return false;
    }
    else if (isID(tokens[pos]) || isNUM(tokens[pos]))
    {
        pos++;
        return true;
    }
    return false;
}

// Term -> Factor * Factor | Factor / Factor | Factor
bool parseTerm()
{
    int saved = pos;

    if (!parseFactor())
    {
        pos = saved;
        return false;
    }

    if (pos < (int)tokens.size() && (tokens[pos] == "*" || tokens[pos] == "/"))
    {
        int opPos = pos;
        pos++; // consume operator
        if (parseFactor())
        {
            return true; // Factor op Factor matched
        }
        pos = opPos; // backtrack the operator, fall back to single Factor
    }

    // Single <Factor> case already consumed above
    return true;
}

// <Exp> -> <Term> + <Term> | <Term> - <Term> | <Term>
bool parseExp()
{
    int saved = pos;

    if (!parseTerm())
    {
        pos = saved;
        return false;
    }

    if (pos < (int)tokens.size() && (tokens[pos] == "+" || tokens[pos] == "-"))
    {
        int opPos = pos;
        pos++; // consume operator
        if (parseTerm())
        {
            return true; // Term op Term matched
        }
        pos = opPos; // backtrack the operator, fall back to single Term
    }

    return true;
}


bool isAccepted(const string &input)
{
    if (!tokenize(input)) return false; // contains invalid characters
    pos = 0;
    bool check = parseExp();
    // The whole input must be consumed for acceptance
    return check && pos == (int)tokens.size() && !tokens.empty();
}

int main()
{
    int n;
    cout << "A2_20220204039_Assignment5.cpp ";
    cout << endl;

    cout << "Enter number of input strings: ";
    cin >> n;
    cin.ignore();

    cout << "\nEnter each expression:\n";
    for (int i = 0; i < n; i++)
    {
        string line;
        getline(cin, line);

        cout << "Input : " << line << "\nOutput: "
             << (isAccepted(line) ? "Accepted" : "Rejected")
             << "\n\n";
    }

    return 0;
}
