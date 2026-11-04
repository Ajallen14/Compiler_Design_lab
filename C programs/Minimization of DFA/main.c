#include <stdio.h>
#define MAX 20

int n, m, t[MAX][MAX], f[MAX], nf, removed[MAX];

int isFinal(int s) {
    for (int i = 0; i < nf; i++)
        if (f[i] == s) return 1;
    return 0;
}

int equivalent(int a, int b) {
    if (isFinal(a) != isFinal(b)) return 0;

    for (int i = 0; i < m; i++)
        if (t[a][i] != t[b][i]) return 0;

    return 1;
}

void substitute(int old, int new) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (t[i][j] == old) t[i][j] = new;
}

int main() {
    printf("Enter number of states: ");
    scanf("%d", &n);

    printf("Enter number of input symbols: ");
    scanf("%d", &m);

    printf("Enter transition table:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            printf("δ(q%d,%c) = ", i, 'a' + j);
            scanf("%d", &t[i][j]);
        }

    printf("Enter number of final states: ");
    scanf("%d", &nf);

    printf("Enter final states: ");
    for (int i = 0; i < nf; i++)
        scanf("%d", &f[i]);

    for (int i = 0; i < n; i++)
        if (!removed[i])
            for (int j = i + 1; j < n; j++)
                if (!removed[j] && equivalent(i, j)) {
                    printf("q%d and q%d are equivalent; eliminating q%d\n",
                           i, j, j);
                    substitute(j, i);
                    removed[j] = 1;
                }

    printf("\nMinimized DFA Transition Table:\nState\t");
    for (int j = 0; j < m; j++) printf("%c\t", 'a' + j);
    printf("\n");

    for (int i = 0; i < n; i++)
        if (!removed[i]) {
            printf("q%d\t", i);
            for (int j = 0; j < m; j++)
                printf("q%d\t", t[i][j]);
            printf("\n");
        }

    return 0;
}