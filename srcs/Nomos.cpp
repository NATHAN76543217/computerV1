#include "Nomos.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/


Nomos::Nomos(ssize_t value, size_t exponent) : _value(value), _exponent(exponent)
{
}

Nomos::Nomos( const Nomos & src ) : _value(src.getValue()), _exponent(src.getExponent())
{
}


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Nomos::~Nomos()
{
	//destructeur pour toute les listes
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
	Nomos nm;
	if (this->_exponent != rhs._exponent)
		throw std::exception();
	nm._value = this->_value + rhs._value;
	return nm;
}

Nomos &				Nomos::operator+=( Nomos const & rhs )
{
	if (this->_exponent != rhs._exponent)
		throw std::exception();
	this->_value += rhs._value;
	return *this;
}

Nomos 				Nomos::operator-( Nomos const & rhs ) const
{
	Nomos nm;
	if (this->_exponent != rhs._exponent)
		throw std::exception();
	nm._value = this->_value - rhs._value;
	return nm;
}

Nomos &				Nomos::operator-=( Nomos const & rhs )
{
	if (this->_exponent != rhs._exponent)
		throw std::exception();
	this->_value -= rhs._value;
	return *this;
}

Nomos 				Nomos::operator*( Nomos const & rhs ) const
{
	Nomos nm;
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
	Nomos nm;
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
	o << "(" << i.getValue() << " * X^" << i.getExponent() << ")";
	return o;
}


/*
** --------------------------------- METHODS ----------------------------------
*/

void				Nomos::addScalar(size_t nb)
{
	this->_value += nb;

}

bool				Nomos::isNull( void ) const
{
	return (this->_value == 0 && this->_exponent == 0);
}
/*
** --------------------------------- ACCESSOR ---------------------------------
*/

ssize_t				Nomos::getValue( void ) const
{
	return this->_value;
}

void				Nomos::setValue( ssize_t value )
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