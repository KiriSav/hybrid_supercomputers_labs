#include<omp.h>
#include<stdio.h>
#include<curses.h> 
#include<math.h>
#define N 10000
int A[N];
int main() {
    int i;
    #pragma omp parallel for
    for (int i=0; i<N; i++) // этот цикл выполняется параллельно,
        A[i]=(int)(i); // итерации распределяются между нитями по умолчанию
    for (int i=0; i<N; i++) // этот цикл выполняется последовательно
        printf("%i ",A[i]);
    printf("%s\n","");

    if (omp_get_max_threads ()<4) {
        printf("not enough threads");
        getch();
        return(0);
    }
    else omp_set_num_threads(4);
    #pragma omp parallel for schedule(static, 10) private(i) shared(A)
    for(i=0; i < N; i++) {
        if (sqrt(A[i]) - (int)sqrt(A[i]) == 0) {
 			printf("%i = %iˆ2\n",A[i], int(sqrt(A[i])));
        }
    }
    return(0);
    
}
