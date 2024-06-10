#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define MAX_CNT 2000
#define GRAPH struct graph


GRAPH{
    int nodeCnt;
    int edgeCnt;
    int *adjList;
};


// check the data while add it to the structure
int checkEdge(int start, int end, int nodeCnt) {
    if (start < 1 || start > nodeCnt ||
    end < 1 || end > nodeCnt){
        printf("bad vertex");
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

    if (edgeCnt < 0 || edgeCnt > (nodeCnt * (nodeCnt - 1) / 2)) {
        printf("bad number of edges");
        return 1;
    }

    return 0;
}


// create graph structure
GRAPH *create(GRAPH *graph, int edgeCnt, int nodeCnt) {
    graph = (GRAPH*)malloc(sizeof(GRAPH));
    int flag = 0, lines = 0, start, end;

    graph->edgeCnt = edgeCnt;
    graph->nodeCnt = nodeCnt;
    graph->adjList = (int*)calloc(nodeCnt * nodeCnt, sizeof(int));

    for (lines; lines < edgeCnt; lines++) {
        if (scanf("%d %d", &start, &end) != 2) {
            printf("bad number of lines");
            exit(0);
        }

        if (checkEdge(start, end, nodeCnt))
            exit(0);

        if (end == nodeCnt || start == nodeCnt)
            flag++;

        start--;
        end--;

        graph->adjList[nodeCnt * start + end] = 1;
    }

    return graph;
}

//topological sort algoritm
void topologicalSort(GRAPH *graph){
    int nodeCnt = graph->nodeCnt, front = 0, back = -1, ind = 0;
    int *stack = (int*)malloc(nodeCnt * sizeof(int)),
    *inDegree = (int*)calloc(nodeCnt, sizeof(int)),
    *result = (int*)malloc(nodeCnt * sizeof(int));

    for (int i = 0; i < nodeCnt; ++i)
        for (int j = 0; j < nodeCnt; ++j)
            if (graph->adjList[nodeCnt * i + j] != 0)
                inDegree[j]++;

    for (int i = 0; i < nodeCnt; ++i)
        if (inDegree[i] == 0)
            stack[++back] = i;

    while (front <= back){
        result[ind++] = stack[front++] + 1;
        
        for (int i = 0; i < nodeCnt; i++)
            if (graph->adjList[nodeCnt * stack[front - 1] + i]){
                inDegree[i]--;
                if (inDegree[i] == 0)
                    stack[++back] = i;
            }
    }

    if (ind != nodeCnt){
        printf("impossible to sort");
        exit(0);
    }

    for (int i = 0; i < nodeCnt; i++)
        printf("%d ", result[i]);

    free(inDegree);
    free(result);
    free(stack);
}


int main() {
    int nodeCnt, edgeCnt;
    GRAPH *graph = NULL;

    if (scanf("%d", &nodeCnt) < 1 || scanf("%d", &edgeCnt) < 1){
        printf("bad number of lines");
        return 0;
    }

    if (check(nodeCnt, edgeCnt))
        return 0;

    graph = create(graph, edgeCnt, nodeCnt);
    topologicalSort(graph);

    free(graph->adjList);
    free(graph);
    return 0;
}