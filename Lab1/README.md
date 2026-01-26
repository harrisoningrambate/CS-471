# Lab 1 Blind Algorithm
Implementation and report of Blind Algorithm on 10 different Benchmark problem functions.

## Compilation
Compilation Requirements:
- Compiler GCC's `g++` compiler
- Be in the src directory

Compile on Windows from the src directory:
```
g++ -std=c++14 *.cpp *.h
```
Compile on Linux from the src directory:
```
g++ -std=c++14 *.cpp *.h -o a.exe
```

## Analyze Results
To analyze results we use analyzer.py a script that calls the compiled executable with an input file.\
Requirements to run analyzer.py:
- Have python 3.0 installed
- Ensure there are <function_name>.csv files for each function in the input directory
- Ensure there is an output directory in the src directory

Run analyzer.py with:
```
python analyzer.py
```
from terminal in the src directory.

### Output
The output from analyzer.py is the average, median, range, standard deviation for each benchmark function evaluated.
The execution time is listed for each experiment.
The mean of average, median, range, standard deviation, and execution time of all functions is also output.
