#include <iostream>

/**** Task 31 ****/
#define HSIZE 27

std::string maze[25] = {
"####B######################",
"# #       #   #      #    #",
"# # # ###### #### ####### #",
"# # # #       #   #       #",
"#   # # ######### # ##### #",
"# # # #   #       #     # #",
"### ### ### ############# #",
"# #   #     # #           #",
"# # #   ####### ###########",
"# # # #       # #         C",
"# # ##### ### # # ####### #",
"# # #     ### # #       # #",
"#   ##### ### # ######### #",
"######### ### #           #",
"# ####### ### #############",
"A           #   ###   #   #",
"# ############# ### # # # #",
"# ###       # # ### # # # #",
"# ######### # # ### # # # F",
"#       ### # #     # # # #",
"# ######### # ##### # # # #",
"# #######   #       #   # #",
"# ####### ######### #######",
"#         #########       #",
"#######E############D######"
};

void printMaze(int X, int Y) {
    for (int y = 0; y < 25; y++) {
        for (int x = 0; x < HSIZE; x++) {
            if (x == X && y == Y) std::cout << "@";
            else std::cout << maze[y][x];
        }
        std::cout << '\n';
    }

    std::cout << "\n\n";
}

/*enum StepDirection {
    UP,
    RIGHT,
    DOWN,
    LEFT,
    START
};*/

bool atLeastOneExit = false;
void step(int x, int y) {
    if (x < 0 || y < 0 ||
        x >= HSIZE || y >= 25 ||
        maze[y][x] == '#')
    {
        return;
    }

    /*printMaze(x, y);
    std::cin.get();*/

    char c = maze[y][x];

    // ��������� �� �����
    if (c != ' ') {
        std::cout << c << ' ';
        atLeastOneExit = true;
    }

    maze[y][x] = '#';

    // ��������� ������, ������ ���� �� ������ �� ���� ������
    step(x+1, y);
    step(x-1, y);
    step(x, y+1);
    step(x, y-1);
}

void task31() {
    int x, y;
    std::cin >> x >> y;

    if (x < 0 || y < 0 ||
        x >= HSIZE || y >= 25 ||
        maze[y][x] == '#')
    {
        std::cout << "�������� ����������\n";
        return;
    }

    step(x, y);
    if (!atLeastOneExit) std::cout << "������ ���";

    std::cout << '\n';
}

/**** Task 32 ****/
#include <stack>
#include <map>
#include <sstream>
#include <vector>
#include <cstring>
#include <math.h>

enum Priority {
    LOWEST,
    LOW,
    MEDIUM,
    HIGH,
};

std::map<char, Priority> priority {
    {'^', HIGH},
    {'*', MEDIUM},
    {'/', MEDIUM},
    {'+', LOW},
    {'-', LOW},
    {'(', LOWEST},
    {')', LOWEST},
};

bool isNumber(char c) {
    return (c >= '0' && c <= '9') || (c == '.');
}

std::string convertToRPN(std::string input) {
    std::stack<char> stack;
    std::string output;

    // ����������� � �� ������, ����� ����� ���� ��������������� strtok
    char* inputCStr = new char[input.length()];
    strcpy(inputCStr, input.c_str());

    // ���������� strtok, ����� ��������� ������ �� �������
    char* lexem = strtok(inputCStr, " ");
    while (lexem != nullptr) {
        char c = lexem[0];

        // ���� ������ ������ - ��� �����, �� ��� ������� - �����
        if (isNumber(c)) {
            output += lexem;
            output += " ";
        }
        else if (c == '(') {
            stack.push(c);
        }
        else if (c == ')') {
            while (!stack.empty() && stack.top() != '(') {
                output += stack.top();
                output += " ";
                stack.pop();
            }

            // ����������� ���� ������ �� �����
            stack.pop();
        }
        // ��������
        else if (c != ' ') {

            if (!stack.empty()) {
                // ���� �������� �� ����� ������������ ���
                // �������� �� ������� ����������������� � � ����������� ��� � "�"
                while (!stack.empty() &&
                       (priority[stack.top()] > priority[c] || (stack.top() != '^' && priority[stack.top()] == priority[c]))) {
                    output += stack.top();
                    output += " ";
                    stack.pop();
                }
            }

            stack.push(c);
        }

        // ���� ��������� �������
        lexem = strtok(nullptr, " ");
    }

    while (!stack.empty()) {
        output += stack.top();
        output += " ";
        stack.pop();
    }

    delete[] inputCStr;
    return output;
}

double calculateRPN(std::string input) {
    std::stack<double> stack;

    // �������� ��������� ������ �� ���������, ����� ������������ ���� �����, � �� �������
    setlocale(LC_ALL, "C");

    // ����������� � �� ������, ����� ����� ���� ��������������� strtok
    char* inputCStr = new char[input.length()];
    strcpy(inputCStr, input.c_str());

    // ���������� strtok, ����� ��������� ������ �� �������
    char* lexem = strtok(inputCStr, " ");
    while (lexem != nullptr) {
        char c = lexem[0];

        // ���� ������ ������ - ��� �����, �� ��� ������� - �����
        if (isNumber(c)) {
            stack.push(atof(lexem));
        }
        // ��������
        else {
            double firstOp, secondOp, result = 0;
            secondOp = stack.top(); stack.pop();
            firstOp = stack.top(); stack.pop();

            switch (c) {
            case '+':
                result = firstOp + secondOp;
                break;
            case '-':
                result = firstOp - secondOp;
                break;
            case '*':
                result = firstOp * secondOp;
                break;
            case '/':
                result = firstOp / secondOp;
                break;
            case '^':
                result = pow(firstOp, secondOp);
                break;
            }

            stack.push(result);
        }

        lexem = strtok(nullptr, " ");
    }

    delete[] inputCStr;
    // ���������� ������ �������
    setlocale(LC_ALL, "Russian");

    return stack.top();
}

void task32() {
    // ���������� ������� ����, ����� getline �������� ���������
    std::cin.ignore();

    std::string input;
    std::getline(std::cin, input);

    std::string converted = convertToRPN(input);
    std::cout << converted << '\n';

    std::cout << calculateRPN(converted) << '\n' << '\n';
}
