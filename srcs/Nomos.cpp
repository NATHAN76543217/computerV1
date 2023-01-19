#include "Nomos.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/


Nomos::Nomos(char unknown, double value, size_t exponent) : _char(unknown), _value(value), _exponent(exponent)
{
}



Nomos::Nomos( const Nomos & src ) : _char(src._char), _value(src.getValue()), _exponent(src.getExponent())
{
}


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Nomos::~Nomos()
{
}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

Nomos &				Nomos::operator=( Nomos const & rhs )
{
	if ( this != &rhs )
	{
		this->_value = rhs.getValue();
		this->_exponent = rhs.getExponent();
	}
	return *this;
}

Nomos 				Nomos::operator+( Nomos const & rhs ) const
{
	Nomos nm(this->_char);

	if (this->_exponent != rhs._exponent)
		throw Nomos::NomosDegreeException();
	nm._value = this->_value + rhs._value;
	return nm;
}

Nomos &				Nomos::operator+=( Nomos const & rhs )
{
	if (this->_exponent != rhs._exponent)
		throw Nomos::NomosDegreeException();
	this->_value += rhs._value;
	return *this;
}

Nomos 				Nomos::operator-( Nomos const & rhs ) const
{
	Nomos nm(this->_char);

	if (this->_exponent != rhs._exponent)
		throw Nomos::NomosDegreeException();
	nm._value = this->_value - rhs._value;
	return nm;
}

Nomos &				Nomos::operator-=( Nomos const & rhs )
{
	if (this->_exponent != rhs._exponent)
		throw Nomos::NomosDegreeException();
	this->_value -= rhs._value;

	return *this;
}

Nomos 				Nomos::operator*( Nomos const & rhs ) const
{
	Nomos nm(this->_char);
	nm._value = this->_value * rhs._value;
	nm._exponent = this->_exponent + rhs._exponent;

	return nm;
}

Nomos &				Nomos::operator*=( Nomos const & rhs )
{
	this->_value *= rhs._value;
	this->_exponent += rhs._exponent;

	return *this;
}

Nomos 				Nomos::operator/( Nomos const & rhs ) const
{
	Nomos nm(this->_char);
	nm._value = this->_value / rhs._value;
	nm._exponent = std::abs((long long)(this->_exponent - rhs._exponent));

	return nm;
}

Nomos &				Nomos::operator/=( Nomos const & rhs )
{
	this->_value /= rhs._value;
	this->_exponent = std::abs((long long)(this->_exponent - rhs._exponent));

	return *this;
}

std::ostream &			operator<<( std::ostream & o, Nomos const & i )
{
	o << "(" << i.getValue() << " * " << i.getUnknownChar() << "^" << i.getExponent() << ")";
	return o;
}


/*
** --------------------------------- METHODS ----------------------------------
*/

void				Nomos::addValue(double nb)
{
	this->_value += nb;
}

bool				Nomos::isNull( void ) const
{
	return (this->_value == 0);
}

void				Nomos::switchSign( void )
{
	this->_value *= -1;
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

char				Nomos::getUnknownChar( void ) const
{
	return this->_char;
}


std::string			Nomos::getRawStr( char unknown ) const
{
	std::stringstream ss;
	ss << this->_value << " * " << unknown << "^" << this->_exponent;
	return ss.str();
}

double				Nomos::getValue( void ) const
{
	return this->_value;
}

void				Nomos::setValue( double value )
{
	this->_value = value;
}

size_t				Nomos::getExponent( void ) const
{
	return this->_exponent;
}

void				Nomos::setExponent( size_t exponent)
{
	this->_exponent = exponent;
}

/* ************************************************************************** */