"""solution.py: Solution to Day x Advent of Code 2021"""
from __future__ import annotations

__author__ = 'Jacob Taylor Cassady'
__email__ = 'jacobtaylorcassady@outlook.com'

# Built-in modules
from unittest import TestCase, main
from enum import Enum
from os.path import isfile, join, dirname
from typing import List, Union
from parse import parse

# 3rd Party modules
from numpy import array, zeros, count_nonzero


class Fold(object):
    FOLD_FORMAT: str = 'fold along {}={}'

    def __init__(self, fold_type: FOLD, location: int) -> None:
        self.fold_type: Fold.FOLD = fold_type
        self.location: int = location

    def perform(self, paper: array) -> array:
        if self.fold_type == Fold.FOLD.LEFT:
            fold_left: array = paper[:self.location, :]
            fold_right: array = paper[self.location+1:, :]

            for row_index, row in enumerate(reversed(fold_right)):
                for column_index, value in enumerate(row):
                    if value:
                        fold_left[row_index, column_index] = 1

            return fold_left
        elif self.fold_type == Fold.FOLD.UP:
            fold_above: array = paper[:, :self.location]
            fold_down: array = paper[:, self.location+1:]

            for row_index, row in enumerate(fold_down):
                for column_index, value in enumerate(reversed(row)):
                    if value:
                        fold_above[row_index, column_index] = 1

            return fold_above

    class FOLD(Enum):
        UP: str = 'y'
        LEFT: str = 'x'



class Origami(object):
    DOT_FORMAT: str = '{},{}'
    def __init__(self, dot_coordinates: array, folds: List[Fold]) -> None:
        self.dot_coordinates: array = dot_coordinates
        self.folds: List[Fold] = folds
        self.oragami_representation: array = Origami.generate_oragami_representation(dot_coordinates=self.dot_coordinates,
                                                                                     folds=self.folds)

    @staticmethod
    def generate_oragami_representation(dot_coordinates: array, folds: List[Fold]) -> array:
        # initialize paper
        paper: array = zeros((max(dot_coordinates[:, 0])+1, max(dot_coordinates[:, 1])+1), dtype=int)

        # Add dots to paper
        for x, y in dot_coordinates:
            paper[x, y] = 1

        # make folds
        for fold in folds:
            paper = fold.perform(paper=paper)

        #print(f"origami:")
        #for row_index, row in enumerate(paper.T):
        #    print(row_index, row)

        return paper

    @staticmethod
    def load(puzzle_input_file_path: str) -> Origami:
        assert isfile(puzzle_input_file_path), f'File not found: {puzzle_input_file_path}'
        dot_coordinates: Union[array, List[array]]= []
        folds: List[Fold] = []
        fold_break_found: bool = False

        with open(puzzle_input_file_path) as puzzle_input_file:
            for puzzle_input_file_line in puzzle_input_file.readlines():
                if not fold_break_found:
                    if puzzle_input_file_line[:-1] == '':
                        fold_break_found = True
                    else:
                        dot_x, dot_y = parse(Origami.DOT_FORMAT, puzzle_input_file_line[:-1])
                        dot_coordinate: array = array((int(dot_x), int(dot_y)))
                        dot_coordinates.append(dot_coordinate)
                else:
                    fold_axis, location = parse(Fold.FOLD_FORMAT, puzzle_input_file_line[:-1])
                    folds.append(Fold(Fold.FOLD(fold_axis), location=int(location)))

        return Origami(dot_coordinates=array(dot_coordinates), folds=folds)


class Examples(TestCase):
    def test_part_one_example(self) -> None:
        print(f'\nPerforming unittest: {Examples.test_part_one_example}')

        test_origami: Origami = Origami.load(puzzle_input_file_path=join(dirname(__file__), 'example.txt'))
        print(test_origami.oragami_representation.T)

        print(f'Unittest {Examples.test_part_one_example} was successful.')

    def test_part_two_example(self) -> None:
        print(f'\nPerforming unittest: {Examples.test_part_two_example}')

        print(f'Unittest {Examples.test_part_two_example} was successful.')

class Solutions(TestCase):
    def test_part_one(self) -> None:
        print(f'\nCalculating solution to {Solutions.test_part_one}')

        test_origami: Origami = Origami.load(puzzle_input_file_path=join(dirname(__file__), 'input.txt'))

        print(f'Part one solution calculated to be: {count_nonzero(test_origami.oragami_representation)}.')

    def test_part_two(self) -> None:
        print(f'\nCalculating solution to {Solutions.test_part_two}')

        test_origami: Origami = Origami.load(puzzle_input_file_path=join(dirname(__file__), 'input.txt'))
        readable: List[array] = []

        for row in test_origami.oragami_representation:
            readable_row: List[str] = []
            for value in row:
                if value == 1:
                    readable_row.append('#')
                elif value == 0:
                    readable_row.append('.')
            readable.append(readable_row)

        readable: array = array(readable)

        for row in readable.T:
            print(list(row))

        print(f'Part two solution calculated to be: {0.}.')

if __name__ == '__main__':
    main()
