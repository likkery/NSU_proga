#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define NUM struct num
#define OPER struct oper
#define MAX_EXP_LEN 1000
#define MAX_NUM_LEN 100


NUM {
    double value;
    NUM* next;
};

OPER {
    char value;
    OPER* next;
};


int check(char *exp);
void error(int err);
int symbType(char symb);
void createNumNode(double value, NUM **head);
void createOperNode(char value, OPER **head);
double popNum(NUM **head);
char popOper(OPER **head);
char takeOper(OPER **head);
long int calc(char *exp);
double doOper(double num1, double num2, char oper);


int main() {
    char exp[MAX_EXP_LEN];
    int res;

    gets(exp);
    
    check(exp);
    res = calc(exp);

    printf("%ld", res);

    return 0;
}


int symbType(char symb) {
    if (isdigit(symb))
        return 10;

    switch (symb) {
        case '+': return 5;
        case '-': return 5;
        case '*': return 6;
        case '/': return 6;
        case '(': return 3;
        case ')': return 2;
        default: return 0;
    }
}


int check(char *exp) {
    int count = 0;

    if (symbType(exp[0]) == 10)
            count++;
    for (int i = 1; i < strlen(exp); i++) {
        if (!symbType(exp[i]) || \
        (symbType(exp[i]) == 5 && symbType(exp[i - 1]) == 5) || \
        (symbType(exp[i]) == 6 && symbType(exp[i - 1]) == 6) || \
        (abs(symbType(exp[i]) - symbType(exp[i - 1])) == 1)) {
            error(0);
        }

        if (i + 1 == strlen(exp) && (symbType(exp[i]) == 5 || symbType(exp[i]) == 6))
            error(0);

        if (symbType(exp[i]) == 10)
            count++;

        if (isspace(exp[i]) != 0)
            error(0);
    }

    if (count == 0)
        error(0);

    return 0;
}


void error(int err) {
    if (!err) {
        printf("syntax error\n");
        exit(0);
    }
    else {
        printf("division by zero\n");
        exit(0);
    }
}


long int calc(char *exp) {
    NUM *headNum = NULL;
    OPER *headOper = NULL;
    double res;

    createOperNode('(', &headOper);

    for (int i = 0; i < strlen(exp); i++) {
        if (isdigit(exp[i])) {
            char num[MAX_NUM_LEN] = "";
            int num_null = i;

            while (isdigit(exp[i])) {
                num[i - num_null] = exp[i];
                i++;
            }

            i--;
            createNumNode(atol(num), &headNum);

            if (headOper -> value == '-') {
                res = doOper(popNum(&headNum), popNum(&headNum), popOper(&headOper));
                createNumNode(res, &headNum);
            }
        }

        else if (symbType(exp[i]) == 6 || exp[i] == '(')
            createOperNode(exp[i], &headOper);

        else if (symbType(exp[i]) == 5) {
            if (headOper -> value == '(' || symbType(takeOper(&headOper)) <= 5)
                createOperNode(exp[i], &headOper);
            else {
                while (headOper -> value != '(') {
                    res = doOper(popNum(&headNum), popNum(&headNum), popOper(&headOper));
                    createNumNode(res, &headNum);
                }
                
                createOperNode(exp[i], &headOper);
            }
        }

        else if (exp[i] == ')') {
            while (headOper -> value != '(') {
                res = doOper(popNum(&headNum), popNum(&headNum), popOper(&headOper));
                createNumNode(res, &headNum);
            }

            if (headOper -> value == '(')
                popOper(&headOper);
                
                if (headOper == NULL)
                    error(0);
                
                if (headOper -> value == '-') {
                res = doOper(popNum(&headNum), popNum(&headNum), popOper(&headOper));
                createNumNode(res, &headNum);
            }
        }
    }

    while (headOper -> value != '(') {
        res = doOper(popNum(&headNum), popNum(&headNum), popOper(&headOper));
        createNumNode(res, &headNum);
    }

    if (headOper -> value == '(' && headNum != NULL)
        return (long int)(headNum -> value);
    else 
        error(0);

    return 0;
}   


void createNumNode(double value, NUM **head) {
    NUM *node = (NUM*)malloc(sizeof(NUM));

    node -> value = value;
    node -> next = *head;
    *head = node;
}


void createOperNode(char value, OPER **head) {
    OPER *node = (OPER*)malloc(sizeof(OPER));

    node -> value = value;
    node -> next = *head;
    *head = node;
}


double popNum(NUM **head) {
    NUM *remove = *head;
    double value;
    
    value = remove -> value;
    *head = remove -> next;

    free(remove);
    return value;
}


char popOper(OPER **head) {
    OPER *remove = *head;
    char value;
    
    value = remove -> value;
    *head = remove -> next;
e(remove);
    return value;
    fre
}

char takeOper(OPER **head) {
    OPER *operand = *head;
    char value = operand -> value;

    return value;
}


double doOper(double num1, double num2, char oper) {
    if (num2 == 0 && oper == '/')
        error(1);
    
    switch (oper) {
        case '+': return num1 + num2;
        case '-': return num1 - num2;
        case '*': return num1 * num2;
        case '/': return num1 / num2;
        default: return 0;
    }
}
