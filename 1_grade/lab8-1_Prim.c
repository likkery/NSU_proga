#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define MAX_CNT 5000
#define GRAPH struct graph
#define MIN(i, j) (((i) < (j)) ? (i) : (j))


GRAPH{
    int nodeCnt;
    int edgeCnt;
    long long int *weight;
};


// check the data while add it to the structure
int checkEdge(int start, int end, int weight, int nodeCnt) {
    if (start < 1 || start > nodeCnt ||
    end < 1 || end > nodeCnt){
        printf("bad vertex");
        return 1;
    }

    if (weight < 0 || weight > INT_MAX){
        printf("bad length");
        return 1;
    }

    return 0;
}


// check for errors constant data in the very beginning
int check(int nodeCnt, int edgeCnt){
    if (nodeCnt < 0 || nodeCnt > MAX_CNT) {
        printf("bad number of vertices");
        return 1;
    }

    if (edgeCnt < 0 || edgeCnt > (nodeCnt * (nodeCnt + 1) / 2)) {
        printf("bad number of edges");
        return 1;
    }

    return 0;
}


// create graph structure
GRAPH *create(GRAPH *graph, int edgeCnt, int nodeCnt) {
    graph = (GRAPH*)malloc(sizeof(GRAPH));
    int flag = 0, lines = 0, start, end;
    long long int weight;

    graph->edgeCnt = edgeCnt;
    graph->nodeCnt = nodeCnt;
    graph->weight = (long long int*)calloc(nodeCnt * nodeCnt, 
    sizeof(long long int));

    for (lines; lines < edgeCnt; lines++) {
        if (scanf("%d %d %lld", &start, &end, &weight) != 3) {
            printf("bad number of lines");
            exit(0);
        }

        if (checkEdge(start, end, weight, nodeCnt))
            exit(0);

        if (end == nodeCnt || start == nodeCnt)
            flag++;

        start--;
        end--;

        graph->weight[nodeCnt * start + end] = weight;
        graph->weight[nodeCnt * end + start] = weight;
    }

    if (flag == 0 && nodeCnt != 1){
        printf("no spanning tree");
        exit(0);
    }

    return graph;
}


//free all structures
void freeMemory(int *visited, int *frame, int *minEdges, GRAPH *graph){
    free(visited);
    free(frame);
    free(minEdges);
    free(graph->weight);
    free(graph);
}


// find next min edge
int minEdge(GRAPH *graph, int *visited, int *minEdge){
    int min = INT_MAX, minInd;

    for (int i = 0; i < graph->nodeCnt; i++)
        if (!visited[i] && minEdge[i] < min) {
            min = minEdge[i];
            minInd = i;
        }

    return minInd;
}


// prim algoritm
void prim(GRAPH* graph, int nodeCnt){
    int *visited = (int*)malloc(nodeCnt * sizeof(int)),
    *minEdges = (int*)malloc(nodeCnt * sizeof(int)),
    *frame = (int*)malloc(nodeCnt * sizeof(int));

    for (int i = 0; i < nodeCnt; i++){
        visited[i] = 0;
        minEdges[i] = INT_MAX;
        frame[i] = -1;
    }

    minEdges[0] = 0;

    for (int i = 0; i < nodeCnt; i++) {
        int min = minEdge(graph, visited, minEdges);
        visited[min] = 1;

        for (int j = 0; j < nodeCnt; j++){
            if (!visited[j] && graph->weight[nodeCnt * min + j] 
            && graph->weight[nodeCnt * min + j] < minEdges[j]){
                frame[j] = min + 1;
                minEdges[j] = graph->weight[nodeCnt * min + j];
            }
        }
    }

    for (int i = nodeCnt; i > 0; i--)
        if (minEdges[i] == INT_MAX){
            printf("no spanning tree");
            freeMemory(visited, frame, minEdges, graph);
            exit(0);
        }

    for (int i = 1; i < nodeCnt; i++){
        if (frame[i] + 1 < i + 1)
            printf("%d %d\n", frame[i], i + 1);
        else
            printf("%d %d\n", i + 1, frame[i]);
    }

    freeMemory(visited, frame, minEdges, graph);
}


int main() {
    int nodeCnt, edgeCnt, edgeLen;
    GRAPH *graph = NULL;

    scanf("%d", &nodeCnt);
    scanf("%d", &edgeCnt);

    if (check(nodeCnt, edgeCnt))
        return 0;

    graph = create(graph, edgeCnt, nodeCnt);
    prim(graph, nodeCnt);

    free(graph);
    return 0;
}
