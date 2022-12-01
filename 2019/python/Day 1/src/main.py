import numpy as np
import os
from math import floor

from FileHandler import FileHandler

def calculate_fuel(mass):
    return floor(mass / 3) - 2

def part1(input_data):
    return sum(list(map(calculate_fuel, input_data)))

def part2(input_data):
    part2_output = list([])

    for module in input_data:
        fuel = calculate_fuel(module)
        valid_fuels = list([])

        while fuel > 0:
            valid_fuels.append(fuel)
            fuel = calculate_fuel(fuel)

        part2_output.append(np.array(valid_fuels).sum(axis=None))

    return np.array(part2_output).sum(axis=None)


if __name__ == '__main__':
    test = [12, 14, 1969, 100756]
    print('test|data', test)
    test_output= list(map(calculate_fuel, test))
    print('test|part1', test_output)
    print('test|part2', part2(test))

    print()

    input_data = FileHandler.read_input(os.getcwd() + os.path.sep + '..' + os.path.sep + 'input.txt')
    print('input', input_data)
    print('part1_output', part1(input_data))
    print('part2_output', part2(input_data))
