#!/usr/bin/env python3
import sys

# Ensure correct number of arguments
if len(sys.argv) != 6:
    print("Usage: python script.py <file1> <file2> <output_file1> <output_file2> <common_file>")
    sys.exit(1)

# Get file paths from command line arguments
file1_path = sys.argv[1]
file2_path = sys.argv[2]
output1_path = sys.argv[4]
output2_path = sys.argv[3]
common_path = sys.argv[5]

# Read lines from file1
with open(file1_path, 'r') as file1:
    lines_file1 = set(file1.readlines())

# Read lines from file2 and remove lines found in file1
with open(file2_path, 'r') as file2:
    filtered_lines = [line for line in file2 if line not in lines_file1]

with open(file2_path, 'r') as file2:
    removed_lines = [line for line in file2 if line in lines_file1]

# Read lines from file1
with open(file1_path, 'r') as file1:
    lines_file1 = [line for line in file1 if line not in removed_lines]

# Write the result to output file
with open(output1_path, 'w') as output_file:
    output_file.writelines(filtered_lines)

# Write the result to output file
with open(output2_path, 'w') as output_file:
    output_file.writelines(lines_file1)

with open(common_path, 'w') as common_file:
    common_file.writelines(removed_lines)

