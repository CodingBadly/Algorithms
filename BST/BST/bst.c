#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
    int key;
    struct _node *left;
    struct _node *right;
} node;

void Insert(int key, node **leaf)
{
    if (NULL == *leaf) {
        *leaf = (node *)malloc(sizeof(node));
        (*leaf)->key = key;
        (*leaf)->left = (*leaf)->right = NULL;
    } else if (key < (*leaf)->key) {
        Insert(key, &(*leaf)->left);
    } else if (key >= (*leaf)->key) {
        Insert(key, &(*leaf)->right);
    }
}

void Destroy(node *leaf)
{
    if (leaf != NULL) {
        Destroy(leaf->left);
        Destroy(leaf->right);
        free(leaf);
    }
}

void Traverse(node *leaf)
{
    if (leaf == NULL) return;
    printf("\n[%x] key=%d, left=%x, right=%x", leaf, leaf->key, leaf->left, leaf->right);
    Traverse(leaf->left);
    Traverse(leaf->right);
}

node *FindMin(node *leaf)
{
    node *temp = leaf;
    while (NULL !=  temp->left) {
        temp = temp->left;
    }
    return temp;
}

node *Remove(int key, node *leaf)
{
    if (leaf == NULL) return NULL;
    else if (key < leaf->key) leaf->left = Remove(key, leaf->left);
    else if (key > leaf->key) leaf->right = Remove(key, leaf->right);
    else {
        if (leaf->left == NULL && leaf->right == NULL) {
            // Case 1: No children
            free(leaf);
            leaf = NULL;
        } else if (leaf->left == NULL) { 
            // Case 2: One child
            node *temp = leaf;
            leaf = leaf->right;
            free(temp);
        } else if (leaf->right == NULL) { 
            // Case 2: One child
            node *temp = leaf;
            leaf = leaf->left;
            free(temp);
        } else {
            // Case 3: 2 children
            node *temp = FindMin(leaf->right);
            leaf->key = temp->key;
            leaf->right = Remove(temp->key, leaf->right);
        }
    }

    return leaf;
}

node *root = NULL;

void main()
{
    int keys[] = {8, 3, 10, 1, 6, 4, 7, 14, 13};

    for (int i = 0; i < sizeof(keys) / sizeof(keys[0]); i++) {
        Insert(keys[i], &root);
    }
    Traverse(root);

    printf("\nCase 1: Rmove 13 - ");
    Remove(13, root);
    Traverse(root);

    printf("\nCase 2 Rmove 10 - ");
    Remove(10, root);
    Traverse(root);

    printf("\nCase 3: Rmove 3 - ");
    Remove(3, root);
    Traverse(root);

    Destroy(root);
}