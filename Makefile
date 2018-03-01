all: datagen main baseline static serialtester

datagen: datagen.c Lab3IO.c
			gcc datagen.c Lab3IO.c -o datagen

main: linearsystemsolver.c Lab3IO.c
			gcc linearsystemsolver.c Lab3IO.c -o main -fopenmp -lm -std=c99 -g -Wall

baseline: baseline.c Lab3IO.c
			gcc baseline.c Lab3IO.c -o baseline -fopenmp -lm -std=c99 -g -Wall

static: static.c Lab3IO.c
			gcc static.c Lab3IO.c -o baseline -fopenmp -lm -std=c99 -g -Wall

serialtester: serialtester.c Lab3IO.c
			gcc serialtester.c Lab3IO.c -o serialtester -lm

clean:
	@rm -rf *.o

