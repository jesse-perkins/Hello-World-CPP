#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;
/*
Initialize Hot Plate
Average Hot Plate(one time through the 2D array)
Print Hot Plate
Export Hot Plate
*/

const int ARRAY_LENGTH = 20;
const int LAST_ARRAY_SLOT = 19;
const int TOP_AND_BOTTOM = 100;
const int CORNERS_EDGES_ELSEWHERE = 0;
const int INTERIOR_START = 1;
const int INTERIOR_ENDS = 18;
const double MIN_VARIANCE = .1;

/*
Initializes a 2 dimensional array of length 20 with all zero values except the non-'corner' top and bottom rows
which are initialized with 100.
i.e:
0 100 100 100 0
0   0   0   0 0
0   0   0   0 0
0 100 100 100 0
@param plate: The array that is being intialized
@return: It does not return anything. The array is passed by reference.
*/
void initializeHotPlate(double plate[][ARRAY_LENGTH])
{
	for (int i = 0; i < ARRAY_LENGTH; i++)
	{
		if (i == 0 || i == LAST_ARRAY_SLOT)
		{
			for (int j = 0; j < ARRAY_LENGTH; j++)
			{
				
				if (i == 0 && j == 0)
				{
					plate[i][j] = CORNERS_EDGES_ELSEWHERE;
				}
				else if (i == 0 && j == LAST_ARRAY_SLOT)
				{
					plate[i][j] = CORNERS_EDGES_ELSEWHERE;
				}
				else if (i == LAST_ARRAY_SLOT && j == 0)
				{
					plate[i][j] = CORNERS_EDGES_ELSEWHERE;
				}
				else if (i == LAST_ARRAY_SLOT && j == LAST_ARRAY_SLOT)
				{
					plate[i][j] = CORNERS_EDGES_ELSEWHERE;
				}
				else
				{
					plate[i][j] = TOP_AND_BOTTOM;
				}
			}
		}
		else
		{
			for (int j = 0; j < ARRAY_LENGTH; j++)
			{
				plate[i][j] = CORNERS_EDGES_ELSEWHERE;
			}
		}
	}
}

/*
Takes the input array and uses a swap array to calculate the new tempurature of each location. Then swaps the swap array 
back into the original array. Also monitors the variance from one array to the next.
@param input: The array that will be used as the base from which new temuratures will be derived and then passed to.
@return: Returns the variance.
*/
double  average_Hot_Plate(double input[][ARRAY_LENGTH], double swap[][ARRAY_LENGTH])
{
	double maxVariance = 0;
	for (int i = INTERIOR_START; i <= INTERIOR_ENDS; i++)
	{
		for (int j = INTERIOR_START; j <= INTERIOR_ENDS; j++)
		{
			swap[i][j] = (input[i - 1][j] + input[i + 1][j] + input[i][j - 1] + input[i][j + 1]) / 4;
		}
	}
	for (int i = 0; i < ARRAY_LENGTH; i++)
	{
		for (int j = 0; j < ARRAY_LENGTH; j++)
		{
			if (maxVariance < swap[i][j] - input[i][j])
			{
				maxVariance = swap[i][j] - input[i][j];
			}
			input[i][j] = swap[i][j];
		}
	}
	return maxVariance;
}

/*
Takes the input array and prints it out.
@param input: The array that will be printed.
@return: Does not return a value.
*/
void print_Hot_Plate(double inArray[][ARRAY_LENGTH])
{
	for (int i = 0; i < ARRAY_LENGTH; i++)
	{
		for (int j = 0; j < ARRAY_LENGTH; j++)
		{
			cout << setw(6) << fixed << setprecision(1) << inArray[i][j];
		}
		cout << endl;
	}
	cout << endl;
}

/*
Takes the input array and exports it into a file that is accepted by excel, openoffice and libreoffice.
@param input: The array that will be exported.
@return: Does not return a value.
*/
void export_Hot_Plate(double inArray[][ARRAY_LENGTH])
{
	ofstream output;
	output.open("hot_plate_outpout.csv");
	for (int i = 0; i < ARRAY_LENGTH; i++)
	{
		for (int j = 0; j < ARRAY_LENGTH; j++)
		{
			output << fixed << setprecision(1) << inArray[i][j] << ",";
		}
		output << endl;
	}
}

int main()
{
	double hotPlateArray[ARRAY_LENGTH][ARRAY_LENGTH];
	double swapArray[ARRAY_LENGTH][ARRAY_LENGTH];
	initializeHotPlate(hotPlateArray);
	initializeHotPlate(swapArray);
	print_Hot_Plate(hotPlateArray);
	double variationInArray;
	variationInArray = average_Hot_Plate(hotPlateArray, swapArray);
	print_Hot_Plate(hotPlateArray);
	while (variationInArray > MIN_VARIANCE)
	{
		variationInArray = average_Hot_Plate(hotPlateArray, swapArray);
	}
	export_Hot_Plate(hotPlateArray);
	return 0;
}