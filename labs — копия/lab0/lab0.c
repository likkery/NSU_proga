#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define MAX_CNT 5000
#define GRAPH struct graph
#define DIJ struct dij
#define IND nodeCnt * min + j


GRAPH{
    int start;
    int end;
    long int *ways;
};


DIJ{
    int *visit;
    long long int *weight;
    int *way;
};


// initilization graph witj matrix of ways
GRAPH *initGraph(int nodeCnt) {
    GRAPH* graph =(GRAPH*)malloc(sizeof(GRAPH));
    graph -> ways = (long int*)malloc(nodeCnt * nodeCnt * sizeof(long int));
    
    for (int i = 0; i < nodeCnt * nodeCnt; i++) 
        graph -> ways[i] = 0;
    
    return graph;
}


// create graph structure
GRAPH *create(GRAPH *graph, int edgeCnt, int nodeCnt) {
    int edgeStart, edgeEnd, strCnt;
    long long int edgeLen;

    for (int i = 0; i < edgeCnt; i++) {
        scanf("%d %d %lld", &edgeStart, &edgeEnd, &edgeLen);

        if (edgeLen < 0 || edgeLen > INT_MAX) {
            printf("bad length");
            exit(0);
        }

        graph -> ways[nodeCnt * (edgeStart - 1) + (edgeEnd - 1)] = edgeLen;
        graph -> ways[nodeCnt * (edgeEnd - 1) + (edgeStart - 1)] = edgeLen;
        strCnt++;
    }

    if (strCnt < edgeCnt) {
        printf("bad number of lines");
        exit(0);
    }

    return graph;
}


// init struct for dijkstra algoritm
DIJ *createDij(int nodeCnt, int start) {
    DIJ *dij = (DIJ*)malloc(sizeof(DIJ));
    dij -> visit = (int*)malloc(nodeCnt * sizeof(int));
    dij -> weight = (long long int*)malloc(nodeCnt * sizeof(long long int));
    dij -> way = (int*)malloc(nodeCnt * sizeof(int));

    for (int i = 0; i < nodeCnt; i++) {
        dij -> weight[i] = LLONG_MAX;
        dij -> visit[i] = 0;
    }

    dij -> weight[start - 1] = 0;

    return dij;
}


// get way with min weight
int minWay(DIJ *dij, int nodeCnt) {
    long long int min = LLONG_MAX;
    int minInd;

    for (int i = 0; i < nodeCnt; i++) 
        if (dij -> visit[i] == 0 && dij -> weight[i] < min) {
            min = dij -> weight[i];
            minInd = i;
        }
        
    return minInd;
}


// find and rewrite destinations from the start
void dijkstra(DIJ *dij, GRAPH *graph, int start, int nodeCnt) {
    for (int i = 0; i < nodeCnt; i++) {
        int min = minWay(dij, nodeCnt);
        dij -> visit[min] = 1;
        for (int j = 0; j < nodeCnt; j++) {
            if (!dij -> visit[j] && graph -> ways[IND] &&
            dij -> weight[min] + graph -> ways[IND] < dij -> weight[j] &&
            dij -> weight[min] != LLONG_MAX) {
                dij -> weight[j] = dij -> weight[min] + graph -> ways[IND];
                dij -> way[j] = min;
            }
        }
    }
}


// print the needed data
void print(GRAPH *graph, DIJ *dij, int start, int end, int nodeCnt) {
    int flag = 0;
    
    // print first string
    for (int i = 0; i < nodeCnt; i++) {
        if (!dij -> visit[i])
            printf("oo ");
        else {
            if (dij -> weight[i] > INT_MAX)
                printf("INT_MAX+ ");
            else
                printf("%d ", dij -> weight[i]);
        }
    }
    printf("\n");

    // print second string
    // check for no path
    if (!dij -> visit[end - 1]) {
        printf("no path");
        return;
    }

    //chek for overflow
    for (int i = 0; i < nodeCnt; i++)
        if (dij -> weight[i] >= INT_MAX && dij -> weight[i] != LLONG_MAX)
            flag++;

    if (flag > 2 && dij -> weight[end - 1] > INT_MAX) {
        printf("overflow");
        return;
    }

    for (int i = end - 1; i != start - 1; i = dij -> way[i])
        printf("%d ", i + 1);
    printf("%d", start);
}


// check for errors constant data in the very beginning
int check(int nodeCnt, int start, int end, int edgeCnt){
    if (nodeCnt < 0 || nodeCnt > MAX_CNT) {
        printf("bad number of vertices");
        return 1;
    }

    if (edgeCnt < 0 || edgeCnt > (nodeCnt * (nodeCnt + 1) / 2)) {
        printf("bad number of edges");
        return 1;
    }

    if (start < 1 || end < 1 || start > nodeCnt || end > nodeCnt) {
        printf("bad vertex");
        return 1;
    }

    return 0;
}


// free memory
void freeMemory(GRAPH *graph, DIJ *dij) {
    free(dij -> visit);
    free(dij -> way);
    free(dij -> weight);
    free(dij);
    free(graph -> ways);
    free(graph);
}


int main() {
    int nodeCnt, start, end, edgeCnt, edgeLen;
    GRAPH *graph = NULL;
    DIJ *dij = NULL;
    
    scanf("%d", &nodeCnt);
    scanf("%d %d", &start, &end);
    scanf("%d", &edgeCnt);

    if (check(nodeCnt, start, end, edgeCnt))
        return 0;

    graph = initGraph(nodeCnt);
    graph = create(graph, edgeCnt, nodeCnt);
    dij = createDij(nodeCnt, start);
    dijkstra(dij, graph, start, nodeCnt);
    print(graph, dij, start, end, nodeCnt);

    freeMemory(graph, dij);
    return 0;
}