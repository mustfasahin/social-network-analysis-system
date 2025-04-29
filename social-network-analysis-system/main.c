#include "social_graph.h"

int main() {
    // Kullanıcı IDlerini indekse dönüştürmek için indeks sistemi
    int userIDToIndex[1000]; // Daha büyük bir ID aralığı için artırılabilir
    for (int i = 0; i < 1000; i++) {
        userIDToIndex[i] = -1; // Başlangıçta tüm IDler geçersiz
    }
    
    // Verileri dosyadan okuma veya manuel giriş
    // Örnek veriler:
    int userIDs[] = {101, 102, 103, 104, 105};
    int numUsers = 5;
    
    // ID'leri indekslere eşleştirme
    for (int i = 0; i < numUsers; i++) {
        userIDToIndex[userIDs[i]] = i;
    }
    
    // Graf oluşturma
    Graph* socialGraph = createGraph(numUsers);
    if (!socialGraph) {
        printf("Graf oluşturulamadı. Program sonlandırılıyor.\n");
        return 1;
    }
    
    // Arkadaşlık ilişkilerini ekleme
    addEdge(socialGraph, userIDToIndex[101], userIDToIndex[102]);
    addEdge(socialGraph, userIDToIndex[101], userIDToIndex[103]);
    addEdge(socialGraph, userIDToIndex[102], userIDToIndex[104]);
    addEdge(socialGraph, userIDToIndex[103], userIDToIndex[104]);
    addEdge(socialGraph, userIDToIndex[104], userIDToIndex[105]);
    
    // Kırmızı-Siyah ağaç oluşturma
    RBTree* userTree = initRBTree();
    if (!userTree) {
        printf("Kırmızı-Siyah ağaç oluşturulamadı. Program sonlandırılıyor.\n");
        freeGraph(socialGraph);
        return 1;
    }
    
    // Kullanıcıları ağaca ekleme
    for (int i = 0; i < numUsers; i++) {
        User* user = (User*)malloc(sizeof(User));
        if (!user) {
            printf("Kullanıcı için bellek ayrılamadı!\n");
            continue;
        }
        user->id = userIDs[i];
        sprintf(user->name, "User %d", userIDs[i]);
        insertRB(userTree, userIDs[i], user);
    }
    
    // Menü bazlı arayüz
    int choice;
    while (1) {
        printf("\n===== Sosyal Ağ Analizi =====\n");
        printf("1. Belirli mesafedeki arkadaşları bul\n");
        printf("2. Ortak arkadaşları bul\n");
        printf("3. Toplulukları tespit et\n");
        printf("4. Kullanıcının etki alanını hesapla\n");
        printf("5. Kullanıcı ara\n");
        printf("0. Çıkış\n");
        printf("Seçiminiz: ");
        scanf("%d", &choice);
        
        if (choice == 0) break;
        
        int userID, user2ID, distance;
        int resultSize;
        int* result;
        
        switch (choice) {
            case 1:
                printf("Kullanıcı ID: ");
                scanf("%d", &userID);
                printf("Mesafe: ");
                scanf("%d", &distance);
                
                if (userIDToIndex[userID] == -1) {
                    printf("Kullanıcı bulunamadı!\n");
                    break;
                }
                
                result = findFriendsAtDistance(socialGraph, userIDToIndex[userID], distance, &resultSize);
                if (!result) {
                    printf("Arkadaş bulma işlemi başarısız oldu!\n");
                    break;
                }
                
                printf("%d mesafedeki arkadaşlar:\n", distance);
                for (int i = 0; i < resultSize; i++) {
                    printf("Kullanıcı %d\n", userIDs[result[i]]);
                }
                
                free(result);
                break;
                
            case 2:
                printf("1. Kullanıcı ID: ");
                scanf("%d", &userID);
                printf("2. Kullanıcı ID: ");
                scanf("%d", &user2ID);
                
                if (userIDToIndex[userID] == -1 || userIDToIndex[user2ID] == -1) {
                    printf("Kullanıcı bulunamadı!\n");
                    break;
                }
                
                result = findCommonFriends(socialGraph, userIDToIndex[userID], userIDToIndex[user2ID], &resultSize);
                if (!result) {
                    printf("Ortak arkadaş bulma işlemi başarısız oldu!\n");
                    break;
                }
                
                printf("Ortak arkadaşlar:\n");
                for (int i = 0; i < resultSize; i++) {
                    printf("Kullanıcı %d\n", userIDs[result[i]]);
                }
                
                free(result);
                break;
                
            case 3: {
                int* community = (int*)malloc(numUsers * sizeof(int));
                if (!community) {
                    printf("Topluluk dizisi için bellek ayrılamadı!\n");
                    break;
                }
                
                int communityCount = detectCommunities(socialGraph, community);
                
                printf("Toplam %d topluluk tespit edildi:\n", communityCount);
                for (int c = 0; c < communityCount; c++) {
                    printf("Topluluk %d: ", c+1);
                    for (int i = 0; i < numUsers; i++) {
                        if (community[i] == c) {
                            printf("Kullanıcı %d ", userIDs[i]);
                        }
                    }
                    printf("\n");
                }
                
                free(community);
                break;
            }
                
            case 4:
                printf("Kullanıcı ID: ");
                scanf("%d", &userID);
                
                if (userIDToIndex[userID] == -1) {
                    printf("Kullanıcı bulunamadı!\n");
                    break;
                }
                
                int influence = calculateInfluence(socialGraph, userIDToIndex[userID]);
                printf("Kullanıcı %d'in etki alanı: %d kişi\n", userID, influence);
                break;
                
            case 5:
                printf("Aranacak Kullanıcı ID: ");
                scanf("%d", &userID);
                
                RBNode* foundNode = searchRB(userTree, userID);
                if (foundNode) {
                    User* user = (User*)foundNode->data;
                    printf("Kullanıcı bulundu: %s (ID: %d)\n", user->name, user->id);
                } else {
                    printf("Kullanıcı bulunamadı!\n");
                }
                break;
                
            default:
                printf("Geçersiz seçim!\n");
        }
    }
    
    // Temizlik
    // Kullanıcı belleğini serbest bırak
    for (int i = 0; i < numUsers; i++) {
        RBNode* current = searchRB(userTree, userIDs[i]);
        if (current) {
            free(current->data);
        }
    }
    
    freeRBTree(userTree);
    freeGraph(socialGraph);
    
    return 0;
}