#include <stdio.h>
#include <string.h>
#include <ctype.h>


int main() {
    char str[1000];
    int cnt = 0;

    gets(str);

    for (int i = 0; str[i] != '\0'; i++) {
        for (int j = 0; str[j] != '\0'; j++)
            if (str[i] == str[j]) 
                cnt++;
        
        if (cnt == 3) {
            printf("%c", str[i]);
            break;
        }
        
        cnt = 0;
    }

    return 0;
}