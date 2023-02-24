#include <iostream>
//#include "Driver.h"

using namespace std;

// na gotowo_________________

class Parameters
{
private:
	//variables
	int velocity, velocityDefined;
	int distance, distanceDefined;
	int choice, choiceCruise;
	bool test;
	char activityV, activityD;

public:

	//constructor
	Parameters(int pVelocity = 30, int pVelocityDefined = 30, int pDistance = 50, int pDistanceDefined = 50, bool pTest = 0, char pActivityV = ' ', char pActivityD = ' ', 
		int pChoice = 1, int pChoiceCruise = 0) : velocity(pVelocity), velocityDefined(pVelocityDefined), distance(pDistance), distanceDefined(pDistanceDefined), test(pTest),
		activityV(pActivityV), activityD(pActivityD), choice(pChoice), choiceCruise(pChoiceCruise) {
		//dynamic memory allocation 
		//velocity = new int;
		//distance = new int;
		cout << "ACC START SYSTEM" << endl << endl;
		cout << "Check system..." << endl;
	}
	void getData();
	void definedData();
	void command();
	void changeD(char activityD);
	void changeV(char activityV);
	void CruiseType();

	friend istream& operator>>(istream& in, Parameters& obiekt);

	//destructor
	//~Parameters() { delete velocity, distance, test; }
};


//przeciążenie operatora in:
istream& operator>>(istream& in, Parameters& obiekt) {
	
	//pętla tak długo, aż pozytywny test
	while (obiekt.test == 0)
	{
		cout << "Result: ";
		in >> obiekt.test;

		if (obiekt.test == 1) { cout << endl << "System is ready to work." << endl << endl; }
		else { cout << "ERROR! Check manual!" << endl; }
	}

	return in;
}

void emergencyStop() { cout << "Emergency Stop!"; };

//zmiana parametrów: velocity, distance
void Parameters::changeV(char activityV) {
	switch (activityV)
	{
	case '+':
		velocity++;
		break;

	case '-':
		velocity--;
		break;
	}
}

void Parameters::changeD(char activityD) {
	switch (activityD)
	{
	case '+':
		distance = distance + 10;
		break;

	case '-':
		distance = distance - 10;
		break;
	}
}

void Parameters::CruiseType() {

	switch (choiceCruise)
	{
		//ACC
	case 1:
		cout << "ACC: " << endl;
		break;

		//Normal
	case 2:
		cout << "CC: " << endl;
		break;
	}

};

//wyświetlanie aktualnych zdefiniowanych danych
void Parameters::definedData() {

	switch (choiceCruise)
	{
		//ACC
	case 1:
		cout << "Defined velocity: " << velocityDefined << " km/h" << endl;
		cout << "Defined distance: " << distanceDefined << " m" << endl;
		break;

	//Normal
	case 2:
		cout << "Defined velocity: " << velocityDefined << " km/h" << endl;
		break;
	}
}

void Parameters::getData() {
	cout << "Velocity: " << velocity << " km/h" << endl;
	cout << "Distance: " << distance << " m" << endl;
}

//pętla do wyboru
void Parameters::command() {

	while (choice != 0)
	{
		cout << endl << "Enter a command" << endl;
		cout << "0/ RESET" << endl;
		cout << "1/ SET" << endl;
		cout << "2/ Velocity +" << endl;
		cout << "3/ Velocity -" << endl;
		cout << "4/ Distance +" << endl;
		cout << "5/ Distance -" << endl;
		cout << "6/ Cruise Controll type:" << endl;
		cout << "Choice: " << endl;
	cin >> choice;

		cout << endl;
	switch (choice)
	{
		case 0:
			emergencyStop();
			break;

		case 6:
			//odwołanie do funkcji
			cout << '\t' << "1. Adaptiv" << endl << '\t' << "2. Normal" << endl;

			//type choice
			choiceCruise = 2;

			CruiseType();
			break;

	case 1:
			distanceDefined = distance;
			velocityDefined = velocity;
			definedData();
		break;

	case 2:
			changeV('+');
			getData();
			break;

		case 3:
			changeV('-');
			getData();
			break;

		case 4:
			changeD('+');
			getData();
			break;

		case 5:
			changeD('-');
			getData();
			break;
	}
}
}


int main()
{
	//parametry do zmiany 

	Parameters p1;
	cin >> p1;

	p1.getData();

	p1.command();
	

}

