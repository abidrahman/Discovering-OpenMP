all: datagen linearsystemsolver serialtester

datagen: datagen.c Lab3IO.c
			gcc datagen.c Lab3IO.c -o datagen

linearsystemsolver: linearsystemsolver.c Lab3IO.c
			gcc linearsystemsolver.c Lab3IO.c -o linearsystemsolver -fopenmp -lm -std=c99 

serialtester: serialtester.c Lab3IO.c
			gcc serialtester.c Lab3IO.c -o serialtester -lm

clean:
	@rm -rf *.o

