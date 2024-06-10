#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>


int main() {
    char str[1000];
    int cnt = 0, mCnt = 0;

    gets(str);
    
    size_t leng = strlen(str);

    for (int i = 0; i < (int)leng; i++) {
        if(isspace(str[i]))
            cnt++;
        else{
            mCnt = fmax(cnt, mCnt);
            cnt = 0;
        }
    }

    printf("%d", mCnt);

    return 0;
}