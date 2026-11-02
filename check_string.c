#include <ctype.h>
#include <pwd.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

bool test(char *input) {
  for (int i = 1; i < strlen(input); i++) {
    if (isdigit(input[i]) == 0) {
      printf("%c\n", input[i]);
      return false;
    }
  }
  return true;
}

void convertToNum(char *input, char *num) {
  int count = 0;
  for (int i = 1; i < strlen(input); i++) {
    if (isdigit(input[i]) != 0) {
      num[count] = input[i];
      count++;
    }
  }
  num[count] = '\0';
}

void str_maker(char *input, char *path) {
  int count = 0;

  for (int i = 1; i < strlen(input); i++) {
    path[count] = input[i];
    printf("%d %c\n", count, input[i]);
    count++;
  }
  path[count] = '\0';
}

int main() {
  char str1[4] = "~\0";
  char path1[4096];

  char str2[17] = "~/units/02-tools\0";
  char path2[4096];
  char dir_path[4096];

  char str3[40] = "~/units02-toolsa8-2026fall-d1-aaa452\0";
  char path3[4096];

  struct passwd *pwd = getpwuid(getuid());

  if (pwd != NULL) {
    // str_maker(str1, pwd->pw_dir, path1);
    str_maker(str3, path3);
    // str_maker(str3, pwd->pw_dir, path3);

    // printf("%s\n", path1);
    snprintf(dir_path, sizeof(dir_path), "%s%s", pwd->pw_dir, path3);

    printf("%s\n", dir_path);
    // printf("%s\n", path3);
  }

  /*
   bool flag = test(string);

  if (flag) {
    printf("String contains a valid number: %d\n", flag);
    convertToNum(string, number);
    long num = atoi(number);
    int x = (int)num;
    printf("Number is : %d\n", x);
  } else {
    printf("String does not contain a valid number.\n");
  }

  return 0;
  */
}
