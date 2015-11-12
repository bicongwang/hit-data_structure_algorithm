#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define INFINITY INT_MAX   // assign infinity the max int.
#define TRUE 1
#define FALSE 0            // boolean

typedef struct vertex
{
    int identifier;
    int distance;
    struct vertex* next;
} vertex;                         // create for every vertex.

typedef struct MarkVertex
{
    int identifier;
    int mark;
    int distance;
    int previous;
} MarkVertex;                     // create for the mark array for dijkstra.

int findMinIndex(MarkVertex* mark_vertex,int n);
void freeTable(vertex* table,int n);
void initial(MarkVertex* mark_vertex,int n);
void printAllMinDistance(vertex* table,int n);
void calculateMinDistance(vertex* table,MarkVertex* mark_vertex,int index,int n);
void printTrace(MarkVertex* mark_vertex,int identifier);
vertex* createTable(int* adj_matrix,int n);

int main()
{
    int n;
    int i,j;
    printf("How many vertexes in the graph?\n");
    scanf("%d",&n);
    printf("Please input the adjacent matrix of the directed graph:\n");
    int* adj_matrix = (int*)malloc(sizeof(int)*n*n);
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            scanf("%d",&adj_matrix[i*n+j]);
        }
    }
    vertex* table = createTable(adj_matrix,n);
    printAllMinDistance(table,n);
    freeTable(table,n);
    free(adj_matrix);
    return 0;
}

// create a table from the adjacent matrix.
vertex* createTable(int* adj_matrix,int n)
{
    int i,j;
    vertex* table = (vertex*)malloc(sizeof(vertex)*n);
    for(i=0; i<n; i++)
    {
        (table+i)->identifier = i + 1;
        (table+i)->distance = 0;
        (table+i)->next= NULL;
    }
    for(i=0; i<n; i++)
    {
        vertex* p = table + i;
        for(j=0; j<n; j++)
        {
            if(adj_matrix[i*n+j] > 0)
            {
                p->next = (vertex*)malloc(sizeof(vertex));
                p = p->next;
                p->identifier = j + 1;
                p->distance = adj_matrix[i*n+j];
            }
        }
        p->next = NULL;
    }
    return table;
}

// initial the mark Array for dijkstra algorithm.
void initial(MarkVertex* mark_vertex,int n)
{
    int i;
    for(i=0; i<n; i++)
    {
        mark_vertex[i].identifier = i + 1;    // differ every vertex.
        mark_vertex[i].mark = FALSE;          // searched or not
        mark_vertex[i].distance = INFINITY;   // the distance from this vertex to certain vertex.
        mark_vertex[i].previous = 0;          // previous vertex's identifier in this trace.if 0 ,this is the initiation point.
    }
}

// find the min unsure distance from the mark array;if not found,return -1.
int findMinIndex(MarkVertex* mark_vertex,int n)
{
    int i;
    int index = -1;
    int min = INFINITY;
    for(i=0; i<n; i++)
    {
        if(!mark_vertex[i].mark && mark_vertex[i].distance!=INFINITY)  // mark is true && distance is known.
        {
            if(mark_vertex[i].distance < min)
            {
                min = mark_vertex[i].distance;
                index = i;
            }
        }
    }
    return index;
}

void printAllMinDistance(vertex* table,int n)
{
    int i;
    MarkVertex* mark_vertex = (MarkVertex*)malloc(sizeof(MarkVertex) * n);
    for(i=0; i<n; i++)
    {
        initial(mark_vertex,n);
        calculateMinDistance(table,mark_vertex,i,n);
        int j;
        for(j=0; j<n; j++)
        {
            if(i==j)
            {
                continue;
            }
            printf("(%d,%d)",i+1,j+1);
            if(mark_vertex[j].distance == INT_MAX)
            {
                printf(" No trace.\n");
            }
            else
            {
                printf(" trace: <");
                printTrace(mark_vertex,j+1);
                printf("> ");
                printf("distance: %d\n",mark_vertex[j].distance);
            }
        }
        printf("\n");
    }
    free(mark_vertex);
}

// calculate the min distance from a vertex to other vertexes.
void calculateMinDistance(vertex* table,MarkVertex* mark_vertex,int index,int n)
{
    mark_vertex[index].distance = 0;
    do
    {
        mark_vertex[index].mark = TRUE;
        vertex* p = table + index;
        while(p->next!=NULL)
        {
            p = p->next;
            int new_distance = mark_vertex[index].distance + p->distance;
            if(new_distance < mark_vertex[p->identifier-1].distance)
            {
                mark_vertex[p->identifier-1].distance = new_distance;
                mark_vertex[p->identifier-1].previous = mark_vertex[index].identifier;
            }
        }
        index = findMinIndex(mark_vertex,n);
    }
    while(index!=-1);
}

// print the trace from a vertex to other vertexes
void printTrace(MarkVertex* mark_vertex,int identifier)
{
    int previous = mark_vertex[identifier-1].previous;
    if(previous)
    {
        printTrace(mark_vertex,previous);
    }
    printf(" %d ",identifier);
}

// free table's memory
void freeTable(vertex* table,int n)
{
    int i;
    for(i=0; i<n; i++)
    {
        vertex* p = table + i;
        vertex* delete_vertex = p;
        while(p)
        {
            p = p->next;
            free(delete_vertex);
            delete_vertex = p;
        }
    }
    free(table);
}
