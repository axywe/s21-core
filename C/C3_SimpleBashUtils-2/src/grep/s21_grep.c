#include <ctype.h>
#include <getopt.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 65536

enum Options {
  OPT_NONE = 0,
  OPT_IGNORE = 1 << 0,
  OPT_PATTERN = 1 << 1,
  OPT_INVERT = 1 << 2,
  OPT_COUNT = 1 << 3,
  OPT_FILES = 1 << 4,
  OPT_NUM = 1 << 5,
  OPT_ERRORS = 1 << 6,
  OPT_LINES = 1 << 7,
  OPT_FILE = 1 << 8,
  OPT_MATCH = 1 << 9
};

int getOptions(int, char **, char **, char **, char **);
bool findPattern(const char *, const char *, bool);
void processFiles(const char *, const char **, int, int);
char *readPattern(const char *);
void outputMatchCount(int, int, int, const char *);
void outputLine(int, int, const char *, const char *);
void outputNumbers(int, int, int, const char *);
void outputMatches(int, int, const char *, const char *, const char *);

int main(int argc, char **argv) {
  char *pattern = NULL, *filename = NULL, *filePattern = NULL;
  int options = getOptions(argc, argv, &pattern, &filename, &filePattern);
  if (!pattern && !filePattern) {
    printf("Error: Pattern is missing\n");
    return 0;
  }
  if (options & OPT_FILE) {
    char *newPattern = readPattern(filePattern);
    if (newPattern) {
      pattern = malloc(SIZE);
      strcpy(pattern, newPattern);
      free(newPattern);
    } else {
      return 0;
    }
  }
  int firstFile = optind, fileCount = argc - firstFile;
  const char *files[fileCount];
  for (int i = 0; i < fileCount; ++i) files[i] = argv[firstFile + i];
  processFiles(pattern, files, fileCount, options);
  if (options & OPT_FILE) free(pattern);
  return 0;
}

int getOptions(int argc, char **argv, char **pattern, char **filename,
               char **filePattern) {
  int opt, options = OPT_NONE;
  while ((opt = getopt(argc, argv, "lne:vichsf:o")) != -1) {
    switch (opt) {
      case 'l':
        options |= OPT_FILES;
        break;
      case 'n':
        options |= OPT_NUM;
        break;
      case 'i':
        options |= OPT_IGNORE;
        break;
      case 'e':
        options |= OPT_PATTERN;
        *pattern = optarg;
        break;
      case 'v':
        options |= OPT_INVERT;
        break;
      case 'c':
        options |= OPT_COUNT;
        break;
      case 'h':
        options |= OPT_LINES;
        break;
      case 's':
        options |= OPT_ERRORS;
        break;
      case 'f':
        options |= OPT_FILE;
        *filePattern = optarg;
        break;
      case 'o':
        options |= OPT_MATCH;
        break;
      default:
        printf("Error: Invalid parameters\n");
        return 0;
    }
  }
  if (!*pattern && optind < argc && !(options & OPT_FILE))
    *pattern = argv[optind++];
  if (optind < argc) *filename = argv[optind];
  return options;
}

bool findPattern(const char *pattern, const char *line, bool ignore) {
  regex_t reg;
  int flags = REG_EXTENDED | (ignore ? REG_ICASE : 0);
  if (regcomp(&reg, pattern, flags) != 0) return false;
  bool found = regexec(&reg, line, 0, NULL, 0) == 0;
  regfree(&reg);
  return found;
}

void processFiles(const char *pattern, const char *files[], int count,
                  int options) {
  for (int i = 0; i < count; ++i) {
    FILE *f = fopen(files[i], "r");
    if (!f) {
      if (!(options & OPT_ERRORS))
        printf("Error: Cannot open file '%s'\n", files[i]);
      continue;
    }
    char line[SIZE];
    int lineNum = 0, matches = 0;
    while (fgets(line, sizeof(line), f)) {
      int len = strlen(line);
      if (len > 0 && line[len - 1] == '\n') line[--len] = '\0';
      ++lineNum;
      bool found = findPattern(pattern, line, options & OPT_IGNORE);
      if ((found && !(options & OPT_INVERT)) ||
          (!found && (options & OPT_INVERT))) {
        if (options & OPT_NUM) outputNumbers(count, options, lineNum, files[i]);
        if (options & OPT_MATCH)
          outputMatches(count, options, files[i], pattern, line);
        else if (!(options & OPT_COUNT) && !(options & OPT_FILES))
          outputLine(count, options, line, files[i]);
        ++matches;
      }
    }
    if (options & OPT_COUNT)
      outputMatchCount(count, options, matches, files[i]);
    if (options & OPT_FILES && matches > 0) printf("%s\n", files[i]);
    fclose(f);
  }
}

char *readPattern(const char *filename) {
  FILE *f = fopen(filename, "r");
  if (!f) return 0;
  char *pattern = malloc(SIZE);
  fgets(pattern, SIZE, f);
  for (int i = 0; i < SIZE; ++i) {
    if (pattern[i] == '\n') {
      pattern[i] = '\0';
      break;
    }
  }
  fclose(f);
  return pattern;
}

void outputMatchCount(int count, int options, int matches,
                      const char *filename) {
  if (count == 1 || options & OPT_LINES)
    printf("%d\n", matches);
  else
    printf("%s:%d\n", filename, matches);
}

void outputLine(int count, int options, const char *line,
                const char *filename) {
  if (count == 1 || options & OPT_LINES || options & OPT_NUM)
    printf("%s\n", line);
  else
    printf("%s:%s\n", filename, line);
}

void outputNumbers(int count, int options, int lineNum, const char *filename) {
  if (count == 1 || options & OPT_LINES)
    printf("%d:", lineNum);
  else
    printf("%s:%d:", filename, lineNum);
}

void outputMatches(int count, int options, const char *filename,
                   const char *pattern, const char *line) {
  regmatch_t match;
  regex_t reg;
  int flags = REG_EXTENDED | (options & OPT_IGNORE ? REG_ICASE : 0);
  if (regcomp(&reg, pattern, flags) != 0) return;
  if (regexec(&reg, line, 1, &match, 0) == 0) {
    if (count == 1 || options & OPT_LINES || options & OPT_NUM)
      printf("%.*s\n", (int)(match.rm_eo - match.rm_so), &line[match.rm_so]);
    else
      printf("%s:%.*s\n", filename, (int)(match.rm_eo - match.rm_so),
             &line[match.rm_so]);
  }
  regfree(&reg);
}
