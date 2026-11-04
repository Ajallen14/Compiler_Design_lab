
#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef struct {
    int *e, count;
} NFA;

NFA nfa[MAX];
int n;

void add(int f, int t) {
    nfa[f].e[nfa[f].count++] = t;
}

void closure(int s, int c[], int *count) {
    for (int i = 0; i < *count; i++)
        if (c[i] == s) return;

    c[(*count)++] = s;

    for (int i = 0; i < nfa[s].count; i++)
        closure(nfa[s].e[i], c, count);
}

void printClosure() {
    for (int i = 0; i < n; i++) {
        int c[MAX], count = 0;

        closure(i, c, &count);
        printf("Epsilon closure of state %d: { ", i);

        for (int j = 0; j < count; j++)
            printf("%d ", c[j]);

        printf("}\n");
    }
}

int main() {
    int t, f, to;

    printf("Enter number of states in the NFA: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        nfa[i].e = malloc(MAX * sizeof(int));
        nfa[i].count = 0;
    }

    printf("Enter number of epsilon transitions: ");
    scanf("%d", &t);
    printf("Enter transitions (from to):\n");

    for (int i = 0; i < t; i++) {
        scanf("%d %d", &f, &to);
        add(f, to);
    }

    printClosure();

    for (int i = 0; i < n; i++)
        free(nfa[i].e);

    return 0;
}
