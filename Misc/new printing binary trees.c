#include <stdio.h>
#include <stdlib.h>

// only for positive powers
unsigned long long myPow(int base, int power) {
    unsigned long long output = 1;
    for (int i = 0; i < power; ++i) {
        output *= base;
    }
    return output;
}

int maxInt(int a, int b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

typedef struct NodeTemp {
    int value;
    struct NodeTemp* left;
    struct NodeTemp* right;
} Node;

Node* createNode(int value) {
    Node* tempNode = (Node*) malloc(sizeof(Node));
    tempNode->value = value;
    tempNode->left = NULL;
    tempNode->right = NULL;
    
    return tempNode;
}

int treeHeight(Node* root) {
    if (root == NULL) {
        return 0;
    } else {
        return 1 + maxInt(treeHeight(root->left), treeHeight(root->right));
    }
}

void printCurrentLevel(Node* root, int level, unsigned long long startingSpaces, FILE* file) {
    if (root == NULL) {
        return;
    }
    if (level == 1) {
        printf("%d", root->value);
        fprintf(file, "%d", root->value);
        unsigned long long betweenSpaces = 2 * startingSpaces + 1;
        for (int i = 0; i < betweenSpaces; ++i) {
            printf(" ");
            fprintf(file, " ");
        }
    } else if (level > 1) {
        printCurrentLevel(root->left, level - 1, startingSpaces, file);
        printCurrentLevel(root->right, level - 1, startingSpaces, file);
    }
    
}


void printTree(Node* root, FILE* file) {
    if (root == NULL) {
        return;
    }

    int height = treeHeight(root);

    for (int i = 0; i < height; ++i) {
        unsigned long long startingSpaces = myPow(2, height - i) - 1;
        for (int ii = 0; ii < startingSpaces; ++ii) {
            printf(" ");
            fprintf(file, " ");
        }
        printCurrentLevel(root, i + 1, startingSpaces, file);
        printf("\n");
        fprintf(file, "\n");
    }
}

Node* buildNSizeTree(int n, int startingValue) {
    if (n <= 0) {
        return NULL;
    }
    Node* tempNode = createNode(startingValue);
    tempNode->left = buildNSizeTree(n - 1, startingValue + 1);
    tempNode->right = buildNSizeTree(n - 1, startingValue + 1);
    return tempNode;
}


int main() {
    Node* tree = buildNSizeTree(7, 0);
    FILE *file = fopen("tree.txt", "w");
    printTree(tree, file);
    fclose(file);

}