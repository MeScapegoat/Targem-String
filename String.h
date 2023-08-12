#ifndef __TARGEMSTRING_H
#define __TARGEMSTRING_H
#include <iostream>


class String
{
public:
	//- Есть конструктор копирования.
	String( const String& str );

	//-Есть оператор присваивания.
	String& operator=( const String& str );

	//- Поддерживается move-сематника.
	String( String&& str ) noexcept;
	String& operator=( String&& str ) noexcept;

	//- Есть оператор `+=`.
	String& operator+=( const String& str );

	//- Есть внешний оператор сложения двух строк.
	friend String operator+( const String& lhs, const String& rhs );

	//- Операции поддерживаются не только для параметров типа `String`, но и для традиционных С-строк, оканчивающихся нулем.
	String( const char* const chr );
	String& operator=( const char* const chr );
	String& operator+=( const char* const chr );
	friend String operator+( const String& str, const char* const chr );
	friend String operator+( const char* const chr, const String& str );

	//
	friend std::ostream& operator<<( std::ostream& os, const String& str );
	friend bool operator< ( const String& lhs, const String& rhs );
	friend bool operator> ( const String& lhs, const String& rhs );
	friend bool operator== ( const String& lhs, const String& rhs );
	char& operator[]( const size_t& n ) { return string[ n ]; }
	const char& operator[]( const size_t& n ) const { return string[ n ]; }
	size_t size() const { return _size; }
	~String() { delete[] string; }
private:
	char* string = nullptr;
	size_t _size = 0;
};


String operator+( const String& lhs, const String& rhs );
String operator+( const String& str, const char* const chr );
String operator+( const char* const chr, const String& str );


bool operator< ( const String& lhs, const String& rhs );
bool operator> ( const String& lhs, const String& rhs );
bool operator== ( const String& lhs, const String& rhs );

std::ostream& operator<<( std::ostream& os, const String& str );


#endif //__TARGEMSTRING_H
