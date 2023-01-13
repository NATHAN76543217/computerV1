# include "Computerv1.hpp"

int		parsing_arguments(int ac, char **av, Computerv1 *com)
{
	char			buf1[256];
	char			buf2[256];
	struct argparse	argparse;
	const char	*const usages[] = { buf1, buf2, NULL };

	if (strlen(av[0]) > 100)
		av[0][100] = '\0';

	buf1[sprintf(buf1, "%s    [options] polynomial_equation", av[0])] = '\0';

	struct argparse_option options[] = {
        OPT_HELP(),
        OPT_GROUP("Basic options"),
        // OPT_STRING('i', "interface", &com->opt.ifName, "Force to use a specific interface.", NULL, 0, 0),
        // OPT_GROUP("Modes:"),
        OPT_BOOLEAN('v', "verbose", com->_getOptVerbose(), "Enable verbose mode.", NULL, 0, 0),
        // OPT_BOOLEAN('r', "reverse", &malc->opt.reverse, "Bidirectional spoof (Man-in-the-middle).", NULL, 0, 0),
		//add timeout with socket option SO_RCVTIMEO (add option -t second)
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