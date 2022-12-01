import numpy as np
import os
from math import floor
import enum
from copy import deepcopy

from FileHandler import FileHandler

class OPCODE(enum.Enum):
    OPCODE_INVALID = 0,
    OPCODE_ONE = 1,
    OPCODE_TWO = 2,
    OPCODE_NINE_NINE = 99

    @staticmethod
    def perform_operation(input_list, opcode, input_position_one, input_position_two, output_position):
        if opcode == OPCODE.OPCODE_ONE:
            input_list[output_position] = input_list[input_position_one] + input_list[input_position_two]
        elif opcode == OPCODE.OPCODE_TWO:
            input_list[output_position] = input_list[input_position_one] * input_list[input_position_two]
        elif opcode == OPCODE.OPCODE_NINE_NINE:
            pass
        elif opcode == OPCODE.OPCODE_INVALID:
            pass

    @staticmethod
    def classify(data):
        if data == 1:
            return OPCODE.OPCODE_ONE
        elif data == 2:
            return OPCODE.OPCODE_TWO
        elif data == 99:
            return OPCODE.OPCODE_NINE_NINE
        else:
            return OPCODE.OPCODE_INVALID

def part1(input_data):
    output_data = deepcopy(input_data)
    current_index = 0
    current_opcode = OPCODE.classify(input_data[current_index])

    while current_opcode != OPCODE.OPCODE_NINE_NINE and current_opcode != OPCODE.OPCODE_INVALID:
        OPCODE.perform_operation(output_data, current_opcode, output_data[current_index+1], output_data[current_index+2], output_data[current_index+3])
        current_index += 4
        current_opcode = current_opcode = OPCODE.classify(output_data[current_index])

    return output_data[0]

def part2(input_data):
    nouns = list(range(100))
    verbs = list(range(100))

    for noun in nouns:
        for verb in verbs:
            data = deepcopy(input_data)
            data[1] = noun
            data[2] = verb
            output = part1(data)
            print('[noun | verb | output] = ', noun, '|', verb, '|', output)

            if output == 19690720:
                return 100*noun+verb

if __name__ == '__main__':
    test0 = [1,9,10,3,2,3,11,0,99,30,40,50]
    print('test0|data', test0)
    print('test0|part1', part1(test0))

    print()
    test1 = [1,0,0,0,99]
    print('test1|data', test1)
    print('test1|part1 [expected]', [2,0,0,0,99])
    print('test1|part1 [actual]', part1(test1))

    print()
    test2 = [2,3,0,3,99]
    print('test2|data', test2)
    print('test2|part1', part1(test2))
    print('test2|part1 [expected]', [2,3,0,6,99])
    print('test2|part1 [actual]', part1(test2))

    print()
    test3 = [2,4,4,5,99,0]
    print('test3|data', test3)
    print('test3|part1', part1(test3))
    print('test3|part1 [expected]', [2,4,4,5,99,9801])
    print('test3|part1 [actual]', part1(test3))

    print()
    test4 = [1,1,1,4,99,5,6,0,99]
    print('test4|data', test4)
    print('test4|part1', part1(test4))
    print('test4|part1 [expected]', [30,1,1,4,2,5,6,0,99])
    print('test4|part1 [actual]', part1(test4))

    print()

    input_data = FileHandler.read_input(os.getcwd() + os.path.sep + '..' + os.path.sep + 'input.txt')
    # Restore gravity assist program
    input_data[1] = 12
    input_data[2] = 2
    print('input', input_data)
    print('part1_output', part1(input_data))
#    print("part2_output", part2(input_data))
    input_data[1] = 65
    input_data[2] = 33
    print('[noun | verb | output] = ', 65, '|', 33, '|', 19690720)
    print('part2_output', 100*65+33)
