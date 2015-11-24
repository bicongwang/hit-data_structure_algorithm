#include <stdio.h>
typedef struct VERTEX
{
    int mark;
    int distance;
    int pastX;
    int pastY;
}VERTEX;
VERTEX vertexs[5][5];
void BFS(int x,int y,int pastX,int pastY,int distance);
void printPath(int x,int y);
int main()
{
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            scanf("%d",&vertexs[i][j].mark);
            vertexs[i][j].distance = 25;
        }
    }
    BFS(0,0,0,0,0);
    printPath(4,4);
    return 0;
}
void BFS(int x,int y,int pastX,int pastY,int distance){
    if(vertexs[x][y].mark||x<0||x>4||y<0||y>4){
        return;
    }
    if(distance < vertexs[x][y].distance){
        vertexs[x][y].distance = distance;
        vertexs[x][y].pastX = pastX;
        vertexs[x][y].pastY = pastY;
    }else{
        return;
    }
    BFS(x-1,y,x,y,distance+1);
    BFS(x+1,y,x,y,distance+1);
    BFS(x,y+1,x,y,distance+1);
    BFS(x,y-1,x,y,distance+1);
}
void printPath(int x,int y){
    if(x||y){
        printPath(vertexs[x][y].pastX,vertexs[x][y].pastY);
    }
    printf("(%d, %d)\n",x,y);
}