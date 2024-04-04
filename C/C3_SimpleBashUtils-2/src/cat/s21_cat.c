#include <stdio.h>
#include <string.h>

#define ERROR 0
#define OK 1
typedef enum { false, true } bool;

void putcharV(char ch) {
  if ((ch < 32) && ch != '\n' && ch != '\t') {
    printf("^%c", ch + 'A' - 1);
  } else if ((ch == 127) && ch != '\n' && ch != '\t') {
    printf("^?");
  } else {
    printf("%c", ch);
  }
}

void def(bool *flags, int *STATUS, int argc, char **argv) {
  for (int i = 1; i < argc - 1 && *STATUS != ERROR; i++) {
    if (!strcmp(argv[i], "-"))
      *STATUS = ERROR;
    else if (argv[i][0] == '-' && argv[i][1] == '-' && i != argc - 1) {
      if (!strcmp("--number-nonblank", argv[i]))
        flags[0] = true;
      else if (!strcmp("--number", argv[i]))
        flags[2] = true;
      else if (!strcmp("--squeeze-blank", argv[i]))
        flags[3] = true;
    } else if (argv[i][0] == '-') {
      for (int j = 1; ((j < argv[i][j]) != '\0') && *STATUS != ERROR; j++) {
        if (argv[i][j] == 'b')
          flags[0] = true;
        else if (argv[i][j] == 'e') {
          flags[5] = true;
          flags[1] = true;
        } else if (argv[i][j] == 'n')
          flags[2] = true;
        else if (argv[i][j] == 's')
          flags[3] = true;
        else if (argv[i][j] == 't') {
          flags[4] = true;
          flags[5] = true;
        } else if (argv[i][j] == 'T')
          flags[4] = true;
        else if (argv[i][j] == 'E')
          flags[1] = true;
        else if (argv[i][j] == 'v')
          flags[5] = true;
        else if (argv[i][j] != 0)
          *STATUS = ERROR;
      }
    }
  }
}

void print(bool *flags, FILE *mf) {
  if (flags[0] && flags[2]) flags[2] = 0;
  int c = fgetc(mf);
  int num = 0;
  int lastch = -1;
  int lastlastch = -1;
  while (c != EOF) {
    if (flags[3] && lastch == c && lastlastch == lastch && c == '\n') {
      c = fgetc(mf);
      continue;
    }
    if (flags[0] && (lastch == '\n' || num == 0) && c != '\n')
      printf("% 6d\t", ++num);
    if (flags[2] && (lastch == '\n' || num == 0)) printf("% 6d\t", ++num);
    if (flags[4] && c == '\t')
      printf("^I");
    else if ((flags[1] && c == '\n') && (flags[0] && lastch == '\n'))
      printf("\t\t$\n");
    else if (flags[1] && c == '\n')
      printf("$\n");
    else if (flags[5])
      putcharV(c);
    else
      printf("%c", c);
    lastlastch = lastch;
    lastch = c;
    c = fgetc(mf);
  }
}

int main(int argc, char *argv[]) {
  int STATUS = OK;
  char *file;

  bool flags[] = {0, 0, 0, 0, 0, 0};
  if (argc > 2) def(flags, &STATUS, argc, argv);
  FILE *mf;
  int opened = 0;
  for (int i = 1; i < argc; i++) {
    file = argv[i];
    if (STATUS == OK && (mf = fopen(file, "r")) != NULL) {
      opened++;
      print(flags, mf);
      fclose(mf);
    }
  }
  if (opened == 0) STATUS = ERROR;
  if (STATUS == ERROR) printf("n/a");
  return 0;
}