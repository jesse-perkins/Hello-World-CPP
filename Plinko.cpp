#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
/*
Test Case 1
Inputs:
-1
3
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
3
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
2
40000000
4
-1
3
Inputs:
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

*/
{
	srand(0);
	//srand(time(NULL));
	//display the menu
	int menuIn = 1;
	do
	{
		cout << "MENU \n"
			<< "\t1 - Drop a single chip into one slot \n"
			<< "\t2 - Drop multiple chips into one slot \n"
			<< "\t3 - Quit the program \n"
			<< "Please enter your selection (1-3): ";
		cin >> menuIn;
		double slotselection = 1.0;
		double slotlocation = 1.0;
		int prizeSlot = 0;
		int prizeMoney = 0;
		int numberOfChips = 0;
		while (menuIn != 1 && menuIn != 2 && menuIn != 3)
		{
			cout << "\n INVALID selection. Please enter a valid input (1-3): ";
			cin.clear();
			cin.ignore(1000, '\n');
			cin >> menuIn;
		}
		switch (menuIn)
		{
		case 1:
			cout << "\t* * * SINGLE CHIP DROP * * * \n" << "Please input a slot number (0-8): ";
			cin >> slotselection;
			while (cin.fail())
			{
				cin.clear();
				cin.ignore(1000, '\n');
				slotselection = -1;
			}
			if (slotselection >= 0 && slotselection <= 8)
			{
				cout << "\t * * * DROPPING CHIP INTO SLOT " << slotselection << " * * * \n";
				slotlocation = slotselection;
				cout << "[";
				for (int row = 0; row < 12; row++)
				{
					cout << setprecision(1) << fixed << slotlocation << " ";
					if (slotlocation == 0)
					{
						slotlocation += 0.5;
					}
					else if (slotlocation == 8)
					{
						slotlocation -= 0.5;
					}
					else
					{
						//rand number generator
						double randPercent = rand()*1.0 / RAND_MAX;
						if (randPercent < .5)
						{
							slotlocation -= .5;
						}
						else
						{
							slotlocation += .5;
						}
					}
				}
				cout << slotlocation << "]\n";
				prizeSlot = slotlocation;
				switch (prizeSlot)
				{
				case 0:
				case 8:
					prizeMoney += 100;
					break;
				case 1:
				case 7:
					prizeMoney += 500;
					break;
				case 2:
				case 6:
					prizeMoney += 1000;
					break;
				case 3:
				case 5:
					prizeMoney += 0;
					break;
				case 4:
					prizeMoney += 10000;
					break;
				}
				cout << "WINNINGS: $" << setprecision(2) << fixed << prizeMoney << "\n";
			}
			else
			{
				cout << "INVALID INPUT" << endl;
			}
			break;
		case 2:
			cout << "\t* * * MULTIPLE CHIP DROP * * * \n" << "Input number of chips dropped (>0): ";
			cin >> numberOfChips;
			while (cin.fail())
			{
				cin.clear();
				cin.ignore(1000, '\n');
				numberOfChips = -1;
			}
			if (numberOfChips <= 0)
			{
				cout << "INVALID INPUT" << endl;
			}
			else
			{
				cout << "Please input a slot number (0-8): ";
				cin >> slotselection;
				while (cin.fail() || slotselection < 0)
				{
					cin.clear();
					cin.ignore(1000, '\n');
					slotselection = -1;
					break;
				}
				for (int counter = 0; counter < numberOfChips; counter++)
				{
					if (slotselection >= 0 && slotselection <= 8)
					{
						slotlocation = slotselection;
						for (int row = 0; row < 12; row++)
						{
							if (slotlocation == 0)
							{
								slotlocation += 0.5;
							}
							else if (slotlocation == 8)
							{
								slotlocation -= 0.5;
							}
							else
							{
								//rand number generator
								double randPercent = rand()*1.0 / RAND_MAX;
								if (randPercent < .5)
								{
									slotlocation -= .5;
								}
								else
								{
									slotlocation += .5;
								}
							}
						}
						prizeSlot = slotlocation;
						switch (prizeSlot)
						{
						case 0:
						case 8:
							prizeMoney += 100;
							break;
						case 1:
						case 7:
							prizeMoney += 500;
							break;
						case 2:
						case 6:
							prizeMoney += 1000;
							break;
						case 3:
						case 5:
							prizeMoney += 0;
							break;
						case 4:
							prizeMoney += 10000;
							break;
						}
					}
					else
					{
						cout << "INVALID INPUT" << endl;
					}
				}
				cout << "TOTAL WINNINGS: $" << setprecision(2) << fixed << prizeMoney << "\n"
					<< "AVERAGE WINNINGS: $" << prizeMoney / numberOfChips << "\n";
			}
			break;
		case 3:
			cout << "GOODBYE \n";
			break;
		}
	} while (menuIn != 3);
	return 0;
}