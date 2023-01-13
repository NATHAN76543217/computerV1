# include "Computerv1.hpp"

int		parsing_arguments(int ac, char **av, Computerv1 *com);

int main(int ac, char **av)
{
	if (ac != 2)
	{
		dprintf(STDERR_FILENO, "Bad number of arguments (1 argument expected but %d provided)\n", ac - 1);
		return EXIT_FAILURE;
	}
	std::cout << GREEN_ANSI << "--- Gathering..." << RESET_ANSI << std::endl;
	Computerv1 com(av[1]);
	parsing_arguments(ac, av, &com);

	std::cout << GREEN_ANSI << "--- Trim..." << RESET_ANSI << std::endl;
	if (com.trim() == false)
		return EXIT_FAILURE;

	std::cout << GREEN_ANSI << "--- Split..." << RESET_ANSI << std::endl;
	if (com.splitSides() == false)
		return EXIT_FAILURE;
	
	std::cout << GREEN_ANSI << "--- Tokenize..." << RESET_ANSI << std::endl;
	if (com.tokeniseSides() == false)
	{
		std::cerr << RED_ANSI << "Error while tokenizing. Aborting..." << RESET_ANSI << std::endl;
		return EXIT_FAILURE;
	}
	com.dumpSides();
	std::cout << "--- Reducing ..." << std::endl;
	com.reduceSides();
	com.dumpSides();
	// std::cout << "--- Swap ..." << std::endl;
	// com.swapSides();
	// com.dumpSides();

	return EXIT_SUCCESS;
}