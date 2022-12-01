/*Jacob Cassady
Advent of Code
Day 1: Challenge 1
First Created: 12/5/15
Last Upadted: 6/17/16*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(void){
	string line;
	int floor = 0,i=0,position=1;
	char temp = '\0';
	char fileLocation[100];

	cout << "Please enter the file path: ";
	cin >> fileLocation;


	ifstream myfile (fileLocation);
	if(myfile.is_open()) {
		while(getline(myfile,line)){
			cout << line << '\n';
			for (i=0;i<line.length();i++){
				temp = line[i];
				if (temp == '('){
					floor++;
				} else if (temp == ')'){
					floor--;
				}
				if(floor == -1){
					cout << "He has now hit the floor -1 at position: " << position << endl;
				}
				position++;
			}
			cout << "Floor " << floor << '\n';
		}
	}
	myfile.close();
}
