#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct node {
    int value;
    struct node *next;
} Node;

typedef struct graph {
    Node **vet; //List vector
    int vertex; //Number of vertex
    int edges;  //Number of edges
} *Graph;


Graph graph_boot(int num_vertex) {
    Graph G = malloc(sizeof (*G));
    G->vertex = num_vertex;
    G->edges = 0;

    G->vet = malloc(num_vertex * sizeof(Node*));
    for (int i = 0; i < num_vertex; i++) 
        G->vet[i] = NULL;
    
    return G;
}

void edge_insert(Graph G, int i, int j) {
    Node *newI = malloc(sizeof(Node));
    newI->value = j;
    newI->next = G->vet[i];
    G->vet[i] = newI;
    G->edges++;
}

void print_graph(Graph G, int target) {
    for (int i = 0; i < G->vertex; i++) {
        Node *aux = G->vet[i];
        if (i == target)
            printf("[*]->");
        else
            printf("[%c]->",i+65);
        while (aux) {
            if (aux->value == target)
                printf("(*)->");
            else
                printf("(%c)->",aux->value+65);
            aux = aux->next;
        }
        printf("NULL\n");
    }
}

void release_graph(Graph G) {
    for (int i = 0; i < G->vertex; i++) {
        Node *aux = G->vet[i];
        while (aux) {
            Node *del = aux;
            aux = aux->next;
            free(del);
        }
        G->vet[i] = NULL;
    }
    free(G->vet);
    G->vet = NULL;
    free(G);
}

int dfs(Graph G, int start, int target, int *visited) {
    if (start == target)
        return 0;

    visited[start] = 1;

    Node *adjacent = G->vet[start];
    int min_distance = G->vertex+1;

    while (adjacent) {
        int neighbor = adjacent->value;

        if (!visited[neighbor]) {
            int distance = 1 + dfs(G, neighbor, target, visited);

            if (distance < min_distance)
                min_distance = distance;
        }
        adjacent = adjacent->next;
    }
    
    visited[start] = 0;
    return min_distance;
}

int shortest_path(Graph G, int start, int target) {
    int *visited = calloc(G->vertex, sizeof(int));

    int shortest = dfs(G, start, target, visited);

    free(visited);

    if (shortest == G->vertex+1)
        return -1;
    else
        return shortest;
}

void search(Graph G, int start, int target, int end) {
    int path1 = shortest_path(G, start, target);
    int path2 = shortest_path(G, target, end);
    
    if (path1 == -1 || path2 == -1) {
        printf("\nPath not found\n");
        return;
    }
    
    printf("\nMinimum points to pick the cheese and leave the maze: %d\n", path1+path2+2);
}

int main() {

    int num_vertex, num_edges, start, end, target;

    scanf("%d %d", &num_vertex, &num_edges);
    
    target = num_vertex-1;
    
    Graph graph = graph_boot(num_vertex);

    for (int i = 0; i < num_edges; i++) {
        char string1[8], string2[8];
        
        scanf("%s %s", string1, string2);

        for (int i = 0; string1[i] != '\0'; i++) {
            string1[i] = toupper(string1[i]);
        }

        for (int i = 0; string2[i] != '\0'; i++) {
            string2[i] = toupper(string2[i]);
        }

        if (strcmp(string1, "ENTRADA")== 0)
            start = string2[0]-'A';
        else if (strcmp(string2, "ENTRADA") == 0)
            start = string1[0]-'A';
        else if (strcmp(string1, "SAIDA") == 0)
            end = string2[0]-'A';
        else if (strcmp(string2, "SAIDA") == 0)
            end = string1[0]-'A';
        else {
            if (string1[0] == '*')
                edge_insert(graph, target, string2[0]-65);
            else if (string2[0] == '*')
                edge_insert(graph, string1[0]-'A', target);
            else
                edge_insert(graph, string1[0]-'A', string2[0]-'A');
        }
    }

    search(graph, start, target, end);
    print_graph(graph, target);
    release_graph(graph);
    
    return 0;
}