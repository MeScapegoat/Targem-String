#include <iostream>
#include <vector>
#include <algorithm>
#include <cctype>
#include "String.h"


//
bool reverse_lexicographic( const String& lhs, const String& rhs )
{
	String llow( lhs );
	String rlow( rhs );

	for ( auto i = 0; i < llow.size(); ++i )
		llow[ i ] = std::tolower( llow[ i ] );
	for ( auto i = 0; i < rlow.size(); ++i )
		rlow[ i ] = std::tolower( rlow[ i ] );

	return llow > rlow;
}


//Написать пример с использованием этого класса строк и какого-либо контейнера STL. 
//Программа должна принимать список строк, затем выдавать его в порядке, обратном
//лексикографическому без учета регистра.
int main()
{
	char str[ 100000 ]; //100'000
	std::vector<String> input;

	std::cout << "Enter strings to sort (type \"0\" to quit):\n";
	while ( true )
	{
		std::cin >> str;
		if ( *str == '0' )
			break;
		input.push_back( String( str ) );
	}

	std::sort( input.begin(), input.end(), reverse_lexicographic );

	std::cout << "Reverse lexicographic:\n";
	for ( auto& str : input )
		std::cout << str << "\n";
}
