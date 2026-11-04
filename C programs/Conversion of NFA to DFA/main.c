
#include <stdio.h>

#define MAX 20

typedef struct {
    int t[MAX][10][MAX], ns, na;
} NFA;

typedef struct {
    int t[MAX][10], ns, na;
} DFA;

void init(NFA *n, int s, int a) {
    n->ns = s;
    n->na = a;
    for (int i = 0; i < s; i++)
        for (int j = 0; j < a; j++)
            for (int k = 0; k < s; k++)
                n->t[i][j][k] = -1;
}

void add(NFA *n, int f, int a, int t) {
    for (int i = 0; i < MAX; i++)
        if (n->t[f][a][i] == -1) {
            n->t[f][a][i] = t;
            break;
        }
}

int exists(int sets[MAX][MAX], int size[], int count, int s[], int n) {
    for (int i = 0; i < count; i++) {
        if (size[i] == n) {
            int j;
            for (j = 0; j < n && sets[i][j] == s[j]; j++);
            if (j == n) return i;
        }
    }
    return -1;
}

void convert(NFA *n, DFA *d) {
    int sets[MAX][MAX], size[MAX], count = 1;
    sets[0][0] = 0;
    size[0] = 1;

    d->na = n->na;

    for (int i = 0; i < count; i++) {
        for (int a = 0; a < n->na; a++) {
            int s[MAX], ns = 0;

            for (int j = 0; j < size[i]; j++) {
                int q = sets[i][j];

                for (int k = 0; k < MAX; k++) {
                    int t = n->t[q][a][k], found = 0;

                    if (t != -1) {
                        for (int l = 0; l < ns; l++)
                            if (s[l] == t) found = 1;

                        if (!found) s[ns++] = t;
                    }
                }
            }

            for (int j = 0; j < ns; j++)
                for (int k = j + 1; k < ns; k++)
                    if (s[j] > s[k]) {
                        int t = s[j];
                        s[j] = s[k];
                        s[k] = t;
                    }

            int index = exists(sets, size, count, s, ns);

            if (index == -1) {
                index = count++;
                for (int j = 0; j < ns; j++)
                    sets[index][j] = s[j];
                size[index] = ns;
            }

            d->t[i][a] = index;
        }
    }

    d->ns = count;
}

void print(DFA *d) {
    printf("\nDFA Transitions:\n");
    for (int i = 0; i < d->ns; i++)
        for (int j = 0; j < d->na; j++)
            printf("DFA state %d on symbol %d -> DFA state %d\n",
                   i, j, d->t[i][j]);
}

int main() {
    NFA n;
    DFA d;
    int s, a, t;

    printf("Enter the number of NFA states: ");
    scanf("%d", &s);
    printf("Enter the number of input symbols: ");
    scanf("%d", &a);

    init(&n, s, a);

    printf("Enter the number of transitions: ");
    scanf("%d", &t);

    printf("Enter transitions (from_state symbol to_state):\n");

    for (int i = 0; i < t; i++) {
        int f, a, t;
        scanf("%d %d %d", &f, &a, &t);
        add(&n, f, a, t);
    }

    convert(&n, &d);
    print(&d);

    return 0;
}
