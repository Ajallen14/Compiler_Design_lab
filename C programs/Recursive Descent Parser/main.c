#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int i = 0;
char a[20];

void T() {
  if (isalpha(a[i])) {
    printf("\nT->id");
    i++;
  } else {
    printf("\nError");
    exit(0);
  }
}

void E_() {
  if (a[i] == '+') {
    printf("\nE'->+TE'");
    i++;
    T();
    E_();
  }

  else {
    printf("\nE'->e");
  }
}

void E() {
  printf("\nE->TE'");
  T();
  E_();
}

int main() {
  printf("Enter the string: ");
  scanf("%s", a);

  E();

  if (a[i] == '\0') {
    printf("\nParser Accepted!\n");
  } else {
    printf("\nInput Rejected!\n");
  }
}