#include <stdio.h>
#include <softfloat.h>

int main(void)
{
   float32_t one = i32_to_f32(1);
    float32_t two = i32_to_f32(2);
    float32_t three = i32_to_f32(3);
    float32_t sum = f32_add(one, two);
    float32_t product = f32_mul(sum, three);
    long result = f32_to_i32_r_minMag(product, false);
    printf("(1 + 2) * 3 = %ld\n", result);
    return 0;
}
