#include <stdio.h>
#include <string.h>


int check(char *str){
    int sum1 = 0, sum2 = 0;

    if (strlen(str) % 2 == 0)
        for (int i = 0; i < strlen(str) / 2; i++){
            sum1 += (int)str[i];
            sum2 += (int)str[strlen(str) - i - 1];
        }

        if (sum1 == sum2)
            return 1;

    return 0;
}


int main(){
    int cnt = 1;

    while(cnt >= 1){
        char str[1000];

        gets(str);

        if (check(str) == 1) {
            printf("%d", cnt);
            break;
        }

        cnt++;
    }

    return 0;
}