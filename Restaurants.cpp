#include <string>
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <ctime>
#include <vector>
#include <cmath>

using namespace std;
/*
TEST CASE 1
Inputs:
6

Outputs:
GOODBYE

TEST CASE 2
Inputs:
-1
potato
1
2
Potato Steve's
3
Potato Dave's
3
Potato Steve's
6

Outputs:
Invalid Input Redisplay menu
Invalid Input Redisplay menu
* * * DISPLAING RESTAURANTS * * * (display the vector separated by commas, not trailing comma.
* * * ADDING A RESTAURANT  * * * Please enter a restaurant name:
Restaurant added to the list. Redisplay menu
* * * REMOVING A RESTAURANT  * * * Please enter a restaurant name:
Restaurant not found! Redisplay menu
* * * REMOVING A RESTAURANT  * * * Please enter a restaurant name:
Restaurant Removed. Redisplay menu
GOODBYE

TEST CASE 3
Inputs:
4
2
Potato Steve's
5
3
Arby's
5
1
2
q
2
2
1
1
1

Outputs:
* * * SHUFFLING RESTAURANTS  * * * Restaurants Shuffled.
* * * ADDING A RESTAURANT  * * * Please enter a restaurant name:
Restaurant added to the list. Redisplay menu
* * * LET THE TOURNAMENT BEGIN!!!  * * * Display Error - Not a Power of 2. Redisplay Menu
* * * REMOVING A RESTAURANT  * * * Please enter a restaurant name:
Restaurant Removed. Redisplay menu
* * * LET THE TOURNAMENT BEGIN!!!  * * * Display match one. Prompt for 1-2
Display match two. Prompt for 1-2
Display match Three. Prompt for 1-2
Error, invalid. Reprompt for 1-2
Display match four. Prompt for 1-2
New Round.  Display match one. Prompt for 1-2
Display match two. Prompt for 1-2
New Round. Display match one. Prompt for 1-2 
DECLARE WINNER. End program.

*/

/*
The following function truncates any decimal inputs, checks for non-numeric input and returns corrected intput.
If the cin failed, it returns -1.

@param checkMe: The variable passed in to be checked
@return: Passes back the corrected input or -1 if the input was non-numeric
*/
int checkInt(int checkMe)
{
	if (cin.fail())
	{
		cin.clear();
		checkMe = -1;
	}
	cin.ignore(1000, '\n');
	return checkMe;
}

/*
Discovers whether or not an inputed restaurant name matches a restaurant name in the vector.

@param findMe: The name of a restaurant the user has entered.
@param restaurantList: The vector containing the list of restaurant names.
@return: -1 if the restaurant name is NOT found. If the restaurant name IS found, the index it is currently in.
*/
int findRestaurant(const vector<string> restaurantList, const string findMe)
{
	int location = -1;
	for (int count = 0; count < restaurantList.size(); count++)
	{
		if (restaurantList[count] == findMe)
		{
			location = count;
		}
	}
	return location;
}

/*
Displays the values inside the the vector parameter in one line with commas as separators.

@param restaurantList: The vector containing the list of restaurant names.
@return: VOID
*/
void displayRestaurants(const vector<string> restaurantList)
{
	for (int count = 0; count < restaurantList.size()-1; count++)
	{
		cout << restaurantList[count] << ", ";
	}
	cout << restaurantList[restaurantList.size() - 1] << "\n";
}

/*
Takes an input from the user Checks to see if a restaurant is in the list. If it is in the list, 
it doesn't put it into the vector again. If it isn't in the list, it adds the new restaurant to 
the vector. It informs the user in either case.

@param restaurantList: The vector that contains the list of restaurants.
@return: nothing
*/
void addRestaurant(vector<string>& restaurantList)
{
	int indexLocation = -1;
	string name = "";
	cout << "Please enter a restaurant name: ";
	//clears out anything that might be in the cin and preps it for the next input, then grabs the next line
	cin.sync();
	getline(cin, name);
	//looks for the entered name in the vector to avoid duplicates.
	indexLocation = findRestaurant(restaurantList, name);
	//if the name is not in the vector, add it to the vector. Otherwise display error.
	if (indexLocation == -1)
	{
		restaurantList.push_back(name);
		cout << "\nRestaurant added to the list.\n";
	}
	else
	{
		cout << "\nError! Restaurant is already on the list!\n";
	}
	return;
}

