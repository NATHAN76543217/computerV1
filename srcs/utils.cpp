#include <iostream>

# define EPSILON_VALUE 0.000001

/*
** My own implementation of SquareRoot on double (floating point numbers)
*/

double my_abs(double nb)
{
	if (nb < 0)
		return -nb;
	return nb;
}

static double my_sqrt_min(double nb)
{
	if (nb <= 0 || nb > 1)
		return 0;
	double xhi = 1;
	double xlo = nb;
	double guess = nb * 2;
	double epsilon = EPSILON_VALUE;
	double sqr = guess * guess;
	while (my_abs((sqr - nb) / guess) > epsilon)
	{
		if (sqr > nb)
		{
			xhi = guess;
		}
		else
			xlo = guess;
		double new_guess = (xhi + xlo) / 2;
		if (guess == new_guess)
			break;
		guess = new_guess;
		sqr = guess * guess;
	}
	return guess;
}

double my_sqrt(double nb)
{
	if (nb <= 0)
		return 0;
	else if (nb == 1)
		return 1;
	else if (nb < 1)
		return my_sqrt_min(nb);
	double xhi = nb;
	double xlo = 0;
	double guess = nb / 2;
	double epsilon = EPSILON_VALUE;
	double sqr = guess * guess;
	while (my_abs((sqr - nb) / guess) > epsilon)
	{
		if (sqr > nb)
		{
			xhi = guess;
		}
		else
			xlo = guess;
		double new_guess = (xhi + xlo)/2;
		if (guess == new_guess)
			break;
		guess = new_guess;
		sqr = guess * guess;
	}
	return guess;
}

// int main()
// {
// 	std::cout << " sqrt(" << 25 << ") = " << my_sqrt(25) << std::endl;
// 	std::cout << " sqrt(" << 100 << ") = " << my_sqrt(100) << std::endl;
// 	std::cout << " sqrt(" << 50 << ") = " << my_sqrt(50) << std::endl;
// 	std::cout << " sqrt(" << 42.42 << ") = " << my_sqrt(42.42) << std::endl;
// 	std::cout << " sqrt(" << 0 << ") = " << my_sqrt(0) << std::endl;
// 	std::cout << " sqrt(" << 0.11 << ") = " << my_sqrt(0.11) << std::endl;
// 	std::cout << " sqrt(" << 0.25 << ") = " << my_sqrt(0.25) << std::endl;
// 	std::cout << " sqrt(" << 0.5 << ") = " << my_sqrt(0.5) << std::endl;
// 	std::cout << " sqrt(" << 0.75 << ") = " << my_sqrt(0.75) << std::endl;
// 	std::cout << " sqrt(" << 1 << ") = " << my_sqrt(1) << std::endl;
// 	std::cout << " sqrt(" << 1.5 << ") = " << my_sqrt(1.5) << std::endl;
// 	std::cout << " sqrt(" << 2 << ") = " << my_sqrt(2) << std::endl;
// 	std::cout << " sqrt(" << 2000 << ") = " << my_sqrt(2000) << std::endl;
// 	return 0;
// }