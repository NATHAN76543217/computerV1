#ifndef COMPUTERV1_HPP
# define COMPUTERV1_HPP

# include <iostream>
# include <unistd.h>
# include <cstdio>
# include <cstdlib>

// Containers
# include <string>
# include <vector>

// Custom classes
# include "Nomos.hpp"

// Lib de parsing
# include "argparse.h"

// DONE get input as string
// DONE check presence of '='
// DONE check for whitespace between tokens
// DONE tokens are: "[0-9] X + - * / ^ = "
// Changed get a list of Nomos separated by a +
// DONE reduce each sides
// TODO forme réduite: end by ' = 0'
// TODO check complexity and select the right resolution method
// TODO Read float numbers
// TODO add arguments
//  - verbose
//  - change the unknown character
//  - display help

class Computerv1
{

	public:
		static const uint	degree_max;

		Computerv1( const char *str );
		Computerv1( Computerv1 const & src );
		~Computerv1();

		bool			checkEquals( void );
		void			splitSides( void );
		bool			tokeniseASide( std::string & input, std::vector<Nomos> & queue);
		bool			tokeniseSides( void );
		void			reduceSides( void );
		void			reduceASide( std::vector<Nomos> & side);
		void			dumpSides( void ) const;
		Computerv1 &	operator=( Computerv1 const & rhs );

		bool			getOptVerbose( void ) const;
		char			getOptChar( void ) const;
		
		bool			*_getOptVerbose( void );
		char			*_getOptChar( void );

		void			setOptVerbose( const bool );
		void			setOptChar( const char );

	private:
		std::string			input;
		std::string			input_right;
		std::string			input_left;
		bool				opt_verbose;
		char				opt_char;
		size_t				equal_pos;
		std::vector<std::string> tokens;
		std::vector<Nomos>	leftside;
		std::vector<Nomos>	rightside;


};

// std::ostream &			operator<<( std::ostream & o, Computerv1 const & i );

#endif /* ****************************************************** COMPUTERV1_H */