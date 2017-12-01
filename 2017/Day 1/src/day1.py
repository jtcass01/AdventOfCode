import numpy as np

def load_in_part1_examples(example_data_location = '/users/jcassady/PycharmProjects/AdventOfCode/2017/Day 1/data/day1_examples.txt'):
    examples = list([])

    with open(example_data_location) as file:
        raw_file_content = file.readlines()
        file_content = [content.strip() for content in raw_file_content]
        for content in file_content:
            example_input, example_output = content.split(' = ')
            example = {}
            example['example_input'] = example_input
            example['example_output'] = int(example_output)
            examples.append(example)

    return examples

def test_part1_examples(examples):
    for example in examples:
        if not test_part1_example(example):
            return False
    return True

def load_puzzle_data(puzzle_data_location = '/users/jcassady/PycharmProjects/AdventOfCode/2017/Day 1/data/day1_input.txt'):
    with open(puzzle_data_location) as file:
        data = file.read()

    return data

def test_part1_example(example):
    if process_part1_string(example['example_input']) == example['example_output']:
        print('Test example passed.  ', 'input: ', example['example_input'], 'output: ', process_part1_string(example['example_input']))
        return True
    else:
        print('Test example failed.  ', 'input: ', example['example_input'], 'output: ', process_part1_string(example['example_input']), 'expected_output: ', example['example_output'])
        return False

def process_part1_string(string_input):
    start_char = string_input[len(string_input)-1]
    neighbors = list([])

    test_sum = 0

    for next_char in string_input:
        if start_char == next_char:
            test_sum += int(start_char)
            neighbors.append(int(start_char))
        start_char = next_char

    sum = np.array(neighbors).sum()

    return sum

def load_in_part2_examples(example_data_location = '/users/jcassady/PycharmProjects/AdventOfCode/2017/Day 1/data/day1_part2_example.txt'):
    examples = list([])

    with open(example_data_location) as file:
        raw_file_content = file.readlines()
        file_content = [content.strip() for content in raw_file_content]
        for content in file_content:
            example = {}
            example_input, example_output = content.split(',')
            example['example_input'] = example_input
            example['example_output'] = int(example_output)
            examples.append(example)

    return examples


def test_part2_examples(examples):
    for example in examples:
        if not test_part2_example(example):
            return False
    return True

def test_part2_example(example):
    if process_part2_string(example['example_input']) == example['example_output']:
        print('Test example passed.  ', 'input: ', example['example_input'], 'output: ',
              process_part2_string(example['example_input']))
        return True
    else:
        print('Test example failed.  ', 'input: ', example['example_input'], 'output: ',
              process_part2_string(example['example_input']), 'expected_output: ', example['example_output'])
        return False


def process_part2_string(string_input):
    look_distance = len(string_input)/2
    start_char = string_input[-1]
    char_pass = 0
    current_char = -1
    next_char = current_char + look_distance
    matches = list([])

    while char_pass < len(string_input):
        if start_char == string_input[next_char]:
            matches.append(int(start_char))

        current_char += 1
        start_char = string_input[current_char]
        next_char = current_char + look_distance

        char_pass += 1

        if next_char >= len(string_input):
            next_char -= len(string_input)

    return np.array(matches).sum()



def main():
    part1_examples = load_in_part1_examples()

    if test_part1_examples(part1_examples):
        print('All Test examples passed.')
    else:
        print('You have failed a test example.')

    part1_puzzle = load_puzzle_data(puzzle_data_location='/users/jcassady/PycharmProjects/AdventOfCode/2017/Day 1/data/day1_input.txt')

    part1_puzzle_answer = process_part1_string(part1_puzzle)

    print('puzzle: ', part1_puzzle)
    print('answer: ', part1_puzzle_answer)
    print('\n\n\n')

    part2_examples = load_in_part2_examples()

    if test_part2_examples(part2_examples):
        print('All Test examples passed.')
    else:
        print('You have failed a test example.')

    part2_puzzle = load_puzzle_data(puzzle_data_location='/users/jcassady/PycharmProjects/AdventOfCode/2017/Day 1/data/day1_part2_input.txt')

    part2_puzzle_answer = process_part2_string(part2_puzzle)

    print('puzzle: ', part2_puzzle)
    print('answer: ', part2_puzzle_answer)

if __name__ == '__main__':
    main()
