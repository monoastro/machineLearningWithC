#include <stdio.h>
#include <math.h>

#define numberOfParameters 1
#define numberOfDataPoints 4

const double e = 2.718281828;
const double alpha = 0.01f;

//hypothesis function
// y = 1/[1 + e^-(beta0 + beta1 * x)]

//{kg of Food eaten, Obese?}
double data[numberOfDataPoints][numberOfParameters + 1] =
{ 
	{0, 0},
	{1, 0},
	{2, 1},
	{3, 1},
};

//log error function
double errFunction(double beta0, double beta1)
{
	double error = 0;
	for(size_t i = 0; i<numberOfDataPoints; i++)
	{
		//here (x, y) = (data[i][0], data[i][1]);
		
		//our hypothesis function
		double sigmoid = 1/(1 + pow( e, -(beta0 + beta1 * data[i][0]) ) );

		error += - data[i][1] * log(sigmoid) - (1 - data[i][1]) * log (1 - sigmoid); 
	}
	error /= numberOfDataPoints;
	return error;
}

//the two sum terms required for the gradient descent algorithm
double sum0(double beta0, double beta1)
{
	double sum0 = 0;
	for(size_t i = 0; i<numberOfDataPoints; i++)
	{
		double sigmoid = 1/(1 + pow( e, -(beta0 + beta1 * data[i][0]) ) );
		sum0 += (sigmoid - data[i][1]) * 1;
	}
	return sum0;
}

double sum1(double beta0, double beta1)
{
	double sum1 = 0;
	for(size_t i = 0; i<numberOfDataPoints; i++)
	{
		double sigmoid = 1/(1 + pow( e, -(beta0 + beta1 * data[i][0]) ) );
		sum1 += (sigmoid - data[i][1]) * data[i][0];
	}
	return sum1;
}

void train(double *beta0, double *beta1)
{
	double error = 10, temp0, temp1;

	//gradient descent is done here
	do
	{
		temp0 = *beta0 - alpha*(1.f/numberOfDataPoints)*sum0(*beta0, *beta1);
		temp1 = *beta1 - alpha*(1.f/numberOfDataPoints)*sum1(*beta0, *beta1);

		*beta0 = temp0;
		*beta1 = temp1;
		
		error = errFunction(*beta0, *beta1);
		printf("%.6f\n", error);

	} while (error > 0.0001f);//double edged sword
}

int main()
{
	double beta0 = 0, beta1 = 0; 
	// at the end of the day, we only care about these two
	//these two along with the equation are our "Machine Learning Model"
	
	train(&beta0, &beta1);
	
	printf("\nFinal sigmoid equation is\ny = 1/(1 + e^-(%f + %fx) )\n\n", beta0, beta1);

	return 0;
}
