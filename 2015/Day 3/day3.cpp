/*Jacob Cassady
Advent of Code
Day 3
Date Created: 12/6/15
Last Updated: 6/17/16*/

#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <cstdlib>

using namespace std;

	class house{
		protected:
			int x;
			int y;
		public:
			house();
			house(int,int);
			int getX(void) {return x;};
			int getY(void) {return y;};
			void setX(int);
			void setY(int);
			void display(void) const;
			bool operator==(const house& other) const{
				if ((x == other.x) && (y == other.y)){
					return true;
				} else {
					return false;
				}
			}
			bool operator<(const house & other) const{
				return (x<=other.x);
			}
	};

	house::house(){
		x=0;
		y=0;
	} // end house constructor

	house::house(int a, int b){
		x=a;
		y=b;
	} //end house constructor

	/////////////////////////////FUNCTION PROTOTYPE////////////////////////////
	int examineLine(string);

	int main(void){
		int count = 0;
		string line;
		//line = "^v^v^v^v^v";
		set<int,int> s;
		char fileLocation[100];

		cout << "Please enter the file path: ";
		cin >> fileLocation;

		ifstream myfile(fileLocation);
		if(myfile.is_open()){
			while(getline(myfile,line)){
				cout << line << endl;
				system("pause");
				count += examineLine(line);
				cout << "Current Count:" << count << endl;;
			}
		}
		myfile.close();
	//	count += examineLine(line);
		cout << "Final count: " << count << endl;
	}

	void house::setX(int a){
		this->x=a;
	} // end house::setX

	void house::setY(int b){
		this->y=b;
	} //end house::setY

	void house::display(void) const{
		cout << "Current position: (" << this->x << "," << this->y << ")" << endl;
	}

	int examineLine(string line){
		int i=0,x=0,y=0,count=0,santaX=0,santaY=0,roboX=0,roboY=0,turn=0;
		bool repeat;
		house temp;
		set<house> visitedHouses;
		set<house>::iterator iter;

		visitedHouses.insert(temp);

		for(i=0;i<line.length();i++){
			repeat = false;
			//Santa's Turn
			if(turn==0){
				switch(line[i]){
					case '>':
						santaX++;
						break;
					case '<':
						santaX--;
						break;
					case '^':
						santaY++;
						break;
					case 'v':
						santaY--;
						break;
				}
				temp.setX(santaX);
				temp.setY(santaY);
				temp.display();
				turn = 1;
			} else if (turn == 1){ //Robo's turn
				switch(line[i]){
					case '>':
						roboX++;
						break;
					case '<':
						roboX--;
						break;
					case '^':
						roboY++;
						break;
					case 'v':
						roboY--;
						break;
				}
				temp.setX(roboX);
				temp.setY(roboY);
				temp.display();
				turn = 0;
			}

			if (visitedHouses.empty()){
				visitedHouses.insert(temp);
			}
			for (iter=visitedHouses.begin(); iter!=visitedHouses.end();++iter){
				if ((*iter) == temp){
					repeat = true;
				}
			}
			if (!repeat){
				visitedHouses.insert(temp);
			}
		}
		//Display set
		cout << "Set display" << endl;
		for (iter=visitedHouses.begin(); iter!=visitedHouses.end();++iter){
			(*iter).display();
			count++;
		}
		cout << "Count within function: " << count << endl;
		return visitedHouses.size();
	}
