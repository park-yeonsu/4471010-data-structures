#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define kTableSize 100003

typedef struct Node {
    int key;
    struct Node* next;
} Node;

typedef struct HashTable {
    Node* buckets[kTableSize];
} HashTable;

int Hash(int key) {
    return (key % kTableSize + kTableSize) % kTableSize;
}

Node* CreateNode(int key) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        exit(1);
    }
    newNode->key = key;
    newNode->next = NULL;
    return newNode;
}

HashTable CreateHashTable() {
    HashTable table;
    
    for (int i = 0; i < kTableSize; i++) {
        table.buckets[i] = NULL;
    }
    
    return table;
}

void Insert(HashTable* table, int key) {
    int index = Hash(key);
    
    Node* current = table->buckets[index];
    while (current != NULL) {
        if (current->key == key) {
            return;
        }
        current = current->next;
    }
    
    Node* newNode = CreateNode(key);
    newNode->next = table->buckets[index];
    table->buckets[index] = newNode;
}

int Search(HashTable* table, int key) {
    int index = Hash(key);
    
    Node* current = table->buckets[index];
    while (current != NULL) {
        if (current->key == key) {
            return 1;
        }
        current = current->next;
    }
    
    return 0;
}

void FreeHashTable(HashTable* table) {
    for (int i = 0; i < kTableSize; i++) {
        Node* current = table->buckets[i];
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
        table->buckets[i] = NULL;
    }
}

int main() {
    int N, M;
    HashTable table = CreateHashTable();
    
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        int num;
        scanf("%d", &num);
        Insert(&table, num);
    }
    
    scanf("%d", &M);
    for (int i = 0; i < M; i++) {
        int num;
        scanf("%d", &num);
        printf("%d\n", Search(&table, num));
    }
    
    FreeHashTable(&table);
    return 0;
}
