#include <stdio.h>
int main()
{
    int n,N;
    int S;
    int price,count;
    long long int sum;
    int past;
    sum = 0;
    scanf("%d %d",&N,&S);
    for(n=0;n<N;n++){
        scanf("%d %d",&price,&count);
        if(n){
            price = price < past + S ? price : past + S;
        }
        sum += price * count;
        past = price;
    }
    printf("%lld",sum);
    return 0;
}