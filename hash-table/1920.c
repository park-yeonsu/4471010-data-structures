#include <stdio.h>
#include <stdlib.h>

#define kInitialCapacity 100003
#define kLoadFactorThreshold 0.75

typedef struct Node {
    int key;
    struct Node* next;
} Node;

typedef struct HashTable {
    Node** buckets;
    int capacity;
    int size;
} HashTable;

int Hash(int key, int capacity) {
    return (key % capacity + capacity) % capacity;
}

void ResizeHashTable(HashTable* table) {
    int oldCapacity = table->capacity;
    Node** oldBuckets = table->buckets;

    table->capacity = 2 * oldCapacity;

    table->buckets = (Node**)calloc(table->capacity, sizeof(Node*));
    if (table->buckets == NULL) {
        table->buckets = oldBuckets; 
        table->capacity = oldCapacity;
        return; 
    }

    for (int i = 0; i < oldCapacity; i++) {
        Node* current = oldBuckets[i];
        while (current != NULL) {
            Node* nodeToRehash = current;
            current = current->next; 

            int newIndex = Hash(nodeToRehash->key, table->capacity);
            
            nodeToRehash->next = table->buckets[newIndex];
            table->buckets[newIndex] = nodeToRehash;
        }
    }
    
    free(oldBuckets);
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

HashTable* CreateHashTable() {
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    if (table == NULL) {
        exit(1);
    }

    table->capacity = kInitialCapacity;
    table->size = 0;
    
    table->buckets = (Node**)calloc(table->capacity, sizeof(Node*));
    if (table->buckets == NULL) {
        free(table);
        exit(1);
    }
    
    return table;
}

void Insert(HashTable* table, int key) {
    int index = Hash(key, table->capacity);
    
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
    table->size++;

    if ((double)table->size / table->capacity > kLoadFactorThreshold) {
        ResizeHashTable(table);
    }
}

int Search(HashTable* table, int key) {
    int index = Hash(key, table->capacity);
    
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
    if (table == NULL) return;

    for (int i = 0; i < table->capacity; i++) {
        Node* current = table->buckets[i];
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(table->buckets);
    free(table);
}

int main() {
    int N, M;
    HashTable* table = CreateHashTable();
    
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        int num;
        scanf("%d", &num);
        Insert(table, num);
    }
    
    scanf("%d", &M);
    for (int i = 0; i < M; i++) {
        int num;
        scanf("%d", &num);
        printf("%d\n", Search(table, num));
    }
    
    FreeHashTable(table);
    return 0;
}
