#include <stdio.h>
#include <stdlib.h>

#define GRAPH struct graph

// check dfs, список смежности и поиски в глубину в ширину

GRAPH{
    int nodeCnt;
    int *list;
    int time;
    int flag;
};

void dfs(GRAPH *graph, int *visited, int nodePrev, int nodeCur, int zoo) {
    int count = 0;
    zoo++;
    visited[nodeCur] = 1;
    graph[nodeCur].flag = graph[nodeCur].time = zoo;
    for (int i = 0; i < graph->nodeCnt; i++) {
        if (visited[i])
            graph[nodeCur].flag = min(graph[nodeCur].flag, graph[i].time);
        else {
            dfs(graph, visited, i, nodeCur, zoo);
            count++;
            graph[nodeCur].flag = min(graph[nodeCur].flag, graph[i].time);
            if (nodePrev != -1 && graph[i].flag >= graph[nodeCur].time)
                printf("%d is cutpoint", nodeCur);
        } 
    }

    if (nodePrev == -1 && count >= 2)
        printf("%d is cutpoint", nodeCur);
}


void findCutpoint(GRAPH *graph, int *visited, int zoo){
    for (int i = 0; i < graph->nodeCnt; i++)
        if (!visited[i])
            dfs(graph, visited, -1, i, zoo);
}