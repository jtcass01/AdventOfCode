/*Jacob Cassady
Advent of Code
Day 6
Date Created: 12/8/15
Last Updated: 6/17/2016*/

#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>

using namespace std;

class light {
protected:
	int b;
public:
	light();
	light(int);
	void toggle(void);
	void toggleOn(void);
	void toggleOff(void);
	int getBrightness(void);
};

light::light() {
	b = 0;
}

light::light(int brightness){
	b = brightness;
}

void light::toggle(void) {
	b += 2;
}

void light::toggleOff(void) {
	if (b > 0) {
		b--;
	}
}

void light::toggleOn(void) {
	b++;
}

int light::getBrightness(void) {
	return b;
}

void examineLine(string, light [1000][1000]);
int checkFunction(string);
bool checkToggle(string);
bool checkToggleOn(string);
bool checkToggleOff(string);
void retrieveCoor(string, int*,int*,int*,int*);
int charToInt(char);
void resetCacheFor2(int[3]);
void resetCacheFor1(int[3]);
void printCache(int[3]);
void clearCache(int[3]);
int cacheToInt(int[3]);
void toggleOffSection(light[1000][1000], int, int, int, int);
void toggleOnSection(light[1000][1000], int, int, int, int);
void toggleSection(light[1000][1000], int, int, int, int);
int findBrightness(light[1000][1000]);

int main()
{
	string line;
	static light grid[1000][1000];
	int litCount = 0;
	char fileLocation[100];

	cout << "Please enter the file path: ";
	cin >> fileLocation;


	ifstream myfile(fileLocation);
	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			examineLine(line,grid);
		}
	}
	myfile.close();
	litCount = findBrightness(grid);
	cout << "Total Brightness: " << litCount << endl;
	//system("pause");
	return 0;
}


void examineLine(string line, light grid[1000][1000]) {
	cout << line << endl;
	int function = 0, x1 = 0, y1 = 0, x2 = 0, y2 = 0;
	function = checkFunction(line);

	switch (function) {
	case 0://ToggleOff
		cout << "ToggleOff function" << endl;
		retrieveCoor(line, &x1, &y1, &x2, &y2);
		toggleOffSection(grid, x1, y1, x2, y2);
		cout << "(" << x1 << "," << y1 << ") (" << x2 << "," << y2 << ")" << endl;
		break;
	case 1://ToggleOn
		cout << "ToggleOn function" << endl;
		retrieveCoor(line, &x1, &y1, &x2, &y2);
		cout << "(" << x1 << "," << y1 << ") (" << x2 << "," << y2 << ")" << endl;
		toggleOnSection(grid, x1, y1, x2, y2);
		break;
	case 2://Toggle
		cout << "Toggle Function" << endl;
		retrieveCoor(line, &x1, &y1, &x2, &y2);
		toggleSection(grid, x1, y1, x2, y2);
		cout << "(" << x1 << "," << y1 << ") (" << x2 << "," << y2 << ")" << endl;
		break;
	default:
		cout << "Error in function report" << endl;
		break;
	}
}

int checkFunction(string line) {
	int result = 4;

	if (checkToggleOff(line)) {
		result = 0;
	}
	if (checkToggleOn(line)) {
		result = 1;
	}
	if (checkToggle(line)){
		result = 2;
	}

	return result;
}

bool checkToggle(string line) {
	bool result = false;
	string temp;
	temp = line.substr(0, 6);
	if (temp == "toggle") {
		result = true;
	}

	return result;
}

bool checkToggleOff(string line) {
	bool result = false;
	string temp;
	temp = line.substr(5, 3);
	if (temp == "off") {
		result = true;
	}

	return result;
}

bool checkToggleOn(string line) {
	bool result = false;
	string temp;
	temp = line.substr(5, 2);
	if (temp == "on") {
		result = true;
	}

	return result;
}

