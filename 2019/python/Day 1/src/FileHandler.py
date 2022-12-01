import numpy as np

class FileHandler():
    @staticmethod
    def read_input(input_file_path):
        input_data = list([])

        with open(input_file_path) as input_file:
            for line in input_file.readlines():
                input_data.append(int(line[:-1]))

        return np.array(input_data)
