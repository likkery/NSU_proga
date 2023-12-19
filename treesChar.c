#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TREE struct tree
#define MAX_LEN_STR 10000


TREE {
    int key;
    int type;
    char* value;
    TREE* no;
    TREE* yes;
    TREE* parent;
};


// init new node with structure of tree element
TREE* createNode(int key, int type, char *string) {
    TREE *tree = (TREE*)malloc(sizeof(TREE));

    tree -> value = (char*)malloc(sizeof(char) * strlen(string));
    tree -> key = key;
    tree -> type = type;
    tree -> no = NULL;
    tree -> yes = NULL;
    tree -> parent = NULL;

    for (int i = 0; i < strlen(string); i++)
        *((tree -> value) + i) = *(string + i);
    *((tree -> value) + (strlen(string) - 1)) = '\0';

    return tree;
}


//check if the line is kind of an answer
int isAns(char *str) {
    if (str[0] == 'A')
        return 1;
    return 0;
}


// add new element from the db to the tree
void insertFromDb(TREE* elem, TREE* new) {
    // case new line is a question
    if (!isAns(new -> value))
        // case new question is about the same property
        if (elem -> type == new -> type && elem -> key != new -> key)
            if (!elem -> no) {
                new -> parent = elem;
                elem -> no = new;
            }
            else
                insertFromDb(elem -> no, new);
        // case new question is about new property
        else if (elem -> type != new -> type && elem -> key != new -> key)
            if (!elem -> yes) {
                new -> parent = elem;
                elem -> yes = new;
                insertFromDb(elem -> no, new);
            }
            else {
                insertFromDb(elem -> yes, new);
                insertFromDb(elem -> no, new);
            }
    // case new line is an answer
    else {
        // case this question have next question and this question dont have an answer
        if (elem -> yes && !isAns(elem -> yes -> value))
            insertFromDb(elem -> yes, new);
        // case this question dont have answer
        else if (!elem -> yes) {
            new -> parent = elem;
            elem -> yes = new;
        }
        // case next question in the branch dont have answer
        else if (elem -> no && !isAns(elem -> yes -> value))
            insertFromDb(elem -> no, new);
        // case this question is the last in the branch
        else if (!elem -> no) {
            new -> parent = elem;
            elem -> no = new;
        }
        // case all questions in this branch have answer
        else if (isAns(elem -> no -> value)) {
            while (isAns(elem -> parent -> yes -> value))
                elem = elem -> parent;

            insertFromDb(elem -> parent -> no, new);
        }
    }
}


// print tree from min len to max len of elements in the tree
void inorder(TREE *elem) {
    if (elem -> no) 
        inorder(elem -> no);

    printf("%s\n", elem -> value);

    if (elem -> yes)
        inorder(elem -> yes);
}


// remove incorrect answer and add correct one from user
void idk(TREE* elem, int yesNo) {
    char new[MAX_LEN_STR], ans[MAX_LEN_STR] = "Answer: ";
    TREE* newNode;
    
    printf("Enter the correct answer\n");
    gets(new);
    strcat(ans, new);

    if (yesNo) {
        newNode = createNode(elem -> yes -> key, elem -> yes -> type, ans);
        free(elem -> yes);
        newNode -> parent = elem;
        elem -> yes = newNode;
    }
    else {
        newNode = createNode(elem -> no -> key, elem -> no -> type, ans);
        free(elem -> yes);
        newNode -> parent = elem;
        elem -> yes = newNode;
    }
}


// find the root of the tree (first question)
TREE* getRoot(TREE* elem) {
    while (elem -> parent)
        elem = elem -> parent;

    return elem;
}


// playing game with user
void game(TREE* tree) {
    int answer, newGame;

    printf("Answer following question (1 - yes, 0 - no)\n");

    while (!isAns(tree -> value)) {
        printf("%s\n", tree -> value);
        scanf("%d\n", &answer);

        if (answer == 1)
            tree = tree -> yes;
        else    
            tree = tree -> no;
    }

    if (strcmp(tree -> value, "Answer was not found"))
        idk(tree -> parent, answer);
    else 
        printf("%s\n", tree -> value);

    printf("Do you wanna start new game? (1 - yes, 0 - no)\n");
    scanf("%d\n", &newGame);

    if (newGame)
        game(getRoot(tree));
    else    
        exit(0);
}


int main() {
    FILE *db = fopen("db.txt", "rb+");
    char string[MAX_LEN_STR];
    TREE* new;
    int line = 1, type = 0;

    fgets(string, sizeof(string), db);
    TREE* root = createNode(line, type, string);
    
    inorder(root);
    
    while(!feof(db)) {
        if (string[0] != (fgets(string, sizeof(string), db))[0])
            type++;

        line++;
        new = createNode(line, type, string);
        insertFromDb(root, new);
    }

    inorder(root);

    fclose(db);
    return 0;
}