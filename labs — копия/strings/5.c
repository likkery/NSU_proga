#include <stdio.h>
#include <string.h>
#include <ctype.h>


int main() {
    char str1[1000], str2[1000], str3[1000], all[1000];
    int cnt = 0;

    gets(str1);
    gets(str2);
    gets(str3);

    strcpy(all, str1);
    strcat(all, str2);
    strcat(all, str3);

    for (int i = 0; all[i] != '\0'; i++) {
        for (int j = 0; all[j] != '\0'; j++)
            if (all[i] == all[j]) 
                cnt++;
        
        if (cnt == 1)
            printf("%c", all[i]);
        
        cnt = 0;
    }

    return 0;
}