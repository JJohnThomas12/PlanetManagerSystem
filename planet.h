#include <iostream>
#include <climits>
#include <string>

using namespace std;

template<typename inputType>
inputType ReadValue(string prompt)
{
	inputType returnValue=0;
	cout << prompt;
	cin >> returnValue;
	while (cin.fail()==1) {
		cout << "Error! Cannot read input.\n";
		cin.clear();
		cin.ignore(INT_MAX,'\n');
		cout << prompt;
		cin >> returnValue;
	}
	return returnValue;
}


template<typename inputType>
inputType ReadValue(string prompt, inputType minValue)
{
	inputType returnValue=0;
	returnValue=ReadValue<inputType>(prompt);
	while (returnValue < minValue) {
		cout << "Error!  Value must be >= " << minValue << endl;
		returnValue=ReadValue<inputType>(prompt);
	}
	return returnValue;
}


template<typename inputType>
inputType ReadValue(string prompt, inputType minValue, inputType maxValue)
{
	inputType returnValue=0;
	returnValue=ReadValue<inputType>(prompt,minValue);
	while (returnValue > maxValue) {
		cout << "Error!  Value must be <= " << maxValue << endl;
		returnValue=ReadValue<inputType>(prompt,minValue);
	}
	return returnValue;
}
jj49642@ares:~/final$ cat final.c
#include <cmath>
#include <iostream>
#include "input.h"
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

//store value of each planet
struct Planet
{
	string name;
	double mass;
	double diameter;
};

//declaring the functions
void addPlanet(vector<Planet>& planets);
void deletePlanet(vector<Planet>& planets);
void findPlanet(const vector<Planet>& planets);
void displayPlanets(const vector<Planet>& planets);
void sortPlanets(vector<Planet>& planets);
void savePlanets(const vector<Planet>& planets);
void loadPlanets(vector<Planet>& planets);

int main() 
{
  //Vector to store the planets
  vector<Planet> planets;

  //Read the data from the file
  loadPlanets(planets);

  //Main menu
  int choice = 0;
  while (choice != 6) 
  {
    cout << endl;
    cout << "1. Add planet" << endl;
    cout << "2. Delete planet" << endl;
    cout << "3. Find planet" << endl;
    cout << "4. Show all planets" << endl;
    cout << "5. Sort planets" << endl;
    cout << "6. Quit" << endl;
    cout << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    cout << endl;

    switch (choice) 
    {
      case 1:
        addPlanet(planets);
        break;
      case 2:
        deletePlanet(planets);
        break;
      case 3:
        findPlanet(planets);
        break;
      case 4:
        displayPlanets(planets);
        break;
      case 5:
        sortPlanets(planets);
        break;
      case 6:
        savePlanets(planets);
        break;
      default:
        cout << "Invalid choice! Please try again!" << endl;
    }
  }

  return 0;
}

void addPlanet(vector<Planet>& planets) 
{
  Planet planet;

  cout << "Enter the name of the planet: ";
  cin >> planet.name;
  cout << "Enter the mass of the planet (kg): ";
  cin >> planet.mass;
  cout << "Enter the diameter of the planet (m): ";
  cin >> planet.diameter;

  planets.push_back(planet);

  cout << endl;
  cout << "Planet added successfully!" << endl;
}

void deletePlanet(vector<Planet>& planets) 
{
  string name;
  cout << "Name of the planet that needs to be deleted: ";
  cin >> name;

  //Find the planet in the vector
  int index = -1;
  for (int i = 0; i < planets.size(); i++) 
  {
    if (planets[i].name == name) 
    {
      index = i;
      break;
    }
  }

  // If the planet was found, delete it from the vector
  if (index != -1) 
  {
    planets.erase(planets.begin() + index);
    cout << "The Planet has been destroyed!" << endl;
  } else 
  {
    cout << "The Planet cannot be detected!" << endl;
  }
}

void findPlanet(const vector<Planet>& planets) 
{
  string name;
  cout << "Enter the name of the planet to find: ";
  cin >> name;

  //Find the planet in the vector
  int index = -1;
  for (int i = 0; i < planets.size(); i++) 
  {
    if (planets[i].name == name) 
    {
      index = i;
      break;
    }
  }

  //display the planet's information
  if (index != -1) 
  {
    cout << "Planet found!" << endl;
    cout << "Name: " << planets[index].name << endl;
    cout << "Mass: " << planets[index].mass << " kg" << endl;
    cout << "Diameter: " << planets[index].diameter << " m" << endl;
    cout << "Surface Area: " << (4 * M_PI * pow((planets[index].diameter/2.0),2.0)) << " m^2" << endl;
    cout << "Density: " << (planets[index].mass/((1.33333) * (M_PI) * (pow((planets[index].diameter/2),3.0)))) << " kg/m^3" << endl;
  } 
  else 
  {
    cout << "Planet not found!" << endl;
  }
}

//Displays all the planets with their values and calculations
void displayPlanets(const vector<Planet>& planets) 
{
  if (planets.size() <= 0)
  {
	  cout << "List is empty!";
	  cout << endl;
  }

  for (int i = 0; i < planets.size(); i++) {
    cout << "Name: " << planets[i].name << endl;
    cout << "Mass: " << planets[i].mass << " kg" << endl;
    cout << "Diameter: " << planets[i].diameter << " m" << endl;
    cout << "Surface Area: " << (4 * M_PI * pow((planets[i].diameter/2.0),2.0)) << " m^2" << endl;
    cout << "Density: " << (planets[i].mass/((1.33333) * (M_PI) * (pow((planets[i].diameter/2),3.0)))) << " kg/m^3" << endl;
    cout << endl;
  }
}

//sorts the planets alphabetically by comparing the name of the planets
void sortPlanets(vector<Planet>& planets) 
{
  sort(planets.begin(), planets.end(), [](const Planet& p1, const Planet& p2) 
  {
    return p1.name < p2.name;
  });

  cout << "Planets sorted alphabetically!" << endl;
}

//saves the values to the file planet.txt
void savePlanets(const vector<Planet>& planets) 
{
  ofstream out_file("planets.txt");
  if (out_file.is_open()) 
  {
    for (const Planet& planet : planets) 
    {
      out_file << planet.name << " " << planet.mass << " " << planet.diameter << " " << endl;
    }
    out_file.close();
    cout << "Planet data written to file successfully!" << endl;
    cout << endl;
  } 
  else 
  {
    cout << "Error opening file!" << endl;
  }
}

//loads the file planet.txt with all the values
void loadPlanets(vector<Planet>& planets) 
{
  ifstream in_file("planets.txt");
  if (in_file.is_open()) 
  {
    while (!in_file.eof()) 
    {
      Planet planet;
      in_file >> planet.name >> planet.mass >> planet.diameter;
      planets.push_back(planet);
    }
    in_file.close();
  } 
  else 
  {
    cout << "File cannot be opened!" << endl;
  }
}
