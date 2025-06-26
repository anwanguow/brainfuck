#include <iostream>
#include <fstream>
#include <string>

void emit_prelude(std::ofstream& out) {
    out << "#include <iostream>\n"
           "#include <vector>\n"
           "using namespace std;\n"
           "int main() {\n"
           "    vector<unsigned char> tape(1, 0);\n"
           "    size_t ptr = 0;\n";
}

void emit_postlude(std::ofstream& out) {
    out << "    return 0;\n"
           "}\n";
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " input.bf output.cpp\n";
        return 1;
    }
    std::ifstream fin(argv[1]);
    std::ofstream fout(argv[2]);
    if (!fin || !fout) {
        std::cerr << "File error\n";
        return 1;
    }
    emit_prelude(fout);
    char c;
    while (fin.get(c)) {
        switch (c) {
            case '>': fout << "    if (++ptr == tape.size()) tape.push_back(0);\n"; break;
            case '<': fout << "    if (ptr == 0) tape.insert(tape.begin(), 0); else --ptr;\n"; break;
            case '+': fout << "    ++tape[ptr];\n"; break;
            case '-': fout << "    --tape[ptr];\n"; break;
            case '.': fout << "    cout << tape[ptr];\n"; break;
            case ',': fout << "    tape[ptr] = cin.get();\n"; break;
            case '[': fout << "    while (tape[ptr]) {\n"; break;
            case ']': fout << "    }\n"; break;
            default:  break;
        }
    }
    emit_postlude(fout);
    return 0;
}