/*
Takes an input from the user Checks to see if a restaurant is in the list. If it is in the list,
it removes the vector from the list, shifts everything in the vector to fill in the slot, and shrinks 
the vector by 1 space, then tells the user that the removal was a success. If it isn't in the list, 
it does nothing and tells the user that the entered name isn't in the list. 

@param restaurantList: The vector that contains the list of restaurants.
@param indexLocation: The location of the restaurant to be removed in the vector.
@return: -1 if the passed index location is outside the size of the vector. 0 if it is not.
*/
int removeRestaurant(vector<string>& restaurantList, int indexLocation)
{
	//prepare the variable to be returned
	int passOrFail = -1;
	//check to see if the passed location is valid. If it is, check for matches. Remove matches.
	if (indexLocation >=0 && indexLocation < restaurantList.size())
	{
		for (int count = indexLocation; count < (restaurantList.size()-1); count++)
		{
			restaurantList[count] = restaurantList[count + 1];
		}
		restaurantList.pop_back();
		//change the return value to success if the restaurant was found and removed from the vector
		passOrFail = 0;
	}
	return passOrFail;
}

/*
This function takes the values of the vector and randomizes them.

@param restaurantList: The vector that contains the list of restaurants.
@return: Nothing
*/
void shuffleVector(vector<string>& restaurantList)
{
	string swap = "";
	//run this loop double the size of the vector. Larger vectors will be randomized more times to ensure thorough randmoization.
	for (int count = (restaurantList.size() * 2); count > 0; count--)
	{
		// Initialize the index locations here so that they reset each time the for loop restarts.
		int locationOne = 0;
		int locationTwo = 0;
		//Randomly select 2 index locations in the vector that are not equal and swap them
		while (locationOne == locationTwo)
		{
			locationOne = rand() % restaurantList.size();
			locationTwo = rand() % restaurantList.size();
		}
		swap = restaurantList[locationOne];
		restaurantList[locationOne] = restaurantList[locationTwo];
		restaurantList[locationTwo] = swap;
	}
	cout << "List of restaurants shuffled. \n";
}

/*
This function checks to see if the size of the vector inputed is a power of 2. If it is not, the function ends.
If it is, then the function displays pairs of vector members and prompts the user to pick one. The vector member
not picked is removed and the next pair is displayed until there are no more pairs left. At this point the function 
starts over and half of them are removed again. When only one vector member remains, the function displays its value.

@param restaurantList: The vector that contains the list of restaurants.
@return: -1 if the number of retaurants is not a power of 2. 0 if it is.
*/
int letsGetReadyToRumble(vector<string> inputVector)
{
	//Getting required variables together and assign fail/null values
	int tourneySuccess = -1;
	int choice = -1;
	int round = 0;
	int match = 0;
	int totalMatches = 0;
	int totalRounds = 0;
	int valueOfN = 0;
	//Setting up the program to check for powers of two.
	const int POWER = 2;
	//I set this equal to one so that if the vector size is only one it gets bumped past the while loop
	int powerOfCheck = 1;
	/*
	This part takes two to the next power and compares it to the size of the vector. 
	If the vector is a power of two, it will eventually match and the while loop will end.
	otherwise, it will exceed the size of the vector and force a return.
	*/
	while (powerOfCheck != inputVector.size())
	{
		//Takes power check to the next power and keeps track of the nth power
		powerOfCheck *= POWER;
		valueOfN++;
		//This section only runs if the power check has failed. 
		if (powerOfCheck > inputVector.size())
		{
			cout << "\nThe length of the list of restaurants needs to be a power of two.\n"
				"Please add or remove restaurants until the length is a power of two.\n";
			return -1;
		}
	}
	//assign total rounds and total matches based on the power to which 2 was taken and its value.
	totalRounds = valueOfN;
	totalMatches = powerOfCheck / 2;
	for (int i = 0; i < totalRounds; i++)
	{
		round++;
		cout << "\n ROUND " << round << "... BEGIN!!! \n";
		for (int j = 0; j < inputVector.size(); j ++)
		{
			match++;
			//Display match with round and ask the user to pick a winner
			cout << "Match " << match << " of " << totalMatches << ", " << "Round " << i + 1 << " of " << totalRounds << ": ";
			cout << inputVector[j] << " VS " << inputVector[j + 1];
			cout << "\nPick the winner [1-2]: ";
			//Check for invalid inputs and reprompt
			while (choice != 1 && choice != 2)
			{
				cin >> choice;
				choice = checkInt(choice);
				if (choice != 1 && choice != 2)
				{
					cout << "\n Invalid Input. \n Please pick a winner [1-2] :";
				}
			}
			//Assign 0 value to the loser location
			if (choice == 1)
			{
				inputVector[j + 1] = "0";
			}
			else if (choice == 2)
			{
				inputVector[j] = "0";
			}
			cout << endl;
			/*
			The below count pushes the count past the second member of the match. 
			I can be certain this will work since I already checked for powers of two.
			*/
			j++;
			//reset choice for each match
			choice = -1;
		}
		//Remove the loser values and shrink the vector size. I added the while loop because 
		//the popback in the remove function sometimes causes it to miss a 0 value.
		bool restart = true;
		while (restart)
		{
			restart = false;
			for (int v = 0; v < inputVector.size(); v++)
			{
				if (inputVector[v] == "0")
				{
					removeRestaurant(inputVector, v);
					restart = true;
				}
			}
		}
		//reset the current match value for each round
		match = 0;
		//Calculate the number of matches for the next round
		totalMatches /= POWER;
	}
	//Declare Winner
	cout << "\nIt's over! The fight is over! " << inputVector[0] << " has won!\n\n";
	return 0;
}

