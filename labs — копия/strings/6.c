#include <stdio.h>
#include <string.h>
#include <ctype.h>


int main() {
    char str[1000];
    
    gets(str);

    int end = strlen(str), start;

    for (int i = strlen(str); i >= 0; i--) {
        if (str[i] == ' ')  {
            start = i;

            for (int j = i + 1; j < end; j++)
                printf("%c", str[j]);
            printf(" ");

            end = start;
        }
        else if (i == 0) {
            for (int j = i; j < end; j++)
                printf("%c", str[j]);
        }
    }

    return 0;
}