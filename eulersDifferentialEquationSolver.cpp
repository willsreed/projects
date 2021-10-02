#include <iostream>
#include <cmath>

void findDifferentialEquation(int stepNumber, double xStartingPoint, double yStartingPoint, double xFinal)
{
	
	double stepCount{ (xFinal - xStartingPoint) / stepNumber };
	double yPrime{ yStartingPoint - (2*xStartingPoint)}; //This is where you set the equation of y'
	yStartingPoint = yStartingPoint + (yPrime * stepCount);
	xStartingPoint = xStartingPoint + stepCount;
	
	if (stepNumber > 1)
	{
		findDifferentialEquation(stepNumber-1, xStartingPoint, yStartingPoint, xFinal);
		return;
	}
	if (stepNumber == 1)
	{
		std::cout << yStartingPoint << '\n';
		std::cout << yPrime << '\n';
		return;
	}
	
}



int main()
{
	findDifferentialEquation(2, 0, 0, 2); //Indicate how many steps you want, the initial x value, the initial y value, and the final x value
	return 0;
}
