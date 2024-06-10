#include <stdio.h>
#include <string.h>
#include <ctype.h>


int check(char str[1000]) {
    char key[][100] = {"False", "class", "from", "or", \
    "None", "def", "if", "raise", "true", "continue", \
    "global", "pass", "and", "del", "import", "return", \
    "as", "elif", "in", "try", "assert", "else", "is",\
    "while", "async", "except", "lambda", "with", "await",\
    "finally", "nonlocal", "yield", "break", "for", "not"};
    int flag = 1;
    
    for (int i = 1; i < strlen(str); i++) {
        if (('0' <= str[i] && '9' >= str[i]) || ('a' <= str[i] && 'z' >= str[i]) || str[i] == '_')
            flag = 1;
        else
            flag = 0;
    }

    for (int i = 0; i < 35; i++)
        if (strcmp(str, key[i]) == 0)
            flag = 0;

    if ('0' <= str[0] && '9' >= str[0])
        flag = 0;

    return flag;
}


int main() {
    char str[1000];

    gets(str);
    tolower(str);
    
    if (check(str) == 1) 
        printf("Yes");
    else
        printf("No");

    return 0;
}