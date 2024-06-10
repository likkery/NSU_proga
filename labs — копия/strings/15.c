#include <stdio.h>
#include <string.h>
#include <ctype.h>


int check(char numb[10], char player[10]) {
    int cntBull = 0, cntCow = 0;

    for (int i = 0; i < 4; i++)
        if (numb[i] == player[i])
            cntBull++;
    
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (j != i && numb[i] == player[j])
                cntCow++;
    
    if (cntBull == 4) {
        printf("WIN");
        return 1;
    }
    else
        printf("Cow: %d, Bull: %d\n", cntCow, cntBull);

    return 0;
}


int main() {
    char numb[10], *player;

    gets(numb);

    for (int i = 0; i < 25; i++)
        printf("\n");

    for (int i = 0; i <= 10; i++) {
        if (i == 10){
            printf("LOSE");
            break;
        }
        
        gets(player);

        if (check(numb, player) == 1)
            break;
    }

    return 0;
}