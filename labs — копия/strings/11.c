#include <stdio.h>
#include <string.h>
#include <ctype.h>


int main() {
    char str[1000], lastSym, sep[1000] = " ";
    char *word;
    int cnt = 1;

    gets(str);

    word = strtok(str, sep);
    lastSym = word[strlen(word) - 1];
    word = strtok(NULL, sep);

    while (word != NULL) {
        cnt++;
        
        if (lastSym != word[0] || word == NULL) {
            cnt--;
            break;        
        }
        
        lastSym = word[strlen(word) - 1];
        word = strtok(NULL, sep);
    }

    if (cnt % 2 == 0)
        printf("Vacya is winner");
    else 
        printf("Petya is winner");

    return 0;
}