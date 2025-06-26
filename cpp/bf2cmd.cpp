#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " program.bf\n";
        return 1;
    }
    ifstream fin(argv[1]);
    if (!fin) {
        cerr << "File error\n";
        return 1;
    }
    string code((istreambuf_iterator<char>(fin)), {});
    vector<unsigned char> tape(1, 0);
    size_t ptr = 0;
    stack<size_t> loop;
    for (size_t i = 0; i < code.size(); ++i) {
        char c = code[i];
        switch (c) {
            case '>':
                if (++ptr == tape.size()) tape.push_back(0);
                break;
            case '<':
                if (ptr == 0) tape.insert(tape.begin(), 0);
                else --ptr;
                break;
            case '+': ++tape[ptr]; break;
            case '-': --tape[ptr]; break;
            case '.': cout << tape[ptr]; break;
            case ',': tape[ptr] = cin.get(); break;
            case '[':
                if (tape[ptr]) loop.push(i);
                else {
                    int cnt = 1;
                    while (cnt) {
                        ++i;
                        if (code[i] == '[') ++cnt;
                        else if (code[i] == ']') --cnt;
                    }
                }
                break;
            case ']':
                if (tape[ptr]) i = loop.top();
                else loop.pop();
                break;
            default:
                break;
        }
    }
    return 0;
}
