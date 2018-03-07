all: datagen serialtester main baseline

datagen: dependencies/datagen.c dependencies/Lab3IO.c
			gcc dependencies/datagen.c dependencies/Lab3IO.c -o datagen

mac: linearsystemsolver/linearsystemsolver.c dependencies/Lab3IO.c
			gcc-7 linearsystemsolver/baseline.c dependencies/Lab3IO.c -o baseline -fopenmp -lm -std=c99 -g -Wall
			gcc-7 linearsystemsolver/linearsystemsolver.c dependencies/Lab3IO.c -o main -fopenmp -lm -std=c99 -g -Wall

main: linearsystemsolver/linearsystemsolver.c dependencies/Lab3IO.c
			gcc linearsystemsolver/linearsystemsolver.c dependencies/Lab3IO.c -o main -fopenmp -lm -std=c99 -g -Wall

baseline: linearsystemsolver/baseline.c dependencies/Lab3IO.c
			gcc linearsystemsolver/baseline.c dependencies/Lab3IO.c -o baseline -fopenmp -lm -std=c99 -g -Wall

serialtester: dependencies/serialtester.c dependencies/Lab3IO.c
			gcc dependencies/serialtester.c dependencies/Lab3IO.c -o serialtester -lm

clean:
	@rm -rf *.o

