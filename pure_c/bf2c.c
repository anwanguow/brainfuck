#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

void emit_prelude(FILE *out) {
    fprintf(out,
        "#include <stdio.h>\n"
        "#include <stdlib.h>\n\n"
        "typedef struct Cell {\n"
        "    unsigned char val;\n"
        "    struct Cell *left, *right;\n"
        "} Cell;\n\n"
        "Cell* make_cell() {\n"
        "    Cell *c = calloc(1, sizeof(Cell));\n"
        "    if (!c) { perror(\"calloc\"); exit(1); }\n"
        "    c->val = 0;\n"
        "    c->left = c->right = NULL;\n"
        "    return c;\n"
        "}\n\n"
        "int main() {\n"
        "    Cell *ptr = make_cell();\n\n"
    );
}

void emit_postlude(FILE *out) {
    fprintf(out,
        "    {\n"
        "        Cell *head = ptr;\n"
        "        while (head->left) head = head->left;\n"
        "        while (head) {\n"
        "            Cell *next = head->right;\n"
        "            free(head);\n"
        "            head = next;\n"
        "        }\n"
        "    }\n"
        "    return 0;\n"
        "}\n"
    );
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s input.bf output.c\n", argv[0]);
        return 1;
    }

    FILE *fin = fopen(argv[1], "r");
    if (!fin) { perror("fopen input"); return 1; }

    FILE *fout = fopen(argv[2], "w");
    if (!fout) { perror("fopen output"); fclose(fin); return 1; }

    emit_prelude(fout);

    int c;
    while ((c = fgetc(fin)) != EOF) {
        switch (c) {
            case '>':
                fprintf(fout,
                    "    if (!ptr->right) ptr->right = make_cell(), ptr->right->left = ptr;\n"
                    "    ptr = ptr->right;\n"
                );
                break;
            case '<':
                fprintf(fout,
                    "    if (!ptr->left) ptr->left = make_cell(), ptr->left->right = ptr;\n"
                    "    ptr = ptr->left;\n"
                );
                break;
            case '+':
                fprintf(fout, "    ++(ptr->val);\n");
                break;
            case '-':
                fprintf(fout, "    --(ptr->val);\n");
                break;
            case '.':
                fprintf(fout, "    putchar(ptr->val);\n");
                break;
            case ',':
                fprintf(fout, "    ptr->val = (unsigned char)getchar();\n");
                break;
            case '[':
                fprintf(fout, "    while (ptr->val) {\n");
                break;
            case ']':
                fprintf(fout, "    }\n");
                break;
            default:
                break;
        }
    }

    emit_postlude(fout);

    fclose(fin);
    fclose(fout);
    return 0;
}
