#include <stdio.h>
#include <string.h>
#include <ctype.h>


int compare(int start1, int end1, int start2, int end2, char str[1000]) {
    int flag = 1;

    for (int i = start1, j = start2; i < end1; i++, j++)
        if (end1 - start1 == end2 - start2) 
            if (str[i] != str[j])
                flag = 0;

    return flag;
}


int printWord(char str[1000], int start1, int end1) {
        for (int i = start1; i < end1; i++)
            printf("%c", str[i]);
        printf(" ");

    return 0;
}


int main() {
    char str[1000];

    gets(str);

    int start1, end1 = strlen(str), start2, end2;

    for (int i = strlen(str); i >= 0; i--)
        if (str[i] == ' ') {
            start1 = i + 1;
            end2 = i;

            for (int j = start1 - 2; j >= 0; j--) 
                if (str[j] == ' ' || j == 0) {
                    start2 = j + 1;
                    if (j == 0)
                        start2 = 0;
                    if (compare(start1, end1, start2, end2, str) == 1) 
                        printWord(str, start1, end1);
                }
        }

    return 0;
}