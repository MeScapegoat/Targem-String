#include "String.h"

String::String( const String& str ) : _size( str._size )
{
	string = new char[ _size ];
	for ( size_t i = 0; i < _size; ++i )
		string[ i ] = str.string[ i ];
}


String::String( String&& str ) noexcept
{
	_size = str._size;
	str._size = 0;
	string = str.string;
	str.string = nullptr;
}


String::String( const char* const chr )
{
	int n = 0;
	while ( chr[ n++ ] != '\0' )
		++_size;
	string = new char[ _size ];
	for ( size_t i = 0; i < _size; ++i )
		string[ i ] = chr[ i ];
}


String& String::operator=( const String& str )
{
	if ( this != &str )
	{
		_size = str._size;
		delete[] string;
		string = new char[ _size ];
		for ( size_t i = 0; i < _size; ++i )
			string[ i ] = str.string[ i ];
	}
	return *this;
}


String& String::operator=( String&& str ) noexcept
{
	if ( this != &str )
	{
		_size = str._size;
		str._size = 0;
		delete[] string;
		string = str.string;
		str.string = nullptr;
	}
	return *this;
}


String& String::operator=( const char* const chr )
{
	delete[] string;
	_size = 0;
	int n = 0;
	while ( chr[ n++ ] != '\0' )
		++_size;
	string = new char[ _size ];
	for ( size_t i = 0; i < _size; ++i )
		string[ i ] = chr[ i ];
	return *this;
}


String& String::operator+=( const String& str )
{
	char* newstring = new char[ _size + str._size ];

	for ( size_t i = 0; i < _size; ++i )
		newstring[ i ] = string[ i ];

	for ( size_t i = 0; i < str._size; ++i )
		newstring[ i + _size ] = str.string[ i ];

	_size = _size + str._size;
	delete[] string;
	string = newstring;
	return *this;
}


String& String::operator+=( const char* const chr )
{
	size_t csize = 0, n = 0;

	while ( chr[ n++ ] != '\0' )
		++csize;

	char* newstring = new char[ _size + csize ];

	for ( size_t i = 0; i < _size; ++i )
		newstring[ i ] = string[ i ];

	for ( size_t i = 0; i < csize; ++i )
		newstring[ i + _size ] = chr[ i ];

	_size = _size + csize;
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


bool operator< ( const String& lhs, const String& rhs )
{
	size_t msize = lhs._size > rhs._size ? rhs._size : lhs._size;
	for ( size_t i = 0; i < msize; ++i )
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
	for ( size_t i = 0; i < msize; ++i )
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
	for ( size_t i = 0; i < lhs._size; ++i )
	{
		if ( lhs[ i ] != rhs[ i ] )
			return false;
	}
	return true;
}


std::ostream& operator<<( std::ostream& os, const String& str )
{
	return os.write(str.string, str._size);
}


std::istream& operator>>( std::istream& is, String& str )
{
	delete[] str.string;
	char letter;
	size_t strSize = 8, inputSize = 0;
	str.string = new char[ strSize ];

	while ( is.get( letter ) and ( letter == '\n' or letter == ' ' ) );

	while ( letter != '\n' and letter != ' ' )
	{
		++inputSize;
		if ( inputSize > strSize )
		{
			strSize *= 2;
			char* tmp;
			tmp = new char[ strSize ];
			for ( size_t i = 0; i < strSize / 2; ++i )
				tmp[ i ] = str.string[ i ];
			delete[] str.string;
			str.string = tmp;
		}
		str.string[ inputSize - 1 ] = letter;

		is.get( letter );
	}

	str._size = inputSize;

	return is;
}


std::istream& getline( std::istream& is, String& str )
{
	delete[] str.string;
	char letter;
	size_t strSize = 8, inputSize = 0;
	str.string = new char[ strSize ];

	while ( is.get( letter ) and letter != '\n' )
	{
		++inputSize;
		if ( inputSize > strSize )
		{
			strSize *= 2;
			char* tmp;
			tmp = new char[ strSize ];
			for ( size_t i = 0; i < strSize / 2; ++i )
				tmp[ i ] = str.string[ i ];
			delete[] str.string;
			str.string = tmp;
		}
		str.string[ inputSize - 1 ] = letter;
	}

	str._size = inputSize;

	return is;
}