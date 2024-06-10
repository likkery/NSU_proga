#include <stdio.h>
#include <malloc.h>

enum {
    N_MAX = 5000,
    I_MAX = 2147483647,
};

typedef struct Item {
    int start;
    int end;
    int weight;
} Item;

void create_item(int start, int end, int weight, Item *item){
    item->end = end;
    item->start = start;
    item->weight = weight;
}

void swap_item(Item *a, Item *b){
    Item temp = *a;
    *a = *b;
    *b = temp;
}

void sorted(Item *a, int begin, int end){ //квик сорт. Располагаем в порядке возрастания
    int i = begin;
    int j = end;
    int pivot = a[(begin + end) / 2].weight;
    do {
        while (a[i].weight < pivot) i++;
        while (a[j].weight > pivot) j--;
        if (i <= j) {
            swap_item(&a[i], &a[j]);
            i++;
            j--;
        }
    } while (i < j);
    if (begin < j) sorted (a, begin, j);
    if (i < end) sorted (a, i, end);
}

int read_data(FILE *flIn, int *N, int *M){
    if (fscanf(flIn, "%d", N) != 1){
        printf("bad number of lines");
        return 1;
    }
    if (*N < 0 || *N > N_MAX){
        printf("bad number of vertices");
        return 1;
    }
    if (fscanf(flIn, "%d", M) != 1){
        printf("bad number of lines");
        return 1;
    }
    int maxi = ((*N + 1) / 2) * (*N);
    if (*M < 0 || *M > maxi){
        printf("bad number of edges");
        return 1;
    }
    if (*N == 0){
        printf("no spanning tree");
        return 1;
    }
    return 0;
}

int build_graph(FILE *fl, int N, int M, Item *item_list){
    int start, end;
    long long int weight;
    for (int i = 0; i < M; i++){
        if (fscanf(fl, "%d %d %lld", &start, &end, &weight) != 3){
            printf("bad number of lines");
            return 1;
        }
        if (start < 0 || start > N || end < 0 || end > N){
            printf("bad vertex");
            return 1;
        }
        if (weight < 0 || weight > I_MAX){
            printf("bad lenght");
            return 1;
        }
        create_item(start, end, (int) weight, &item_list[i]);
    }
    return 0;
}

int ver_in_trees(int trees[], int ver){ //проверка: принадлежит ли вершина уже какому либо дереву, если да, то возвращаем корень
    if (trees[ver] == ver) //верниша ver явл корнем дерева
        return ver;
    trees[ver] = ver_in_trees(trees, trees[ver]);
    return trees[ver];//иначе рекурсивно вызываем функцию для корневой
        //вершины, чтобы найти корень дерева
}//эта функция нужна будет для объядинения деревьев. Также она помогает проверить цикличность
//ведь если объединить деревья, где лежит одна и та же вершина, получится цикл.

void swap(int *a, int *b){
    int temp = *b;
    *b = *a;
    *a = temp;

}

void unite_trees(int start_node, int end_node, int trees[]){
    int start = ver_in_trees(trees, start_node);//функция находит корень для вершины start_node
    int end = ver_in_trees(trees, end_node);
    swap(&start, &end);
    if (start != end){
        trees[start] = end;//устанавливается связь между корнями путем присвоения одного корня в качестве другого
    }
}

int algorithm_kraskala(Item *item_list, char *marker, int N, int M){
    int trees[N];
    int index = 0;//для кол-ва вершин в остовном дереве
    int cost = 0;//для отслеживания общей суммы
    for (int i = 0; i < N; i++){
        trees[i] = i;
        marker[i] = i;
    }

    if (M > 0){
        sorted(item_list, 0, M - 1);//сортировка вершин по весу
    }

    for (int i = 0; i < M; i++){ //рассматриваем отсортированные ребра
        Item cur_item = item_list[i];//работа с текущим ребром(соединяющее вершины старт и энд)
        int start = cur_item.start;
        int end = cur_item.end;
        int weight = cur_item.weight;
        
        if (ver_in_trees(trees, start - 1) != ver_in_trees(trees, end - 1)){ //проверка: принадлежат ли вершины одному дереву
            cost += weight;
            unite_trees(start - 1, end - 1, trees);//нет? значит объединяем деревья
            item_list[index].start = start;//информация о новом ребере добавляется в массив
            item_list[index].end = end;
            marker[start - 1] = 0;//таким образом мы удаляем данную вершину из дерева.
            marker[end - 1] = 0;
            index++;
        }
    }
    return index;
}

int check_tree(char *marker, int N){//фукнция проверяет массив маркер на принадлежность каких-либо вершин к деревьям в графе
    for (int i = 0; i < N; i++){
        if (marker[i] != 0){ //если элемент не равен 0 - значит вершина i принадлежит какому то дереву
            return 1;//если хотя бы один элемент ненулевой, функция вернет значение 1
        }
    }
    return 0;
}


int main(){
    int N, M;
    FILE *fl = fopen("in.txt", "r");
    if (fl == NULL){
        return 0;
    }
    if (read_data(fl, &N, &M)){
        fclose(fl);
        return 0;
    }

    Item *item_list = malloc(sizeof(Item) * M);
    if (item_list == NULL){
        fclose(fl);
        return 0;
    }

    if (build_graph(fl, N, M, item_list)){
        free(item_list);
        fclose(fl);
        return 0;
    }

    char marker[N];
    int index = algorithm_kraskala(item_list, marker, N, M);
    int flag = check_tree(marker, N);

    if (flag && N != 1){ //нам нужны вершины без принадлежности к деревьям
        printf("no spanning tree\n");
    }
    else {
        for (int i = 0; i < index; i++){
            if (item_list[i].start > item_list[i].end)
                swap(&item_list[i].start, &item_list[i].end);
            printf("%d %d\n", item_list[i].start, item_list[i].end);
        }
    }
    free(item_list);
    fclose(fl);
    return 0;
}
