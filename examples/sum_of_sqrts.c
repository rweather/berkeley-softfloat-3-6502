
// Compute the sum and inverse-sum of the square roots of 1..100.
// Tests f32_add(), f32_sub(), f32_mul(), f32_div(), and f32_sqrt().

#include <stdio.h>
#include <softfloat.h>

float32_t one_million;

void print_f32_init(void)
{
    one_million = i32_to_f32(1000000L);
}

void print_f32(float32_t value)
{
    float32_t a = f32_roundToInt(value, softfloat_round_min, false);
    float32_t b = f32_mul(f32_sub(value, a), one_million);
    long a2 = f32_to_i32(a, softfloat_round_min, false);
    long b2 = f32_to_i32(b, softfloat_round_min, false);
    printf("%ld.%06ld", a2, b2);
}

int main(void)
{
    float32_t sum = i32_to_f32(0);
    float32_t x;
    int n;

    print_f32_init();

    for (n = 1; n <= 100; ++n) {
        printf("sqrt(%d) = ", n);
        x = f32_sqrt(i32_to_f32(n));
        print_f32(x);
        sum = f32_add(sum, x);
        printf("\n");
    }

    printf("sum = ");
    print_f32(sum);

    printf("\ninverse = ");
    x = f32_div(one_million, sum);
    printf("0.%06ld\n", (long)f32_to_i32(x, softfloat_round_min, false));

    return 0;
}
