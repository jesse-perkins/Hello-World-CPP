#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;
/*
============================ TEST CASES ============================
Test Case 1
Inputs:
-1
4
Outputs:
MENU
INVALID Selection
GOODBYE

Test Case 2
Inputs:
1
0
1
8
4
Outputs:
MENU
SINGLE CHIP DROP
SLOT PROMPT
[data array starting at 0, then .5]
Winnings
MENU
SINGLE CHIP DROP
SLOT PROMPT:
[data array starting at 8, then 7.5]
Winnings
MENU
GOODBYE

Test Case 3
Inputs:
2
40000000
4
-1
4

Outputs:
MENU
MULTIPLE CHIP DROP
NUMBER OF CHIPS PROMPT
SLOT PROMPT
Total Winnings
Average Winnings
MENU
INVALID Selection
GOODBYE


Test Case 4
Inputs:
3
400000
4
potato
4

Outputs:
MENU
ALL CHIP DROP
NUMBER OF CHIPS PROMPT
Total Winnings slot 0
Average Winnings slot 0
Total Winnings slot 1
Average Winnings slot 1
Total Winnings slot 2
Average Winnings slot 2
Total Winnings slot 3
Average Winnings slot 3
Total Winnings slot 4
Average Winnings slot 4
Total Winnings slot 5
Average Winnings slot 5
Total Winnings slot 6
Average Winnings slot 6
Total Winnings slot 7
Average Winnings slot 7
Total Winnings slot 8
Average Winnings slot 8
MENU
INVALID Selection
GOODBYE


*/


//number of pegs to hit on the way down. Essentially the number of times to loop fallSimulator
const int NUM_OF_PEGS = 12;

//Number of prize slots available
const int NUM_OF_SLOTS = 9;

//Prize Values
const double PRIZES_0_8 = 100;
const double PRIZES_1_7 = 500;
const double PRIZES_2_6 = 1000;
const double PRIZES_3_5 = 0;
const double PRIZE_4 = 10000;

/* 
The following function truncates any decimal inputs and checks for non-numeric input and returns corrected output.
If the cin failed, it returns -1.
*/
int inputCheck(int checkMe)
{
	while (cin.fail())
	{
		cin.clear();
		checkMe = -1;
	}
	cin.ignore(1000, '\n');
	return checkMe;
}

//The following function simulates every single individual fall of the chip and returns the location after that single fall
double fallSimulator(double slotLocation)
{
	if (slotLocation == 0)
	{
		slotLocation += 0.5;
	}
	else if (slotLocation == 8)
	{
		slotLocation -= 0.5;
	}
	else
	{
		//rand number generator
		double randPercent = rand()*1.0 / RAND_MAX;
		if (randPercent < .5)
		{
			slotLocation -= .5;
		}
		else
		{
			slotLocation += .5;
		}
	}
	return slotLocation;
}

// The following function takes the final location of the chip and assigns it the prize value, then returns that value
double getPrizeMoney(int prizeSlot)
{
	double prizeMoney = 0;
	switch (prizeSlot)
	{
	case 0:
	case 8:
		prizeMoney += PRIZES_0_8;
		break;
	case 1:
	case 7:
		prizeMoney += PRIZES_1_7;
		break;
	case 2:
	case 6:
		prizeMoney += PRIZES_2_6;
		break;
	case 3:
	case 5:
		prizeMoney += PRIZES_3_5;
		break;
	case 4:
		prizeMoney += PRIZE_4;
		break;
	}
	return prizeMoney;
}

