#include "social_graph.h"

// Kırmızı-Siyah ağaç için yeni düğüm oluşturma
RBNode* createRBNode(int key, void* data, RBTree* tree) {
    RBNode* node = (RBNode*)malloc(sizeof(RBNode));
    if (!node) {
        printf("RB düğümü için bellek ayrılamadı!\n");
        return NULL;
    }
    
    node->key = key;
    node->data = data;
    node->color = RED;
    node->left = tree->NIL;
    node->right = tree->NIL;
    node->parent = tree->NIL;
    return node;
}

// Kırmızı-Siyah ağaç başlatma
RBTree* initRBTree() {
    RBTree* tree = (RBTree*)malloc(sizeof(RBTree));
    if (!tree) {
        printf("RB ağacı için bellek ayrılamadı!\n");
        return NULL;
    }
    
    // NIL düğümü oluştur
    RBNode* nil = (RBNode*)malloc(sizeof(RBNode));
    if (!nil) {
        printf("NIL düğümü için bellek ayrılamadı!\n");
        free(tree);
        return NULL;
    }
    
    nil->color = BLACK;
    nil->left = NULL;
    nil->right = NULL;
    nil->parent = NULL;
    nil->key = 0;
    nil->data = NULL;
    
    tree->NIL = nil;
    tree->root = tree->NIL;
    
    return tree;
}

// Sola döndürme
void leftRotate(RBTree* tree, RBNode* x) {
    RBNode* y = x->right;
    x->right = y->left;
    
    if (y->left != tree->NIL)
        y->left->parent = x;
    
    y->parent = x->parent;
    
    if (x->parent == tree->NIL)
        tree->root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    
    y->left = x;
    x->parent = y;
}

// Sağa döndürme
void rightRotate(RBTree* tree, RBNode* y) {
    RBNode* x = y->left;
    y->left = x->right;
    
    if (x->right != tree->NIL)
        x->right->parent = y;
    
    x->parent = y->parent;
    
    if (y->parent == tree->NIL)
        tree->root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;
    
    x->right = y;
    y->parent = x;
}

// Ekleme sonrası düzeltme
void fixInsert(RBTree* tree, RBNode* k) {
    RBNode* u;
    
    while (k->parent->color == RED) {
        if (k->parent == k->parent->parent->right) {
            u = k->parent->parent->left;
            
            if (u->color == RED) {
                u->color = BLACK;
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                k = k->parent->parent;
            } else {
                if (k == k->parent->left) {
                    k = k->parent;
                    rightRotate(tree, k);
                }
                
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                leftRotate(tree, k->parent->parent);
            }
        } else {
            u = k->parent->parent->right;
            
            if (u->color == RED) {
                u->color = BLACK;
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                k = k->parent->parent;
            } else {
                if (k == k->parent->right) {
                    k = k->parent;
                    leftRotate(tree, k);
                }
                
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                rightRotate(tree, k->parent->parent);
            }
        }
        
        if (k == tree->root)
            break;
    }
    
    tree->root->color = BLACK;
}

// Düğüm ekleme
void insertRB(RBTree* tree, int key, void* data) {
    RBNode* node = createRBNode(key, data, tree);
    if (!node) return;
    
    RBNode* y = tree->NIL;
    RBNode* x = tree->root;
    
    while (x != tree->NIL) {
        y = x;
        if (node->key < x->key)
            x = x->left;
        else
            x = x->right;
    }
    
    node->parent = y;
    
    if (y == tree->NIL)
        tree->root = node;
    else if (node->key < y->key)
        y->left = node;
    else
        y->right = node;
    
    // Ekleme sonrası düzeltme
    if (node->parent == tree->NIL) {
        node->color = BLACK;
        return;
    }
    
    if (node->parent->parent == tree->NIL)
        return;
    
    fixInsert(tree, node);
}

// Arama fonksiyonu
RBNode* searchRB(RBTree* tree, int key) {
    RBNode* current = tree->root;
    
    while (current != tree->NIL && key != current->key) {
        if (key < current->key)
            current = current->left;
        else
            current = current->right;
    }
    
    return (current == tree->NIL) ? NULL : current;
}

// Kırmızı-Siyah ağacın düğümlerini serbest bırakma
void freeRBTreeNodes(RBTree* tree, RBNode* node) {
    if (node != tree->NIL) {
        freeRBTreeNodes(tree, node->left);
        freeRBTreeNodes(tree, node->right);
        free(node);
    }
}

// Kırmızı-Siyah ağacı serbest bırakma
void freeRBTree(RBTree* tree) {
    if (tree) {
        freeRBTreeNodes(tree, tree->root);
        free(tree->NIL);
        free(tree);
    }
}