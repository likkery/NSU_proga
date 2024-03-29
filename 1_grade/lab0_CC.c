#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>


int check(int b1, char *x) {
    int len = strlen(x), dot = 0;

    for (int i = 0; i < len; i++) {
        if (x[i] == '.')
            dot++;

        if ((x[i] < '0' && x[i] != '.') || \
            (x[i] > '9' && x[i] < 'a') || x[i] > 'f')
            return 1;

        if ((x[i] >= '0' && x[i] <= '9') && x[i] - '0' >= b1)
            return 1;
        else if ((x[i] >= 'a' && x[i] <= 'f') && x[i] - 'a' >= b1 - 10)
            return 1;
    }

    if (dot > 1 || x[0] == '.' || x[len - 1] == '.') 
        return 1;

    return 0;
}

char numToChar(int num) {
    if (num >= 0 && num <= 9) 
        return num + '0';
    else if (num >= 10 && num <= 15) 
        return num - 10 + 'a';
    
    return '\0';
}

int charToNum(char c) {
    if (c >= '0' && c <= '9') 
        return c - '0';
    else if (c >= 'a' && c <= 'f') 
        return 10 + c - 'a';
    
    return 0;
}

double toDecNot(int b1, char *x) {
    char *intPart, *fractPart;
    double res = 0;
    int dot = 0;

    for (int i = 0; x[i] != '\0'; i++)
        if (x[i] == '.')
            dot++;

    if (dot != 0) {
        intPart = strtok(x, ".");
        fractPart = strtok(NULL, ".");
    }
    else 
        intPart = x;
    
    for (int i = strlen(intPart) - 1, power = 0; i >= 0; i--, power++) 
        res += charToNum(intPart[i]) * pow(b1, power);

    if (fractPart != NULL)
        for (int i = 0, power = -1; fractPart[i] != '\0'; i++, power--)
            res += charToNum(fractPart[i]) * pow(b1, power);

    return res;
}

int fromDecNot(int b2, double decNot) {
    int index = 0, digit;
    long long int intPart = (long long int)decNot;
    double fractPart = decNot - intPart;
    char res[100], fractRes[15], tmp;

    for (int i = 0; i < 100; i++)
        res[i] = '0';

    if (intPart == 0){
        res[0] == '0';
        index++;
    }

    while (intPart > 0) {
        res[index] = numToChar(intPart % b2);
        intPart /= b2;
        index++;
    }

    res[index] = '\0';

    for (int i = 0; i < strlen(res) / 2; i++) {
        tmp = res[i];
        res[i] = res[strlen(res) - i - 1];
        res[strlen(res) - i - 1] = tmp;
    }

    printf("%s", res);

    if (fractPart > 0) {
        printf(".");

        for (int i = 0; i < 12; i++) {
            fractPart *= b2;
            digit = (int)fractPart;
            fractRes[i] = numToChar(digit);
            fractPart -= digit;
        }

        int lastIndex = strlen(fractRes) - 1;

        while (fractRes[lastIndex] == '0') {
            fractRes[lastIndex] = '\0';
            lastIndex--;
    }

        printf("%s", fractRes);
    }
}

int main() {
    int b1, b2;
    char x[14];

    scanf_s("%d %d", &b1, &b2);
    scanf("%14s", &x);

    for (int i = 0; x[i] != '\0';  i++) 
        x[i] = tolower(x[i]);

    if ((b1 < 2 || b1 > 16) || (b2 < 2 || b2 > 16) || check(b1, x)) {
        printf("Bad input");
        return 0;
    }

    double decNot = toDecNot(b1, x);
    fromDecNot(b2, decNot);

    return 0;
}
