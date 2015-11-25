#include <stdio.h>
#include <stdlib.h>
#define MAX 1000
void quickSort(int a[],int start,int end);
void printArray(int a[],int n);
int* createRandomArray(int n);
int main()
{
    int *arr = createRandomArray(MAX);
    quickSort(arr,0,MAX-1);
    printArray(arr,MAX);
    free(arr);
    return 0;
}
void quickSort(int a[],int start,int end){
    if(end - start<1){
        return;
    }
    int i = start;
    int j = end;
    int temp = a[start];
    while(i<j){
        while(i<j){
            if(a[j] < temp){
                a[i++] = a[j];
                break;
            }
            j--;
        }
        while(i<j){
            if(a[i] > temp){
                a[j--] = a[i];
                break;
            }
            i++;
        }
    }
    a[i] = temp;
    quickSort(a,start,i-1);
    quickSort(a,i+1,end);
}
void printArray(int a[],int n){
    int i;
    for(i=0;i<n;i++){
        printf("%d\n",a[i]);
    }
    printf("\n");
}
int* createRandomArray(int n){
    int i;
    int* arr = (int*)malloc(sizeof(int)*n);
    srand(time(NULL));
    for(i=0;i<n;i++){
        arr[i] = rand();
    }
    return arr;
}
