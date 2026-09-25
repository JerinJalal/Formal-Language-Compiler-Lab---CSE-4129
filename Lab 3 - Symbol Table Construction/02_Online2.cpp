#include<bits/stdc++.h>
using namespace std;
string update_token(string st) // [id x1] [kw float] [op =]
{
    if(st[0] == '[' && st == "[id")
        return st+" ";
    else if(st[0] == '[')
        return "[";
    return st + " ";
}
struct SymbolEntry
{
    int sl_no;
    string name;
    string id_type;
    string data_type;
    string scope = "global";
    string value;
};
vector<SymbolEntry> table;
int next_sl = 1;

// Step 3
int insert(string name)
{
    table.push_back({next_sl++, name, "", "", "", ""});
    return table.size() - 1; //last updated index number
}
void set_attribute(int index, string id_type, string data_type, string scope, string value)
{
    if (index >= 0 && index < table.size())
    {
        if (!id_type.empty()) table[index].id_type = id_type;
        if (!data_type.empty()) table[index].data_type = data_type;
        if (!scope.empty()) table[index].scope = scope;
        if (!value.empty()) table[index].value = value;
    }
}

void free_table()
{
    table.clear();
    next_sl = 1;
}

int lookup(string name, string scope)
{
    for (int i = 0; i < table.size(); i++)
    {
        if (table[i].name == name && (table[i].scope == scope || table[i].scope == "global"))
        {
            return i;
        }
    }
    return -1; // Not found
}

