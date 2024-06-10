#include <stdio.h>
#include <string.h>


int main(){
    char tip[1000], word[1000], ans[1000];
    int choice;

    gets(tip);
    gets(word);

    for(int i = 0; i < strlen(word); i++) {
        ans[i]='*';
        ans[i+1] = '\0';
    }

    for (int i = 0; i < 25; i++)
        printf("\n");
    printf("%s\n", tip);
    printf("%s\n", ans);
    printf("Letter or word (0 - letter, 1 - word)? ");

    for(int k = 0; k < 10; k++) {
        char player[1000];

        scanf_s("%d", &choice);

        if (choice == 0) {
            gets(player);

            for (int i = 0; i < strlen(word); i++)
                if (word[i] == player[0])
                    ans[i] = word[i];

            printf("%s\n",ans);
        }
        else if (choice == 1) {
            gets(player);

            if (strcmp(player, word)==0) {
                printf("WIN");
                return 0;
            }
        }
    }

    printf("LOSE");

    return 0;
}