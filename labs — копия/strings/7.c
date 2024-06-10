#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>


int main() {
    char str[1000];
    int minLen = 10000, len = 0, start, end;

    gets(str);

    end = strlen(str);

    for (int i = strlen(str); i >= 0; i--){
        if (str[i] == ' ') {
            start = i;
            len = end - start - 1;
            minLen = fmin(minLen, len);
            end = start;
            len = 0;
        }
        else if (i == 0) {
            start = 0;
            len = end - start;
            minLen = fmin(minLen, len);
            end = start;
            len = 0;
        }
    }

    printf("%d", minLen);
    
    return 0;        
}