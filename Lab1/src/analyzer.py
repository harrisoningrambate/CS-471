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


def standard_deviation(values):
    result = 0
    mean = average(values)
    for value in values:
        result += (value - mean) * (value - mean)
    result /= (len(values) - 1)
    result = result ** 0.5
    return result


# list of functions to execute the subprocess on
# each function should have a correlating .csv file in the local input folder
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
function_results = {}
# map from function name to execution time
exec_times = {}
for input in functions:
    start_time = time.perf_counter()
    subprocess.run(["./a.exe", input + ".csv"])
    stop_time = time.perf_counter()
    exec_times[input] = stop_time - start_time
    function_results[input] = []

# read output fitness values into function_results
for file in functions:
    try:
        f = open("output/" + file + ".csv", 'r')
        for line in f:
            # output file has "fitness,vec[0],vec[1],...,vec[dimension - 1]"
            first_comma = line.find(',')
            function_results[file].append(float(line[:first_comma]))
    except FileNotFoundError:
        print(f"Error: The file '{file}.csv' was not in the output directory")

function_averages = {}
function_medians = {}
function_ranges = {}
function_stand_dev = {}
for function in functions:
    # sort results once since multiple functions require a sorted list
    function_results[function].sort()
    function_averages[function] = average(function_results[function])
    function_medians[function] = median(function_results[function])
    function_ranges[function] = fitness_range(function_results[function])
    function_stand_dev[function] = standard_deviation(
        function_results[function])


for function in functions:

    print(function)
    print(f"\tAverage: {function_averages[function]:.2f}")
    print(f"\tMedian: {function_medians[function]:.2f}")
    print(f"\tRange: {function_ranges[function]:.2f}")
    print(f"\tStandard Deviation: {function_stand_dev[function]:.2f}")
    print(f"\tExecution Time: {exec_times[function]:.4f}")

print(f"Mean of Averages: {average(list(function_averages.values())):.2f}")
print(f"Mean of Medians: {average(list(function_medians.values())):.2f}")
print(f"Mean of Range: {average(list(function_ranges.values())):.2f}")
print(f"Mean of Standard Deviations: {
      average(list(function_stand_dev.values())):.2f}")
print(f"Mean of Execution Time: {average(list(exec_times.values())):.4f}")
