Repository for ECE 420 Lab 3

### Goal: Explore openmp multithreading and compare the speed of different pragma operations
### In order to do so, we solve a linear system of equations via Gauss-Jordan elimination

There are three components to this project:
1) Datagen
    - Generates the input data for the program
2) Serialtester
    - Has the correct serial implementation of a gauss-jordan solver
    - Used to test the correctness of the multithreaded solution
3) LinearSystemSolver
    - Includes the multithreaded solution via openmp
    - The given baseline solution is also present

### Build instructions 

To make: 
 - `$ make all`
 - `$ make mac` for MacOS X ([ensure gcc-7 installed](http://www.mathcancer.org/blog/setting-up-gcc-openmp-on-osx-homebrew-edition/))

### Run instructions

A bash script is provided to quickly run and test the multithreaded solution with the following parameters:
 - Input size of the data: 64, 256, 1024
 - Number of threads: 1, 4, 16 
 - Duplicates (amount of times each trial is run): 4

To run the script:
 - `chmod +x check.sh`
 - `./check.sh`

