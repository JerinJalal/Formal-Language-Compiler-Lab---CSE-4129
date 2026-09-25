#include<iostream>
#include<vector>
#include<sstream>
#include<string>
using namespace std;

// ---------- Step 1: Tokenizer / Spacer ----------
bool space;

string tokenize_line(string st)
{
    string answer;
    space = false; // reset for each new line

    for (int i = 0; i < (int)st.size(); i++)
    {
        if (st[i] == ' ')
        {
            if (space) continue;
            space = true;
        }
        else if (st[i] == ';' || st[i] == ',' || st[i] == '(' || st[i] == ')' ||
                  st[i] == '}' || st[i] == '{' || st[i] == '[' || st[i] == ']' ||
                  st[i] == '\'')
        {
            if (!space) answer += ' ';
            answer += st[i];
            answer += ' ';
            space = true;
            continue;
        }
        else if (st[i] == '>' || st[i] == '<' || st[i] == '=' || st[i] == '+' ||
                  st[i] == '-' || st[i] == '/' || st[i] == '*' || st[i] == '&' ||
                  st[i] == '|' || st[i] == '^')
        {
            if (!space) answer += ' ';
            if (st[i+1] == '>' || st[i+1] == '<' || st[i+1] == '=' || st[i+1] == '+' ||
                st[i+1] == '-' || st[i+1] == '/' || st[i+1] == '*' || st[i+1] == '&' ||
                st[i+1] == '|' || st[i+1] == '^')
            {
                answer += st[i];
                answer += st[i+1];
                answer += ' ';
                i++;
            }
            else //jokhon space ase
            {
                answer += st[i];
                answer += ' ';
            }
            space = true;
            continue;
        }
        else
        {
            space = false;
        }
        answer += st[i];
    }
    return answer;
}

// ---------- Step 2: Token Classifier (DFA-based) ----------
bool isNum(string s)
{
    if (s.empty()) return false;
    int state = 0; // 0 start, 1 digits before dot, 2 dot seen, 3 digits after dot

    for (int i = 0; i < (int)s.length(); i++)
    {
        char ch = s[i];
        if (state == 0)
        {
            if (isdigit(ch)) state = 1;
            else if (ch == '.') state = 2;
            else return false;
        }
        else if (state == 1)
        {
            if (isdigit(ch)) state = 1;
            else if (ch == '.') state = 2;
            else return false;
        }
        else if (state == 2)
        {
            if (isdigit(ch)) state = 3;
            else return false;
        }
        else if (state == 3)
        {
            if (isdigit(ch)) state = 3;
            else return false;
        }
    }
    return state == 1 || state == 3;
}

bool isId(string s)
{
    if (s.empty()) return false;
    int state = 0; // 0 start, 1 valid identifier
    for (int i = 0; i < (int)s.length(); i++)
    {
        char ch = s[i];
        if (state == 0)
        {
            if (isalpha(ch) || ch == '_') state = 1;
            else return false;
        }
        else if (state == 1)
        {
            if (isalnum(ch) || ch == '_') continue;
            else return false;
        }
    }
    return state == 1;
}

string op[] = {
    "+", "-", "*", "/", "%", "=", "==", "!=", "<", ">", "<=", ">=",
    "&&", "||", "!", "&", "|", "^", "~", "<<", ">>", "++", "--",
    "+=", "-=", "*=", "/=", "%=", "&=", "|=", "^="
};

string kw[] = {
    "auto", "break", "case", "char", "const", "continue", "default", "do",
    "double", "else", "enum", "extern", "float", "for", "goto", "if",
    "int", "long", "register", "return", "short", "signed", "sizeof", "static",
    "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while"
};

string sep[] = { ";", ",", "'" };
string par[] = { "(", ")", "{", "}", "[", "]" };

bool isOp(string st)  { for (auto i : op)  if (i == st) return true; return false; }
bool isKw(string st)  { for (auto i : kw)  if (i == st) return true; return false; }
bool isSep(string st) { for (auto i : sep) if (i == st) return true; return false; }
bool isPar(string st) { for (auto i : par) if (i == st) return true; return false; }

void classify_token(string st)
{
    if (isKw(st))       cout << "[kw ";
    else if (isPar(st)) cout << "[par ";
    else if (isSep(st)) cout << "[sep ";
    else if (isNum(st)) cout << "[num ";
    else if (isId(st))  cout << "[id ";
    else if (isOp(st))  cout << "[op ";
    else                cout << "[unkn ";
    cout << st << "]";
}

// ---------- Main: does both steps in one pass ----------
int main()
{
    freopen("input.cpp", "r", stdin);
    cout << "Input File : input.cpp" << endl;

    vector<string> lines;
    string line;
    while (getline(cin, line))
    {
        lines.push_back(line);
        cout << line << endl;
    }
    cout << endl;

    // Step 1: tokenize every line and collect the resulting tokens
    vector<string> tokens;
    for (auto &l : lines)
    {
        string spaced = tokenize_line(l);
        stringstream ss(spaced);
        string tok;
        while (ss >> tok) tokens.push_back(tok);
    }

    cout << "Tokenized Output :" << endl;
    for (auto &t : tokens) cout << t << " ";
    cout << endl << endl;

    // Step 2: classify every token
    cout << "Classified Output :" << endl;
    for (auto &t : tokens) classify_token(t);
    cout << endl;

    return 0;
}
