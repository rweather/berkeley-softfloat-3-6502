
.PHONY: all clean

COMPILE_C = mos-sim-clang -Os
LINK_OPTIONS = -lsoftfloat

EXAMPLES = \
	mandelbrot \
	simple_example \
	sum_of_sqrts

all: $(EXAMPLES)

mandelbrot: mandelbrot.c
	$(COMPILE_C) -o $@ $< $(LINK_OPTIONS)

simple_example: simple_example.c
	$(COMPILE_C) -o $@ $< $(LINK_OPTIONS)

sum_of_sqrts: sum_of_sqrts.c
	$(COMPILE_C) -o $@ $< $(LINK_OPTIONS)

clean:
	rm -f $(EXAMPLES) *.elf
