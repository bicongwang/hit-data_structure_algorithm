#include <stdio.h>
#include <stdlib.h>
int cmp(const void* a,const void* b);
int check(int x,int* stall,int n,int c);
int main()
{
    int n,c;
    scanf("%d %d",&n,&c);
    int* stall = (int*)malloc(sizeof(int)*n);
    for(int i=0;i<n;i++){
        scanf("%d",stall+i);
    }
    qsort(stall,n,sizeof(stall[0]),cmp);
    int l = 0;
    int r = stall[n-1]-stall[0];
    int mid;
    while(l<=r){
        mid = (l+r)/2;
        if(check(mid,stall,n,c)){
            l = mid + 1;
        }else{
            r = mid - 1;
        }
    }
    printf("%d",l-1);
    free(stall);
    return 0;
}
int cmp(const void* a,const void* b){
    return *(int*)a > *(int *)b;
}
int check(int x,int* stall,int n,int c){
    int thisC = 1;
    int start = stall[0];
    for(int i=0;i<n;i++){
        if(stall[i] - start >= x){
            start = stall[i];
            thisC++;
        }
    }
    return thisC >= c;
}
