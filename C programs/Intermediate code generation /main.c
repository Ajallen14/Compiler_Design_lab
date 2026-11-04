#include <ctype.h>
#include <stdio.h>

int temp = 0;

void generate(char op, char a, char b, int x, int y) {
    printf("t%d = %c%d %c %c%d\n", temp, a, x, op, b, y);
    temp++;
}

void intermediate(char *expr) {
    char stack[100];
    int num[100], top = -1;

    for (int i = 0; expr[i]; i++) {
        if (isalnum(expr[i])) {
            stack[++top] = expr[i];
            num[top] = -1;
        } else if (expr[i] == '+' || expr[i] == '-' ||
                   expr[i] == '*' || expr[i] == '/') {
            char b = stack[top];
            int y = num[top--];

            char a = stack[top];
            int x = num[top--];

            printf("t%d = ", temp);

            if (x == -1) printf("%c", a);
            else printf("t%d", x);

            printf(" %c ", expr[i]);

            if (y == -1) printf("%c", b);
            else printf("t%d", y);

            printf("\n");

            stack[++top] = 't';
            num[top] = temp++;
        }
    }
}

int main() {
    char expr[100];

    printf("Enter an expression: ");
    scanf("%s", expr);

    intermediate(expr);
    return 0;
}