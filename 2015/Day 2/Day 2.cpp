/*Jacob Cassady
Advent of Code
Day 2
First Created: 12/6/15
Last Upadted: 6/17/16
*/


#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int examineLine(string);
void printLine(int, int, int, int, int, int, bool, bool, bool);
void printLine(int, int, int);
int combine(int, int, bool);
int compute(int, int, int);
int ribbonNeeded(int, int, int);

int main(void) {
	string line;
	int lineNumber = 1, total = 0;
	char fileLocation[100];

	cout << "\n\tPlease enter the file path: ";
	cin >> fileLocation;

	ifstream myfile(fileLocation);
	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			total += examineLine(line);
		}
	}
	cout << "Total: " << total << endl;
	myfile.close();
}

void printLine(int l1, int l2, int w1, int w2, int h1, int h2, bool l2status, bool w2status, bool h2status) {
	if (l2status && w2status && h2status) {
		cout << l1 << l2 << "x" << w1 << w2 << "x" << h1 << h2 << endl;
	}
	if (!l2status && w2status && h2status) {
		cout << l1 << "x" << w1 << w2 << "x" << h1 << h2 << endl;
	}
	if (l2status && !w2status && h2status) {
		cout << l1 << l2 << "x" << w1 << "x" << h1 << h2 << endl;
	}
	if (l2status && w2status && !h2status) {
		cout << l1 << l2 << "x" << w1 << w2 << "x" << h1 << endl;
	}
	if (!l2status && w2status && !h2status) {
		cout << l1 << "x" << w1 << w2 << "x" << h1 << endl;
	}
	if (!l2status && !w2status && h2status) {
		cout << l1 << "x" << w1 << "x" << h1 << h2 << endl;
	}
	if (l2status && !w2status && !h2status) {
		cout << l2 << "x" << w1 << "x" << h1 << endl;
	}
} //end printLine()

void printLine(int length, int width, int height) {
	cout << length << "x" << width << "x" << height << endl;
} //end printLine()

int combine(int i1, int i2, bool i2status) {
	if (i2status) {
		i1 *= 10;
		return (i1 + i2);
	}
	else {
		return i1;
	}
} // end combine()

int ribbonNeeded(int length, int width, int height) {
	int result = 0, volume = 0, smallestPerimeter = 0;

	if ((length >= width) && (length >= height)) {
		smallestPerimeter = ((2 * width) + (2 * height));
	}
	else if ((width >= length) && (width >= height)) {
		smallestPerimeter = ((2 * length) + (2 * height));
	}
	else if ((height >= length) && (height >= width)) {
		smallestPerimeter = ((2 * width) + (2 * length));
	}

	volume = (length*width*height);

	result = (volume + smallestPerimeter);
}

int compute(int length, int width, int height) {
	int result = 0, slack = 0, surfaceArea = 0;

	if ((length >= width) && (length >= height)) {
		slack = (width*height);
	}
	else if ((width >= length) && (width >= height)) {
		slack = (length*height);
	}
	else if ((height >= length) && (height >= width)) {
		slack = (length*width);
	}

	surfaceArea = ((2 * length*width) + (2 * width*height) + (2 * height*length));

	result = surfaceArea + slack;
	cout << "Result: " << result << endl;
	return result;
}

int examineLine(string line) {
	int i = 0, l1 = 0, l2 = 0, w1 = 0, w2 = 0, h1 = 0, h2 = 0, length = 0, width = 0, height = 0;
	bool l2status = false;
	bool w2status = false;
	bool h2status = false;

	//01x45x67
	l1 = (int)line[0] - 48;
	if (line[1] == 'x') {
		//0xxxxxx
		w1 = (int)line[2] - 48;
		if (line[3] == 'x') {
			//0x2xxxx
			h1 = line[4] - 48;
			if (line.length() == 6) {
				//0x2x45
				h2 = (int)line[5] - 48;
				h2status = true;
			}
		}
		else {
			//0x23x56
			w2 = (int)line[3] - 48;
			w2status = true;
			h1 = (int)line[5] - 48;
			if (line.length() == 7) {
				h2 = (int)line[6] - 48;
				h2status = true;
			}
		}
	}
	else {
		//01xxxxxx
		l2 = (int)line[1] - 48;
		l2status = true;
		w1 = (int)line[3] - 48;
		if (line[4] == 'x') {
			h1 = (int)line[5] - 48;
			if (line.length() == 7) { //01x3x56
				h2 = (int)line[6] - 48;
				h2status = true;
			}
		}
		else {
			//01x34x67
			w2 = (int)line[4] - 48;
			w2status = true;
			h1 = (int)line[6] - 48;
			if (line.length() == 8) {
				h2 = (int)line[7] - 48;
				h2status = true;
			}
		}
	}
	length = combine(l1, l2, l2status);
	width = combine(w1, w2, w2status);
	height = combine(h1, h2, h2status);
	printLine(length, width, height);
	return ribbonNeeded(length, width, height);
}
