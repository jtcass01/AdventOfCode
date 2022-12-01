"""solution.py: Solution to Day x Advent of Code 2021"""
from __future__ import annotations

__author__ = 'Jacob Taylor Cassady'
__email__ = 'jacobtaylorcassady@outlook.com'

# Built-in modules
from unittest import TestCase, main
from enum import unique, Enum
from os.path import isfile, join, dirname
from typing import List, Tuple
from parse import parse

# 3rd Party modules

@unique
class PART(Enum):
    ONE: str = 'one'
    TWO: str = 'two'

class Rule(object):
    FORMAT: str = '{} -> {}'

    def __init__(self, substring: str, insertion: str) -> None:
        self.substring: str = substring
        self.insertion: str = insertion

    def apply(self, polymer_templates: List[str]) -> List[str]:
        def chunk_splits(splits: List[str]) -> Tuple[List[str]]:
            return (splits[index: index+2] for index in range(0, len(splits), 2))

        new_representation: List[str] = polymer_templates

        for polymer_template_index, polymer_template_substring in enumerate(polymer_templates):
            if self.substring in polymer_template_substring and len(polymer_template_substring):
                new_representation: List[str] = [template_substring for template_index, template_substring \
                                                 in enumerate(polymer_templates) if template_index != polymer_template_index]
                print(f'{self.substring} found in {polymer_template_substring}')

                print(f'Before: {polymer_templates}')

                splits = polymer_template_substring.split(self.substring)

                print(f'splits: {splits}')

                for split_chunk in chunk_splits(splits=splits):
                    new_representation.append(split_chunk[0] + self.substring[0])
                    new_representation.append(self.insertion)
                    new_representation.append(self.substring[1] + split_chunk[1])
                    print(split_chunk, new_representation)

                print(f'after: {new_representation}')
        return new_representation


class PolymerizationEquipment(object):
    def __init__(self, polymer_template: str, rules: List[Rule]) -> None:
        self.polymer_template: str = polymer_template
        self.rules: List[Rule] = rules

    def __str__(self) -> str:
        return f'polymer_template: {self.polymer_template} | rules: {self.rules}'

    def step(self) -> None:
        polymer_templates: str = [self.polymer_template]

        for rule in self.rules:
            polymer_templates = rule.apply(polymer_templates)
            print(polymer_templates)

    @staticmethod
    def load(puzzle_input_file_path: str) -> PolymerizationEquipment:
        assert isfile(puzzle_input_file_path), f'File not found: {puzzle_input_file_path}'
        base_string_found: bool = False
        rules: List[Rule] = []

        with open(puzzle_input_file_path) as puzzle_input_file:
            for line in puzzle_input_file.readlines():
                if base_string_found:
                    substring, insertion = parse(Rule.FORMAT, line[:-1])
                    rules.append(Rule(substring=substring, insertion=insertion))
                else:
                    if line[:-1] == '':
                        base_string_found = True
                    else:
                        polymer_template: str = line[:-1]

        return PolymerizationEquipment(polymer_template=polymer_template, rules=rules)


class Examples(TestCase):
    def test_part_one_example(self) -> None:
        print(f'\nPerforming unittest: {Examples.test_part_one_example}')

        polymerization_equipment: PolymerizationEquipment = PolymerizationEquipment.load(puzzle_input_file_path=join(dirname(__file__), 'example.txt'))
        polymerization_equipment.step()

        print(f'Unittest {Examples.test_part_one_example} was successful.')

    def test_part_two_example(self) -> None:
        print(f'\nPerforming unittest: {Examples.test_part_two_example}')

        print(f'Unittest {Examples.test_part_two_example} was successful.')

class Solutions(TestCase):
    def test_part_one(self) -> None:
        print(f'\nCalculating solution to {Solutions.test_part_one}')

        print(f'Part one solution calculated to be: {0.}.')

    def test_part_two(self) -> None:
        print(f'\nCalculating solution to {Solutions.test_part_two}')

        print(f'Part two solution calculated to be: {0.}.')

if __name__ == '__main__':
    main()
