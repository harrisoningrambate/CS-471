Author: Harrison Ingram-Bate
Date Last Updated: 03/16/2026


--------------------------------
Introduction
--------------------------------
This project implemts NEH and ACO for the flow shop scheduling problem in both
non-blocking and blocking versions.
The included report CS471_Project4 lists gives a brief descriptions of NEH and 
ACO and lists the resulting makespans and execution times.
The src directory contains .cpp and .h for an executable, a python script to
automate running the executable.
The Result_CSV directory includes the results used in the report.


--------------------------------
File Structure
--------------------------------
project_root/
|--src/
|  |--Taillard_TestData/
|  |  `--*.txt (* 1-120)
|  |--output/
|  |  |--neh/
|  |  |  |--non_blocking/
|  |  |  |  `--*.txt (* 1-120)
|  |  |  `--blocking/
|  |  |     `--*.txt (* 1-120)
|  |  `--aco/
|  |     |--non_blocking/
|  |     |  `--*.txt (* 1-120)
|  |     `--blocking/
|  |        `--*.txt (* 1-120)
|  |--main.cpp
|  |--MakespanFunctions.h
|  |--MakespanFunctions.cpp
|  |--FShop.h
|  |--FShop.cpp
|  |--NEH.h
|  |--NEH..cpp
|  |--ACO.h
|  |--ACO.cpp
|  `runner.py
|--CS471_Project4.pdf (Project Report)
|--CS471_Proj4.pdf (Doxygen pdf)
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
Run Executable
--------------------------------
To run the executable for all testdata with both blocking and non_blocking makespans
on both NEH and ACO fed with NEH.


Requirements to run analyzer.py:
- Have python 3.0 installed
- Ensure that the Taillard_TestData is in the same directory
- Ensure there is the required output dir structure listed in the file structure.

Run runner.py with:
python runner.py
from terminal in the src directory.


--------------------------------
Output
--------------------------------
The output of runner.py is all non-blocking and blocking makespans and the flow shop
in the corresponding file heirarchy found in the file structure.
