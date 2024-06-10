#include <stdio.h>
#include <string.h>
#include <math.h>


int main() {
    char str[1000];
    int cnt = 1, mCnt = 0;

    gets(str);
    
    for (int i = 1; i < strlen(str); i++) {
        if (str[i] == str[i - 1]) {
            cnt++;
            mCnt = fmax(mCnt, cnt);
        }
        else
            cnt = 1;
    }

    printf("%d", mCnt);

    return 0;
}