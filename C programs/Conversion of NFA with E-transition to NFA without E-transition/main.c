
#include <stdio.h>
#include <stdbool.h>

#define MAX 20

typedef struct {
    int t[MAX][10][MAX], e[MAX][MAX], ns, na;
} ENFA;

void init(ENFA *n, int s, int a) {
    n->ns = s;
    n->na = a;

    for (int i = 0; i < s; i++) {
        for (int j = 0; j < a; j++)
            for (int k = 0; k < s; k++)
                n->t[i][j][k] = -1;

        for (int j = 0; j < s; j++)
            n->e[i][j] = -1;
    }
}

void add(ENFA *n, int f, int a, int t) {
    for (int i = 0; i < MAX; i++)
        if (n->t[f][a][i] == -1) {
            n->t[f][a][i] = t;
            break;
        }
}

void addE(ENFA *n, int f, int t) {
    for (int i = 0; i < MAX; i++)
        if (n->e[f][i] == -1) {
            n->e[f][i] = t;
            break;
        }
}

void closure(ENFA *n, int s, bool v[], int c[]) {
    if (v[s]) return;

    v[s] = true;
    c[s] = 1;

    for (int i = 0; i < n->ns; i++)
        if (n->e[s][i] != -1)
            closure(n, n->e[s][i], v, c);
}

void convert(ENFA *n) {
    int c[MAX][MAX] = {0};

    for (int i = 0; i < n->ns; i++) {
        bool v[MAX] = {0};
        closure(n, i, v, c[i]);
    }

    printf("\nEpsilon closures:\n");

    for (int i = 0; i < n->ns; i++) {
        printf("Epsilon closure of state %d: { ", i);
        for (int j = 0; j < n->ns; j++)
            if (c[i][j]) printf("%d ", j);
        printf("}\n");
    }

    printf("\nNFA transitions:\n");

    for (int s = 0; s < n->ns; s++)
        for (int a = 0; a < n->na; a++) {
            bool r[MAX] = {0};

            for (int i = 0; i < n->ns; i++)
                if (c[s][i])
                    for (int j = 0; j < MAX; j++) {
                        int t = n->t[i][a][j];
                        if (t != -1) r[t] = true;
                    }

            printf("From state %d on symbol %d: { ", s, a);
            for (int i = 0; i < n->ns; i++)
                if (r[i]) printf("%d ", i);
            printf("}\n");
        }
}

int main() {
    ENFA n;
    int s, a, t, f;

    printf("Enter the number of states: ");
    scanf("%d", &s);
    printf("Enter the number of symbols: ");
    scanf("%d", &a);

    init(&n, s, a);

    printf("Enter the number of transitions: ");
    scanf("%d", &t);
    printf("Enter transitions (from_state symbol to_state):\n");

    for (int i = 0; i < t; i++) {
        scanf("%d %d %d", &f, &a, &s);
        add(&n, f, a, s);
    }

    printf("Enter the number of epsilon transitions: ");
    scanf("%d", &t);
    printf("Enter epsilon transitions (from_state to_state):\n");

    for (int i = 0; i < t; i++) {
        scanf("%d %d", &f, &s);
        addE(&n, f, s);
    }

    convert(&n);
    return 0;
}