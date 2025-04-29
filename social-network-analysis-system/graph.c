#include "social_graph.h"

// Yeni graf oluşturma
Graph* createGraph(int V) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    if (!graph) {
        printf("Graf için bellek ayrılamadı!\n");
        return NULL;
    }
    
    graph->V = V;
    graph->array = (AdjList*)malloc(V * sizeof(AdjList));
    if (!graph->array) {
        printf("Graf dizisi için bellek ayrılamadı!\n");
        free(graph);
        return NULL;
    }
    
    for (int i = 0; i < V; i++)
        graph->array[i].head = NULL;
    
    return graph;
}

// Grafa kenar ekleme (yönsüz graf için)
void addEdge(Graph* graph, int src, int dest) {
    // Src -> Dest
    AdjListNode* newNode = (AdjListNode*)malloc(sizeof(AdjListNode));
    if (!newNode) {
        printf("Kenar düğümü için bellek ayrılamadı!\n");
        return;
    }
    
    newNode->dest = dest;
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
    
    // Dest -> Src (yönsüz graf için)
    newNode = (AdjListNode*)malloc(sizeof(AdjListNode));
    if (!newNode) {
        printf("Kenar düğümü için bellek ayrılamadı!\n");
        return;
    }
    
    newNode->dest = src;
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

// Graf yapısını serbest bırak
void freeGraph(Graph* graph) {
    if (graph) {
        for (int i = 0; i < graph->V; i++) {
            AdjListNode* current = graph->array[i].head;
            while (current) {
                AdjListNode* temp = current;
                current = current->next;
                free(temp);
            }
        }
        free(graph->array);
        free(graph);
    }
}