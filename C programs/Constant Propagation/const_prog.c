#include <ctype.h>
#include <stdio.h>

int main() {
  char c, x;
  char a[5][2];
  int i = 0, j;

  FILE *f1 = fopen("input.txt", "r");
  FILE *f2 = fopen("output.txt", "w");

  c = fgetc(f1);
  x = c;

  while (c != EOF) {
    fputc(c, f2);

    if (c == '=') {
      c = fgetc(f1);
      if (isdigit(c)) {
        a[i][0] = x;
        a[i][1] = c;
        fputc(c, f2);
        i++;
      }
      if (isalpha(c)) {
        for (j = 0; j < i; j++) {
          if (c == a[j][0]) {
            fputc(a[j][1], f2);
            break;
          }
        }
      }
    }
    c = fgetc(f1);
  }

  fclose(f1);
  fclose(f2);

  return 0;
}