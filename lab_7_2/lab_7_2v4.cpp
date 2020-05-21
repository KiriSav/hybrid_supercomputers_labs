#include <omp.h>
#include <stdio.h>

void calculate_cartesian_product(int a1[], int lenght_a1, int a2[], int lenght_a2, int a3[], int lenght_a3, int a4[], int lenght_a4) {
    int numthreads = 4;
    
    int index_a1 = 0;
    int index_a2 = 0;
    int index_a3 = 0;
    int index_a4 = 0;
    
    printf("A1 X A2 X A3 X A4 = (\n");
    #pragma omp parallel num_threads(numthreads) shared(index_a1, index_a2, index_a3, index_a4)
    {
        #pragma omp for collapse(3)
        for (index_a1=0; index_a1<lenght_a1; index_a1++) {
            for (index_a2=0; index_a2<lenght_a2; index_a2++){
                for (index_a3=0; index_a3<lenght_a3; index_a3++){
                    for (index_a4=0; index_a4<lenght_a4; index_a4++){
                        printf("(%i, %i, %i, %i)\n", a1[index_a1], a2[index_a2], a3[index_a3], a4[index_a4]);
                    }
                }
            }
        }
    }
    printf(")\n");
}

int main() {
    
    int a1[2] = {2, 3};
    int a2[3] = {3, 4, 5};
    int a3[2] = {7, 8};
    int a4[2] = {5, 1};
    
    int lenght_a1 = (sizeof(a1)/sizeof(*a1));
    int lenght_a2 = (sizeof(a2)/sizeof(*a2));
    int lenght_a3 = (sizeof(a3)/sizeof(*a3));
    int lenght_a4 = (sizeof(a4)/sizeof(*a4));
    
    calculate_cartesian_product(a1,lenght_a1, a2, lenght_a2, a3, lenght_a3, a4, lenght_a4);
}
