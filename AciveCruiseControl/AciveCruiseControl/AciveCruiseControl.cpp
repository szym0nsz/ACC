#include <iostream>
#include <cmath>
#include <stdio.h>

using namespace std;

//klasa Parameters
class Parameters
{
private:
	//variables
	unsigned int velocity, velocityDefined;
	unsigned int distance, distanceDefined;
	unsigned int distanceObstacle;
	int choice, choiceCruise;
	bool test;
	char activityV, activityD;

public:

	//constructor
	Parameters(unsigned int pVelocity = 30, unsigned int pVelocityDefined = 30, unsigned int pDistance = 50, unsigned int pDistanceDefined = 50, bool pTest = 0, 
		char pActivityV = ' ', char pActivityD = ' ', int pChoice = 1, int pChoiceCruise = 1, int distanceObstacle = 50) : velocity(pVelocity), 
		velocityDefined(pVelocityDefined), distance(pDistance), distanceDefined(pDistanceDefined), test(pTest), activityV(pActivityV), activityD(pActivityD), 
		choice(pChoice), choiceCruise(pChoiceCruise){
		//dynamic memory allocation 
		//velocity = new int;
		//distance = new int;
		cout << "---ACC START SYSTEM---" << endl << endl;
		cout << "Check system..." << endl;
	}
	void getData();
	void definedData();
	void command();
	void changeD(char activityD);
	void changeV(char activityV);
	void cruiseType();

	friend istream& operator>>(istream& in, Parameters& obiekt);

	//destructor
	//~Parameters() { delete distance, distanceDefined, distanceObstacle, choice, choiceCruise, test, activityV, activityD; }
};

//operator in:
istream& operator>>(istream& in, Parameters& obiekt) {
	
	//test loop
	while (obiekt.test == 0)
	{
		cout << "Result: ";
		in >> obiekt.test;

		if (obiekt.test == 1)	{ cout << endl << "System is ready to work." << endl << endl; }
		else					{ cout << "ERROR! Check manual!" << endl; }
	}

	return in;
}

//emergency stop
string* emergencyStop() {

	//dynamic memory alocation
	static string* s;
	s = new string;
	*s = "Emergency Stop!";

	return s; 
};

//velocity modification
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

//distance modification
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

//funkcja definiująca rodzaj tempomatu
void Parameters::cruiseType() {
	//dystans na sekundę - zerowanie
	auto s = 0;
	auto t = 0;
	
	switch (choiceCruise)
	{
		//ACC
	case 1:
		cout << endl << "---Adaptiv cruise control---" << endl;
		definedData();
		cout << endl;

		//pętla STOP.
		while (choice != 0)
		{
			cout << endl << "If stop press 0: ";
			cin >> choice;

			if (choice == 0)
			{
				cout << "ACC Stop!";
				break;
			}

			cout << "---Set distance obstacle: ";
			cin >> distanceObstacle;

			if (distanceObstacle < distanceDefined)
			{
		//handling (a = -10 km/h)
		do
		{
					cout << endl << "-!BRAKE!-" << endl;

					//calculate distance
			distanceObstacle = distanceObstacle + floor(velocity * 0.278);
					cout << "Virtual distance: " << distanceObstacle << " m" << endl;

					//calculate velocity
			velocity = velocity - 10;
					cout << "Virtual velocity: " << velocity << " km/h" << endl << endl;

					//naprawić z tym definiowaniem prędkości
			getData();
		} while (distanceObstacle <= distanceDefined);
			}

			else if (distanceObstacle > distanceDefined && velocity != velocityDefined)
			{
		//acceleration (a = 10 km/h)
		do
		{
					cout << endl << "-!Acceleration!-" << endl;

					//calculate distance
					distanceObstacle = distanceObstacle - floor(velocity * 0.278);
					cout << "Virtual distance: " << distanceObstacle << " m" << endl;

					//calculate velocity
					velocity = velocity + 10;
					cout << "Virtual velocity: " << velocity << " km/h" << endl << endl;


			//naprawić z tym definiowaniem prędkości
				getData();
				} while (distanceObstacle >= distanceDefined);
			}
		}
		break;

		//Normal
	case 2:
		cout << endl << "---Cruise control--- " << endl;
		definedData();
		break;
	}
};

//wyświetlanie zdefiniowanych danych pojazdu
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

//wyświetlanie chwilowych (niezapisanych) danych pojazdu
void Parameters::getData() {
	cout << "Velocity: " << velocity << " km/h" << endl;
	cout << "Distance: " << distance << " m" << endl;
}

//pętla działania programu
void Parameters::command() {

	while (choice != 0)
	{
		cout << endl << "---Enter a command---" << endl;
		cout << "0/ RESET" << endl;
		cout << "1/ SET" << endl;
		cout << "2/ Velocity +" << endl;
		cout << "3/ Velocity -" << endl;
		cout << "4/ Distance +" << endl;
		cout << "5/ Distance -" << endl;
		cout << "6/ Cruise Controll type:" << endl;
		cout << "Choice: ";
	cin >> choice;

		cout << endl;
	switch (choice)
	{
		case 0:
			//creation pointer
			string * pS;
			pS = emergencyStop();
			cout << * pS << endl;

			//memory release for emergencyStop()
			delete (pS);
			break;

		case 6:
			//odwołanie do funkcji
			cout << '\t' << "1. Adaptiv" << endl << '\t' << "2. Normal" << endl<<"enter type: ";

			cin >> choiceCruise;
			cruiseType();
			break;

	case 1:
			distanceDefined = distance;
			velocityDefined = velocity;
			definedData();
		break;

	case 2:
			changeV('+');

			//catch exception < 210km/h
			try {
				if (velocity > 210) {
					velocity--;
					throw 210; 
				}
			getData();
			}
			catch (int excV) { 
				//instead of getData();
			cout << "Velocity: " << excV << " km/h" << endl;
			cout << "Distance: " << distance << " m" << endl;
			}
			break;

		case 3:
			changeV('-');

			//catch exception < 30km/h
			try {
				if (velocity < 30) {
					velocity++;
					throw 30;
				}
			getData();
			}
			catch (int excV) {
				//instead of getData();
				cout << "Velocity: " << excV << " km/h" << endl;
				cout << "Distance: " << distance << " m" << endl;
			}
			break;

		case 4:
			changeD('+');

			//catch exception > 200m
			try {
				if (distance > 200) {
					distance = distance - 10;
					throw 200;
				}
			getData();
			}
			catch (int excD) {
				//instead of getData();
				cout << "Velocity: " << velocity << " km/h" << endl;
				cout << "Distance: " << excD << " m" << endl;
			}
			break;

		case 5:
			changeD('-');

			//catch exception < 50m
			try {
				if (distance < 50) {
					distance = distance + 10;
					throw 50;
				}
			getData();
			}
			catch (int excD) {
				//instead of getData();
				cout << "Velocity: " << velocity << " km/h" << endl;
				cout << "Distance: " << excD << " m" << endl;
			}
			break;
	}
}
}

int main()
{
	//p1 object creation in class Parameters 
	Parameters p1;

	//use of operator>> for the p1 object
	cin >> p1;

	//use of function command() for p1 object
	p1.command();
	
}


