
.PHONY: all clean

COMPILE_C = mos-sim-clang -Os
LINK_OPTIONS = -lbsoftfloat

EXAMPLES = \
	mandelbrot_f16 \
	mandelbrot_f32 \
	mandelbrot_f64 \
	simple_example \
	sum_of_sqrts

all: $(EXAMPLES)


mandelbrot_f16: mandelbrot.c
	$(COMPILE_C) -DUSE_FLOAT16 -o $@ $< $(LINK_OPTIONS)

mandelbrot_f32: mandelbrot.c
	$(COMPILE_C) -DUSE_FLOAT32 -o $@ $< $(LINK_OPTIONS)

mandelbrot_f64: mandelbrot.c
	$(COMPILE_C) -DUSE_FLOAT64 -o $@ $< $(LINK_OPTIONS)

simple_example: simple_example.c
	$(COMPILE_C) -o $@ $< $(LINK_OPTIONS)

sum_of_sqrts: sum_of_sqrts.c
	$(COMPILE_C) -o $@ $< $(LINK_OPTIONS)

clean:
	rm -f $(EXAMPLES) *.elf
