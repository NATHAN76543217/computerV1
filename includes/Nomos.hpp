#ifndef NOMOS_HPP
# define NOMOS_HPP

# include <iostream>
# include <string>
# include <sstream>

class Nomos
{

	public:

        class NomosDegreeException : public std::exception
        {
            public:
                const char  *what(void) const throw(){
                    return "It's impossible to add or substract two Nomos with a different degree.";
                }
        };

		Nomos(char unknown = 'X', double value = 0, size_t exponent = 0 );
		Nomos( Nomos const & src );
		~Nomos();

		Nomos &		operator=( Nomos const & rhs );

		Nomos 		operator+( Nomos const & rhs ) const;
		Nomos 		operator-( Nomos const & rhs ) const;
		Nomos 		operator*( Nomos const & rhs ) const;
		Nomos 		operator/( Nomos const & rhs ) const;

		Nomos &		operator+=( Nomos const & rhs );
		Nomos &		operator-=( Nomos const & rhs );
		Nomos &		operator*=( Nomos const & rhs );
		Nomos &		operator/=( Nomos const & rhs );

		std::string	getRawStr( char unknown ) const;
		char		getUnknownChar( void ) const;

		double		getValue( void ) const;
		void		setValue( double value);
		void		addValue(double n);
		size_t		getExponent( void ) const;
		void		setExponent( size_t exponent );
		void		switchSign( void );
		bool		isNull(void) const;

	private:
		char		_char;
		double		_value;
		size_t		_exponent;
};

std::ostream &			operator<<( std::ostream & o, Nomos const & i );

#endif /* *********************************************************** NOMOS_H */