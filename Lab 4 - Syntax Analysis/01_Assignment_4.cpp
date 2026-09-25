#include<bits/stdc++.h>
using namespace std;
bool comment;
bool space = 0;
string code(string st)
{
    string out = "";
    for(int i = 0; i<st.size(); i++)
    {
        // Multi-Line Comment
        if(comment && st[i] == '*' && st[i+1] == '/')
        {
            comment = false;
            i++;
            continue;
        }
        else if(st[i] == '/' && st[i+1] == '*')
        {
            comment = true;
            i++;
            continue;
        }
        // Currently in a multi-line comment
        if(comment == true) continue;

        // Single-Line Comment
        if(st[i] == '/' && st[i+1] == '/')
        {
            break;
        }

        if(st[i] == ' ')
        {
            //Found a space
            if(space == true) continue; // Already has a space
            space = true;
        }
        else
        {
            // Not found a space
            space = false;
        }
        out+=st[i];
    }
    if(comment == false && !space) // currently on a part of a comment and has not printed a space, then print a space after every line
    {
        space = true;
        out+=' ';
    }
    return out;
}

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


bool isNum(string s)
{
    if (s.empty()) return false;
    int state = 0;                              // 0 start, 1 digit, 2 dot, 3 digit after dot
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
    int state = 0;
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

string op[] =
{
    "+", "-", "*", "/", "%", "=", "==", "!=", "<", ">", "<=", ">=",
    "&&", "||", "!", "&", "|", "^", "~", "<<", ">>", "++", "--",
    "+=", "-=", "*=", "/=", "%=", "&=", "|=", "^="
};
string kw[] =
{
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

bool isDataType(string st)
{
    return st == "int" || st == "float" || st == "double" || st == "char"
           || st == "void" || st == "long" || st == "short";
}

string classify(string st)
{
    if (isKw(st))       return "kw";
    else if (isPar(st)) return "par";
    else if (isSep(st)) return "sep";
    else if (isNum(st)) return "num";
    else if (isId(st))  return "id";
    else if (isOp(st))  return "op";
    return "unkn";
}


struct SymbolEntry
{
    int sl_no;
    string name;
    string id_type;
    string data_type;
    string scope = "global";
    string value;
    int line;
};
vector<SymbolEntry> table;
int next_sl = 1;

int insert(string name, int line)
{
    table.push_back({next_sl++, name, "", "", "", "", line});
    return table.size() - 1;
}

void set_attribute(int index, string id_type, string data_type, string scope, string value)
{
    if (index >= 0 && index < (int)table.size())
    {
        if (!id_type.empty())   table[index].id_type = id_type;
        if (!data_type.empty()) table[index].data_type = data_type;
        if (!scope.empty())     table[index].scope = scope;
        if (!value.empty())     table[index].value = value;
    }
}

int lookup(string name, string scope)                 // same scope or global
{
    for (int i = 0; i < (int)table.size(); i++)
        if (table[i].name == name && (table[i].scope == scope || table[i].scope == "global"))
            return i;
    return -1;
}

int lookup_any(string name)                           // any scope
{
    for (int i = 0; i < (int)table.size(); i++)
        if (table[i].name == name) return i;
    return -1;
}

void free_table()
{
    table.clear();
    next_sl = 1;
}

void display()
{
    cout << "Step 3: Symbol Table :" << endl << endl;
    cout << left << setw(10) << "Sl.No."
         << setw(10) << "Name"
         << setw(10) << "Id Type"
         << setw(12) << "Data Type"
         << setw(10) << "Scope"
         << setw(10) << "Line"
         << "Value" << endl;
    cout << string(70, '-') << endl;
    for (auto &e : table)
        cout << left << setw(10) << e.sl_no
             << setw(10) << e.name
             << setw(10) << e.id_type
             << setw(12) << e.data_type
             << setw(10) << e.scope
             << setw(10) << e.line
             << e.value << endl;
    cout << endl;
}

// Syntax Error Detection

vector<pair<int, string> > errors;

void add_error(int line, string msg)
{
    errors.push_back(make_pair(line, msg));
}

string closing_of(string o)
{
    if (o == "(") return ")";
    if (o == "{") return "}";
    return "]";
}

// Error 4 & 5 : duplicate declaration and undeclared identifier
// (found while the symbol table is being built)
// every token carries its line number
struct Token
{
    string type;
    string lex;
    int line;
};
vector<Token> T;
void build_symbol_table()
{
    string scope = "global";
    string last_type = "";
    string last_id = "";

    for (int i = 0; i < (int)T.size(); i++)
    {
        string tok = T[i].lex;
        string nxt = (i + 1 < (int)T.size()) ? T[i + 1].lex : "";

        if (isDataType(tok))
        {
            last_type = tok;
        }
        else if (T[i].type == "id")
        {
            if (last_type != "")                          //declaration
            {
                int idx = lookup(tok, scope);
                if (idx != -1)
                    add_error(T[i].line, "Duplicate declaration of identifier '" + tok + "'");
                else
                {
                    idx = insert(tok, T[i].line);
                    if (nxt == "(") set_attribute(idx, "func", last_type, "global", "");
                    else            set_attribute(idx, "var", last_type, scope, "");
                }
                if (nxt == "(") scope = tok;              // entering function body
                last_type = "";
            }
            else                                          // usage
            {
                if (nxt != "(" && lookup_any(tok) == -1)
                    add_error(T[i].line, "Undeclared identifier '" + tok + "'");
            }
            last_id = tok;
        }
        else if (tok == "=")
        {
            if (i + 1 < (int)T.size() && T[i + 1].type == "num")
            {
                int idx = lookup(last_id, scope);
                if (idx != -1) set_attribute(idx, "", "", "", T[i + 1].lex);
            }
        }
        else if (tok == "}")
        {
            scope = "global";
            last_type = "";
        }
        else if (tok == ";" || tok == ")" || tok == "{") last_type = "";
    }
}

void check_syntax()
{
    int n = T.size();

    // 1. Duplication of tokens (parentheses, braces and semicolons may repeat)
    for (int i = 0; i + 1 < n; i++)
    {
        string a = T[i].lex, b = T[i + 1].lex;
        if (a == b && !isPar(a) && a != ";")
            add_error(T[i + 1].line, "Duplicate token '" + a + "'");
    }

    // 2. Unbalanced braces / parentheses
    stack<Token> sk;
    for (int i = 0; i < n; i++)
    {
        string t = T[i].lex;
        if (t == "(" || t == "{" || t == "[") sk.push(T[i]);
        else if (t == ")" || t == "}" || t == "]")
        {
            if (sk.empty())
                add_error(T[i].line, "Mismatched '" + t + "' : no matching opening symbol");
            else
            {
                Token o = sk.top();
                sk.pop();
                if (closing_of(o.lex) != t)
                    add_error(T[i].line, "Mismatched '" + t + "' : '" + o.lex
                              + "' of line " + to_string(o.line) + " needs '" + closing_of(o.lex) + "'");
            }
        }
    }
    while (!sk.empty())
    {
        add_error(sk.top().line, "Unbalanced '" + sk.top().lex + "' : never closed");
        sk.pop();
    }

    // 3. Unmatched 'else'  ( 'else if' works, because 'if' pushes again )
    int if_cnt = 0;
    for (int i = 0; i < n; i++)
    {
        if (T[i].lex == "if") if_cnt++;
        else if (T[i].lex == "else")
        {
            if (if_cnt > 0) if_cnt--;
            else add_error(T[i].line, "'else' without a previous 'if'");
        }
    }

    // 6. for loop construct  ->  for ( init ; condition ; update )
    for (int i = 0; i < n; i++)
    {
        if (T[i].lex != "for") continue;

        if (i + 1 >= n || T[i + 1].lex != "(")
        {
            add_error(T[i].line, "'for' must be followed by '('");
            continue;
        }
        int depth = 0, semi = 0;
        bool closed = false;
        for (int j = i + 1; j < n; j++)
        {
            if (T[j].lex == "(") depth++;
            else if (T[j].lex == ")")
            {
                depth--;
                if (depth == 0)
                {
                    closed = true;
                    // after for( ... ) a body or a ';' must follow
                    if (j + 1 >= n)
                        add_error(T[i].line, "'for' loop has no body");
                    break;
                }
            }
            else if (T[j].lex == ";" && depth == 1) semi++;
        }
        if (!closed)
            add_error(T[i].line, "'for' loop parenthesis is not closed");
        else if (semi != 2)
            add_error(T[i].line, "'for' loop needs exactly 2 semicolons, found " + to_string(semi));
    }
}

void report_errors()
{
    sort(errors.begin(), errors.end());
    errors.erase(unique(errors.begin(), errors.end()), errors.end());

    cout << "Step 4: Syntax Errors (sorted by line number) :" << endl << endl;
    if (errors.empty()) cout << "No syntax error found." << endl;
    for (auto &e : errors)
        cout << "Line " << e.first << " : " << e.second << endl;
    cout << endl;
}


int main()
{
    freopen("input.cpp", "r", stdin);
    cout << "Input File : input.cpp" << endl << endl;

    vector<string> lines;
    string line;
    while (getline(cin, line)) lines.push_back(line);

    for (int i = 0; i < (int)lines.size(); i++)
        cout<< lines[i] << endl;
    cout << endl;

    cout << "Step 1: Scanned & Filtered Source :" << endl << endl;
    vector<string> clean(lines.size());
    for (int i = 0; i < (int)lines.size(); i++)
    {
        clean[i] = code(lines[i]);
        if (clean[i].size()) cout << i + 1 << ". " << clean[i] << endl;
    }
    cout << endl;

    cout << "Step 2: Tokenized & Classified Lexemes :" << endl << endl;
    for (int i = 0; i < (int)clean.size(); i++)
    {
        if (clean[i].empty()) continue;

        stringstream ss(tokenize_line(clean[i]));
        string tok;
        cout << "[line " << i + 1 << "] ";          // dedicated line number token
        while (ss >> tok)
        {
            Token t;
            t.lex = tok; //name
            t.type = classify(tok);
            t.line = i + 1;
            T.push_back(t);
            cout << "[" << t.type << " " << t.lex << "] ";
        }
        cout << endl;
    }
    cout << endl;

    //Step 3 : symbol table
    build_symbol_table();
    display();

    // Step 4 : syntax errors
    check_syntax();
    report_errors();

    free_table();
    return 0;
}
