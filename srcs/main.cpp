# include "Computerv1.hpp"

typedef struct opt
{
	bool verbose;
	const char *unknown;
}	opt;

int		parsing_arguments(int ac, char **av, opt *com);

int main(int ac, char **av)
{
	opt opts = {0, NULL};
	std::string	defaultunknownChar = std::string("X");
	if (parsing_arguments(ac, av, &opts) == EXIT_FAILURE)
		return EXIT_FAILURE;

	if (opts.unknown == NULL)
		opts.unknown = defaultunknownChar.c_str();

	std::cout << GREEN_ANSI << "--- Options gathering..." << RESET_ANSI << std::endl;
	std::cout << "- verbose: '" << std::boolalpha << opts.verbose << "'" << std::endl;
	std::cout << "- unknown's sign: '" << opts.unknown[0] << "'" << std::endl;
	
	Computerv1 com(av[0], opts.verbose, opts.unknown[0]);

	std::cout << GREEN_ANSI << "--- Trim..." << RESET_ANSI << std::endl;
	if (com.trim() == false)
		return EXIT_FAILURE;

	std::cout << GREEN_ANSI << "--- Split..." << RESET_ANSI << std::endl;
	if (com.splitSides() == false)
		return EXIT_FAILURE;
	
	std::cout << GREEN_ANSI << "--- Tokenize..." << RESET_ANSI << std::endl;
	if (com.tokeniseSides() == false)
		return EXIT_FAILURE;
	if (com.getOptVerbose())
		com.dumpSides();
	
	std::cout << GREEN_ANSI << "--- Swap..." << RESET_ANSI << std::endl;
	com.swapSides();
	if (com.getOptVerbose())
		com.dumpSides();

	std::cout << GREEN_ANSI << "--- Reducing..." << RESET_ANSI << std::endl;
	com.reduceLeftSide();
	if (com.getOptVerbose())
		com.dumpSides();

	std::cout << GREEN_ANSI << "--- Interpretation..." << RESET_ANSI << std::endl;
	if (com.interpretation() == false)
		return EXIT_FAILURE;

	std::cout << GREEN_ANSI << "--- Resolution..." << RESET_ANSI << std::endl;
	if (com.resolve() == false)
		return EXIT_FAILURE;

	return EXIT_SUCCESS;
}