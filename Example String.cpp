#include <iostream>
#include <vector>
#include <algorithm>
#include <cctype>
#include "String.h"

#ifndef NDEBUG
#include <sstream>
void simpleStringTests()
{
	// **** ВОЛЬНОЕ ТВОРЧЕСТВО ****
	//Конструктор по умолчанию
	{
		String s;
		if ( s.size() != 0 )
			throw std::logic_error( "Incorrect size of default constructor!\n" );

		if ( s.data() != nullptr )
			throw std::logic_error( "Incorrect data of default constructor!\n" );
	}

	// сравнение <
	{
		String a( "aaa" ), A( "AAA" ), b( "bbb" ), empty;
		if ( !( A < a ) )
			throw std::logic_error("Incorrect operator< for different letter cases!");

		if (a < a )
			throw std::logic_error( "Incorrect operator< for the same letters!" );

		if ( !( a < b ) )
			throw std::logic_error( "Incorrect operator< for different letters!" );

		if ( !( empty < a) )
			throw std::logic_error( "Incorrect operator< for empty string!" );
	}

	// сравнение >
	{
		String a( "aaa" ), A( "AAA" ), b( "bbb" ), empty;
		if ( A > a )
			throw std::logic_error( "Incorrect operator> for different letter cases!" );

		if ( a > a )
			throw std::logic_error( "Incorrect operator> for the same letters!" );

		if ( a > b )
			throw std::logic_error( "Incorrect operator> for different letters!" );

		if ( empty > a )
			throw std::logic_error( "Incorrect operator> for empty string!" );
	}

	// сравнение ==
	{
		String a1( "aaa" ), a2(a1), A( "AAA" ), b( "bbb" ), empty1, empty2;
		if ( A == a1 )
			throw std::logic_error( "Incorrect operator== for different letter cases!" );

		if ( !( a1 == a1 ) )
			throw std::logic_error( "Incorrect operator== for itself!" );

		if ( !( a1 == a2 ) )
			throw std::logic_error( "Incorrect operator== for the same letters!" );

		if ( a1 == b )
			throw std::logic_error( "Incorrect operator== for different letters!" );

		if ( !(empty1 == empty2 ) )
			throw std::logic_error( "Incorrect operator== for empty strings!" );
	}

	// оператор вывода
	{
		char text[] = "I believe i can fly!";
		std::ostringstream os;
		String s( text );
		os << s;
		if ( s.size() != os.str().size() )
			throw std::logic_error( "Incorrect size of output!" );

		for (size_t n = 0; n < s.size(); ++n)
			if (s.data()[n] != os.str()[n] )
				throw std::logic_error( "Incorrect data of output!" );
	}

	// оператор ввода
	{
		std::istringstream is( "Apples are made of apples.");
		char fWord[] = "Apples";
		String s;
		is >> s;

		if ( s.size() != (sizeof fWord - 1) )
			throw std::logic_error( "Incorrect size of input!" );

		for (size_t n = 0; n < s.size(); ++n )
			if ( s.data()[ n ] != fWord[n] )
				throw std::logic_error( "Incorrect data of input!" );
	}

	// чтение всей строки
	{
		std::istringstream is( "Apples are made of apples." );
		String s;
		getline( is, s );

		if ( s.size() != is.str().size() )
			throw std::logic_error( "Incorrect size of line input!" );

		for ( size_t n = 0; n < s.size(); ++n )
			if ( s.data()[ n ] != is.str()[ n ] )
				throw std::logic_error( "Incorrect data of line input!" );
	}
	// **** ВОЛЬНОЕ ТВОРЧЕСТВО ****


	//**** ТРЕБУЕТСЯ ПО УСЛОВИЮ ****
	//Конструктор копирования для c-строки
	{
		const char text[]  = "I believe i can fly!";
		String s( text );
		if (s.size() != (sizeof text - 1))
			throw std::logic_error( "Incorrect size of copy c-str constructor!\n" );

		for ( size_t n = 0; n < s.size(); ++n )
			if (text[n] != s.data()[n] )
				throw std::logic_error( "Incorrect data of copy c-str constructor!\n" );
	}

	//Оператор присваивания  для c-строки
	{
		const char text[] = "I believe i can fly!";
		String s;
		s = text;
		if ( s.size() != ( sizeof text - 1 ) )
			throw std::logic_error( "Incorrect size of c-str assignment!\n" );

		for ( size_t n = 0; n < s.size(); ++n )
			if ( text[ n ] != s.data()[ n ] )
				throw std::logic_error( "Incorrect data of c-str assignment!\n" );
	}

	//оператор += для c-строки
	{
		const char text[] = "I believe i can fly! I believe i can touch the sky!";
		const char part[] = " I believe i can touch the sky!";
		String s( "I believe i can fly!" );
		s += part;

		if ( s.size() != ( sizeof text - 1 ) )
			throw std::logic_error( "Incorrect size of c-str operator+=!\n" );

		for ( size_t n = 0; n < s.size(); ++n )
			if ( text[ n ] != s.data()[ n ] )
				throw std::logic_error( "Incorrect data of c-str operator+=!\n" );
	}

	//Внешний оператор сложения для c-строки и класса
	{
		const char text[] = "I believe i can fly! I believe i can touch the sky!";
		const char part[] = "I believe i can fly!";
		String s( " I believe i can touch the sky!" );

		if ( ( part + s ).size() != ( sizeof text - 1 ) )
			throw std::logic_error( "Incorrect size of operator+ c-str and class!\n" );

		for ( size_t n = 0; n < ( part + s ).size(); ++n )
			if ( text[ n ] != ( part + s ).data()[ n ] )
				throw std::logic_error( "Incorrect data of operator+ c-str and class !\n" );
	}

	//Внешний оператор сложения для класса и c-строки
	{
		const char text[] = "I believe i can fly! I believe i can touch the sky!";
		const char part[] = " I believe i can touch the sky!";
		String s( "I believe i can fly!" );

		if ( ( s + part ).size() != ( sizeof text - 1 ) )
			throw std::logic_error( "Incorrect size of operator+ class and c-str!\n" );

		for ( size_t n = 0; n < ( s + part ).size(); ++n )
			if ( text[ n ] != ( s + part ).data()[ n ] )
				throw std::logic_error( "Incorrect data of operator+ class and c-str!\n" );
	}

	//Конструктор копирования для класса
	{
		String s1( "I believe i can fly." );
		String s2( s1 );
		if ( s1.size() != s2.size() )
			throw std::logic_error( "Incorerct size of copy class constructor!\n" );

		for ( size_t n = 0; n < s1.size(); ++n )
			if ( s1.data()[ n ] != s2.data()[ n ] )
				throw std::logic_error( "Incorrect data of copy class constructor!\n" );
	}

	//Оператор присваивания  для класса
	{
		String s1( "I believe i can fly." );
		String s2;
		s2 = s1;
		if ( s1.size() != s2.size() )
			throw std::logic_error( "Incorerct size of class assignment!\n" );

		for ( size_t n = 0; n < s1.size(); ++n )
			if ( s1.data()[ n ] != s2.data()[ n ] )
				throw std::logic_error( "Incorrect data of class assignment!\n" );

		//Особый случай - присваивание самого себя
		s2 = s2;
		if ( s1.size() != s2.size() )
			throw std::logic_error( "Incorerct size of class self-assignment!\n" );

		for ( size_t n = 0; n < s1.size(); ++n )
			if ( s1.data()[ n ] != s2.data()[ n ] )
				throw std::logic_error( "Incorrect data of class self-assignment!\n" );
	}

	//move-семантика
	{
		//Move конструктор копирования
		char text[] = "I believe i can fly.";
		String s1( text );
		String s2( std::move( s1 ) );

		if ( s2.size() != ( sizeof text - 1 ) )
			throw std::logic_error( "Incorrect size of move copy semantics!\n" );

		for (size_t n = 0; n < s2.size(); ++n)
			if (s2.data()[n] != text[n] )
				throw std::logic_error( "Incorrect data of move copy semantics!\n" );


		if (s1.size() != 0 )
			throw std::logic_error( "Incorrect size of move copy semantics of left object!\n" );

		if (s1.data() != nullptr )
			throw std::logic_error( "Incorrect data of move copy semantics of left object!\n" );


		//Move присваивание 
		String s3( text );
		String s4;
		s4 = std::move( s3 );

		if ( s4.size() != ( sizeof text - 1 ) )
			throw std::logic_error( "Incorrect size of move assignment semantics!\n" );

		for ( size_t n = 0; n < s4.size(); ++n )
			if ( s4.data()[ n ] != text[ n ] )
				throw std::logic_error( "Incorrect data of move assignment semantics!\n" );


		if ( s3.size() != 0 )
			throw std::logic_error( "Incorrect size of move assignment semantics of left object!\n" );

		if ( s3.data() != nullptr )
			throw std::logic_error( "Incorrect data of move assignment semantics of left object!\n" );


		//Особый случай - Move присваивание самого себя 
		String s5( text );
		s5 = std::move( s5 );

		if ( s5.size() != ( sizeof text - 1 ) )
			throw std::logic_error( "Incorrect size of move self-assignment semantics!\n" );

		for ( size_t n = 0; n < s5.size(); ++n )
			if ( s5.data()[ n ] != text[ n ] )
				throw std::logic_error( "Incorrect data of move self-assignment semantics!\n" );
	}

	//оператор += для класса
	{
		char text[] = "I believe i can fly! I believe i can touch the sky!";
		String s1( "I believe i can fly!" );
		String s2(" I believe i can touch the sky!");
		s1 += s2;

		if ( s1.size() != (sizeof text - 1) )
			throw std::logic_error( "Incorerct size of class opeator+=!\n" );

		for ( size_t n = 0; n < s1.size(); ++n )
			if ( s1.data()[ n ] != text[ n ] )
				throw std::logic_error( "Incorrect data of class opeator+=!\n" );
	}

	//Внешний оператор сложения двух строк
	{
		char text[] = "I believe i can fly! I believe i can touch the sky!";
		String s1( "I believe i can fly!" );
		String s2( " I believe i can touch the sky!" );

		if ( ( s1 + s2 ).size() != ( sizeof text - 1 ) )
			throw std::logic_error( "Incorerct size of operator+ between two class objects!\n" );

		for ( size_t n = 0; n < ( s1 + s2 ).size(); ++n )
			if ( ( s1 + s2 ).data()[ n ] != text[ n ] )
				throw std::logic_error( "Incorrect data of operator+ between two class objects!\n" );
	}
	//**** ТРЕБУЕТСЯ ПО УСЛОВИЮ ****
}
#endif //NDEBUG

