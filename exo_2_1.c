#include <omp.h>
#include <stdio.h>


int main(){
    omp_set_num_threads(4);


    #pragma omp parallel
    {
        int threadNum = omp_get_thread_num();
        printf("threadNum = %d\n", threadNum);
    }
}