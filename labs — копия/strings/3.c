#include <stdio.h>
#include <string.h>
#include <ctype.h>


int main() {
    char str[1000];
    int cnt = 0;

    gets(str);

    for (int i = 0; str[i] != '\0';  i++) 
        str[i] = tolower(str[i]);

    for (int i = 0; str[i] != '\0'; i++) {
        if ((strchr(str, str[i]) - str == i) && str[i] >= 'a' && str[i] <= 'z')
            cnt++;
    }

    printf("%d", cnt);

    return 0;
}