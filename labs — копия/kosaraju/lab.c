#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define MAX_CNT 2000
#define GRAPH struct graph
#define STACK struct stack


GRAPH{
    int nodeCnt;
    int edgeCnt;
    int *adjList;
    int *revAdjList;
    int *visited;
};


STACK{
    int value;
    struct stack *next;
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


// init stack
STACK* createStack(){
    STACK *elem = (STACK*)malloc(sizeof(STACK));
    elem->next = NULL;
    return elem;
}


// push new element to stack
void push(STACK *stack, int value){
    STACK *elem = (STACK*)malloc(sizeof(STACK));
    elem->value = value;
    elem->next = stack->next;
    stack->next = elem;
}


// check if the stack is empty
int empty(STACK *stack){
    return stack->next == NULL;
}


// pop last elen from stack
int pop(STACK *stack){
    if (empty(stack))
        return -1;
    
    STACK *elem = stack->next;
    int value = elem->value;
    stack->next = elem->next;

    free(elem);
    return value;
}


// create graph structure
GRAPH *create(GRAPH *graph, int edgeCnt, int nodeCnt) {
    graph = (GRAPH*)malloc(sizeof(GRAPH));
    int flag = 0, lines = 0, start, end;

    graph->edgeCnt = edgeCnt;
    graph->nodeCnt = nodeCnt;
    graph->adjList = (int*)calloc(nodeCnt * nodeCnt, sizeof(int));
    graph->revAdjList = (int*)calloc(nodeCnt * nodeCnt, sizeof(int));
    graph->visited = (int*)calloc(nodeCnt, sizeof(int));

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
        graph->revAdjList[nodeCnt * end + start] = 1;
    }

    return graph;
}


// dfs in right order, fill stack
void dfs(GRAPH *graph, STACK *stack, int index){
    int nodeCnt = graph->nodeCnt;
    graph->visited[index] = 1;

    for (int i = 0; i < nodeCnt; i++)
        if (graph->adjList[index * nodeCnt + i] && !graph->visited[i])
            dfs(graph, stack, i);
    
    push(stack, index);
}


// second dfs, find strong components and mark them with flags
void revDfs(GRAPH *graph, int index, int flag){
    int nodeCnt = graph->nodeCnt;
    graph->visited[index] = flag;

    for (int i = 0; i < nodeCnt; i++)
        if (graph->revAdjList[index * nodeCnt + i] && graph->visited[i] == 0)
            revDfs(graph, i, flag);
}


//kosaraju algoritm
void kosaraju(GRAPH *graph){
    int flag = 0, node;
    STACK *stack = createStack();

    for (int i = 0; i < graph->nodeCnt; i++)
        if (!graph->visited[i])
            dfs(graph, stack, i);
    
    for (int i = 0; i < graph->nodeCnt; i++)
        graph->visited[i] = 0;

    while(!empty(stack)){
        node = pop(stack);
        if (!graph->visited[node])
            revDfs(graph, node, ++flag);
    }
    
    printf("%d\n", flag);
    for (int i = 1; i < flag + 1; i++){
        for (int j = 0; j < graph->nodeCnt; j++)
            if (graph->visited[j] == i)
                printf("%d ", j + 1);
        printf("\n");
    }
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
    kosaraju(graph);

    free(graph->adjList);
    free(graph);
    return 0;
}