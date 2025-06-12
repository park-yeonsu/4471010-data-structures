#include <stdio.h>
#include <stdlib.h>

const char WHITE = 'W';
const char GRAY = 'G';
const char BLACK = 'B';
const int NIL = 0;

typedef struct AdjListNode {
    int dest_computer;
    struct AdjListNode* next_node;
} AdjListNode;

typedef struct AdjList {
    AdjListNode* head_node;
} AdjList;

typedef struct Graph {
    int num_computers;
    AdjList* adj_lists_array;
} Graph;

int time_stamp;
char* color;
int* pred;
int* d;
int* f;

AdjListNode* NewAdjListNode(int dest_computer) {
    AdjListNode* new_node = (AdjListNode*)malloc(sizeof(AdjListNode));
    if (new_node == NULL) {
        perror("Failed to allocate memory for AdjListNode");
        exit(EXIT_FAILURE);
    }
    new_node->dest_computer = dest_computer;
    new_node->next_node = NULL;
    return new_node;
}

Graph* CreateGraph(int num_computers) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    if (graph == NULL) {
        perror("Failed to allocate memory for Graph");
        exit(EXIT_FAILURE);
    }
    graph->num_computers = num_computers;
    graph->adj_lists_array = (AdjList*)malloc((num_computers + 1) * sizeof(AdjList));
    if (graph->adj_lists_array == NULL) {
        free(graph);
        perror("Failed to allocate memory for AdjList array");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i <= num_computers; ++i) {
        graph->adj_lists_array[i].head_node = NULL;
    }
    return graph;
}

void AddEdge(Graph* graph, int src_computer, int dest_computer) {
    AdjListNode* new_node1 = NewAdjListNode(dest_computer);
    new_node1->next_node = graph->adj_lists_array[src_computer].head_node;
    graph->adj_lists_array[src_computer].head_node = new_node1;

    AdjListNode* new_node2 = NewAdjListNode(src_computer);
    new_node2->next_node = graph->adj_lists_array[dest_computer].head_node;
    graph->adj_lists_array[dest_computer].head_node = new_node2;
}

void FreeGraph(Graph* graph) {
    if (graph == NULL) return;
    for (int i = 0; i <= graph->num_computers; ++i) {
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

void DFS_VISIT(Graph* graph, int u) {
    time_stamp = time_stamp + 1;
    d[u] = time_stamp;
    color[u] = GRAY;

    AdjListNode* v_node = graph->adj_lists_array[u].head_node;
    while (v_node != NULL) {
        int v = v_node->dest_computer;
        if (color[v] == WHITE) {
            pred[v] = u;
            DFS_VISIT(graph, v);
        }
        v_node = v_node->next_node;
    }

    color[u] = BLACK;
    time_stamp = time_stamp + 1;
    f[u] = time_stamp;
}

int main() {
    int n;
    scanf("%d", &n);

    int m;
    scanf("%d", &m);

    Graph* network_graph = CreateGraph(n);

    for (int i = 0; i < m; ++i) {
        int comp1, comp2;
        scanf("%d %d", &comp1, &comp2);
        AddEdge(network_graph, comp1, comp2);
    }

    color = (char*)malloc((n + 1) * sizeof(char));
    pred = (int*)malloc((n + 1) * sizeof(int));
    d = (int*)malloc((n + 1) * sizeof(int));
    f = (int*)malloc((n + 1) * sizeof(int));

    if (color == NULL || pred == NULL || d == NULL || f == NULL) {
        perror("Failed to allocate memory for DFS arrays");
        FreeGraph(network_graph);
        free(color); free(pred); free(d); free(f);
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i <= n; ++i) {
        color[i] = WHITE;
        pred[i] = NIL;
    }
    time_stamp = 0;

    if (color[1] == WHITE) {
        DFS_VISIT(network_graph, 1);
    }

    int infected_count = 0;
    for (int i = 1; i <= n; ++i) {
        if (color[i] != WHITE) {
            infected_count++;
        }
    }
    
    printf("%d\n", infected_count - 1);

    FreeGraph(network_graph);
    free(color);
    free(pred);
    free(d);
    free(f);

    return 0;
}
