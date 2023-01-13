# include "Computerv1.hpp"

int		parsing_arguments(int ac, char **av, Computerv1 *com);

int main(int ac, char **av)
{
	if (ac != 2)
	{
		dprintf(STDERR_FILENO, "Bad number of arguments (1 argument expected but %d provided)\n", ac - 1);
		return EXIT_FAILURE;
	}
	Computerv1 com(av[1]);
	parsing_arguments(ac, av, &com);
	if (com.checkEquals() == false)
		return EXIT_FAILURE;
	com.splitSides();
	std::cout << "--- Tokenize ..." << std::endl;
	if (com.tokeniseSides() == false)
	{
		std::cerr << "Error while tokenizing. Aborting..." << std::endl;
		return EXIT_FAILURE;
	}
	com.dumpSides();
	std::cout << "--- Reducing ..." << std::endl;
	com.reduceSides();
	com.dumpSides();
	// swap sides
	// com.swapSides();
	// com.dumpSides();

	return EXIT_SUCCESS;
}