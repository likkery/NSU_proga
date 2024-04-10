#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define MAX_CNT 5000
#define GRAPH struct graph


GRAPH{
    int start;
    int end;
    long long int weight;
};


// check the data while add it to the structure
int checkEdge(GRAPH edge, int nodeCnt) {
    if (edge.start < 1 || edge.start > nodeCnt ||
    edge.end < 1 || edge.end > nodeCnt){
        printf("bad vertex");
        return 1;
    }

    if (edge.weight < 0 || edge.weight > INT_MAX){
        printf("bad length");
        return 1;
    }

    return 0;
}


// comparator for qsort
int edgeCompare(const void* first, const void* second){
    return ((GRAPH*)first) -> weight - ((GRAPH*)second) -> weight;
}


//find parent of node
int findParent(int node, int parent[]){
    if (parent[node] == -1)
        return node;
    return findParent(parent[node], parent);
}


// create graph structure
GRAPH *create(GRAPH *edge, int edgeCnt, int nodeCnt) {
    edge = (GRAPH*)malloc(edgeCnt * sizeof(GRAPH));
    int flag = 0, lines = 0;

    for (lines; lines < edgeCnt; lines++) {
        if (scanf("%d %d %lld", &edge[lines].start, &edge[lines].end,
        &edge[lines].weight) != 3) {
            printf("bad number of lines");
            exit(0);
        }

        if (checkEdge(edge[lines], nodeCnt))
            exit(0);

        if (edge[lines].end == nodeCnt || edge[lines].start == nodeCnt)
            flag++;

        edge[lines].start--;
        edge[lines].end--;
    }

    if (flag == 0 && nodeCnt != 1){
        printf("no spanning tree");
        exit(0);
    }

    return edge;
}


// check for errors in the constant data in the very beginning
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
// swap nodes
void swap (GRAPH *a, GRAPH *b) {
    GRAPH c = *a;
    *a = *b;
    *b = c;
}
// partition for quicksort
int partition (GRAPH* arr, int low, int hight) {
    int mid = arr[(low + hight) / 2].weight;
    int i = low, j = hight;
    while (1) {
        while (arr[i].weight < mid)
            i++;
        while (arr[j].weight > mid)
            j--;
        if (i >= j) {
            return j;
        }
        swap(&arr[i++], &arr[j--]);
    }
}

void quicksort (GRAPH* arr, int low, int hight) {
    if (low < hight) {
        int part = partition(arr, low, hight);
        quicksort(arr, low, part);
        quicksort(arr, part + 1, hight);
    }
}


// kruskal algoritm
void kruskal(GRAPH* edge, int edgeCnt, int nodeCnt){
    int edges = 0, start, end,
    *parents = (int*)malloc(nodeCnt * sizeof(int));
    GRAPH* frame = (GRAPH*)malloc(nodeCnt * sizeof(GRAPH));
    quicksort(edge, 0, edgeCnt - 1);

    for (int i = 0; i < nodeCnt; i++)
        parents[i] = -1;

    for (int i = 0; i < edgeCnt && edges < nodeCnt;){
        GRAPH current = edge[i++];
        start = findParent(current.start, parents);
        end = findParent(current.end, parents);

        if (start != end){
            frame[edges++] = current;
            parents[start] = end;
        }
    }

    if (edges < nodeCnt - 1)
        printf("no spanning tree");
    else
        for (int i = 0; i < nodeCnt - 1; i++) {
            if (frame[i].start < frame[i].end)
                printf("%d %d\n", frame[i].start + 1, frame[i].end + 1);
            else
                printf("%d %d\n", frame[i].end + 1, frame[i].start + 1);
        }

    free(parents);
    free(frame);
}


int main() {
    int nodeCnt, edgeCnt, edgeLen;
    GRAPH *edge = NULL;

    scanf("%d", &nodeCnt);
    scanf("%d", &edgeCnt);

    if (check(nodeCnt, edgeCnt))
        return 0;

    edge = create(edge, edgeCnt, nodeCnt);
    kruskal(edge, edgeCnt, nodeCnt);

    free(edge);
    return 0;
}
