
#include <stdio.h>
#include <softfloat.h>

// Number of iterations to run for each point.
#define ITERATIONS 27

// Size of the field of view.
#define MAXX 75
#define MAXY 30

#if defined(USE_FLOAT16)

typedef float16_t number_t;
static number_t four;
static number_t onethou;
#define number_init() (four = i32_to_f16(4), onethou = i32_to_f16(1000))
#define number_add(x, y) f16_add((x), (y))
#define number_sub(x, y) f16_sub((x), (y))
#define number_mul(x, y) f16_mul((x), (y))
#define number_div(x, y) f16_div((x), (y))
#define number_gt(x, y)  f16_lt((y), (x))
#define number_four() four
#define number_from_int(x) (i32_to_f16((x)))
#define number_from_fixed(x) (f16_div(i32_to_f16((x)), onethou))

#elif defined(USE_FLOAT64)

typedef float64_t number_t;
static number_t four;
static number_t onethou;
#define number_init() (four = i32_to_f64(4), onethou = i32_to_f64(1000))
#define number_add(x, y) f64_add((x), (y))
#define number_sub(x, y) f64_sub((x), (y))
#define number_mul(x, y) f64_mul((x), (y))
#define number_div(x, y) f64_div((x), (y))
#define number_gt(x, y)  f64_lt((y), (x))
#define number_four() four
#define number_from_int(x) (i32_to_f64((x)))
#define number_from_fixed(x) (f64_div(i32_to_f64((x)), onethou))

#else // USE_FLOAT32

typedef float32_t number_t;
static number_t four;
static number_t onethou;
#define number_init() (four = i32_to_f32(4), onethou = i32_to_f32(1000))
#define number_add(x, y) f32_add((x), (y))
#define number_sub(x, y) f32_sub((x), (y))
#define number_mul(x, y) f32_mul((x), (y))
#define number_div(x, y) f32_div((x), (y))
#define number_gt(x, y)  f32_lt((y), (x))
#define number_four() four
#define number_from_int(x) (i32_to_f32((x)))
#define number_from_fixed(x) (f32_div(i32_to_f32((x)), onethou))

#endif

// Determine if a point is in the mandelbrot set or not.
// Returns the palette index to draw for the point.
//
// Based on:
// https://github.com/ttsiodras/Blue_Pill_Mandelbrot/blob/master/BluePill_TFT16K_Mandelbrot.ino
static uint8_t mandelbrot_point(number_t x, number_t y)
{
    number_t rez, imz;
    number_t t1, o1, o2, o3;
    uint8_t k = 0;
    imz = rez = number_from_int(0);
    while (k < ITERATIONS) {
        o1 = number_mul(rez, rez);
        o2 = number_mul(imz, imz);
        o3 = number_mul(number_sub(rez, imz), number_sub(rez, imz));
        t1 = number_sub(o1, o2);
        rez = number_add(t1, x);
        imz = number_add(number_sub(number_add(o1, o2), o3), y);
        if (number_gt(number_add(o1, o2), number_four()))
            break;
        ++k;
    }
    return k;
}

static void mandelbrot_draw(number_t x1, number_t y1, number_t x2, number_t y2)
{
    number_t xstep, ystep, x, y;
    int px, py;
    uint8_t color;
    xstep = number_div(number_sub(x2, x1), number_from_int(MAXX));
    ystep = number_div(number_sub(y2, y1), number_from_int(MAXY));
    y = y1;
    for (py = 0; py < MAXY; ++py) {
        x = x1;
        for (px = 0; px < MAXX; ++px) {
            color = mandelbrot_point(x, y);
            putchar(' ' + color - 1);
            x = number_add(x, xstep);
        }
        y = number_add(y, ystep);
        putchar('\n');
    }
    putchar('\n');
}

int main(void)
{
    number_init();

    // x1 = -2.30, y1 = -2.00, x2 = 2.30, y2 = 2.00
    mandelbrot_draw(number_from_fixed(-2300), number_from_fixed(-2000),
                    number_from_fixed( 2300), number_from_fixed( 2000));

    return 0;
}
