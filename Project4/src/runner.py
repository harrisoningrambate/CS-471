# Name: Harrison Ingram-Bate
import subprocess

# run neh
neh_input = "Taillard_TestData"
aco_input = "output/neh"

# non-blocking
for i in range(1, 121):
    input_dir = f"{neh_input}/{i}.txt"
    output_dir = f"{aco_input}/non_blocking/{i}.txt"
    subprocess.run(["./a.exe", input_dir, output_dir, str(1), str(1)])
# blocking
for i in range(1, 121):
    input_dir = f"{neh_input}/{i}.txt"
    output_dir = f"{aco_input}/blocking/{i}.txt"
    subprocess.run(["./a.exe", input_dir, output_dir, str(1), str(2)])

# run aco
aco_output = "output/aco"
# non-blocking
for i in range(1, 121):
    input_dir = f"{aco_input}/non_blocking/{i}.txt"
    output_dir = f"{aco_output}/non_blocking/{i}.txt"
    subprocess.run(["./a.exe", input_dir, output_dir, str(2), str(1)])
# blocking
for i in range(1, 121):
    input_dir = f"{aco_input}/blocking/{i}.txt"
    output_dir = f"{aco_output}/blocking/{i}.txt"
    subprocess.run(["./a.exe", input_dir, output_dir, str(2), str(2)])
