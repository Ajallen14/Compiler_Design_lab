
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int n, m, i, j;
char a[10][10], f[10];

void first(char c);
void follow(char c);

int main() {
    int z;
    char c;

    printf("Enter number of productions: ");
    scanf("%d", &n);

    printf("Enter productions (example: E=E+T):\n");
    for (i = 0; i < n; i++)
        scanf("%s", a[i]);

    do {
        m = 0;
        printf("\nEnter element for FIRST & FOLLOW: ");
        scanf(" %c", &c);

        first(c);
        printf("FIRST(%c) = { ", c);
        for (i = 0; i < m; i++) printf("%c ", f[i]);
        printf("}\n");

        strcpy(f, " ");
        m = 0;

        follow(c);
        printf("FOLLOW(%c) = { ", c);
        for (i = 0; i < m; i++) printf("%c ", f[i]);
        printf("}\n");

        printf("Continue? (1 = yes / 0 = no): ");
        scanf("%d", &z);

    } while (z == 1);

    return 0;
}

void first(char c) {
    if (!isupper(c)) {
        f[m++] = c;
        return;
    }

    for (int k = 0; k < n; k++)
        if (a[k][0] == c) {
            if (a[k][2] == '$')
                follow(a[k][0]);
            else if (islower(a[k][2]))
                f[m++] = a[k][2];
            else
                first(a[k][2]);
        }
}

void follow(char c) {
    if (a[0][0] == c) f[m++] = '$';

    for (i = 0; i < n; i++)
        for (j = 2; j < strlen(a[i]); j++)
            if (a[i][j] == c) {
                if (a[i][j + 1] != '\0')
                    first(a[i][j + 1]);

                if (a[i][j + 1] == '\0' && c != a[i][0])
                    follow(a[i][0]);
            }
}