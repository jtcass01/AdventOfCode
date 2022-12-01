import numpy as np
import matplotlib.pyplot as plt
import os
from math import floor
import enum
from copy import deepcopy

from FileHandler import FileHandler


class FrontPanel(object):
    def __init__(self, wires):
        self.wires = wires
        self.gui = FrontPanel.GUI(wires)

    class GUI(object):
        def __init__(self, wires):
            self.wires = wires
            self.display_char = self.genereate_display()

        def __str__(self):
            return str(self.display_char)

        def genereate_display(self):
            current_location = np.array((0, 0), dtype=np.float32)
            locations_visited = list([current_location])
            intersections = list([])
            lines = list([])

            for wire in self.wires:
                print()
                print('adding wire', wire)
                new_location = wire.augment_location(current_location)
                for line in lines:
                    intersection = FrontPanel.GUI.calculate_intersection(line, (current_location, new_location))
                    if intersection is not None:
                        intersections.append(intersection)
                lines.append((current_location, new_location))
                print('intersections', intersections)
                locations_visited.append(new_location)
                current_location = new_location
                print(current_location, 'current_location')


                x_coords = list([])
                y_coords = list([])
                for location in locations_visited:
                    x_coords.append(location[0])
                    y_coords.append(location[1])

                plt.plot(x_coords, y_coords)
                plt.show()



        @staticmethod
        def calculate_intersection(line1, line2):
            def bounding_boxes_intersect(line1, line2):
                return line1[0][0] <= line2[1][0] and line1[1][0] >= line2[0][0] and line1[0][1] <= line2[1][1] and line1[1][1] >= line2[0][1]

            def perp(a):
                b = np.empty_like(a)
                b[0] = -a[1]
                b[1] = a[0]
                return b

            a1, a2 = line1
            b1, b2 = line2

            if bounding_boxes_intersect(line1, line2):
                da = a2-a1
                db = b2-b1
                dp = a1-b1
                dap = perp(da)
                denom = np.dot(dap, db)
                num = np.dot(dap, dp)

                result = (num / denom.astype(float)) * db + b1

                return result
            else:
                return None



class Wire(object):
    def __init__(self, wire_string):
        self.direction = Wire.DIRECTION.classify(wire_string[0])
        self.length = int(wire_string[1:])

    def __str__(self):
        return str(self.direction) + '|' + str(self.length)

    def __eq__(self, other):
        return self.direction == other.direction and self.length == other.length

    def __lt__(self, other):
        return self.length < other.length

    def __le__(self, other):
        return self.length <= other.length

    def __gt__(self, other):
        return self.length > other.length

    def __ge__(self, other):
        return self.length >= other.length

    def augment_location(self, current_location):
        new_location = list(current_location)

        if self.direction == Wire.DIRECTION.DIRECTION_UP:
            new_location[1] += self.length
            return np.array(new_location, dtype=np.float32)
        elif self.direction == Wire.DIRECTION.DIRECTION_RIGHT:
            new_location[0] += self.length
            return np.array(new_location, dtype=np.float32)
        elif self.direction == Wire.DIRECTION.DIRECTION_DOWN:
            new_location[1] -= self.length
            return np.array(new_location, dtype=np.float32)
        elif self.direction == Wire.DIRECTION.DIRECTION_LEFT:
            new_location[0] -= self.length
            return np.array(new_location, dtype=np.float32)

    class DIRECTION(enum.Enum):
        DIRECTION_INVALID = 0,
        DIRECTION_UP = 1,
        DIRECTION_RIGHT = 2,
        DIRECTION_DOWN = 3,
        DIRECTION_LEFT = 4

        @staticmethod
        def classify(data):
            if data == 'U':
                return Wire.DIRECTION.DIRECTION_UP
            elif data == 'R':
                return Wire.DIRECTION.DIRECTION_RIGHT
            elif data == 'D':
                return Wire.DIRECTION.DIRECTION_DOWN
            elif data == 'L':
                return Wire.DIRECTION.DIRECTION_LEFT
            else:
                return Wire.DIRECTION.DIRECTION_INVALID

def part1(input_data):
    wires = list([])

    # Generate wire objects
    for wire_string in input_data:
        wire = Wire(wire_string)
        wires.append(wire)

    front_panel = FrontPanel(wires)



def part2(input_data):
    pass

if __name__ == '__main__':
    test0 = ['R8','U5','L5','D3']
    print('test0|data', test0)
    print('test0|part1 [expected]', 6)
    print('test0|part1 [actual]', part1(test0))

    print()

    test1 = ['R75','D30','R83','U83','L12','D49','R71','U7','L72','U62','R66','U55','R34','D71','R55','D58','R83']
    print('test1|data', test1)
    print('test1|part1 [expected]', 159)
    print('test1|part1 [actual]', part1(test1))

#    print()

#    test2 = ["R98","U47","R26","D63","R33","U87","L62","D20","R33","U53","R51","U98","R91","D20","R16","D67","R40","U7","R15","U6","R7"]
#    print("test2|data", test2)
#    print("test2|part1 [expected]", 135)
#    print("test2|part1 [actual]", part1(test2))

#    input_data = FileHandler.read_input(os.getcwd() + os.path.sep + ".." + os.path.sep + "input.txt")
#    print("input", input_data)
#    print("part1_output", part1(input_data))
