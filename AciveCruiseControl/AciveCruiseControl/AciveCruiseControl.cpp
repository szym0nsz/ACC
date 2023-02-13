#include <iostream>
//#include "Driver.h"

using namespace std;

//system modes
void readyMode() {};
void errorTest() {};
void emergencyStop() {};
void adaptiveMode() {};
void passiveMode() {};

// na gotowo_________________

class Parameters
{
private:
	//variables
	int velocity;
	int distance;
	bool test;

public:

	//constructor
	Parameters(int pVelocity = 30, int pDistance = 50, bool pTest = 0) : velocity(pVelocity), distance(pDistance), test(pTest) {
		//dynamic memory allocation 
		//velocity = new int;
		//distance = new int;
		cout << "ACC START SYSTEM" << endl << endl;
		cout << "Check system..." << endl;

	}
	void getData();
	friend istream& operator>>(istream& in, Parameters& obiekt);

	//destructor
	//~Parameters() { delete velocity, distance; }
};


//przeciążenie operatora in:
istream& operator>>(istream& in, Parameters& obiekt) {
	cout << "Wynik testu: ";
	in >> obiekt.test;
	if (obiekt.test == 1) {
		cout << "OK" << endl;
		//getData();
	}
	else { cout << "ERROR! Check manual." << endl; }

	return in;
}


void Parameters::getData() {
	cout << "Defined velocity: " << velocity << endl;
	cout << "Defined distance: " << distance << endl;
}

int main()
{
	Parameters p1;
	cin >> p1;


	
	//p1.getData();

}

