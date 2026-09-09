#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <stack>
#include <cctype>
#include <cstdlib>
#include <algorithm>

using namespace std;

struct Instruction
{
    int line_number;
    string command;
    string args;
};

map<char, int> memory;
map<int, size_t> line_map;
vector<Instruction> program;

void error(const string &msg, int line_num = -1)
{
    if (line_num != -1)
    {
        cerr << "Erro de sintaxe na linha " << line_num << ": " << msg << endl;
    }
    else
    {
        cerr << "Erro de sintaxe: " << msg << endl;
    }
    exit(1);
}

bool isValidVar(char c)
{
    return islower(c);
}

int precedence(char op)
{
    if (op == '*' || op == '/' || op == '%')
        return 2;
    if (op == '+' || op == '-')
        return 1;
    return 0;
}

int applyOp(int a, int b, char op)
{
    switch (op)
    {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        if (b == 0)
        {
            cerr << "Erro em tempo de execução: divisão por zero." << endl;
            exit(1);
        }
        return a / b;
    case '%':
        if (b == 0)
        {
            cerr << "Erro em tempo de execução: divisão por zero." << endl;
            exit(1);
        }
        return a % b;
    }
    return 0;
}

int evaluateExpression(const string &expr)
{
    stack<int> values;
    stack<char> ops;

    for (size_t i = 0; i < expr.length(); i++)
    {
        if (isspace(expr[i]))
            continue;

        if (islower(expr[i]))
        {
            if (i + 1 < expr.length() && islower(expr[i + 1]))
            {
                error("Identificador de variável deve possuir apenas uma letra minúscula.");
            }
            values.push(memory[expr[i]]);
        }
        else if (isdigit(expr[i]))
        {
            int val = 0;
            while (i < expr.length() && isdigit(expr[i]))
            {
                val = (val * 10) + (expr[i] - '0');
                i++;
            }
            i--;
            values.push(val);
        }
        else if (expr[i] == '(')
        {
            ops.push(expr[i]);
        }
        else if (expr[i] == ')')
        {
            while (!ops.empty() && ops.top() != '(')
            {
                int val2 = values.top();
                values.pop();
                int val1 = values.top();
                values.pop();
                char op = ops.top();
                ops.pop();
                values.push(applyOp(val1, val2, op));
            }
            if (!ops.empty())
                ops.pop();
        }
        else if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/' || expr[i] == '%')
        {
            while (!ops.empty() && precedence(ops.top()) >= precedence(expr[i]))
            {
                int val2 = values.top();
                values.pop();
                int val1 = values.top();
                values.pop();
                char op = ops.top();
                ops.pop();
                values.push(applyOp(val1, val2, op));
            }
            ops.push(expr[i]);
        }
        else if (isupper(expr[i]))
        {
            error("Letras maiúsculas não são permitidas em expressões.");
        }
        else
        {
            error("Caractere inválido na expressão.");
        }
    }

    while (!ops.empty())
    {
        int val2 = values.top();
        values.pop();
        int val1 = values.top();
        values.pop();
        char op = ops.top();
        ops.pop();
        values.push(applyOp(val1, val2, op));
    }

    return values.empty() ? 0 : values.top();
}

bool evaluateCondition(const string &cond)
{
    string ops[] = {"==", "!=", "<=", ">=", "<", ">"};
    string found_op = "";
    size_t pos = string::npos;

    for (const string &op : ops)
    {
        pos = cond.find(op);
        if (pos != string::npos)
        {
            found_op = op;
            break;
        }
    }

    if (found_op == "")
        error("Operador relacional ausente ou inválido na condição.");

    string left = cond.substr(0, pos);
    string right = cond.substr(pos + found_op.length());

    int val1 = evaluateExpression(left);
    int val2 = evaluateExpression(right);

    if (found_op == "==")
        return val1 == val2;
    if (found_op == "!=")
        return val1 != val2;
    if (found_op == "<=")
        return val1 <= val2;
    if (found_op == ">=")
        return val1 >= val2;
    if (found_op == "<")
        return val1 < val2;
    if (found_op == ">")
        return val1 > val2;

    return false;
}