void display()
{
    cout<<endl<<endl<<"Step 2 :" <<"                 Symbol Table:         "<<endl<<endl;
    cout << left << setw(10) << "Sl.No." //Sl.No.    Name      Id Type    Data Type
         << setw(10) << "Name"
         << setw(10) << "Id Type"
         << setw(15) << "Data Type"
         << setw(10) << "Scope"
         << "Value" << endl;
    cout << string(65, '-') << endl;
    for (const auto& entry : table)
    {
        cout << left << setw(10) << entry.sl_no
             << setw(10) << entry.name
             << setw(10) << entry.id_type
             << setw(15) << entry.data_type
             << setw(10) << entry.scope
             << entry.value << endl;
    }

    cout<<endl<<endl;
}
void prep(vector<string> tokens) // float id x1 = 3.12 ;
{
    string current_scope = "global";
    string last_data_type = ""; //tracking korbe
    string last_id = "";

    for (int i = 0; i < tokens.size(); i++)
    {
        string tok = tokens[i];

        // Track data types
        if (tok == "int" || tok == "float" || tok == "double" || tok == "void")
        {
            last_data_type = tok;
        }
        // Process identifiers
        else if (tok.size() >= 2 && tok[0] == 'i' && tok[1] == 'd') //id x1
        {
            string name = "";
            for(int ind = 3;ind<tok.size();ind++)
                name+=tok[ind];

            int idx = lookup(name, current_scope);

            // If preceded by a data type, it's a declaration
            if (last_data_type != "")
            {
                if (idx == -1)
                {
                    idx = insert(name); // Step 3: insert()
                }

                string id_type = "var";
                string scope_to_set = current_scope;

                // Look ahead to see if it's a function declaration
                if (tokens[i+1] == "(")
                {
                    id_type = "func";
                    scope_to_set = "global";
                    current_scope = name; // Change active scope to the function body
                }

                // Step 3: set_attribute()
                set_attribute(idx, id_type, last_data_type, scope_to_set, "");
                last_data_type = ""; // Reset after declaration
            }
            last_id = name; // Remember the last seen ID for assignments
        }
        // Process assignments
        else if (tok == "=")
        {
            // Check if the next token is a numerical value (not another id)
            if (tokens[i+1].size() < 2 || tokens[i+1][0] != 'i' && tokens[i+1][1] != 'd')
            {
                string val = tokens[i+1];
                int idx = lookup(last_id, current_scope); // Step 3: lookup()
                if (idx != -1)
                {
                    set_attribute(idx, "", "", "", val); // Update value
                }
            }
        }
        // Reset scope at the end of a function block
        else if (tok == "}")
        {
            current_scope = "global";
        }
        // Reset data type at the end of a statement
        else if (tok == ";")
        {
            last_data_type = "";
        }
    }
}
void generate_modified_stream(vector<string> tokens)
{
    string current_scope = "global";
    string last_data_type = "";
    string modified_stream = "";

    for (int i = 0; i < tokens.size(); i++)
    {
        string tok = tokens[i];

        // Track data types
        if (tok == "int" || tok == "float" || tok == "double" || tok == "void")
        {
            last_data_type = tok;
            modified_stream += "[" + tok + "] ";
        }
        // Process identifiers --> sl no
        else if (tok.size() >= 3 && tok[0] == 'i' && tok[1] == 'd')
        {
            string name = "";
            for(int ind = 3;ind<tok.size();ind++)
                name+=tok[ind];

            if (last_data_type != "")
            {
                if (tokens[i+1] == "(")
                {
                    current_scope = name;
                }
                last_data_type = ""; // Reset after declaration
            }

            // Lookup the identifier in the symbol table to get its sl_no
            int idx = lookup(name, current_scope);
            if (idx != -1)
            {
                modified_stream += "[id " + to_string(table[idx].sl_no) + "] ";
            }
            else
            {
                modified_stream += "[" + tok + "] "; // Fallback if somehow not found
            }
        }
        // Reset scope at the end of a function block
        else if (tok == "}")
        {
            current_scope = "global";
            modified_stream += "[" + tok + "] ";
        }
        // Reset data type at the end of a statement
        else if (tok == ";")
        {
            last_data_type = "";
            modified_stream += "[" + tok + "] ";
        }
        // All other tokens (operators, braces, numbers, etc.)
        else
        {
            modified_stream += "[" + tok + "] ";
        }
    }

    cout << "Step 4: Modified token stream for Syntax Analysis:" << endl;
    cout << modified_stream << endl;
}
void load_symbol_table()
{
    table.clear();
    next_sl = 1;
    ifstream fin("SymbolTable.txt");
    if (!fin.is_open()) return;

    int sl;
    string name, id_type, scope;
    while (fin >> sl >> name >> id_type >> scope)
    {
        SymbolEntry entry;
        entry.sl_no = next_sl++;
        entry.name = name;
        entry.id_type = id_type;
        entry.scope = scope;
        entry.data_type = "";
        entry.value = "";
        table.push_back(entry);
    }
    fin.close();
}
void update_or_insert(string var_name, string target_scope, string new_value)
{
    bool updated = false;


    for (auto &entry : table)
    {
        if (entry.name == var_name && entry.scope == target_scope)
        {
            entry.value = new_value;
            updated = true;
            break;
        }
    }

}
void display_assignment_output()
{
    cout << "The updated Symbol Table:" << endl;
    for (auto &e : table)
    {
        cout << left << setw(4) << e.sl_no
             << setw(10) << e.name
             << setw(8) << e.id_type
             << setw(10) << e.scope;
        if (!e.value.empty())
        {
            cout << setw(8) << e.value;
        }
        cout << endl;
    }
}

vector<string> tokenize(string tokens_str)
{
    vector<string> tokens;
    string current_token = "";
    for(char c : tokens_str) // [id x1] ="id x1" , [float] = "float"
    {
        if(c == '[')
        {
            current_token = "";
        }
        else if(c == ']')
        {
            tokens.push_back(current_token);
        }
        else
        {
            current_token += c;
        }
    }
    return tokens;
}
int main()
{
     load_symbol_table();
     display_assignment_output();

    string var_name = "", target_scope = "", new_value = "";
    string input_line;

    while (getline(cin, input_line))
    {
        stringstream ss(input_line);
        string word;
        while (ss >> word)
        {
            if (word == "variable")
            {
                ss >> var_name;
            }
            else if (word == "Scope")
            {
                ss >> target_scope;
            }
            else if (word == "Value")
            {
                ss >> new_value;
            }
        }
    }


    update_or_insert(var_name, target_scope, new_value);

    display_assignment_output();




    return 0;
}
