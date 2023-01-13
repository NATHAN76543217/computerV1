#include "Computerv1.hpp"

const uint				Computerv1::degree_max = 2;


/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Computerv1::Computerv1( const char *str ) : input(str), opt_verbose(false), opt_char('X')
{
	this->input_saved = this->input;
	std::cout << "Original: " << this->input_saved << std::endl;; 
}

Computerv1::Computerv1( const Computerv1 & src ) : input(src.input), opt_verbose(src.opt_verbose), opt_char(src.opt_char)
{
	this->input_saved = this->input;

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
	std::cout << " --- Dump Left ---" << std::endl;
	while (lit != this->leftside.end())
	{
		std::cout << "  - Nomos: "<< *lit << std::endl;
		lit++;
	}

	std::vector<Nomos>::const_iterator rit = this->rightside.begin();
	std::cout << " --- Dump Right ---" << std::endl;
	while (rit != this->rightside.end())
	{
		std::cout << "  - Nomos: " << *rit << std::endl;
		rit++;
	}
}


void			Computerv1::reduceLeftSide()
{
	std::vector<Nomos> reducedSide;

	for (uint i = 0; i <= Computerv1::degree_max ; i++)
	{
		Nomos nm(0, i);
		for (std::vector<Nomos>::iterator it = this->leftside.begin(); it != this->leftside.end(); it++)
		{
			if (it->getExponent() == i)
				nm += *it;
		}
		if (nm.getValue() != 0)
		{
			reducedSide.push_back(nm);
			this->degree = i;
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
			this->reduced_form.append(it->getRawStr());
		}
	}
	this->reduced_form += " = 0";
	std::cout << "Reduced form: " << this->reduced_form << std::endl;
	std::cout << "Polynomial degree: " << this->degree << std::endl;
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
// Remove all whitespaces in the input
*/
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

Nomos*			Computerv1::extractX( std::string & input )
{
	double value = 1;
	ssize_t exp = 0;
	size_t offset = 0;
	if (input.size() == 0)
		return nullptr;
	
	if (input[0] == '+')
	{
		input.erase(input.begin());
	}
	
	if ( input[0] == '-')
	{
		value = -1;
		input.erase(input.begin());
	}

	if (input[0] != this->opt_char)
	{ 
		std::cerr << "RM Invalid character: number(X) expected (get '" << input[0] << "')" << std::endl;
		return nullptr;
	}

	std::cout << "-followed by a X ";
	input.erase(input.begin() + offset); // Erase X
	if (input[0] != '^')
	{
		// exponent is 1
		exp = 1;
		std::cout << "with no exponent specified" << std::endl;
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
			std::cout << " exponent " << exp << std::endl;
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
	Nomos* nomos =	new Nomos(value, exp);
	std::cout << "Xtracted: " << (*nomos)  << std::endl;
	return nomos;
}

bool			Computerv1::tokeniseASide( std::string & input, std::vector<Nomos> & queue )
{
	size_t pos		= 0;
	Nomos* nomos	= nullptr;
	Nomos* nomos2	= nullptr;
	// size_t oper_pos	= 0;
	std::string::iterator it = input.begin();
	while (input.length() != 0)
	{
		std::cout << "To process left = (" << input << ") len = " << input.length() << std::endl;
		try {
			// read a whole number
			it = input.begin();
			nomos = new Nomos(std::stod(input, &pos));
		}
		catch (std::invalid_argument & e)
		{
			// X next to start or preceded by a + or - 
			nomos = this->extractX(input);
			if (nomos == nullptr)
			{
				std::cerr << RED_ANSI << "Syntax error: Impossible to extract the next value (near ..." << input << ")." << RESET_ANSI << std::endl;
				return false;
			}
			std::cout << "----------" << std::endl;
			queue.push_back(*nomos);
			// this
			// std::cout << "LEFT: " << input << std::endl;
			continue;
		}
		std::cout << "TOK = " << *nomos << std::endl;
		// check next char
		char oper = input[pos];
		std::cout << " followed by oper = '" << oper << "'" << std::endl;
		if (oper == '+' || oper == '-' || oper == '\0')
		{
			// next token
			std::cout << "----------" << std::endl;
			if (oper == '+')
				input.erase(it, it + pos + 1);
			else
				input.erase(it, it + pos + 1);
			queue.push_back(*nomos);
			delete nomos;
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
					nomos2 = new Nomos(std::stod(input, &pos));
				}
				catch (std::invalid_argument & e)
				{
					// next after * is X
					nomos2 = this->extractX(input);
					pos = 0;
				}

				std::cout << "TOK after [*/] = " << *nomos2 << std::endl;
				if (oper == '*')
				{
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
						std::cerr << "This equation imply a division by 0 which is forbidden." << std::endl; 
						return false;
					}
					std::cout << (*nomos) << " / " << (*nomos2) << " = " << *nomos / *nomos2 << std::endl;
					*nomos /= *nomos2;
				}
				delete (nomos2);
				oper = input[pos];
				std::cout << "and next oper = '" << oper << "'" << std::endl;
				
			}
			std::cout << "----------" << std::endl;
			input.erase(it, it + pos + 1);
			queue.push_back(*nomos);
			delete nomos;
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
// Select the right resolution method and call it  
*/
bool			Computerv1::resolve( void )
{
	double A = 0;
	double B = 0;
	double result = 0;
	switch (this->degree)
	{
		case 0:
			// Only numbers
			if (this->leftside.empty())
			{
				std::cout << "This equation is correct (" << this->input_saved << ")." << std::endl;
			}
			else
			{
				std::cout << "RM Should be empty: "<< this->leftside[0] << std::endl; 
				std::cout << "This equation is wrong (" << this->input_saved << ")." << std::endl;
			}
			break;
		case 1:
			// distinguish X in A*X^0 + B*X^1 = 0
			// = -A / B
			A = this->getDegreeLeftX(0).getValue();
			B = this->getDegreeLeftX(1).getValue();
			if (B == 0)
			{
				std::cerr << "This equation imply a division by 0 and so have no resolution." << std::endl;
				break;
			}
			result = -A / B;
			std::cout << "X = " << result << std::endl;

			break;
		case 2:
			// compute disciminant
			break;
	}
	return true;
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/*
// Return the first occurence of a Nomos of the specified 'degree' 
*/
Nomos&			Computerv1::getDegreeLeftX( size_t degree)
{
	std::vector<Nomos>::iterator it = this->leftside.begin();
	for (; it != this->leftside.end(); it++)
	{
		if (it->getExponent() == degree)
		{
			return *it;
		}
	}
	std::cerr << "Pas sensé passer ici" << std::endl;
	return *it;
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