#include <stdio.h>
#include <string.h>

char a[16], stk[15], ac[20], act[10];
int c;

void check();

int i = 0, j = 0, k = 0;

int main() {
  printf("GRAMMAR is \nE->E+E\nE->E*E\nE->(E)\nE->id\n");

  printf("Enter input string: ");
  scanf("%[^\n]", a);

  c = strlen(a);

  strcpy(act, "SHIFT->");

  printf("Stack \t Input \t Action\n");

  for (k = 0; j < c; k++, i++, j++) {
    if (a[j] == 'i' && a[j + 1] == 'd') {
      stk[i] = a[j];
      stk[i + 1] = a[j + 1];
      stk[i + 2] = '\0';
      a[j] = ' ';
      a[j + 1] = ' ';

      printf("\n$%s\t%s$\t%sid", stk, a, act);
      check();
    }

    else {
      stk[i] = a[j];
      stk[i + 1] = '\0';
      a[j] = ' ';
      printf("\n$%s\t%s$\t%ssymbols", stk, a, act);
      check();
    }
  }

  printf("\n");
}

void check() {
  strcpy(ac, "REDUCTION TO E");

  for (int z = 0; z < c; z++) {
    if (stk[z] == 'i' && stk[z + 1] == 'd') {
      stk[z] = 'E';
      stk[z + 1] = '\0';

      printf("\n$%s\t%s$\t%s", stk, a, ac);
      j++;
    }
  }

  for (int z = 0; z < c; z++) {
    if (stk[z] == 'E' && stk[z + 1] == '+' && stk[z + 2] == 'E') {
      stk[z] = 'E';
      stk[z + 1] = '\0';
      stk[z + 2] = '\0';

      printf("\n$%s\t%s$\t%s", stk, a, ac);
      i = i - 2;
    }
  }

  for (int z = 0; z < c; z++) {
    if (stk[z] == 'E' && stk[z + 1] == '*' && stk[z + 2] == 'E') {
      stk[z] = 'E';
      stk[z + 1] = '\0';
      stk[z + 2] = '\0';

      printf("\n$%s\t%s$\t%s", stk, a, ac);
      i = i - 2;
    }
  }

  for (int z = 0; z < c; z++) {
    if (stk[z] == '(' && stk[z + 1] == 'E' && stk[z + 2] == ')') {
      stk[z] = 'E';
      stk[z + 1] = '\0';
      stk[z + 2] = '\0';

      printf("\n$%s\t%s$\t%s", stk, a, ac);
      i = i - 2;
    }
  }
}