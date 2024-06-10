#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
 
#define START 1 
#define MASK_MAX_LEN 17 
#define TEXT_MAX_LEN 1000
 
int move(char symb, char *mask, int maskLen) { 
    for (int i = maskLen - 2; i >= 0; i--) 
        if (mask[i] == symb) 
            return maskLen - i - 1; 
 
    return maskLen; 
} 
 
int compare(char *text, char *mask, int checkInd, int maskLen) { 
    for (int i = 0; i < maskLen; i++) { 
        printf("%d ", checkInd + START - i); 
 
        if (mask[maskLen - 1 - i] != text[checkInd - i]) 
            return move(text[checkInd], mask, maskLen); 
    } 
 
    return move(mask[checkInd - maskLen], mask, maskLen); 
}

void moore(int maskLen, int textLen, char *text, char *mask) {
    int checkInd = maskLen - 1;

    while (checkInd < textLen) 
        checkInd += compare(text, mask, checkInd, maskLen);
}

int main() { 
    char mask[MASK_MAX_LEN], *text, symb; 
    int maskLen, textLen = 0; 
 
    scanf_s("%17[^\n]\n", mask); 
 
    maskLen = strlen(mask); 
    text = (char *)malloc(1 * sizeof(char));
 
    while (scanf("%c", &symb) != EOF) { 
        textLen++;
        text = (char *)realloc(text, textLen * sizeof(char)); 
        text[textLen - 1] = symb; 

        if (textLen == TEXT_MAX_LEN) {
            moore(maskLen, textLen, text, mask);

            for (int i = 0, j = -1 * maskLen; i < maskLen; i++, j++) 
                text[i] = text[j];

            textLen = maskLen;
            text = (char *)realloc(text, textLen * sizeof(char));
        }
    }
    
    if (maskLen > textLen) { 
        free(text); 
    
        return 0; 
    }

    moore(maskLen, textLen, text, mask);
    free(text); 
 
    return 0; 
}