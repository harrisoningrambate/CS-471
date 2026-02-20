# Name: Harrison Ingram-Bate
import subprocess
import time


# returns the average value from a list
def average(values):
    result = 0.0
    for value in values:
        result += value

    result /= len(values)
    return result


# returns the median from a sorted list
def median(values):
    if len(values) % 2 == 1:
        return values[len(values) // 2]
    else:
        val1 = values[(len(values) // 2) - 1]
        val2 = values[(len(values) // 2)]
        return (val1 + val2) / 2


# returns the range of a sorted list
def fitness_range(values):
    low = values[0]
    high = values[len(values) - 1]
    return high - low


# returns the standard deviation of a list
def standard_deviation(values):
    result = 0
    mean = average(values)
    for value in values:
        result += (value - mean) * (value - mean)
    result /= (len(values) - 1)
    result = result ** 0.5
    return result


def analyze_input(input_dir, output_dir, alg_num, strat=0):
    functions = ["Schwefel",
                 "FirstDeJong",
                 "Rosenbrock",
                 "Rastrigin",
                 "Griewangk",
                 "SineEnvelope",
                 "StretchedV",
                 "AckleyOne",
                 "AckleyTwo",
                 "EggHolder"]
    # function_results is a map with a function name as the key and the results from the executable as a list
    # map from function name to execution time
    function_results = {}
    exec_times = {}
    for function in functions:
        if (strat != 0):
            print(f"Searching {input_dir + str(strat)}/{function}")
        else:
            print(f"Searching {input_dir + function}")
        start_time = time.perf_counter()
        subprocess.run(
            ["./a.exe", input_dir + function + ".csv", str(alg_num), str(strat)])
        stop_time = time.perf_counter()
        exec_times[function] = stop_time - start_time
        function_results[function] = []

    # read output fitness values into function_results
    for file in functions:
        try:
            f = open(output_dir + file + ".csv", 'r')
            for line in f:
                # output file has "fitness,vec[0],vec[1],...,vec[dimension - 1]"
                first_comma = line.find(',')
                function_results[file].append(float(line[:first_comma]))
        except FileNotFoundError:
            print(f"Error: The file '{
                  file}.csv' was not in the output directory")

    # best fit maps a function name to its best fitness result
    best_fit = {}
    for function in functions:
        best_fit[function] = function_results[function][0]
        for fit in function_results[function]:
            if fit < best_fit[function]:
                best_fit[function] = fit

    function_averages = {}
    function_stand_dev = {}
    for function in functions:
        # sort results once since average function requires a sorted list
        function_results[function].sort()
        function_averages[function] = average(function_results[function])
        function_stand_dev[function] = standard_deviation(
            function_results[function])

    # log condensed results to a .txt file in same dir as all functions
    with open(output_dir + "CondensedResults.txt", 'w') as fp:
        for function in functions:
            fp.write(function + "\n")
            fp.write(f"\tAvg: {function_averages[function]:.2f}\n")
            fp.write(f"\tSD: {function_stand_dev[function]:.2f}\n")
            fp.write(f"\tExec Time: {exec_times[function]:.2f}\n\n")

    return


# lists used for different input files precedence being 1. Dimensions, 2. alg, 3. functions
dimensions = ["10", "20", "30"]
algs = ["DE", "PS"]

# call analyze_input for each possible combination of dimensions optimization, optimization algorithm, and strat(DE specific)
for dimension in dimensions:
    for alg in algs:
        input_dir = dimension + "/" + alg + "/"
        output_dir = "output/" + dimension + "/" + alg + "/"
        alg_num = 0
        if alg == "DE":
            alg_num = 1
            for strat in range(1, 11):
                analyze_input(input_dir, output_dir +
                              str(strat) + "/", alg_num, strat)
        else:
            alg_num = 2
            analyze_input(input_dir, output_dir, alg_num)