//
bool reverse_lexicographic( const String& lhs, const String& rhs )
{
	String llow( lhs );
	String rlow( rhs );

	for ( size_t i = 0; i < llow.size(); ++i )
		llow[ i ] = std::tolower( llow[ i ] );

	for ( size_t i = 0; i < rlow.size(); ++i )
		rlow[ i ] = std::tolower( rlow[ i ] );

	return llow > rlow;
}


//Написать пример с использованием этого класса строк и какого-либо контейнера STL. 
//Программа должна принимать список строк, затем выдавать его в порядке, обратном
//лексикографическому без учета регистра.
int main()
{
#ifndef NDEBUG
	try
	{
		simpleStringTests();
	}
	catch ( std::exception& e )
	{
		std::cerr << e.what() << std::endl;
		return -1;
	}
#endif //NDEBUF

	{
		std::vector<String> input;
		String str;

		std::cout << "Enter strings to sort (type \"0\" to quit):\n";
		while ( true )
		{
			getline( std::cin, str );
			if ( str == "0" )
				break;

			input.push_back( String( str ) );
		}

		std::sort( input.begin(), input.end(), reverse_lexicographic );

		std::cout << "Reverse lexicographic:\n";
		for ( auto& s : input )
			std::cout << s << "\n";
	}

	return 0;
}

