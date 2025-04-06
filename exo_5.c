#include <stdio.h>
#include <math.h>
#include <omp.h>

#define WIDTH 2500
#define HEIGHT 2500
#define N_ITER 200
#define MAX_BOUNDS 200

typedef struct
{
    double real;
    double imag;
} Complex;

double norm(Complex z)
{
    return z.real * z.real + z.imag * z.imag;
}

int julia_converge(Complex z, Complex c)
{
    int n;
    for (n = 0; n < N_ITER; n++)
    {
        double temp_real = z.real * z.real - z.imag * z.imag + c.real;
        double temp_imag = 2.0 * z.real * z.imag + c.imag;

        z.real = temp_real;
        z.imag = temp_imag;

        if (norm(z) > MAX_BOUNDS)
        {
            return 0;
        }
    }
    return 1;
}

void generate_julia_image(Complex c)
{
    unsigned char image[HEIGHT][WIDTH];
    double x_min = -1.5;
    double x_max = 1.5;
    double y_min = -1.5;
    double y_max = 1.5;

    double x_step = (x_max - x_min) / WIDTH;
    double y_step = (y_max - y_min) / HEIGHT;

#pragma omp parallel for collapse(2) schedule(dynamic)
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            Complex z;
            z.real = x_min + x * x_step;
            z.imag = y_min + y * y_step;

            if (julia_converge(z, c))
            {
                image[y][x] = 255;
            }
            else
            {
                image[y][x] = 0;
            }
        }
    }

    FILE *f = fopen("julia.pgm", "wb");
    if (!f)
    {
        fprintf(stderr, "Erreur d'ouverture du fichier\n");
        return;
    }

    // Header for binary PGM format
    fprintf(f, "P5\n");
    fprintf(f, "%d %d\n", WIDTH, HEIGHT);
    fprintf(f, "255\n");

    fwrite(image, sizeof(unsigned char), WIDTH * HEIGHT, f);

    fclose(f);
}

int main()
{
    Complex c;
    c.real = -0.8;
    c.imag = 0.156;

    // Test with 1 to 12 threads
    for (int i = 1; i < 13; i++)
    {
        omp_set_num_threads(i);
        double start_time = omp_get_wtime();
        generate_julia_image(c);
        double end_time = omp_get_wtime();
        printf("time = %f\n", (end_time - start_time));
    }

    return 0;
}
