Author: Harrison Ingram-Bate
Date Last Updated: 02/06/2026


--------------------------------
Introduction
--------------------------------
This project implements Blind Search and Repeated Local Search for N dimensions on 10 different Benchmark functions.
The included report CS471_Proj2 lists fitness functions and their specifications that are used to analyze the results.
The src directory contains .cpp and .h files for an executable, a python script to automate executaion for all functions,
an input directory that the executable uses to get specifications for all fitness functions, and an empty output directory
where you can find the results from running the executable.
The Results_CSV directory includes the results used for both blind search and repeated local search in the report.


--------------------------------
File Structure
--------------------------------
project_root/
|--src/
|  |--input/
|  |  `--*.csv	(* all function names)
|  |--output/
|  |  `--*.csv	(* all function names)
|  |--Main.cpp
|  |--Population.cpp
|  |--Population.h
|  |--Problem.cpp
|  |--Problem.h
|  |--Blind.cpp
|  |--Blind.h
|  |--RepeatedLocalSearch.cpp
|  |--RepeatedLocalSearch.h
|  `--analyzer.py
|--Results_CSV/
|  |--Blind_Results_CSV/
|  |  `--*.csv	(* all function names)
|  `--Repeated_Local_Search_CSV/
|     `--*.csv	(* all function names)
|--CS471_Proj2.pdf
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
- Ensure there is an output directory in the src directory

Run analyzer.py with:
python analyzer.py
from terminal in the src directory.

--------------------------------
Output
--------------------------------
The output from analyzer.py is the minimum fitness found, average, median, range, standard deviation for each benchmark
function evaluated.
The execution time is listed for each experiment. The mean of minimum fitness found, average, median, range, standard 
deviation, and execution time of all functions is also output.