from enum import Enum

class NUMBER(Enum):
    ONE: str = 'one'
    TWO: str = 'two'
    THREE: str = 'three'
    FOUR: str = 'four'
    FIVE: str = 'five'
    SIX: str = 'six'
    SEVEN: str = 'seven'
    EIGHT: str = 'eight'
    NINE: str = 'nine'

    def __str__(self) -> str:
        return self.value

number_dict: dict = {}
for index, number in enumerate(list(NUMBER), start=1):
    number_dict[index] = number.value

## Part 1
with open('input.txt', 'r') as file:
    total_calibration_value: int = 0
    lines: list = file.readlines()

    for line in lines:
        first_index: int = float('inf')
        first_number: str = ''
        last_index: int = float('-inf')
        last_number: str = ''

        for number in list(range(0, 10)):
            if str(number) in line:
                first_number_index: int = line.find(str(number))
                last_number_index: int = line.rfind(str(number))

                if first_number_index < first_index:
                    first_index = first_number_index
                    first_number = number
                if last_number_index >= last_index:
                    last_index = last_number_index
                    last_number = number

        total_calibration_value += int(first_number)*10 + int(last_number)

print(total_calibration_value)

## Part 2

with open('input.txt', 'r') as file:
    total_calibration_value: int = 0
    lines: list = file.readlines()

    for line in lines:
        first_index: int = float('inf')
        first_number: str = ''
        last_index: int = float('-inf')
        last_number: str = ''

        for value, number in number_dict.items():
            if number in line:
                first_number_index: int = line.find(number)
                last_number_index: int = line.rfind(number)

                if first_number_index < first_index:
                    first_index = first_number_index
                    first_number = value
                if last_number_index > last_index:
                    last_index = last_number_index
                    last_number = value

        for number in list(range(0, 10)):
            if str(number) in line:
                first_number_index: int = line.find(str(number))
                last_number_index: int = line.rfind(str(number))

                if first_number_index < first_index:
                    first_index = first_number_index
                    first_number = number
                if last_number_index >= last_index:
                    last_index = last_number_index
                    last_number = number

        total_calibration_value += int(first_number)*10 + int(last_number)

print(total_calibration_value)
