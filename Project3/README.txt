Author: Harrison Ingram-Bate
Date Last Updated: 02/06/2026


--------------------------------
Introduction
--------------------------------
This project implements Differential Evolution(with 10 different strategies)
and Particle Swarm Optimization for N dimensions on 10 different Benchmark functions.
The included report CS471_Project3 lists fitness functions and their specifications that are used to analyze the results.
The src directory contains .cpp and .h files for an executable, a python script to automate executaion for all functions,
an input directory that the executable uses to get specifications for all fitness functions, and an empty output directory
where you can find the results from running the executable.
The Results_CSV directory includes the results used for all tests run.


--------------------------------
File Structure
--------------------------------
project_root/
|--src/
|  |--input/
|  |  |--10
|  |  |  |--DE
|  |  |  |   `--*.csv (* all function names)
|  |  |  `--PS
|  |  |      `--*.csv
|  |  |--20
|  |  |  |--DE
|  |  |  |   `--*.csv
|  |  |  `--PS
|  |  |      `--*.csv
|  |  `--30
|  |     |--DE
|  |     |   `--*.csv
|  |     `--PS
|  |         `--*.csv
|  |--output/
|  |  |--10
|  |  |  |--DE
|  |  |  |  `--n (n is 1-10 indicating the strategy used)
|  |  |  |     `--*.csv (* all function names)
|  |  |  `--PS
|  |  |      `--*.csv
|  |  |--20
|  |  |  |--DE
|  |  |  |  `--n (n is 1-10 indicating the strategy used)
|  |  |  |     `--*.csv (* all function names)
|  |  |  `--PS
|  |  |      `--*.csv
|  |  `--30
|  |     |--DE
|  |  |  |  `--n (n is 1-10 indicating the strategy used)
|  |  |  |     `--*.csv (* all function names)
|  |     `--PS
|  |         `--*.csv
|  |--Main.cpp
|  |--Population.cpp
|  |--Population.h
|  |--Problem.cpp
|  |--Problem.h
|  |--DifferentialEvolution.cpp
|  |--DifferentialEvolution.h
|  |--ParticleSwarm.cpp
|  |--ParticleSwarm.h
|  `--analyzer.py
|--Results_CSV/
|  |--10
|  |  |--DE
|  |  |  `--n (n is 1-10 indicating the strategy used)
|  |  |     `--*.csv (* all function names)
|  |  `--PS
|  |      `--*.csv
|  |--20
|  |  |--DE
|  |  |  `--n (n is 1-10 indicating the strategy used)
|  |  |     `--*.csv (* all function names)
|  |  `--PS
|  |      `--*.csv
|  `--30
|     |--DE
|     |  `--n (n is 1-10 indicating the strategy used)
|     |     `--*.csv (* all function names)
|     `--PS
|         `--*.csv
|--CS471_Project3.pdf	(Project Report)
|--CS471_Proj3.pdf	(Doxygen pdf)
`--README.txt


--------------------------------
Compilation
--------------------------------
Compilation Requirements:
- Compiler GCC's g++ compiler
- Be in the src directory

To compile on Windows from the src directory:
g++ -std=c++14 *.cpp *.h

To compile on Linux from the src directory:
g++ -std=c++14 *.cpp *.h -o a.exe


--------------------------------
Analyze Results
--------------------------------
To analyze results for either Blind Search or Repeated Local Searchwe use analyzer.py a script that calls the compiled
executable with an input file.

Requirements to run analyzer.py:
- Have python 3.0 installed
- Ensure there are <function_name>.csv files for each function in the input directory
- Ensure there is the required output dir structure listed in the file structure.

Run analyzer.py with:
python analyzer.py
from terminal in the src directory.

--------------------------------
Output
--------------------------------
The output of analyzer.py is the correct .csv file in all locations and in each group of 10 functions a CondensedResults.txt
file that gives the average, standard deviation, and exectution time for 30 iterations of either DE or PSO