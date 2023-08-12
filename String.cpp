#include "String.h"


String::String( const String& str ) : _size( str._size )
{
	string = new char[ _size ];
	for ( auto i = 0; i < _size; ++i )
		string[ i ] = str.string[ i ];
}


String& String::operator=( const String& str )
{
	_size = str._size;
	delete[] string;
	string = new char[ _size ];
	for ( auto i = 0; i < _size; ++i )
		string[ i ] = str.string[ i ];
	return *this;
}


String::String( String&& str ) noexcept
{
	_size = str._size;
	str._size = 0;
	string = str.string;
	str.string = nullptr;
}


String& String::operator=( String&& str ) noexcept
{
	if ( this != &str )
	{
		_size = str._size;
		str._size = 0;
		string = str.string;
		str.string = nullptr;
	}
	return *this;
}


String& String::operator+=( const String& str )
{
	int i = 0;
	char* newstring = new char[ _size + str._size ];
	for ( auto i = 0; i < _size; ++i )
		newstring[ i ] = string[ i ];
	for ( auto i = 0; i < str._size; ++i )
		newstring[ i + _size ] = str.string[ i ];

	_size = _size + str._size;
	delete[] string;
	string = newstring;
	return *this;
}


String operator+( const String& lhs, const String& rhs )
{
	String str( lhs );
	str += rhs;
	return str;
}


String::String( const char* const chr )
{
	int n = 0;
	while ( chr[ n++ ] != '\0' )
		++_size;
	string = new char[ _size ];
	for ( auto i = 0; i < _size; ++i )
		string[ i ] = chr[ i ];
}


String& String::operator=( const char* const chr )
{
	delete[] string;
	_size = 0;
	int n = 0;
	while ( chr[ n++ ] != '\0' )
		++_size;
	string = new char[ _size ];
	for ( auto i = 0; i < _size; ++i )
		string[ i ] = chr[ i ];
	return *this;
}


String& String::operator+=( const char* const chr )
{ 
	int csize = 0, i = 0;
	while ( chr[ i++ ] != '\0' )
		++csize;
	char* newstring = new char[ _size + csize ];
	for ( auto i = 0; i < _size; ++i )
		newstring[ i ] = string[ i ];
	for ( auto i = 0; i < csize; ++i )
		newstring[ i + _size ] = chr[ i ];

	_size = _size + csize;
	delete[] string;
	string = newstring;
	return *this; 
}


String operator+( const String& str, const char* const chr )
{
	String s( str );
	s += chr;
	return s;
}


String operator+( const char* const chr, const String& str )
{ 
	String s( chr );
	s += str;
	return s;
}


std::ostream& operator<<( std::ostream& os, const String& str )
{
	for ( auto i = 0; i < str._size; ++i )
		os << str.string[ i ];
	return os;
}


bool operator< ( const String& lhs, const String& rhs )
{
	size_t msize = lhs._size > rhs._size ? rhs._size : lhs._size;
	for ( auto i = 0; i < msize; ++i )
	{
		if ( lhs[ i ] < rhs[ i ] )
			return true;
		if ( lhs[ i ] > rhs[ i ] )
			return false;
	}
	return lhs._size < rhs._size;
}


bool operator> ( const String& lhs, const String& rhs )
{
	size_t msize = lhs._size > rhs._size ? rhs._size : lhs._size;
	for ( auto i = 0; i < msize; ++i )
	{
		if ( lhs[ i ] > rhs[ i ] )
			return true;
		if ( lhs[ i ] < rhs[ i ] )
			return false;
	}
	return lhs._size > rhs._size;
}


bool operator== ( const String& lhs, const String& rhs )
{
	if ( lhs._size != rhs._size )
		return false;
	for ( auto i = 0; i < lhs._size; ++i )
	{
		if ( lhs[ i ] != rhs[ i ] )
			return false;
	}
	return true;
}