void parseAndStore(const string &line)
{
    if (line.empty())
        return;

    stringstream ss(line);
    int line_num;
    if (!(ss >> line_num))
        return;

    string cmd;
    if (!(ss >> cmd))
        error("Instrução incompleta.", line_num);

    if (cmd != "rem")
    {
        for (char c : line)
        {
            if (isupper(c))
            {
                error("Caracteres maiúsculos são permitidos apenas em comentários.", line_num);
            }
        }
    }

    string args = "";
    string temp;
    while (ss >> temp)
    {
        if (!args.empty())
            args += " ";
        args += temp;
    }

    if (cmd != "rem" && cmd != "input" && cmd != "let" && cmd != "print" &&
        cmd != "goto" && cmd != "if" && cmd != "end")
    {
        error("Comando não reconhecido: " + cmd, line_num);
    }

    program.push_back({line_num, cmd, args});
}

void execute()
{
    size_t pc = 0;
    while (pc < program.size())
    {
        const Instruction &inst = program[pc];

        if (inst.command == "rem")
        {
            pc++;
        }
        else if (inst.command == "input")
        {
            string var_name = inst.args;
            var_name.erase(remove_if(var_name.begin(), var_name.end(), ::isspace), var_name.end());

            if (var_name.length() != 1 || !isValidVar(var_name[0]))
            {
                error("Comando input requer uma variável de uma única letra minúscula.", inst.line_number);
            }
            cout << "? " << flush;
            int val;
            cin >> val;
            memory[var_name[0]] = val;
            pc++;
        }
        else if (inst.command == "let")
        {
            size_t eq_pos = inst.args.find('=');
            if (eq_pos == string::npos)
                error("Sintaxe incorreta no comando let.", inst.line_number);

            string var_str = inst.args.substr(0, eq_pos);
            var_str.erase(remove_if(var_str.begin(), var_str.end(), ::isspace), var_str.end());

            if (var_str.length() != 1 || !isValidVar(var_str[0]))
            {
                error("Atribuição inválida no comando let.", inst.line_number);
            }

            string expr = inst.args.substr(eq_pos + 1);
            memory[var_str[0]] = evaluateExpression(expr);
            pc++;
        }
        else if (inst.command == "print")
        {
            string var_name = inst.args;
            var_name.erase(remove_if(var_name.begin(), var_name.end(), ::isspace), var_name.end());

            if (var_name.length() != 1 || !isValidVar(var_name[0]))
            {
                error("Comando print requer uma variável de uma única letra minúscula.", inst.line_number);
            }
            cout << memory[var_name[0]] << endl;
            pc++;
        }
        else if (inst.command == "goto")
        {
            int target = stoi(inst.args);
            if (line_map.find(target) == line_map.end())
            {
                error("Linha de destino do goto não encontrada: " + to_string(target), inst.line_number);
            }
            pc = line_map[target];
        }
        else if (inst.command == "if")
        {
            size_t goto_pos = inst.args.find("goto");
            if (goto_pos == string::npos)
                error("Sintaxe incorreta no comando if/goto.", inst.line_number);

            string cond = inst.args.substr(0, goto_pos);
            int target = stoi(inst.args.substr(goto_pos + 4));

            if (line_map.find(target) == line_map.end())
            {
                error("Linha de destino do if/goto não encontrada: " + to_string(target), inst.line_number);
            }

            if (evaluateCondition(cond))
            {
                pc = line_map[target];
            }
            else
            {
                pc++;
            }
        }
        else if (inst.command == "end")
        {
            break;
        }
    }
}

int main(int argc, char *argv[])
{
    for (char c = 'a'; c <= 'z'; ++c)
    {
        memory[c] = 0;
    }

    istream *input_stream = &cin;
    ifstream file_stream;

    if (argc > 1)
    {
        file_stream.open(argv[1]);
        if (!file_stream.is_open())
        {
            cerr << "Erro ao abrir o arquivo: " << argv[1] << endl;
            return 1;
        }
        input_stream = &file_stream;
    }

    string line;
    int last_line_num = -1;

    while (getline(*input_stream, line))
    {
        if (line.empty())
            continue;
        stringstream ss(line);
        int line_num;
        if (ss >> line_num)
        {
            if (line_num <= last_line_num)
            {
                error("As linhas devem estar em ordem crescente.", line_num);
            }
            last_line_num = line_num;
            parseAndStore(line);
            line_map[line_num] = program.size() - 1;
        }
    }

    execute();
    return 0;
}