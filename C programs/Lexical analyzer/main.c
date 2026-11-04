#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAX 100

char *keywords[] = {
    "auto", "break", "case", "char", "const", "continue", "default",
    "do", "double", "else", "enum", "extern", "float", "for", "goto",
    "if", "int", "long", "register", "return", "short", "signed",
    "sizeof", "static", "struct", "switch", "typedef", "union",
    "unsigned", "void", "volatile", "while"
};

int isKeyword(char *s) {
    for (int i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++)
        if (!strcmp(s, keywords[i])) return 1;
    return 0;
}

int isSeparator(char c) {
    return strchr("(){}[],;:.#", c) != NULL;
}

int isOperator(char c) {
    return strchr("+-*/%=<>&|^!~", c) != NULL;
}

int main() {
    FILE *f = fopen("lexAnalysis.txt", "r");
    char token[MAX], header[MAX];
    int c, i = 0;

    if (!f) {
        printf("Error opening file.\n");
        return 1;
    }

    while ((c = fgetc(f)) != EOF) {
        if (c == '#') {
            token[i++] = c;
            while ((c = fgetc(f)) != EOF && c != '\n')
                token[i++] = c;

            token[i] = '\0';
            i = 0;

            if (!strncmp(token, "#include", 8)) {
                char *s = strchr(token, '<'), *e = strchr(token, '>');
                if (!s || !e) {
                    s = strchr(token, '"');
                    e = strrchr(token, '"');
                }

                if (s && e && s < e) {
                    strncpy(header, s + 1, e - s - 1);
                    header[e - s - 1] = '\0';
                    printf("Header File: %s\n", header);
                } else printf("Preprocessor Directive: %s\n", token);
            } else printf("Preprocessor Directive: %s\n", token);
        }

        else if (isalpha(c) || c == '_') {
            token[i++] = c;
            while ((c = fgetc(f)) != EOF && (isalnum(c) || c == '_'))
                token[i++] = c;

            token[i] = '\0';
            printf("%s: %s\n", isKeyword(token) ? "Keyword" : "Identifier", token);
            i = 0;
            ungetc(c, f);
        }

        else if (isdigit(c)) {
            token[i++] = c;
            while ((c = fgetc(f)) != EOF && (isdigit(c) || c == '.'))
                token[i++] = c;

            token[i] = '\0';
            printf("Number: %s\n", token);
            i = 0;
            ungetc(c, f);
        }

        else if (c == ';')
            printf("Delimiter: %c\n", c);

        else if (isSeparator(c))
            printf("Separator: %c\n", c);

        else if (isOperator(c))
            printf("Operator: %c\n", c);

        else if (c == '"') {
            token[i++] = c;
            while ((c = fgetc(f)) != EOF && c != '"') {
                token[i++] = c;
                if (c == '\\') token[i++] = fgetc(f);
            }

            token[i++] = c;
            token[i] = '\0';
            printf("String: %s\n", token);
            i = 0;
        }

        else if (!isspace(c))
            printf("Other: %c\n", c);
    }

    fclose(f);
    return 0;
}