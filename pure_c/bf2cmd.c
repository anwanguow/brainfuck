#include <stdio.h>
#include <stdlib.h>

typedef struct Cell {
    unsigned char val;
    struct Cell *left, *right;
} Cell;

Cell* make_cell() {
    Cell *c = calloc(1, sizeof(Cell));
    if (!c) { perror("calloc"); exit(1); }
    return c;
}

char* load_code(const char *path, size_t *out_len) {
    FILE *f = fopen(path, "r");
    if (!f) { perror("fopen"); exit(1); }
    char *buf = NULL;
    size_t cap = 0, len = 0;
    int ch;
    while ((ch = fgetc(f)) != EOF) {
        if (ch=='>'||ch=='<'||ch=='+'||ch=='-'||
            ch=='.'||ch==','||ch=='['||ch==']') {
            if (len+1 > cap) {
                cap = cap ? cap*2 : 1024;
                buf = realloc(buf, cap);
                if (!buf) { perror("realloc"); exit(1); }
            }
            buf[len++] = ch;
        }
    }
    fclose(f);
    buf = realloc(buf, len+1);
    buf[len] = '\0';
    *out_len = len;
    return buf;
}

int* build_jumptable(const char *code, size_t len) {
    int *jmp = malloc(len * sizeof(int));
    int *stack = malloc(len * sizeof(int));
    size_t sp = 0;
    for (size_t i = 0; i < len; i++) {
        if (code[i] == '[') {
            stack[sp++] = i;
        } else if (code[i] == ']') {
            if (sp == 0) {
                fprintf(stderr, "Unmatched ']' at %zu\n", i);
                exit(1);
            }
            size_t j = stack[--sp];
            jmp[j] = i;
            jmp[i] = j;
        }
    }
    if (sp) {
        fprintf(stderr, "Unmatched '[' at %d\n", stack[sp-1]);
        exit(1);
    }
    free(stack);
    return jmp;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s program.bf\n", argv[0]);
        return 1;
    }

    size_t code_len;
    char *code = load_code(argv[1], &code_len);
    int *jmp = build_jumptable(code, code_len);

    Cell *ptr = make_cell();
    for (size_t ip = 0; ip < code_len; ip++) {
        switch (code[ip]) {
            case '>':
                if (!ptr->right) {
                    ptr->right = make_cell();
                    ptr->right->left = ptr;
                }
                ptr = ptr->right;
                break;
            case '<':
                if (!ptr->left) {
                    ptr->left = make_cell();
                    ptr->left->right = ptr;
                }
                ptr = ptr->left;
                break;
            case '+': ++ptr->val; break;
            case '-': --ptr->val; break;
            case '.': putchar(ptr->val); break;
            case ',': ptr->val = (unsigned char)getchar(); break;
            case '[':
                if (ptr->val == 0) ip = jmp[ip];
                break;
            case ']':
                if (ptr->val != 0) ip = jmp[ip];
                break;
        }
    }

    return 0;
}
