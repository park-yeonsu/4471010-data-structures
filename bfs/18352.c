#include <stdio.h>
#include <stdlib.h>

typedef struct AdjListNode {
    int dest_city;
    struct AdjListNode* next_node;
} AdjListNode;

typedef struct AdjList {
    AdjListNode* head_node;
} AdjList;

typedef struct Graph {
    int num_vertices;
    AdjList* adj_lists_array;
} Graph;

AdjListNode* NewAdjListNode(int dest_city) {
    AdjListNode* new_node = (AdjListNode*)malloc(sizeof(AdjListNode));
    if (new_node == NULL) {
        perror("Failed to allocate memory for AdjListNode");
        exit(EXIT_FAILURE);
    }
    new_node->dest_city = dest_city;
    new_node->next_node = NULL;
    return new_node;
}

Graph* CreateGraph(int num_vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    if (graph == NULL) {
        perror("Failed to allocate memory for Graph");
        exit(EXIT_FAILURE);
    }
    graph->num_vertices = num_vertices;
    graph->adj_lists_array = (AdjList*)malloc((num_vertices + 1) * sizeof(AdjList));
    if (graph->adj_lists_array == NULL) {
        free(graph);
        perror("Failed to allocate memory for AdjList array");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i <= num_vertices; ++i) {
        graph->adj_lists_array[i].head_node = NULL;
    }
    return graph;
}

void AddEdge(Graph* graph, int src_city, int dest_city) {
    AdjListNode* new_node = NewAdjListNode(dest_city);
    new_node->next_node = graph->adj_lists_array[src_city].head_node;
    graph->adj_lists_array[src_city].head_node = new_node;
}

void FreeGraph(Graph* graph) {
    if (graph == NULL) return;
    for (int i = 0; i <= graph->num_vertices; ++i) {
        AdjListNode* current_node = graph->adj_lists_array[i].head_node;
        while (current_node != NULL) {
            AdjListNode* temp_node = current_node;
            current_node = current_node->next_node;
            free(temp_node);
        }
    }
    if (graph->adj_lists_array != NULL) {
        free(graph->adj_lists_array);
    }
    free(graph);
}

typedef struct Queue {
    int* items_array;
    int capacity;
    int current_size;
    int front_index;
    int rear_index;
} Queue;

Queue* CreateQueue(int capacity) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    if (queue == NULL) {
        perror("Failed to allocate memory for Queue");
        exit(EXIT_FAILURE);
    }
    queue->items_array = (int*)calloc(capacity, sizeof(int));
    if (queue->items_array == NULL) {
        free(queue);
        perror("Failed to allocate memory for Queue items_array");
        exit(EXIT_FAILURE);
    }
    queue->capacity = capacity;
    queue->current_size = 0;
    queue->front_index = 0;
    queue->rear_index = -1;
    return queue;
}

void Enqueue(Queue* queue, int item) {
    if (queue->current_size == queue->capacity) {
        fprintf(stderr, "Queue overflow\n");
        return;
    }
    queue->rear_index = (queue->rear_index + 1) % queue->capacity;
    queue->items_array[queue->rear_index] = item;
    queue->current_size++;
}

int Dequeue(Queue* queue) {
    if (queue->current_size == 0) {
        fprintf(stderr, "Queue underflow\n");
        exit(EXIT_FAILURE);
    }
    int item = queue->items_array[queue->front_index];
    queue->front_index = (queue->front_index + 1) % queue->capacity;
    queue->current_size--;
    return item;
}

int IsQueueEmpty(Queue* queue) {
    return queue->current_size == 0;
}

void FreeQueue(Queue* queue) {
    if (queue == NULL) return;
    if (queue->items_array != NULL) {
        free(queue->items_array);
    }
    free(queue);
}

int main() {
    int num_cities, num_roads, target_distance, start_city_id;
    scanf("%d %d %d %d", &num_cities, &num_roads, &target_distance, &start_city_id);

    Graph* road_network = CreateGraph(num_cities);

    for (int i = 0; i < num_roads; ++i) {
        int city_a, city_b;
        scanf("%d %d", &city_a, &city_b);
        AddEdge(road_network, city_a, city_b);
    }

    int* distances = (int*)malloc((num_cities + 1) * sizeof(int));
    if (distances == NULL) {
        FreeGraph(road_network);
        perror("Failed to allocate memory for distances array");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i <= num_cities; ++i) {
        distances[i] = -1;
    }

    Queue* city_queue = CreateQueue(num_cities);

    distances[start_city_id] = 0;
    Enqueue(city_queue, start_city_id);

    while (!IsQueueEmpty(city_queue)) {
        int current_city_id = Dequeue(city_queue);

        AdjListNode* current_neighbor_node = road_network->adj_lists_array[current_city_id].head_node;
        while (current_neighbor_node != NULL) {
            int neighbor_city_id = current_neighbor_node->dest_city;
            if (distances[neighbor_city_id] == -1) {
                distances[neighbor_city_id] = distances[current_city_id] + 1;
                Enqueue(city_queue, neighbor_city_id);
            }
            current_neighbor_node = current_neighbor_node->next_node;
        }
    }

    int found_city_at_target_distance = 0;

    for (int i = 1; i <= num_cities; ++i) {
        if (distances[i] == target_distance) {
            printf("%d\n", i);
            found_city_at_target_distance = 1;
        }
    }

    if (found_city_at_target_distance == 0) {
        printf("-1\n");
    }

    FreeGraph(road_network);
    free(distances);
    FreeQueue(city_queue);

    return 0;
}