/*
The following function takes and simulates one chip drop into a specific slot, outputting the exact fall location as
it drops. This is why fallSimulator does not have a for loop in it. It returns 0 to clear the menuIn variable.
*/
int singleChip(double slotSelection)
{
	double slotLocation = -1;
	double prizeMoney = 0;
	//This if statement is in charge of the chip fall and displays the location as it falls.
	if (slotSelection >= 0 && slotSelection <= 8)
	{
		cout << "\n\t * * * DROPPING CHIP INTO SLOT " << setprecision(0) << fixed << slotSelection << " * * * \n";
		cout << "[";

		//This loop displays the location of every step down as the chip falls.
		for (int row = 0; row < NUM_OF_PEGS; row++)
		{
			cout << setprecision(1) << fixed << slotSelection << " ";
			slotSelection = fallSimulator(slotSelection);
		}
		cout << slotSelection << "]\n";
		prizeMoney = getPrizeMoney(slotSelection);
		cout << "\nWINNINGS: $" << setprecision(2) << fixed << prizeMoney << "\n\n";
	}
	else
	{
		cout << "\n INVALID INPUT \n" << endl;
	}
	return 0;
}

/*
The following function takes and simulates multiple chips dropped into a specific slot, then provides the total
and average value of the prize money. It returns 0 to clear the menu variable
*/
int multiChip(int numberOfChips, double slotSelection)
{
	double slotLocation = 0;
	double prizeMoney = 0;
	if (slotSelection >= 0 && slotSelection <= 8 && numberOfChips > 0)
	{
		for (int counter = 0; counter < numberOfChips; counter++)
		{
			slotLocation = slotSelection;
			for (int row = 0; row < NUM_OF_PEGS; row++)
			{
				slotLocation = fallSimulator(slotLocation);
			}
			prizeMoney += getPrizeMoney(slotLocation);
		}
		cout << "\nTOTAL WINNINGS: $" << setprecision(2) << fixed << prizeMoney << "\n"
			<< "AVERAGE WINNINGS: $" << prizeMoney / numberOfChips << "\n\n";
	}
	else
	{
		cout << "\n INVALID INPUT \n" << endl;
	}
	return 0;
}
int allSlotChip(double numberOfChips)
{
	for (int count = 0; count < NUM_OF_SLOTS; count++)
	{
		cout << "\nWinnings in slot " << count << endl;
		multiChip(numberOfChips, count);
	}
	return 0;
}

// The following function is essentially the menu interface for the program. 
int main()
{
	srand(time(NULL));
	int menuIn = 0;
	double slotIn = -1;
	int chipNum = -1;
	double prize = 0;

	//display the menu
	do
	{
		cout << "\tMENU \n"
			<< "  1 - Drop a single chip into one slot \n"
			<< "  2 - Drop multiple chips into one slot \n"
			<< "  3 - Drop multiple chips into all slots \n"
			<< "  4 - Quit the program \n"
			<< "Please enter your selection (1-4): ";
		cin >> menuIn;
		menuIn = inputCheck(menuIn);
		switch (menuIn)
		{
		case 1:
			cout << "\n\n\t* * * SINGLE CHIP DROP * * * \n" << "Please input a slot number (0-8): ";
			cin >> slotIn;
			slotIn = inputCheck(slotIn);
			menuIn = singleChip(slotIn);
			break;
		case 2:
			cout << "\n\n\t* * * MULTIPLE CHIP DROP * * * \n" << "Input number of chips dropped (>0): ";
			cin >> chipNum;
			chipNum = inputCheck(chipNum);
			if (chipNum <= 0)
			{
				cout << "\n INVALID INPUT \n" << endl;
			}
			else
			{
				cout << "Please input a slot number (0-8): ";
				cin >> slotIn;
				slotIn = inputCheck(slotIn);
				menuIn = multiChip(chipNum, slotIn);
			}
			break;
		case 3:
			cout << "\n\n\t* * * ALL SLOT CHIP DROP * * * \n" << "Input number of chips to drop into each slot (>0): ";
			cin >> chipNum;
			chipNum = inputCheck(chipNum);
			if (chipNum <= 0)
			{
				cout << "\n INVALID INPUT \n" << endl;
			}
			else
			{
				menuIn = allSlotChip(chipNum);
			}
			break;
		case 4:
			cout << "GOODBYE \n";
			break;
		default:
			cout << "\n INVALID INPUT \n" << endl;
		}
	} while (menuIn != 4);
	return 0;
}