#include <iostream>
#include <string>
using namespace std;
/*

EXTRA CREDIT ANSWER = 166.667
													  TEST CASES

														INPUTS
			______________________________________________________________________________________________________________________
           |		     |       |				   |		 |				   |			   |	   |               |		  |
		   |milesPerYear |gasCost|hybridInitialCost|hybridMPG|hybrid5YearResale|normInitialCost|normMPG|norm5YearResale|gasOrTotal|
___________|_____________|_______|_________________|_________|_________________|_______________|_______|_______________|__________|
		   |		     |	     |				   |		 |				   |			   |	   |			   |		  |
  Test 1   |     1000    |  2.5  |       1000      |   50    |      1000       |    1000000    |   25  |     750000    |  Total   |
___________|_____________|_______|_________________|_________|_________________|_______________|_______|_______________|__________|
		   |		     |       |				   |	     |				   |			   |	   |			   |		  |
  Test 2   |    10000    |   5   |    1000000      |   45    |    750000       |      1000     |   15  |       1000    |  Total   |
___________|_____________|_______|_________________|_________|_________________|_______________|_______|_______________|__________|
		   |		     |	     |				   |		 |				   |			   |	   |			   |		  |
  Test 3   |  -1->5000   | -1->1 | -1 -> 40000     |-40-> 40 |   -10->25000    | -10->15000    |-20->20|-10->10000     |  Gas     |
___________|_____________|_______|_________________|_________|_________________|_______________|_______|_______________|__________|

														OUTPUTS
			 ________________________________________________________________________________________________________________
			|			  |				|				|			|			|			  |								 |
			|hybridGasUsed|hybridGasCost|hybridTotalCost|normGasUsed|normGasCost|normTotalCost| Which Car is displayed First?|
____________|_____________|_____________|_______________|___________|___________|_____________|______________________________|
			|			  |				|				|			|			|			  |								 |
   Test 1	|    20       |    250      |       250		|	40		|	500		|  250500	  |	    Hybrid Car				 |
____________|_____________|_____________|_______________|___________|___________|_____________|______________________________|
			|			  |				|				|			|			|			  |								 |
   Test 2	|  222.222    |  5555.56    |    255556		| 666.667	|16666.7	|16666.7	  |	Non-Hybrid Car				 |
____________|_____________|_____________|_______________|___________|___________|_____________|______________________________|
			|			  |				|				|			|			|			  |								 |
   Test 3	|   125       |    625      |    15625		|	250		| 1250  	|	6250	  |		Hybrid Car				 |
____________|_____________|_____________|_______________|___________|___________|_____________|______________________________|

*/
int main()
{
	//Initialize all the variables with a built in if statement that checks for valid input.

	int milesPerYear;
	cout << "Please enter the number of miles driven per year: ";
	cin >> milesPerYear;
	if (milesPerYear<= 0)
	{
		cout << "\nError; Please input a positive integer: ";
		cin >> milesPerYear;
	}

	double gasCost;
	cout << "\nPlease enter the estimated cost of gas: ";
	cin >> gasCost;
	if (gasCost <= 0)
	{
		cout << "\nError; Please input a positive number: ";
		cin >> gasCost;
	}


	int hybridInitialCost;
	cout << "\nPlease enter the purchase price of the hybrid car: ";
	cin >> hybridInitialCost;
	if (hybridInitialCost<= 0)
	{
		cout << "\nError; Please input a positive integer: ";
		cin >> hybridInitialCost;
	}

	double hybridMPG;
	cout << "\nPlease enter the hybrid car's gas milage: ";
	cin >> hybridMPG;
	if (hybridMPG<= 0)
	{
		cout << "\nError; Please input a positive integer: ";
		cin >> hybridMPG;
	}

	double hybrid5YearResale;
	cout << "\nPlease enter the resale value of the hybrid car in five years: ";
	cin >> hybrid5YearResale;
	if (hybrid5YearResale<= 0)
	{
		cout << "\nError; Please input a positive integer: ";
		cin >> hybrid5YearResale;
	}

	int normInitialCost;
	cout << "\nPlease enter the purchase price of the non-hybrid car: ";
	cin >> normInitialCost; 
	if (normInitialCost<= 0)
	{
		cout << "\nError; Please input a positive integer: ";
		cin >> normInitialCost;
	}

	double normMPG;
	cout << "\nPlease enter the non-hybrid car's gas mileage: ";
	cin >> normMPG; 
	if (normMPG <= 0)
	{
		cout << "\nError; Please input a positive integer: ";
		cin >> normMPG;
	}

	double norm5YearResale;
	cout << "\nPlease enter the resale value of the non-hybrid car in five years: ";
	cin >> norm5YearResale;
	if (norm5YearResale<= 0)
	{
		cout << "\nError; Please input a positive integer: ";
		cin >> norm5YearResale;
	}

	string gasOrCost;
	cout << "\nPlease enter purchasing criteria (Gas|Total): ";
	cin >> gasOrCost;

	//Calculate the total gallons of fuel used and its cost as well as the total depreciation of the car.
	
	const int yearsCarIsOwned = 5;

	double hybridGasUsed = milesPerYear / hybridMPG * yearsCarIsOwned;
	double hybridGasCost = hybridGasUsed * gasCost;
	double hybridTotalCost = hybridInitialCost - hybrid5YearResale + hybridGasCost;

	double normGasUsed = milesPerYear / normMPG * yearsCarIsOwned;
	double normGasCost = normGasUsed * gasCost;
	double normTotalCost = normInitialCost - norm5YearResale + normGasCost;

	//Determine which criteria was used and output based on that criteria

	if (gasOrCost == "Gas" || gasOrCost == "gas")
	{
		if (hybridGasUsed <= normGasUsed)
		{
			cout << "\nHybrid: \n" << "Total gas used: " << hybridGasUsed;
			cout << "\nTotal Cost of Ownership over 5 years: " << hybridTotalCost << "\n";

			cout << "\nNon-Hybrid: \n" << "Total gas used: " << normGasUsed;
			cout << "\nTotal Cost of Ownership  over 5 years: " << normTotalCost << "\n";
		}
		else
		{
			cout << "\nNon-Hybrid: \n" << "Total gas used: " << normGasUsed;
			cout << "\nTotal Cost of Ownership: " << normTotalCost << "\n";

			cout << "\nHybrid: \n" << "Total gas used: " << hybridGasUsed;
			cout << "\nTotal Cost of Ownership: " << hybridTotalCost << "\n";
		}
	}
	else
	{
		if (hybridTotalCost <= normTotalCost)
		{
			cout << "\nHybrid: \n" << "Total gas used: " << hybridGasUsed;
			cout << "\nTotal Cost of Ownership: " << hybridTotalCost << "\n";

			cout << "\nNon-Hybrid: \n" << "Total gas used: " << normGasUsed;
			cout << "\nTotal Cost of Ownership: " << normTotalCost << "\n";
		}
		else
		{
			cout << "\nNon-Hybrid: \n" << "Total gas used: " << normGasUsed;
			cout << "\nTotal Cost of Ownership: " << normTotalCost << "\n";

			cout << "\nHybrid: \n" << "Total gas used: " << hybridGasUsed;
			cout << "\nTotal Cost of Ownership: " << hybridTotalCost << "\n";
		}
	}
	system("pause");
	return 0;
}