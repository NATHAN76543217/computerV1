# include "Computerv1.hpp"

typedef struct opt
{
	bool verbose;
	char *unknown;
}	opt;

int		parsing_arguments(int ac, char **av, opt *opts)
{
	char			buf1[256];
	struct argparse	argparse;
	const char	*const usages[] = { buf1, NULL };

	if (strlen(av[0]) > 100)
		av[0][100] = '\0';

	buf1[sprintf(buf1, "%s    [options] polynomial_equation", av[0])] = '\0';

	struct argparse_option options[] = {
        OPT_HELP(),
        OPT_GROUP("Basic options"),
        OPT_STRING('c', "unknown", &(opts->unknown), "Set a different character for unknowns (default: X).", NULL, 0, 0),
        OPT_BOOLEAN('v', "verbose", &(opts->verbose), "Enable verbose mode.", NULL, 0, 0),
        OPT_END(),
    };

    argparse_init(&argparse, options, usages, 0);
    argparse_describe(&argparse, "\nComputerV1.", "\nSolves a polynomial second or lower degree equation.");
	
	ac = argparse_parse(&argparse, ac, (const char**)av);
	if (ac != 1)
	{
		argparse_usage(&argparse);
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}