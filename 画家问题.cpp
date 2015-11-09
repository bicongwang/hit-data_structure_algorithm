#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <math.h>

void enumerate(int* matrix,int n);
int guess(int* in_matrix,int* out_matrix,int n);

int main()
{
	int t,T;
	scanf("%2d",&T);
	for(t=0;t<T;t++){
		int n;
		char c;
		scanf("%d ",&n);
		int i,j;
		int* in_matrix = (int*)malloc((n+1)*(n+2)*sizeof(int));
		int* out_matrix = (int*)malloc((n+1)*(n+2)*sizeof(int));
		memset(out_matrix,0,(n+1)*(n+2)*sizeof(int));
		for(i=1;i<=n;i++){
			for(j=1;j<=n;j++){
				scanf("%c",&c);
				in_matrix[i*(n+2) + j] = (c == 'w'? 1 : 0);
			}
            getchar();
		}
		int min = guess(in_matrix,out_matrix,n);
		if(min == n*n && n!=1){
            printf("inf\n");
		}else{
		    printf("%d\n",min);
		}
		free(in_matrix);
		free(out_matrix);
	}
}

void enumerate(int* matrix,int n){
	matrix[n+2 + 1] ++;
	int i;
	for(i=1;i<n;i++){
		if(matrix[n+2+i]>1){
			matrix[n+2+i+1]++;
			matrix[n+2+i] = 0;
		}else{
			break;
		}
	}
}

int guess(int* in_matrix,int* out_matrix,int n){
	int k;
	int min = n*n;
	for(k=0;k<pow(2,n);k++){
		int mark = 1;
		int i,j;
		for(i=2;i<=n;i++){
			for(j=1;j<=n;j++){
				out_matrix[i*(n+2) + j] = (in_matrix[(i-1)*(n+2) + j] + out_matrix[(i-1)*(n+2) + j] + out_matrix[(i-2)*(n+2) + j] + out_matrix[(i-1)*(n+2) + j + 1] + out_matrix[(i-1)*(n+2) + j - 1]) % 2;
			}
		}
		for(j=1;j<=n;j++){
			if(in_matrix[n*(n+2)+j] != ((out_matrix[n*(n+2)+j] + out_matrix[n*(n+2)+j - 1] + out_matrix[n*(n+2)+j + 1] + out_matrix[(n-1)*(n+2)+j]) % 2)){
				mark = 0;
			}
		}
		int count = 0;
		if(mark){
			for(i=1;i<=n;i++){
				for(j=1;j<=n;j++){
					if(out_matrix[i*(n+2) + j]){
						count++;
					}
				}
			}
			min = min < count? min:count;
		}
		enumerate(out_matrix,n);
	}
	return min;
}
