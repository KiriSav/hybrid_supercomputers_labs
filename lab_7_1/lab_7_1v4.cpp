#include <omp.h>
#include <stdio.h>
#include <curses.h> 
#include <iostream>

int main() {
    double a1[4] = {2, 2, 3, 4};
    double a2[6] = {3, 4, 5, 6, 7, 8};
    double a3[7] = {7, 5, 6, 2, 12, 3, 4};
    double a4[1] = {5};
    if (omp_get_max_threads()<4) {
        printf("not enough threads");
        getch();
        return(0);
    }
    else omp_set_num_threads(4);
    printf("A1 X A2 X A3 X A4 = (\n");
    #pragma omp parallel
    {
        #pragma omp for nowait
        for (int a=0; a<(sizeof(a1)/sizeof(*a1)); a++) {
            for (int b=0; b<(sizeof(a2)/sizeof(*a2)); b++){
                for (int c=0; c<(sizeof(a3)/sizeof(*a3)); c++){
                    for (int d=0; d<(sizeof(a4)/sizeof(*a4)); d++){
                        printf("(%f, %f, %f, %f)\n", a1[a], a2[b], a3[c], a4[d]);
                    }
                }
            }
        }
    }
    printf(")\n");
}
