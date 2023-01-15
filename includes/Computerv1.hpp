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

// TODO handle negative possibilities for degree 2

// ANSII COLORS
# define RESET_ANSI		"\033[0m"		
# define BOLD_ANSI		"\033[1m"		
# define RED_ANSI		"\033[91m"		
# define YELLOW_ANSI	"\033[93m"		
# define BLUE_ANSI		"\033[96m"		
# define LGREY_ANSI		"\033[37m"		
# define GREEN_ANSI		"\033[92m"		
# define DBLUE_ANSI		"\033[94m"	


// Utils 
double my_abs(double nb);
double my_sqrt(double nb);

class Computerv1
{

	public:
		static const uint	degree_max;

		Computerv1( const char *str, bool verbose = false, char unknown = 'X' );
		~Computerv1();

		bool			trim( void );
		bool			splitSides( void );
		bool			tokeniseASide( std::string & input, std::vector<Nomos> & queue);
		bool			tokeniseSides( void );
		void			reduceLeftSide();
		void			swapSides( void );
		Nomos*			extractX( std::string & input );

		bool			resolve( void );
		bool			interpretation( void );
		void			dumpSides( void ) const;

		double			getDegreeLeftValue( size_t degree);

		Computerv1 &	operator=( Computerv1 const & rhs );

		bool			getOptVerbose( void ) const;
		char			getOptChar( void ) const;
		
		bool			*_getOptVerbose( void );
		char			*_getOptChar( void );

		void			setOptVerbose( const bool );
		void			setOptChar( const char );

	private:
		std::string			input;
		std::string			input_saved;
		std::string			input_right;
		std::string			input_left;
		std::string			reduced_form;
		bool				opt_verbose;
		char				opt_char;
		size_t				degree;
		std::vector<Nomos>	leftside;
		std::vector<Nomos>	rightside;


};


#endif /* ****************************************************** COMPUTERV1_H */