#include <stdio.h>
#include <memory.h>
#include <math.h>

void enumerate(int arr[][3]){
    arr[0][0]++;
    for(int i=0;i<2;i++){
        if(arr[0][i] == 4){
            arr[0][i] = 0;
            arr[0][i+1]++;

        }else{
            break;
        }
    }
}

int guess(int input_arr[][3],int mark_arr[][3]){
    for(int i=0;i<3;i+=2){
        mark_arr[1][i] = (4 - (input_arr[0][i] + mark_arr[0][i] + mark_arr[0][1]) % 4) % 4;
    }
    mark_arr[1][1] = (4 - (input_arr[0][1] + mark_arr[0][1] + mark_arr[0][2] + mark_arr[0][0]) % 4) % 4;
    for(int i=0;i<3;i+=2){
        mark_arr[2][i] = (4 - (input_arr[1][i] + mark_arr[0][i] + mark_arr[1][i] + mark_arr[1][1]) % 4) % 4;
    }
    mark_arr[2][1] = (4 - (input_arr[2][1] + mark_arr[2][0] + mark_arr[2][2] + mark_arr[1][1]) % 4) % 4;
    if((input_arr[1][1] + mark_arr[1][1] + mark_arr[0][0] + mark_arr[0][2] + mark_arr[2][0] + mark_arr[2][2]) % 4 != 0){
        return 0;
    }
    for(int i=0;i<3;i+=2){
        if((input_arr[2][i] + mark_arr[2][i] + mark_arr[1][i] + mark_arr[2][1]) % 4 != 0 ){
            return 0;
        }
    }
    return 1;
}

void copy(int arr1[][3],int arr2[][3]){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            arr2[i][j] = arr1[i][j];
        }
    }
}

void run(int input_arr[][3],int mark_arr[][3]){
    int reser_arr[3][3];
    for(int i=0;i<pow(4,3);i++){
        if(guess(input_arr,mark_arr)){
            int sum = 0;
            for(int j=0;j<3;j++){
                for(int k=0;k<3;k++){
                    sum += mark_arr[j][k];
                }
            }
            static int min = sum;
            if(sum <= min){
                copy(mark_arr,reser_arr);
                min = sum;
            }
        }
        enumerate(mark_arr);
    }
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            while(reser_arr[i][j] > 0){
                reser_arr[i][j] -- ;
                printf("%d ",i*3 + j + 1);
            }
        }
    }
}

int main()
{
    int input_arr[3][3];
    int mark_arr[3][3];
    memset(mark_arr,0,sizeof(int)*9);
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            scanf("%d",&input_arr[i][j]);
        }
    }
    run(input_arr,mark_arr);
}
