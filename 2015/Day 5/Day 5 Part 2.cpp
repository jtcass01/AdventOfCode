/*Jacob Cassady
Advent of Code
Day 5 Part 2
Date Created: 12/6/15
Last Updated: 6/17/16*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int examineLine(string);
bool repeatCheck(string);
bool skipCheck(string);

int main(void){
	string line;
	int niceCount=0;
	char fileLocation[100];

	cout << "Please enter the file path: ";
	cin >> fileLocation;


	ifstream myfile (fileLocation);
	while(getline(myfile,line)){
		cout << line << endl;
		niceCount += examineLine(line);
	}
	myfile.close();
	cout << "niceCount: " << niceCount << endl;
}

bool repeatCheck(string line){
	int i,j;
	string temp1;
	string temp2;

	for(i=0;i<(line.length()-3);i++){
		temp1 = line.substr(i,2);
		for(j=(i+2);j<(line.length()-1);j++){
			temp2=line.substr(j,2);
			if(temp1 == temp2){
				return true;
			}
		}
	}
	return false;
}

bool skipCheck(string line){
	int i;
	char temp;

	for (i=0;i<(line.length()-2);i++){
		temp = line[i+2];
		cout << "line[i]: " << line[i] << endl;
		cout << "Temp: " << temp << endl;
		if(line[i] == temp){
			return true;
		}
	}
	return false;
}

int examineLine(string line){
	if (repeatCheck(line) && skipCheck(line)){
		cout << "Nice String found!" << endl;
		return 1;
	} else {
		return 0;
	}
}// end examineLine()
