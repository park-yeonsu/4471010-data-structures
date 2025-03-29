#include <stdio.h>
#include <stdlib.h>

typedef struct BSTNode {
    int key;
    struct BSTNode* left;
    struct BSTNode* right;
} BSTNode;

BSTNode* CreateNode(int key) {
    BSTNode* new_node = (BSTNode*)malloc(sizeof(BSTNode));
    if (new_node == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    new_node->key = key;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

BSTNode* Insert(BSTNode* root, int key) {
    if (root == NULL)
        return CreateNode(key);
    
    if (key < root->key)
        root->left = Insert(root->left, key);
    else if (key > root->key)
        root->right = Insert(root->right, key);
    
    return root;
}

int Search(BSTNode* root, int key) {
    if (root == NULL)
        return 0;
    
    if (root->key == key)
        return 1;
    
    if (key > root->key)
        return Search(root->right, key);
    
    return Search(root->left, key);
}

int CountNodes(BSTNode* root) {
    if (root == NULL)
        return 0;
    return 1 + CountNodes(root->left) + CountNodes(root->right);
}

void FreeBST(BSTNode* root) {
    if (root == NULL)
        return;
    
    FreeBST(root->left);
    FreeBST(root->right);
    free(root);
}

int main() {
    int size_a, size_b;
    scanf("%d %d", &size_a, &size_b);
    
    BSTNode* set_a = NULL;
    BSTNode* set_b = NULL;
    
    for (int i = 0; i < size_a; i++) {
        int element;
        scanf("%d", &element);
        set_a = Insert(set_a, element);
    }
    
    int in_both_sets = 0;
    
    for (int i = 0; i < size_b; i++) {
        int element;
        scanf("%d", &element);
        
        if (Search(set_a, element)) {
            in_both_sets++;
        } else {
            set_b = Insert(set_b, element);
        }
    }
    
    int only_in_a = CountNodes(set_a) - in_both_sets;
    int only_in_b = CountNodes(set_b);
    
    printf("%d\n", only_in_a + only_in_b);
    
    FreeBST(set_a);
    FreeBST(set_b);
    
    return 0;
}
