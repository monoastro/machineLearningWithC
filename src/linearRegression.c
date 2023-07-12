#include <stdio.h>
#include <math.h>

#define numberOfDataPoints 4
#define numberOfParameters 1

//learning rate
const double alpha = 0.001f;

//hypothesis function
//y_cap = theta0*1 + theta1*x; // a more general form

//data table
double data[numberOfDataPoints][numberOfParameters + 1] = {
	{1, 1},
	{2, 2},
	{3, 3},
	{4, 4},
};

//Mean Square Error function
double errFunction(double theta0, double theta1)
{
	double error = 0;
	for(size_t i = 0; i<numberOfDataPoints; i++)
	{
		//here (x, y) = (data[i][0], data[i][1]);
		error += pow(theta0 + theta1 * data[i][0] - data[i][1], 2);
		//error += (theta0 + theta1 * data[i][0] - data[i][1]) * (theta0 + theta1 * data[i][0] - data[i][1]);
		//doesn't use external libs tho
	}
	error /= 2.0f*numberOfDataPoints;
	return error;
}

double sum0(double theta0, double theta1)
{
	double sum0 = 0;
	for(size_t i = 0; i<numberOfDataPoints; i++)
	{
		sum0 += (theta0 + theta1 * data[i][0] - data[i][1]);
	}
	return sum0;
}

double sum1(double theta0, double theta1)
{
	double sum1 = 0;
	for(size_t i = 0; i<numberOfDataPoints; i++)
	{
		sum1 += (theta0 + theta1 * data[i][0] - data[i][1]) * data[i][0];
	}
	return sum1;
}

//notice how the term (theta0 + theta1 * data[i][0] - data[i][1]) 
//i.e. the deviation is repeated multiple times

void train(double *theta0, double *theta1)
{
	double error = 10, temp0, temp1;
	do
	{
		temp0 = *theta0 - alpha*(1.f/numberOfDataPoints)*sum0(*theta0, *theta1);
		temp1 = *theta1 - alpha*(1.f/numberOfDataPoints)*sum1(*theta0, *theta1);

		*theta0 = temp0;
		*theta1 = temp1;

		error = errFunction(*theta0, *theta1);
		printf("%.6f\n", error);

	} while (error > 0.001f);//double edged sword
}

int main()
{
	double theta0 = 0, theta1 = 0; // at the end of the day, we only care about these two
	//these two along with the equation are our "Machine Learning Model"
	
	train(&theta0, &theta1);
	printf("\nFinal linear equation is\ny = %fx + %f\n\n", theta1, theta0);
	return 0;
}
