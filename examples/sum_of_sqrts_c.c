
// Compute the sum and inverse-sum of the square roots of 1..100.

#include <stdio.h>

extern float floorf(float x);
extern float sqrtf(float x);

void print_f32(float value)
{
    float a = floorf(value);
    float b = (value - a) * 1000000.0f;
    long a2 = (long)a;
    long b2 = (long)b;
    printf("%ld.%06ld", a2, b2);
}

int main(void)
{
    float sum = 0.0f;
    float x;
    int n;

    for (n = 1; n <= 100; ++n) {
        printf("sqrt(%d) = ", n);
        x = sqrtf((float)n);
        print_f32(x);
        sum += x;
        printf("\n");
    }

    printf("sum = ");
    print_f32(sum);

    printf("\ninverse = ");
    x = 1000000.0f / sum;
    printf("0.%06ld\n", (long)x);

    return 0;
}
