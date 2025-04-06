#include <stdio.h>
#include <omp.h>

int main()
{

    static long nb_pas = 1000000000;
    double pas;

    int i;
    double x, pi, som = 0.0;
    pas = 1.0 / (double)nb_pas;
    double start_time = omp_get_wtime();
    for (i = 0; i < nb_pas; i++)
    {
        x = (i + 0.5) * pas;
        som = som + 4.0 / (1.0 + x * x);
    }
    double end_time = omp_get_wtime();

    pi = pas * som;
    printf("time elapsed = %f PI=%2.15f\n", (end_time - start_time), pi);

    for (int j = 2; j < 12; j++)
    {
        int i;
        double sum_time = 0.0;
        pas = 1.0 / (double)nb_pas;
        omp_set_num_threads(j);

        for (int k = 0; k < 10; k++)
        {
            x = 0.0;
            pi = 0.0;
            som = 0.0;
            start_time = omp_get_wtime();

#pragma omp parallel for schedule(static) private(x) reduction(+ : som)
            for (i = 0; i < nb_pas; i++)
            {
                x = (i + 0.5) * pas;
                som = som + 4.0 / (1.0 + x * x);
            }
            pi = pas * som;
            end_time = omp_get_wtime();
            double elapsed = (end_time - start_time);

            sum_time += elapsed;
            // printf("Using %d thread PI=%2.15f time = %f\n", j, pi, elapsed);
        }

        printf("Average time using %d threads: %f seconds\n\n", j, sum_time / 10.0);
    }
    // for (i=0;i< nb_pas; i++){
    //     x = (i + 0.5)*pas;
    //     som=som+4.0/(1.0+x*x);
    // }
    return 0;
}