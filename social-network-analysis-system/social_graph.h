#ifndef SOCIAL_GRAPH_H
#define SOCIAL_GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Kullanıcı yapısı
typedef struct User {
    int id;
    char name[50];
    // Diğer kullanıcı bilgileri eklenebilir
} User;

// ---------- Graf Yapıları ----------

// Graf için komşuluk listesi düğümü
typedef struct AdjListNode {
    int dest;
    struct AdjListNode* next;
} AdjListNode;

// Komşuluk listesi
typedef struct AdjList {
    struct AdjListNode* head;
} AdjList;

// Graf yapısı
typedef struct Graph {
    int V; // Düğüm sayısı
    struct AdjList* array;
} Graph;

// Graf fonksiyonları
Graph* createGraph(int V);
void addEdge(Graph* graph, int src, int dest);
void freeGraph(Graph* graph);

// ---------- Kırmızı-Siyah Ağaç Yapıları ----------

enum Color { RED, BLACK };

typedef struct RBNode {
    int key;            // Kullanıcı ID
    void* data;         // Kullanıcı verisi (User yapısı)
    enum Color color;
    struct RBNode *left, *right, *parent;
} RBNode;

typedef struct {
    RBNode* root;
    RBNode* NIL;  // Sentinel node
} RBTree;

// Kırmızı-Siyah ağaç fonksiyonları
RBTree* initRBTree();
void insertRB(RBTree* tree, int key, void* data);
RBNode* searchRB(RBTree* tree, int key);
void freeRBTree(RBTree* tree);

// ---------- Analiz Fonksiyonları ----------

// DFS ile belirli mesafedeki arkadaşları bulma
int* findFriendsAtDistance(Graph* graph, int user, int maxDistance, int* resultSize);
// Ortak arkadaşları bulma
int* findCommonFriends(Graph* graph, int user1, int user2, int* resultSize);
// Topluluk tespiti
int detectCommunities(Graph* graph, int community[]);
// Etki alanı hesaplama
int calculateInfluence(Graph* graph, int user);

#endif // SOCIAL_GRAPH_H