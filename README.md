Repository for ECE 420 Lab 3

### Goal: explore speed of using the open mp standard of threads

![alt text](logfiles/results.png "Server-Side Average Memory Access Latency")


### Build instructions 

To make on the lab machine: 
 - `$ make createdata`
 - `$ make`

To make on MacOS X:
(ensure gcc-7 installed, instructions here: http://www.mathcancer.org/blog/setting-up-gcc-openmp-on-osx-homebrew-edition/)
 - `$ make createdata`
 - `$ make solver`


### Run instructions

To run client:
 - `$ ./solver.o <num_threads>`


### Data output 

Data output is automattically placed as logfiles/data_output. Change the name of this file to preserve it, else it will be overwritten the next time the program is run. 

Data input is also automattically placed in the logfiles folder as logfiles/data_input. 

Make clean will remove the default data_output and data_input files
