#include <stdio.h>

int main() {
    FILE *mcode = fopen("machinecode.txt", "w");
    char tac[20][20], q[20][4], op;
    int n;

    printf("Enter number of lines: ");
    scanf("%d", &n);

    printf("Enter the Code : \n");

    for (int i = 0; i < n; i++) {
        scanf("%s", tac[i]);

        q[i][0] = tac[i][3] ? tac[i][3] : '=';
        q[i][1] = tac[i][2];
        q[i][2] = tac[i][3] ? tac[i][4] : '_';
        q[i][3] = tac[i][0];
    }

    printf("\nQuadruples:\nOp\tArg1\tArg2\tResult\n");

    for (int i = 0; i < n; i++)
        printf("%c\t%c\t%c\t%c\n", q[i][0], q[i][1], q[i][2], q[i][3]);

    for (int i = 0; i < n; i++) {
        fprintf(mcode, "MOV R%d, %c\n", i, q[i][1]);
        op = q[i][0];

        if (op != '=') {
            switch (op) {
                case '+': fprintf(mcode, "ADD R%d, %c\n", i, q[i][2]); break;
                case '-': fprintf(mcode, "SUB R%d, %c\n", i, q[i][2]); break;
                case '*': fprintf(mcode, "MUL R%d, %c\n", i, q[i][2]); break;
                case '/': fprintf(mcode, "DIV R%d, %c\n", i, q[i][2]); break;
            }
        }

        fprintf(mcode, "MOV %c, R%d\n", q[i][3], i);
    }

    printf("\nTAC:\n");
    for (int i = 0; i < n; i++)
        printf("%s\n", tac[i]);

    return 0;
}