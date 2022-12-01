import numpy as np

class FileHandler():
    @staticmethod
    def read_input(input_file_path):
        input_data = list([])

        with open(input_file_path) as input_file:
            for line in input_file.readlines():
                return np.array(list(map(int, line[:-1].split(','))))
