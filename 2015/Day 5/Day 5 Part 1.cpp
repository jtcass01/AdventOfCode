/*Jacob Cassady
Advent of Code
Day 5
Date Created: 12/6/15
Last Updated: 06/17/16*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int examineLine(string);
bool vowelCheck(string);
bool repeatCheck(string);
bool stringCheck(string);

int main(void){
	string line;
	int niceCount=0;
//	line = "haegwjzuvuyypxyu";
	char fileLocation[100];

	cout << "Please enter the file path: ";
	cin >> fileLocation;


	ifstream myfile (fileLocation);

	while(getline(myfile,line)){
		cout << line << endl;
		niceCount += examineLine(line);
	}
	myfile.close();
//	niceCount += examineLine(line);
	cout << "niceCount: " << niceCount << endl;
}

bool vowelCheck(string line){
	int i, vowelCount=0;

	for (i=0;i<line.length();i++){
		if((line[i] == 'a')){
			vowelCount++;
		}
		if((line[i] == 'e')){
			vowelCount++;
		}
		if((line[i] == 'i')){
			vowelCount++;
		}
		if((line[i] == 'o')){
			vowelCount++;
		}
		if((line[i] == 'u')){
			vowelCount++;
		}
	}
	if (vowelCount >= 3){
		return true;
	} else {
		return false;
	}
}// end vowelCheck();

bool repeatCheck(string line){
	char temp;
	int i;

	for (i=1;i<line.length();i++){
		temp = line[(i-1)];
		if (temp == line[i]){
			return true;
		}
	}
	return false;
}// end repeatCheck();

bool stringCheck(string line){
	int i;
	string temp;
	string ab = "ab";
	string cd = "cd";
	string pq = "pq";
	string xy = "xy";

	 for (i=0;i<((line.length())-1);i++){
		temp = line.substr(i,2);
	 	if(temp == ab){
	 		return false;
	 	}
	 	if(temp == cd){
	 		return false;
	 	}
	 	if(temp == pq){
	 		return false;
	 	}
	 	if(temp == xy){
	 		return false;
	 	}
	 }
	 return true;
}

int examineLine(string line){
	if (vowelCheck(line) && repeatCheck(line) && stringCheck(line)){
		return 1;
	} else {
		return 0;
	}
}// end examineLine()
