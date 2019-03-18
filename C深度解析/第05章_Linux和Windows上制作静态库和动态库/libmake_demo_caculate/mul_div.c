#include "caculate.h"

double power(double arg)
{
	double sum = 0;

	sum = mul(arg, arg);

	return sum;
}

double mul(double arg1, double arg2)
{
	double sum = 0;

	sum = arg1 * arg2;

	return sum;
}

double div(double arg1, double arg2)
{
	double sum = 0;

	sum = arg1 / arg2;

	return sum;
}
