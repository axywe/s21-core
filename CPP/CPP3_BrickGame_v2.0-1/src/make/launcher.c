#include <stdio.h>
#include <stdlib.h>

int main() {
  int choice;
  do {
    printf(
        "\033[41;31m#\033[0m \033[43;33m#\033[0m \033[42;32m#\033[0m Steam "
        "Community\n      https://steamcommunity.com/\n");
    printf("Library:\n");
    printf("1. Tetris\n");
    printf("2. Snake\n");
    printf("3. Exit\n");
    scanf("%d", &choice);
    switch (choice) {
      case 1:
        system("./bin/tetris");
        break;
      case 2:
        system("./bin/s21_snake.app/Contents/MacOS/s21_snake");
        break;
      case 3:
        printf("Exiting...\n");
        break;
      default:
        printf("Invalid choice\n");
    }
  } while (choice != 3);
  return 0;
}
