#include <iostream>
#include <cmath>
#include <stdio.h>
//#include "Driver.h"

using namespace std;

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
		//wyjątek21
		distance = distance + 10;
		break;

	case '-':
		//wyjątek22
		distance = distance - 10;
		break;
	}
}

void Parameters::CruiseType() {
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
		//distanceObstacle = 40;

		//pętla tak długo, aż nie STOP.
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

			//obliczenie dystansu
			distanceObstacle = distanceObstacle + floor(velocity * 0.278);
					cout << "Virtual distance: " << distanceObstacle << " m" << endl;

			//obliczenie prędkości
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

			//obliczenie dystansu
					distanceObstacle = distanceObstacle - floor(velocity * 0.278);
					cout << "Virtual distance: " << distanceObstacle << " m" << endl;

			//obliczenie prędkości
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

//pętla wyboru
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
			emergencyStop();
			break;

		case 6:
			//odwołanie do funkcji
			cout << '\t' << "1. Adaptiv" << endl << '\t' << "2. Normal" << endl<<"enter type: ";

			cin >> choiceCruise;
			CruiseType();
			break;

	case 1:
			distanceDefined = distance;
			velocityDefined = velocity;
			definedData();
		break;

	case 2:
			changeV('+');

			//wyłapanie wyjątku powyżej 210km/h
			try {
				if (velocity > 210) {
					velocity--;
					throw 210; 
				}
			getData();
			}
			catch (int excV) { 
				//zamiast getData();
			cout << "Velocity: " << excV << " km/h" << endl;
			cout << "Distance: " << distance << " m" << endl;
			}
			break;

		case 3:
			changeV('-');

			//wyłapanie wyjątku poniżej 30km/h
			try {
				if (velocity < 30) {
					velocity++;
					throw 30;
				}
			getData();
			}
			catch (int excV) {
				//zamiast getData();
				cout << "Velocity: " << excV << " km/h" << endl;
				cout << "Distance: " << distance << " m" << endl;
			}
			break;

		case 4:
			changeD('+');

			//wyłapanie wyjątku powyżej 200m
			try {
				if (distance > 200) {
					distance = distance - 10;
					throw 200;
				}
			getData();
			}
			catch (int excD) {
				//zamiast getData();
				cout << "Velocity: " << velocity << " km/h" << endl;
				cout << "Distance: " << excD << " m" << endl;
			}
			break;

		case 5:
			changeD('-');

			//wyłapanie wyjątku poniżej 50m
			try {
				if (distance < 50) {
					distance = distance + 10;
					throw 50;
				}
			getData();
			}
			catch (int excD) {
				//zamiast getData();
				cout << "Velocity: " << velocity << " km/h" << endl;
				cout << "Distance: " << excD << " m" << endl;
			}
			break;
	}
}
}


int main()
{
	//otworzenie obiektu p1
	Parameters p1;
	cin >> p1;

	p1.command();
	
}