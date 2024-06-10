#include <stdio.h>
#include <string.h>
#include <ctype.h>


int repeat(char *word2) {
    int flag = 1;

    for (int i = 0; i < strlen(word2); i++)
        for (int j = i + 1; j < strlen(word2); j++)
            if (word2[i] == word2[j])
                flag = 0;

    return flag;
}


int compare(char *word1, char *word2) {
    int flag = 1;

    for (int i = 0, j = 0; i < strlen(word1); i++, j++)
        if (word1[i] != word2[j] || strlen(word1) != strlen(word2))
            flag = 0;
    
    return flag;
}


int main() {
    char str[1000], sep[100] = " ";
    char *word1, *word2;

    gets(str);

    word1 = strtok(str, sep);

    while (word2 != NULL) {
        word2 = strtok(NULL, sep);
        if (compare(word1, word2) == 0  && repeat(word2) == 1)
            printf("%s ", word2);
    }
}