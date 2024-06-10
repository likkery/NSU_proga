#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <malloc.h>

int sort(int *lens, int cnt) {
    for (int i = 0; i < cnt - 1; i++)
        for (int j = 0; j < cnt - i - 1; j++)
            if (lens[j] > lens[j + 1]) {
                int tmp = lens[j];
                lens[j] = lens[j + 1];
                lens[j + 1] = tmp;
            }
    
    return 0;
}


int printWord(int start, int end, char str[1000]) {
    for (int i = start; i < end; i++)
        printf("%c", str[i]);
    
    printf(" ");
}


int checkLen(char str[1000], int len)  {
    int start, end = strlen(str), lenWord;

    for (int i = strlen(str); i >= 0; i--)
        if (str[i] == ' ') {
            start = i;
            lenWord = end - start - 1;

            if (len == lenWord) 
                printWord(start, end, str);

            end = start;
        }
        else if (i == 0) {
            start = 0;
            lenWord = end - start;

            if (len == lenWord) 
                printWord(start, end, str);

            end = start;
        }

    return 0;
}


int main() {
    char str[1000], word[100];
    int len, start, end, cnt = 1, check = 0;
    

    gets(str);

    end = strlen(str);

    for (int i = strlen(str); i >= 0; i--)
        if (str[i] == ' ') 
            cnt++;
    
    int *lens = (int *)malloc(cnt * sizeof(int));

    for (int i = strlen(str); i >= 0; i--){
        if (str[i] == ' ') {
            start = i;
            len = end - start - 1;
            lens[check] = len;
            check++;
            end = start;
        }
        else if (i == 0) {
            start = 0;
            len = end - start;
            lens[check] = len;
            check++;
            end = start;
        }
    }

    sort(lens, cnt);

    for (int i = 0; i < cnt; i++) 
        checkLen(str, lens[i]);

    return 0;
}