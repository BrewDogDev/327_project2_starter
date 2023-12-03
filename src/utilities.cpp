/*
 * utilities.cpp
 *
 *  Created on: Sep 10, 2017
 *      Author: keith
 */
#include <string>
#include <algorithm>
#include <sstream>

#include "utilities.h"

using namespace std;

/*look up transform in algorithm, fragile, does not work for non-ascii char sets*/
void toUpper(string &myString) {
	std::transform(myString.begin(), myString.end(), myString.begin(),
			::toupper);
}

string intToString(int Number) {
	std::stringstream ss;
	ss << Number;
	return ss.str();
}

//get rid of these three chars so 'end.' and 'end\r' become 'end'
//also dump spaces so if in the end the string length is 0 then it was a space so do not add it
//this would be much easier with c++11 compiler support set but thats not what eclipse defaults to
void strip_char(string &s, char badchar){
	const int NUMBER_CHARS_TO_ERASE = 1;
	if (s.empty())
		return;

	std::size_t found = s.find(badchar);
	if (found!=std::string::npos)
		s.erase(found,NUMBER_CHARS_TO_ERASE);
}

bool strip_unwanted_chars(string &mystring){
	strip_char(mystring,'\r');
	strip_char(mystring,'.');
	strip_char(mystring,' ');
	strip_char(mystring,',');
	return (mystring.length()>0);
}

