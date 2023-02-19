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
	char activityV, activityD;

public:

	//constructor
	Parameters(int pVelocity = 30, int pDistance = 50, bool pTest = 0, char pActivityV=' ', char pActivityD = ' ')
		: velocity(pVelocity), distance(pDistance), test(pTest), activityV(pActivityV), activityD(pActivityD) {
		//dynamic memory allocation 
		//velocity = new int;
		//distance = new int;
		cout << "ACC START SYSTEM" << endl << endl;
		cout << "Check system..." << endl;
	}

	void getData();
	void changeD(char activityD);
	void changeV(char activity);
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

		if (obiekt.test == 1)	{ cout << endl << "System is ready to work." << endl << "Enter a command" << endl << endl; }
		else					{ cout << "ERROR! Check manual!" << endl; }
	}

	return in;
}

//zmiana parametrów
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

//wyświetlanie aktualnych zdefiniowanych danych
void Parameters::getData() {
	cout << "Defined velocity: " << velocity << " km/h" << endl;
	cout << "Defined distance: " << distance << " m" << endl;
}

//pętla do wyboru
void command() {
	//variable definition;
	int choice = 0;

	cout << "Wpisać polecenie! (Wypisać wszystkie funkcje)" << endl;
	cin >> choice;

	switch (choice)
	{
	case 1:
		//odwołanie do funkcji
		cout << "OK";
		break;

	case 2:
		//odwołanie do funkcji
		break;
	}
}

int main()
{
	//parametry do zmiany 

	Parameters p1;
	cin >> p1;

	p1.getData();

	command();
	
	//koniec testów - start programu!
	//dodać pętle while z warunkiem, aż nie będzie wciśnięty STOP, a w ciele ma być ???
	p1.changeV('+');
	p1.changeD('-');
	p1.getData();



}

