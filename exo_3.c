#include <omp.h>
#include <stdio.h>

/*
    private ne donne pas la garantie que la valeur est bien init quand les Thread démarre
    tandis que la directive firstprivate nous assure que la valeur est init
 */
int main()
{
    omp_set_num_threads(4);

    double time_acc = 0.0;
    for (int i = 0; i < 10; i++)
    {
        double start_time = omp_get_wtime();
        for (int j = 0; j < 50; j++)
        {
            // printf("j = %d ", j);
        }
        double end_time = omp_get_wtime();
        time_acc += (end_time - start_time);
    }

    printf("Average time one thread : %f\n", time_acc / 10.0);

    time_acc = 0.0;
    for (int j = 0; j < 10; j++)
    {
        double start_time = omp_get_wtime();

#pragma omp parallel for
        for (int i = 0; i < 50; i++)
        {
            int threadNum = omp_get_thread_num();
            printf("threadNum = %d i = %d\n", threadNum, i);
        };

        double end_time = omp_get_wtime();
        time_acc += (end_time - start_time);
    }

    printf("Average time 4 threads : %f\n", time_acc / 10.0);
}