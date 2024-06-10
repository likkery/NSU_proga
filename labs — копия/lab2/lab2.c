#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 1000


int check(char *str) {
    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] < '0' || str[i] > '9' || strchr(str, str[i]) - str != i)    
            return 1;

    if (strlen(str) > 10)
        return 1;

    return 0;
}


int checkMax(char *str) {
    int flag = 0;

    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] > str[i + 1])
            flag++;

    if (flag == strlen(str))
        return 0;

    return 1;
}

void swap(char* a, char* b) {
    char tmp = *a;
    *a = *b;
    *b = tmp;
}


void reverse(char *str, int startRev) {
    int endRev = strlen(str) - 1;

    while (startRev < endRev) {
        swap(&str[startRev], &str[endRev]);
        startRev++;
        endRev--;
    }
}


int permutation(char *str, int cnt) {
    int ind = strlen(str) - 2;

    for (int i = 0; i < cnt; i++) {
        while (ind >= 0 && str[ind] >= str[ind + 1])
            ind--;

        if (ind == -1)
            return 0;

        if (ind >= 0) {
            int j = strlen(str) - 1;

            while (str[j] < str[ind])
                j--;
            
            swap(&str[ind], &str[j]);
        }

        reverse(str, ind + 1);
        printf("%s \n", str); 

        if (checkMax(str) == 0)
            return 0;
    }

    return 0;
}


int main() {
    char str[MAX_LEN];
    int cnt;

    scanf("%1000s", &str);
    scanf_s("%d", &cnt);

    if (check(str) == 1) {
        printf("bad input");
        return 0;
    }

    if (checkMax(str))
        permutation(str, cnt);

    return 0;
}