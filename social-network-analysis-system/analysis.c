#include "social_graph.h"

// DFS ile belirli mesafedeki arkadaşları bulma yardımcı fonksiyonu
void DFSUtil(Graph* graph, int user, int distance, int maxDistance, int visited[], int result[], int* resultSize) {
    if (distance > maxDistance)
        return;
    
    visited[user] = 1;
    
    if (distance > 0 && distance <= maxDistance) {
        result[(*resultSize)++] = user;
    }
    
    AdjListNode* pCrawl = graph->array[user].head;
    while (pCrawl) {
        if (!visited[pCrawl->dest])
            DFSUtil(graph, pCrawl->dest, distance + 1, maxDistance, visited, result, resultSize);
        pCrawl = pCrawl->next;
    }
}

// Belirli mesafedeki arkadaşları bul
int* findFriendsAtDistance(Graph* graph, int user, int maxDistance, int* resultSize) {
    int* visited = (int*)calloc(graph->V, sizeof(int));
    if (!visited) {
        printf("Ziyaret dizisi için bellek ayrılamadı!\n");
        *resultSize = 0;
        return NULL;
    }
    
    int* result = (int*)malloc(graph->V * sizeof(int));
    if (!result) {
        printf("Sonuç dizisi için bellek ayrılamadı!\n");
        free(visited);
        *resultSize = 0;
        return NULL;
    }
    
    *resultSize = 0;
    
    DFSUtil(graph, user, 0, maxDistance, visited, result, resultSize);
    
    free(visited);
    return result;
}

// Ortak arkadaşları bulma
int* findCommonFriends(Graph* graph, int user1, int user2, int* resultSize) {
    int* friends1 = (int*)calloc(graph->V, sizeof(int));
    if (!friends1) {
        printf("Arkadaş dizisi 1 için bellek ayrılamadı!\n");
        *resultSize = 0;
        return NULL;
    }
    
    int* friends2 = (int*)calloc(graph->V, sizeof(int));
    if (!friends2) {
        printf("Arkadaş dizisi 2 için bellek ayrılamadı!\n");
        free(friends1);
        *resultSize = 0;
        return NULL;
    }
    
    int* common = (int*)malloc(graph->V * sizeof(int));
    if (!common) {
        printf("Ortak arkadaş dizisi için bellek ayrılamadı!\n");
        free(friends1);
        free(friends2);
        *resultSize = 0;
        return NULL;
    }
    
    *resultSize = 0;
    
    // Kullanıcı 1'in arkadaşlarını işaretle
    AdjListNode* pCrawl = graph->array[user1].head;
    while (pCrawl) {
        friends1[pCrawl->dest] = 1;
        pCrawl = pCrawl->next;
    }
    
    // Kullanıcı 2'nin arkadaşlarını kontrol et
    pCrawl = graph->array[user2].head;
    while (pCrawl) {
        friends2[pCrawl->dest] = 1;
        if (friends1[pCrawl->dest]) {
            common[(*resultSize)++] = pCrawl->dest;
        }
        pCrawl = pCrawl->next;
    }
    
    free(friends1);
    free(friends2);
    return common;
}

// Topluluk tespiti için yardımcı DFS
void communityDFS(Graph* graph, int user, int visited[], int community[], int communityID) {
    visited[user] = 1;
    community[user] = communityID;
    
    AdjListNode* pCrawl = graph->array[user].head;
    while (pCrawl) {
        if (!visited[pCrawl->dest])
            communityDFS(graph, pCrawl->dest, visited, community, communityID);
        pCrawl = pCrawl->next;
    }
}

// Tüm toplulukları tespit et
int detectCommunities(Graph* graph, int community[]) {
    int* visited = (int*)calloc(graph->V, sizeof(int));
    if (!visited) {
        printf("Ziyaret dizisi için bellek ayrılamadı!\n");
        return 0;
    }
    
    int communityCount = 0;
    
    for (int i = 0; i < graph->V; i++) {
        if (!visited[i]) {
            communityDFS(graph, i, visited, community, communityCount);
            communityCount++;
        }
    }
    
    free(visited);
    return communityCount;
}

// Kullanıcının etki alanını hesapla
int calculateInfluence(Graph* graph, int user) {
    int* visited = (int*)calloc(graph->V, sizeof(int));
    if (!visited) {
        printf("Ziyaret dizisi için bellek ayrılamadı!\n");
        return 0;
    }
    
    int influence = 0;
    
    // BFS kullanarak etki alanını hesapla
    int* queue = (int*)malloc(graph->V * sizeof(int));
    if (!queue) {
        printf("Kuyruk için bellek ayrılamadı!\n");
        free(visited);
        return 0;
    }
    
    int front = 0, rear = 0;
    
    visited[user] = 1;
    queue[rear++] = user;
    
    while (front < rear) {
        int current = queue[front++];
        
        AdjListNode* pCrawl = graph->array[current].head;
        while (pCrawl) {
            if (!visited[pCrawl->dest]) {
                visited[pCrawl->dest] = 1;
                queue[rear++] = pCrawl->dest;
                influence++;
            }
            pCrawl = pCrawl->next;
        }
    }
    
    free(visited);
    free(queue);
    return influence;
}