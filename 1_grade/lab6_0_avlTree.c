#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define TREE struct tree
#define MAX(i, j) (((i) > (j)) ? (i) : (j))


TREE {
    int value;
    TREE* left;
    TREE* right;
};


// get height of the node
int getHeight(TREE* tree) {
    if (tree == NULL)
        return 0;

    return MAX(getHeight(tree -> left), getHeight(tree -> right)) + 1;
}


// check if we need balancing
int balanceFactor(TREE* tree) {
    return getHeight(tree -> right) - getHeight(tree -> left);
}


// doing left rotation
TREE *leftRotate(TREE *tree) {
    TREE *fix = tree -> right;

    tree -> right = fix -> left;
    fix -> left = tree;

    return fix;
}


// doing right rotation
TREE *rightRotate(TREE *tree) {
    TREE *fix = tree -> left;

    tree -> left = fix -> right;
    fix -> right = tree;

    return fix;
}


// balancing AVL tree
TREE *balance(TREE *tree) {
    // doing left rotate or big left rotate
    if (balanceFactor(tree) == 2) {
        if (balanceFactor(tree -> right) < 0)
            tree -> right = rightRotate(tree -> right);
        return leftRotate(tree);
    }
    
    // doing right rotate or big right rotate
    if (balanceFactor(tree) == -2) {
        if (balanceFactor(tree -> left) > 0)
            tree -> left = leftRotate(tree -> left);
        return rightRotate(tree);
    }

    return tree;
}


// init the node with the data
TREE* create(int value) {
    TREE* node = (TREE*)malloc(sizeof(TREE));

    node -> value = value;
    node -> right = NULL;
    node -> left = NULL;

    return node;
}


// add new node to the tree
TREE* insert(TREE *tree, int value) {
    if (tree == NULL)
        return create(value);
    
    if (value < tree -> value)
        tree -> left = insert(tree -> left, value);
    else
        tree -> right = insert(tree -> right, value);

    return balance(tree);
}


// free memory after using programm
void deleteTree(TREE *tree) {
    if (tree) {
        deleteTree(tree -> left);
        deleteTree(tree -> right);
        free(tree);
    }
}

// symmetric output
void inorderPrint(TREE *tree) {
    if (tree == NULL)
        return;
    
    inorderPrint(tree -> left);
    printf("%d", tree -> value);
    inorderPrint(tree -> right);
}


// search element by it's value
int search(TREE *tree, int val) {
    if (tree == NULL) {
        printf("Element doesn't exist");
        return 0;
    }
    
    if (tree -> value == val)
        printf("Element was found");
    else if (tree -> value < val)
        search(tree -> right, val);
    else 
        search(tree -> left, val);

    return 1;
}


int main() {
    TREE* node = NULL;
    int value, amount, forSearch;

    scanf("%d", &amount);

    for (int i = 0; i < amount; i++) {
        scanf("%d", &value);
        node = insert(node, value);
    }

    printf("%d", getHeight(node));
    deleteTree(node);

    return 0;
}
