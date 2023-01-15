#include "Computerv1.hpp"

const uint				Computerv1::degree_max = 2;


/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Computerv1::Computerv1( const char *str, bool verbose, char unknown ) : input(str), opt_verbose(verbose), opt_char(unknown)
{
	this->input_saved = this->input;
	std::cout << BOLD_ANSI << "Original: \"" << RESET_ANSI << BLUE_ANSI << this->input_saved << RESET_ANSI << "\"" <<std::endl;; 
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Computerv1::~Computerv1()
{
}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

Computerv1 &				Computerv1::operator=( Computerv1 const & rhs )
{
	if ( this != &rhs )
	{
		this->input = rhs.input;
		this->opt_verbose = rhs.opt_verbose;
		this->opt_char = rhs.opt_char;
	}
	return *this;
}


/*
** --------------------------------- METHODS ----------------------------------
*/

void 			Computerv1::dumpSides( void ) const
{
	std::vector<Nomos>::const_iterator lit = this->leftside.begin();
	std::cout << "--- Left Stack ---" << std::endl;
	while (lit != this->leftside.end())
	{
		std::cout << "  - Nomos: "<< *lit << std::endl;
		lit++;
	}

	std::vector<Nomos>::const_iterator rit = this->rightside.begin();
	std::cout << "--- Right Stack ---" << std::endl;
	while (rit != this->rightside.end())
	{
		std::cout << "  - Nomos: " << *rit << std::endl;
		rit++;
	}
}


void			Computerv1::reduceLeftSide()
{
	std::vector<Nomos> reducedSide;
	std::vector<Nomos>::iterator it = this->leftside.begin();
	std::vector<Nomos>::iterator itend = this->leftside.end();

	//Reduce elements up to max_degree 
	if (this->leftside.size() == 0)
		return ;
	for (uint i = 0; i <= Computerv1::degree_max ; i++)
	{
		Nomos nm(this->opt_char, 0, i);
		it = this->leftside.begin();
		itend = this->leftside.end();
		while (it != itend)
		{
			if (it->getExponent() != i)
				it++;
			else
			{
				nm += *it;
				this->leftside.erase(it);
				it = this->leftside.begin();
				itend = this->leftside.end();
			}
		}
		if (nm.getValue() != 0)
		{
			reducedSide.push_back(nm);
			this->degree = i;
		}
	}

	//Reduce elements of a different degree 

	while (this->leftside.size() != 0)
	{
		it = this->leftside.begin();
		itend = this->leftside.end();
		Nomos nm(*it);
		this->leftside.erase(it);
		it++;
		it = this->leftside.begin();
		itend = this->leftside.end();
		while (it != itend)
		{
			if (it->getExponent() == nm.getExponent())
			{
				nm += *it;
				this->leftside.erase(it);
				it = this->leftside.begin();
				itend = this->leftside.end();
			}
			else
				it++;
		}
		if (nm.getValue() != 0)
		{
			if (nm.getExponent() > this->degree)
				this->degree = nm.getExponent();
			reducedSide.push_back(nm);
		}
	}
	this->leftside = reducedSide;
}


bool			Computerv1::interpretation( void )
{
	if (this->rightside.size() != 0)
	{
		std::cerr << "Error: the right side isn't empty at the interpretation phase" << std::endl;
		return false;
	}

	if (this->leftside.size() == 0)
		this->reduced_form = "0";
	else
	{
		for (std::vector<Nomos>::iterator it = this->leftside.begin(); it != this->leftside.end(); it++)
		{
			if (it != this->leftside.begin())
				this->reduced_form += " + ";
			this->reduced_form.append(it->getRawStr( this->getOptChar() ));
		}
	}
	this->reduced_form += " = 0";
	std::cout << "Reduced form: " << BLUE_ANSI << this->reduced_form << RESET_ANSI << std::endl;
	std::cout << "Polynomial degree: " << BLUE_ANSI << this->degree << RESET_ANSI << std::endl;
	if (this->degree > Computerv1::degree_max || this->degree < 0)
	{
		std::cerr << RED_ANSI << "Error: This is an equation of degree " << RESET_ANSI << this->degree << RED_ANSI << ". We can't resolve this. Aborting..." << RESET_ANSI << std::endl;
		return false;
	}
	return true;
}

void			Computerv1::swapSides( void )
{
	std::vector<Nomos>::iterator rit = this->rightside.begin();
	while (rit != this->rightside.end())
	{
		rit->switchSign();
		this->leftside.push_back(*rit);
		rit++;
	}
	this->rightside.clear();
}

/*
** Remove all whitespaces in the input
*/
bool			Computerv1::trim( void )
{
	this->input.erase(remove_if(this->input.begin(), this->input.end(), isspace), this->input.end());
	if (this->getOptVerbose())
		std::cout << BOLD_ANSI << "Trimed: \"" << RESET_ANSI << BLUE_ANSI << this->input << RESET_ANSI << std::endl;
	return true;
}

bool			Computerv1::tokeniseSides( void )
{
	if (this->opt_verbose)
		std::cout << " - Left Side - "<< std::endl;
	if (this->tokeniseASide(this->input_left, this->leftside) == false)
		return false;
	
	if (this->opt_verbose)
		std::cout << " - Right Side - "<< std::endl;
	if (this->tokeniseASide(this->input_right, this->rightside) == false)
		return false;
	return true;
}

Nomos*			Computerv1::extractX( std::string & input )
{
	double	value = 1;
	ssize_t	exp = 0;
	size_t	offset = 0;

	if (input.size() == 0)
		return nullptr;
	
	if (input[0] == '+')
		input.erase(input.begin());
	
	if ( input[0] == '-')
	{
		value = -1;
		input.erase(input.begin());
	}

	if (input[0] != this->opt_char)
	{ 
		// std::cerr << "RM Invalid character: number(X) expected (get '" << input[0] << "')" << std::endl;
		return nullptr;
	}

	input.erase(input.begin() + offset); // Erase X
	if (input[0] != '^')
	{
		exp = 1;
		// goto next operand
	}
	else
	{
		// Remove exponent sign
		input.erase(input.begin());
		try {
			// Get exponant value
			exp	= std::stoi(input, &offset);
			// exp is valid
			input.erase(input.begin(), input.begin() + offset);

			// goto next operand
		}
		catch (std::exception & e)
		{
			// exponant value is invalid
			std::cerr << "Invalid exponent: valid number expected" << std::endl;
			return nullptr;
		}			
	}
	Nomos* nomos =	new Nomos(this->opt_char, value, exp);
	if (this->getOptVerbose())
		std::cout << "Xtracted: " << (*nomos)  << std::endl;
	return nomos;
}

bool			Computerv1::tokeniseASide( std::string & input, std::vector<Nomos> & queue )
{
	size_t oper_pos	= 0;
	Nomos* nomos	= nullptr;
	Nomos* nomos2	= nullptr;
	char oper = ' ';
	std::string::iterator it = input.begin();
	while (input.length() != 0)
	{
		if (this->opt_verbose)
			std::cout << "Left to process: \"" << input << "\"" << std::endl;
		it = input.begin();
		try {
			// read a whole number
			nomos = new Nomos(this->opt_char, std::stod(input, &oper_pos));
		}
		catch (std::invalid_argument & e)
		{
			// X next to start or preceded by a + or - 
			// oper = input[0];
			nomos = this->extractX(input);
			if (nomos == nullptr)
			{
				std::cerr << RED_ANSI << "-Syntax error: Impossible to extract the next value (near \"..." << input << "\")." << RESET_ANSI << std::endl;
				return false;
			}
			if (this->getOptVerbose())
				std::cout << "----------" << std::endl;
		}
		oper = input[oper_pos];
		// check next char
		if (this->getOptVerbose())
		{
			std::cout << "TOK = " << *nomos << std::endl;
			std::cout << "OPER = '" << oper << "'" << std::endl;
		}	
		if (oper == '+' || oper == '-' || oper == '\0')
		{
			// next token
			if (this->getOptVerbose())
				std::cout << "----------" << std::endl;
			if (oper == '+')
				input.erase(it, it + oper_pos + 1);
			else if (oper == '-' && input[oper_pos + 1] == '-')
				input.erase(it, it + oper_pos + 1);
			else
				input.erase(it, it + oper_pos);
			queue.push_back(*nomos);
			delete nomos;
			continue;
		}
		else if (oper != '*' && oper != '/')
		{
			std::cerr << RED_ANSI << "Invalid Syntax: Bad character after number. '" << oper << "' at " << oper_pos + 1 << "" << std::endl;
			return false;		
		}
		else
		{
			// after number its a * or /
			while ((oper == '*' || oper == '/') && input.length() != 0)
			{
				input.erase(it, it + oper_pos + 1);
				try {
					//after * is a number
					nomos2 = new Nomos(this->opt_char, std::stod(input, &oper_pos));
				}
				catch (std::invalid_argument & e)
				{
					// next after * is X
					nomos2 = this->extractX(input);
					if (nomos == nullptr)
					{
						delete nomos;
						delete nomos2;
						std::cerr << RED_ANSI << "Syntax error: Impossible to extract the next value (near \"..." << input << "\")." << RESET_ANSI << std::endl;
						return false;
					}
					oper_pos = 0;
				}
				if (this->getOptVerbose())
					std::cout << "TOK " << oper << *nomos2 << std::endl;
				if (oper == '*')
				{
					if (this->getOptVerbose())
						std::cout << (*nomos) << " * " << (*nomos2) << " = " << *nomos * *nomos2 << std::endl;
					*nomos *= *nomos2;
				}
				else
				{
					if (nomos2->isNull())
					{
						// Avoid division by 0
						delete nomos;
						delete nomos2;
						std::cerr << RED_ANSI << "This equation imply a division by 0 which is forbidden." << RESET_ANSI << std::endl; 
						return false;
					}
					else if (this->getOptVerbose())
						std::cout << (*nomos) << " / " << (*nomos2) << " = " << *nomos / *nomos2 << std::endl;
					*nomos /= *nomos2;
				}
				delete (nomos2);
				oper = input[oper_pos];
				if (this->getOptVerbose())
					std::cout << "0PER = '" << oper << "'" << std::endl;
				
			}
			if (this->getOptVerbose())
				std::cout << "----------" << std::endl;
			input.erase(it, it + oper_pos);
			queue.push_back(*nomos);
			delete nomos;
			continue;
		}
	}
	return true;
}

bool			Computerv1::splitSides( void )
{
	size_t first = 0;
	size_t last = 0;
	size_t equal_pos = 0;
	first = this->input.find_first_of('=');
	if (first == std::string::npos)
	{
		std::cerr << RED_ANSI << "Invalid Syntax: No Equal Sign (=) Found" << RESET_ANSI << std::endl;
		return false;
	}
	last = this->input.find_last_of('=');
	if (last != first)
	{
		std::cerr << RED_ANSI << "Invalid Syntax: Too Many Equal Sign (=) Found" << RESET_ANSI << std::endl;
		return false;
	}
	equal_pos = last;
	this->input_left = this->input.substr(0, equal_pos);
	this->input_right = this->input.substr(equal_pos + 1);
	std::cout << BOLD_ANSI << " Left string: \"" << RESET_ANSI << BLUE_ANSI << this->input_left << RESET_ANSI << "\"" << std::endl;
	std::cout << BOLD_ANSI << "Right string: \"" << RESET_ANSI << BLUE_ANSI << this->input_right << RESET_ANSI << "\"" << std::endl;
	if (this->input_left.empty())
	{
		std::cerr << RED_ANSI << "invalid Syntax: Left side is empty." << RESET_ANSI << std::endl;
		return false;
	}
	if (this->input_right.empty())
	{
		std::cerr << RED_ANSI << "invalid Syntax: Right side is empty." << RESET_ANSI << std::endl;
		return false;
	}
	return true;
}

/*
** Select the right resolution method and call it  
*/
bool			Computerv1::resolve( void )
{
	double A = 0;
	double B = 0;
	double C = 0;
	double delta = 0;
	double result = 0;
	switch (this->degree)
	{
		case 0:
			// degree 0 
			// Only numbers
			if (this->leftside.empty())
			{
				std::cout << YELLOW_ANSI << "-> This equation is valid (" << this->input_saved << ")." << RESET_ANSI << std::endl;
			}
			else
			{
				std::cout << "RM Should be empty: "<< this->leftside[0] << std::endl; 
				std::cout << YELLOW_ANSI << "-> This equation is wrong (" << this->input_saved << ")." << RESET_ANSI << std::endl;
			}
			break;
		case 1:
			// degree 1 
			// distinguish X in A*X^0 + B*X^1 = 0
			// X = -B / A
			A = this->getDegreeLeftValue(1);
			B = this->getDegreeLeftValue(0);
			if (A == 0)
			{
				std::cerr << RED_ANSI << "This equation imply a division by 0 and so have no resolution." << RESET_ANSI << std::endl;
				break;
			}
			result = -B / A;
			std::cout << YELLOW_ANSI << "-> X = (-B / A) = " << -B << " / " << A << " = " << result << RESET_ANSI << std::endl;

			break;
		case 2:
			// degree 2 
			A = this->getDegreeLeftValue(2);
			B = this->getDegreeLeftValue(1);
			C = this->getDegreeLeftValue(0);
			delta = (B * B) - (4 * A * C);
			std::cout << "Discriminant: " << delta << std::endl;
			if (delta < 0)
				std::cout << YELLOW_ANSI << "Delta is strictly negative. This equation have 2 complex solutions: \n-> "\
					<< this->opt_char << "1 = " << \
					(- B / (2 * A) ) << " - " << my_sqrt(my_abs(delta)) << " * (i / " << (2 * A) \
					<< ")\n-> " << this->opt_char << "2 = " << \
					(- B / (2 * A) ) << " + " << my_sqrt(my_abs(delta)) << " * (i / " << (2 * A) << ")" << RESET_ANSI << std::endl;
			else if (delta == 0)
				std::cout << YELLOW_ANSI << "Delta is null. This equation have 1 solution: \n-> " \
					<< this->opt_char << "2 = " << (- B / (2 * A)) << RESET_ANSI << std::endl;
			else
			{
				// two solutions
				std::cout << YELLOW_ANSI << "Delta is strictly positive. This equation have 2 solutions: \n-> " \
					<< this->opt_char << "1 = " << ((- B - my_sqrt(delta) ) / (2 * A)) \
					<< "\n-> " << this->opt_char << "2 = " << ((- B + my_sqrt(delta) ) / (2 * A)) << RESET_ANSI << std::endl;
			}
			break;
	}
	return true;
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/*
** Return the first occurence of a Nomos of the specified 'degree' 
*/
double			Computerv1::getDegreeLeftValue( size_t degree)
{
	std::vector<Nomos>::iterator it = this->leftside.begin();
	for (; it != this->leftside.end(); it++)
	{
		if (it->getExponent() == degree)
			return it->getValue();
	}
	return 0;
}


bool*			Computerv1::_getOptVerbose( void )
{
	return &(this->opt_verbose);
}

char*			Computerv1::_getOptChar( void )
{
	return &(this->opt_char);
}

bool			Computerv1::getOptVerbose( void ) const
{
	return this->opt_verbose;
}

char			Computerv1::getOptChar( void ) const
{
	return this->opt_char;
}

void			Computerv1::setOptVerbose( const bool opt)
{
	this->opt_verbose = opt;
}

void			Computerv1::setOptChar( const char opt)
{
	this->opt_char = opt;
}

/* ************************************************************************** */