void retrieveCoor(string line, int* x1, int* y1, int* x2, int* y2) {
	int i = 0,isDigitCount=0,clearCount=0;
	int cache[3] = { 0,0,0 };

	for (i = 0; i < line.length(); i++) {
		if (isdigit(line[i])) {
			cache[isDigitCount] = charToInt(line[i]);
			isDigitCount++;
		}
		else {
			if (isDigitCount > 0) {
				switch (isDigitCount) {
				case 0: //No digits found
					break;
				case 1: //1 DIGIT
					resetCacheFor1(cache);
					switch (clearCount) {
					case 0: //x1 spot
						(*x1) = cacheToInt(cache);
						clearCount++;
						clearCache(cache);
						break;
					case 1: //y1 spot
						(*y1) = cacheToInt(cache);
						clearCount++;
						clearCache(cache);
						break;
					case 2: //x2 spot
						(*x2) = cacheToInt(cache);
						clearCount++;
						clearCache(cache);
						break;
					}
					break;
				case 2: //2 DIGITS
					resetCacheFor2(cache);
					switch (clearCount) {
					case 0: //x1 spot
						(*x1) = cacheToInt(cache);
						clearCount++;
						clearCache(cache);
						break;
					case 1: //y1 spot
						(*y1) = cacheToInt(cache);
						clearCount++;
						clearCache(cache);
						break;
					case 2: //x2 spot
						(*x2) = cacheToInt(cache);
						clearCount++;
						clearCache(cache);
						break;
					}
					break;
				case 3: // 3DIGITS
					switch (clearCount) {
					case 0: //x1 spot
						(*x1) = cacheToInt(cache);
						clearCount++;
						clearCache(cache);
						break;
					case 1: //y1 spot
						(*y1) = cacheToInt(cache);
						clearCount++;
						clearCache(cache);
						break;
					case 2: //x2 spot
						(*x2) = cacheToInt(cache);
						clearCount++;
						clearCache(cache);
						break;
					}
					break;
				}
			}
			isDigitCount = 0;
		}
	}
	if (clearCount == 3) {
		switch(isDigitCount){
			case 1:
				resetCacheFor1(cache);
				break;
			case 2:
				resetCacheFor2(cache);
				break;
			case 3:
				break;
		}
		(*y2) = cacheToInt(cache);
	}
	clearCache(cache);
	clearCount++;
}

int charToInt(char c) {
	int result;

	result = c - '0';

	return result;
}

void printCache(int cache[3]) {
	int i = 0;

	for (i = 0; i < 3; i++) {
		cout << cache[i];
	}
	cout << endl;
}

void clearCache(int cache[3]) {
	int i = 0;

	for (i = 0; i < 3; i++) {
		cache[i] = 0;
	}
}

void resetCacheFor2(int cache[3]) {
	int temp1 = 0,temp2=0;

	temp1 = cache[0];
	temp2 = cache[1];
	clearCache(cache);
	cache[2] = temp2;
	cache[1] = temp1;
}

void resetCacheFor1(int cache[3]) {
	int temp = 0;
	temp = cache[0];
	clearCache(cache);
	cache[2] = temp;
}

int cacheToInt(int cache[3]) {
	int hundred=0,ten=0,one=0,result=0;

	hundred = (cache[0] * 100);
	ten = (cache[1] * 10);
	one = (cache[2]);

	result = (hundred + ten + one);
	return result;
}

void toggleOffSection(light grid[1000][1000], int x1, int y1, int x2, int y2) {
	int i = 0,j=0;

	for (i = x1; i <= x2; i++) {
		for (j = y1; j <= y2; j++) {
			grid[i][j].toggleOff();
		}
	}
}

void toggleOnSection(light grid[1000][1000], int x1, int y1, int x2, int y2) {
	int i = 0, j = 0;

	for (i = x1; i <= x2; i++) {
		for (j = y1; j <= y2; j++) {
			grid[i][j].toggleOn();
		}
	}
}

void toggleSection(light grid[1000][1000], int x1, int y1, int x2, int y2) {
	int i = 0, j = 0;

	for (i = x1; i <= x2; i++) {
		for (j = y1; j <= y2; j++) {
			grid[i][j].toggle();
		}
	}
}

int findBrightness(light grid[1000][1000]) {
	int i = 0, j = 0, brightness=0;

	for (i = 0; i < 1000; i++) {
		for (j = 0; j < 1000; j++) {
			brightness += (grid[i][j].getBrightness());
		}
	}
	cout << brightness << endl;
	return brightness;
}
