#include "Computerv1.hpp"

const uint				Computerv1::degree_max = 2;


/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Computerv1::Computerv1( const char *str ) : input(str), opt_verbose(false), opt_char('X')
{
}

Computerv1::Computerv1( const Computerv1 & src ) : input(src.input), opt_verbose(src.opt_verbose), opt_char(src.opt_char)
{
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

// std::ostream &			operator<<( std::ostream & o, Computerv1 const & i )
// {
// 	//o << "Value = " << i.getValue();
// 	return o;
// }


/*
** --------------------------------- METHODS ----------------------------------
*/

void 			Computerv1::dumpSides( void ) const
{
	std::vector<Nomos>::const_iterator lit = this->leftside.begin();
	std::cout << "--- Dump Left ---" << std::endl;
	while (lit != this->leftside.end())
	{
		std::cout << "Nomos: "<< *lit << std::endl;
		lit++;
	}

	std::vector<Nomos>::const_iterator rit = this->rightside.begin();
	std::cout << "--- Dump Right ---" << std::endl;
	while (rit != this->rightside.end())
	{
		std::cout << "Nomos: " << *rit << std::endl;
		rit++;
	}
}

void			Computerv1::reduceSides( void )
{
	this->reduceASide(this->leftside);
	this->reduceASide(this->rightside);
}

void			Computerv1::reduceASide( std::vector<Nomos> & side)
{
	std::vector<Nomos> reducedSide;

	for (uint i = 0; i <= Computerv1::degree_max ; i++)
	{
		Nomos nm(0, i);
		for (std::vector<Nomos>::iterator it = side.begin(); it != side.end(); it++)
		{
			if (it->getExponent() == i)
			{
				nm += *it;
			}
		}
		if (nm.getValue() != 0)
			reducedSide.push_back(nm);
	}
	side = reducedSide;
}

bool			Computerv1::trim( void )
{
	this->input.erase(remove_if(this->input.begin(), this->input.end(), isspace), this->input.end());
	std::cout << "Trimed: " << this->input << std::endl;
	return true;
}

bool			Computerv1::tokeniseSides( void )
{
	if (this->tokeniseASide(this->input_left, this->leftside) == false)
		return false;
	if (this->tokeniseASide(this->input_right, this->rightside) == false)
		return false;
	return true;
}

bool			Computerv1::tokeniseASide( std::string & input, std::vector<Nomos> & queue )
{
	size_t pos	= 0;
	// size_t oper_pos	= 0;
	std::string::iterator it = input.begin();
	while (input.length() != 0)
	{
		std::cout << "To process left = (" << input << ") len = " << input.length() << std::endl;
		// read a whole number
		it = input.begin();
		Nomos* nomos = new Nomos(std::stod(input, &pos));

		std::cout << "TOK = " << *nomos << std::endl;
		// check next char
		char oper = input[pos];
		std::cout << " followed by oper = '" << oper << "'" << std::endl;
		if (oper == '+' || oper == '-' || oper == '\0')
		{
			// next token
			std::cout << "End of token" << std::endl;
			input.erase(it, it + pos);
			queue.push_back(*nomos);
			continue;
		}
		else if (oper == '*' || oper == '/')
		{
			// after number its a * or /
			while ((oper == '*' || oper == '/') && input.length() != 0)
			{
				input.erase(it, it + pos + 1);
				try {
					//after * is a number
					Nomos* nomos2 = new Nomos(std::stod(input, &pos));
					std::cout << "TOK after [*/] = " << *nomos2 << std::endl;
					if (oper == '*')
					{
						std::cout << (*nomos) << " * " << (*nomos2) << " = " << *nomos * *nomos2 << std::endl;
						*nomos *= *nomos2;
					}
					else
					{
						std::cout << (*nomos) << " / " << (*nomos2) << " = " << *nomos / *nomos2 << std::endl;
						*nomos /= *nomos2;
					}
					delete (nomos2);
				}
				catch (std::invalid_argument & e)
				{
					// next after * is X
					if (input[0] != this->opt_char)
					{
						std::cerr << "Invalid character: number(X) expected (get '" << input << "'" << std::endl;
						return false;
					}
					std::cout << "followed by a X ";
					pos = 1;
					// Nomos* nomos2 = new Nomos(nomos);
					// delete X
					// input.erase(input.begin(), input.begin() + 1);
					if (input[1] != '^')
					{
						// exponent is 1
						std::cout << "without exponent" << std::endl;
						nomos->setExponent(1);
						// goto next operand
					}
					else
					{
						input.erase(input.begin(), input.begin() + 2);
						// check exponent
						try {
							ssize_t exp	= std::stoi(input, &pos);
							// exp is valid
							std::cout << "with exponent " << exp << std::endl;
							nomos->setExponent(nomos->getExponent() + exp);
							// goto next operand
						}
						catch (std::exception & e)
						{
							// exp is invalid
							std::cerr << "Invalid exponent: valid number expected" << std::endl;
							return false;
						}
						
					}
					std::cout << (*nomos) << " <= old * X" << std::endl;
				}

				oper = input[pos];
				std::cout << "and next oper = '" << oper << "'" << std::endl;
				
			}
			std::cout << "End of token" << std::endl;
			input.erase(it, it + pos + 1);
			queue.push_back(*nomos);
			continue;
		}
		else
		{
			std::cerr << "Invalid operand after number. '" << oper << "' at " << pos + 1 << "" << std::endl;
			return false;		
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
		std::cerr << "Invalid Syntax: No Equal Sign (=) Found" << std::endl;
		return false;
	}
	last = this->input.find_last_of('=');
	if (last != first)
	{
		std::cerr << "Invalid Syntax: Too Many Equal Sign (=) Found" << std::endl;
		return false;
	}
	equal_pos = last;
	this->input_left = this->input.substr(0, equal_pos);
	this->input_right = this->input.substr(equal_pos + 1);
	std::cout << "Left  string: " << this->input_left << std::endl;
	std::cout << "Right string: " << this->input_right << std::endl;
	return true;
}


/*
** --------------------------------- ACCESSOR ---------------------------------
*/

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