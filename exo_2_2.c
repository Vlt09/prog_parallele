#include <omp.h>
#include <stdio.h>

/*
    Notes exo 2 :

    private ne donne pas la garantie que la valeur est bien init quand les Thread démarre
    tandis que la directive firstprivate nous assure que la valeur est init
 */
int main()
{
    omp_set_num_threads(4);

    int VALEUR_1 = 1000, VALEUR_2 = 2000;
#pragma omp parallel firstprivate(VALEUR_2)
    {
        int threadNum = omp_get_thread_num();

        VALEUR_2++;
        printf("threadNum = %d VALEUR_1 = %d VALEUR_2 = %d\n", threadNum, VALEUR_1, VALEUR_2);
    }
}