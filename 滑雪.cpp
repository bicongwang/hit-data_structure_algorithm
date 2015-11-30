#include <stdio.h>
#define MAX 100
typedef struct VERTEX
{
    int height;
    int distance;
}VERTEX;
VERTEX vertexs[MAX][MAX];
int findMax(int* x,int* y,int r,int c);
void BFS(int x,int y,int r,int c,int distance,int height);
int main()
{
    int r,c;
    scanf("%d %d",&r,&c);
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            scanf("%d",&vertexs[i][j].height);
            vertexs[i][j].distance = -1;
        }
    }
    int x;
    int y;
    while(findMax(&x,&y,r,c)){
        BFS(x,y,r,c,1,10000);
    }
    int max = vertexs[0][0].distance;
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            max = vertexs[i][j].distance > max ? vertexs[i][j].distance : max;
        }
    }
    printf("%d",max);
    return 0;
}
int findMax(int* x,int* y,int r,int c){
    int max = 0;
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            if(vertexs[i][j].distance==-1 && vertexs[i][j].height > max){
                *x = i;
                *y = j;
                max = vertexs[i][j].height;
            }
        }
    }
    return max;
}
void BFS(int x,int y,int r,int c,int distance,int height){
    if(height < vertexs[x][y].height||x<0||x>=r||y<0||y>=c){
        return;
    }
    if(distance > vertexs[x][y].distance){
        vertexs[x][y].distance = distance;
        BFS(x+1,y,r,c,vertexs[x][y].distance+1,vertexs[x][y].height);
        BFS(x-1,y,r,c,vertexs[x][y].distance+1,vertexs[x][y].height);
        BFS(x,y+1,r,c,vertexs[x][y].distance+1,vertexs[x][y].height);
        BFS(x,y-1,r,c,vertexs[x][y].distance+1,vertexs[x][y].height);
    }
}