int main()
{
	//initialize the vector
	vector<string> restaurants(8);
	restaurants[0] = "Burger King";
	restaurants[1] = "McDonald's";
	restaurants[2] = "Arby's";
	restaurants[3] = "Taco Bell";
	restaurants[4] = "Costa Vida";
	restaurants[5] = "In N Out";
	restaurants[6] = "Outback";
	restaurants[7] = "Olive Garden";
	//Prepare variables and initailize srand for the rand number generator
	srand(time(NULL));
	int input = 0;
	string name = "";
	int findIndex = 0;
	int passFail = 0;
	int tourneySuccess = -1;
	while (input != 6)
	{
		//display menu
		cout <<
			" 1 - Display all restaurants"
			"\n 2 - Add a restaurant"
			"\n 3 - Remove a restaurant"
			"\n 4 - Shuffle the vector"
			"\n 5 - Begin the tournament"
			"\n 6 - Quit the program "
			"\n Please enter a selection [1-6]: ";
		//take input and check for bad input.
		cin >> input;
		input = checkInt(input);
		switch (input)
		{
		case 1:
			cout << "\n * * * DISPLAING RESTAURANTS * * * \n";
			displayRestaurants(restaurants);
			break;
		case 2:
			cout << "\n * * * ADDING A RESTAURANT  * * * \n";
			addRestaurant(restaurants);
			break;
		case 3:
			/*
			This is a bit more elaborate because I wanted the function removeRestaurant to have functionality 
			that I could use in the toruney function, so I had to shift the functionality need for this 
			application. I decided here was good.
			*/
			cout << "\n * * * REMOVING A RESTAURANT  * * * \n";
			cout << "Please enter a restaurant name: ";
			cin.sync();
			getline(cin, name);
			findIndex = findRestaurant(restaurants, name);
			passFail = removeRestaurant(restaurants, findIndex);
			if (passFail == 0)
			{
				cout << "\nRestaurant removed from the list.\n";
			}
			else
			{
				cout << "\nError! Restaurant not found on the list!\n";
			}
			break;
		case 4:
			cout << "\n * * * SHUFFLING RESTAURANTS  * * * \n";
			shuffleVector(restaurants);
			break;
		case 5:
			cout << "\n * * * LET THE TOURNAMENT BEGIN!!!  * * * \n";
			tourneySuccess = letsGetReadyToRumble(restaurants);
			//This if statement makes the program end if the tournament completed correctly.
			if (tourneySuccess == 0)
			{
				return 0;
			}
			break;
		case 6:
			cout << "\n GOODBYE";
			break;
		default:
			cout << "\nInvalid Input.";
		}
		cout << "\n";
	}
	return 0;
}