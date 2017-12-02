
import numpy as np

def part1(data_location = '/home/durzo/PycharmProjects/AdventOfCode/2017/Day 2/data/part1_data.txt'):
    row_difference = list([])

    with open(data_location) as file:
        data = file.read()
        lines = data.split('\n')
        for line in lines:
            row = np.array(line.split('\t'), dtype=int)
            max_value = np.amax(row)
            min_value = np.amin(row)
            row_difference.append(max_value-min_value)

    return np.array(row_difference, dtype=int).sum()

def part2(data_location = '/home/durzo/PycharmProjects/AdventOfCode/2017/Day 2/data/part2_data.txt'):
    result = list([])

    with open(data_location) as file:
        data = file.read()
        lines = data.split('\n')
        for line in lines:
            row = np.array(line.split('\t'),dtype=float)
            row_value = process_row(row)
            print(row, row_value)
            result.append(row_value)

    return np.array(result).sum()

def process_row(row):
    for value in row:
        for top_value in row:
            if value == top_value:
                pass
            else:
                if top_value % value == 0:
                    print(top_value, value)
                    return top_value / value


def main():
    part1_answer = part1()

    print(part1_answer)

    part2_answer = part2()

    print(part2_answer)

if __name__ == '__main__':
    main()