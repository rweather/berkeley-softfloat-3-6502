
.PHONY: all all_c clean

COMPILE_C = mos-sim-clang -Os
LINK_OPTIONS = -lbsoftfloat

EXAMPLES = \
	mandelbrot_f16 \
	mandelbrot_f32 \
	mandelbrot_f64 \
	simple_example \
	sum_of_sqrts

C_EXAMPLES = \
	mandelbrot_f32_c \
	mandelbrot_f64_c \
	sum_of_sqrts_c

all: $(EXAMPLES)

all_c: $(C_EXAMPLES)

mandelbrot_f16: mandelbrot.c
	$(COMPILE_C) -DUSE_FLOAT16 -o $@ $< $(LINK_OPTIONS)

mandelbrot_f32: mandelbrot.c
	$(COMPILE_C) -DUSE_FLOAT32 -o $@ $< $(LINK_OPTIONS)

mandelbrot_f32_c: mandelbrot.c
	$(COMPILE_C) -DUSE_FLOAT32_C -o $@ $< $(LINK_OPTIONS)

mandelbrot_f64: mandelbrot.c
	$(COMPILE_C) -DUSE_FLOAT64 -o $@ $< $(LINK_OPTIONS)

mandelbrot_f64_c: mandelbrot.c
	$(COMPILE_C) -DUSE_FLOAT64_C -o $@ $< $(LINK_OPTIONS)

simple_example: simple_example.c
	$(COMPILE_C) -o $@ $< $(LINK_OPTIONS)

sum_of_sqrts: sum_of_sqrts.c
	$(COMPILE_C) -o $@ $< $(LINK_OPTIONS)

sum_of_sqrts_c: sum_of_sqrts_c.c
	$(COMPILE_C) -o $@ $< $(LINK_OPTIONS)

clean:
	rm -f $(EXAMPLES) $(C_EXAMPLES) *.elf
