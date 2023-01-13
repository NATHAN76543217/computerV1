#ifndef NOMOS_HPP
# define NOMOS_HPP

# include <iostream>
# include <string>

class Nomos
{

	public:

		Nomos(ssize_t value = 0, size_t exponent = 0);
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

		ssize_t		getValue( void ) const;
		void		setValue( ssize_t value);
		size_t		getExponent( void ) const;
		void		setExponent( size_t exponent );
		void		addScalar(size_t n);
		bool		isNull(void) const;

	private:
		ssize_t		_value;
		size_t		_exponent;
};

std::ostream &			operator<<( std::ostream & o, Nomos const & i );

#endif /* *********************************************************** NOMOS_H */