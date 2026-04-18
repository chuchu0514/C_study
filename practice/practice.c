#include <stdio.h>
#include <stdlib.h>


int main()
{
    int ***ary;
    int p,z,m;

    ary = (int***)malloc(sizeof(int**) * p);

    for(int i = 0; i < p; i++){
        ary[i] = (int**)malloc(sizeof(int*) * z);
        for(int j = 0; j < z; j++){
            ary[i][j] = (int*)malloc(sizeof(int) * m);
        }
    }



    for(int i = 0; i < p; i++){
        for(int j = 0; j < z; j++){
            free(ary[i][j]);
        }
        free(ary[i]);
    }
    free(ary);
}