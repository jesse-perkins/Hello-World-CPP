#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
	/*
	TEST CASES
	 _____________________________________________________________________________________________________
	|		  |		  |			 |			 |			|			   |					 |			  |
	| People  |  Tip  |  Larges  |  Mediums  |  Smalls  |  Area (in2)  |  Area/Person (in2)  |  Cost ($)  |
	|_________|_______|__________|___________|__________|______________|_____________________|____________|
	|		  |		  |			 |			 |			|			   |					 |			  |
	|    5    |  50%  |     0    |     1     |     2    |    427.256   |       85.4512       |     $39    |
	|_________|_______|__________|___________|__________|______________|_____________________|____________|
	|		  |		  |			 |			 |			|			   |					 |			  |
	|   30    |  100% |     4    |     0     |     2    |    1482.83   |       49.4277       |    $147    |
	|_________|_______|__________|___________|__________|______________|_____________________|____________|
	|		  |		  |			 |			 |			|			   |					 |			  |
	|  200    |  10%  |    28    |     1     |     1    |    9110.61   |       45.5531       |    $473    |
	|_________|_______|__________|___________|__________|______________|_____________________|____________|
	*/

	//request number of people coming to the party
	cout << "Please input the number of people attending the party: ";
	int numberOfPartyGuests;
	cin >> numberOfPartyGuests;
	int remainingGuests = numberOfPartyGuests;

	//initialize constant variables based on the number of people fed by each type of pizza
	const double PI = 3.14159; //pi
	
	const int peoplePerLarge  = 7;
	const int peoplePerMedium = 3;
	const int peoplePerSmall  = 1;
	
	const int radiusOfLarge  = 10;
	const int radiusOfMedium = 8;
	const int radiusOfSmall  = 6;

	const double costOfLarge = 14.68;
	const double costOfMedium = 11.48;
	const double costOfSmall = 7.28;

	const double areaOfLarge = PI * radiusOfLarge * radiusOfLarge;
	const double areaOfMedium = PI * radiusOfMedium * radiusOfMedium;
	const double areaOfSmall = PI * radiusOfSmall * radiusOfSmall;

	//initialize the remaining variables
	int numberOfLarges = 0, numberOfMediums = 0, numberOfSmalls = 0;

	//define number of larges and take the remaining people out for the next stage
	numberOfLarges = remainingGuests / peoplePerLarge;
	remainingGuests %= peoplePerLarge;
	
	//define number of mediums and take the remaining people out for the next stage
	numberOfMediums = remainingGuests / peoplePerMedium;
	remainingGuests %= peoplePerMedium;
	
	//define number of smalls
	numberOfSmalls = remainingGuests / peoplePerSmall;
	
	//compute the total area of the pizzas and pizza amount per person
	double totalAreaOfPizza = areaOfLarge * numberOfLarges + areaOfMedium * numberOfMediums + areaOfSmall * numberOfSmalls;
	double areaOfPizzaPerPerson = totalAreaOfPizza / numberOfPartyGuests;

	//display the requested stats
	cout << "\n" << numberOfLarges << "\n" << numberOfMediums << "\n" << numberOfSmalls << "\n" << endl;
	cout << totalAreaOfPizza << " total square inches of pizza." << endl;
	cout << areaOfPizzaPerPerson << " square inches of pizza per person. \n" << endl;
	
	//request tip information input
	cout << "What percentage of tip would you like to give? (0-100): "; 
	double tipPercent;
	cin >> tipPercent;
	tipPercent /= 100; //convert tipPercent into an actual percentage
	double totalCost = numberOfLarges * costOfLarge + numberOfMediums * costOfMedium + numberOfSmalls * costOfSmall;
	double tipAmount = totalCost * tipPercent;
	totalCost += tipAmount;

	//round the cost and tip to dollars and display
	int roundedCost = totalCost + .5;
	cout << "The total cost of the pizzas rounded to the nearest dollar is \$" << roundedCost << ". \n" << endl;

	system("pause");
}