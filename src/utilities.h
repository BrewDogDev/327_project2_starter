/*
 * utilities.h
 *
 *  Created on: Sep 10, 2017
 *      Author: keith
 */

#ifndef UTILITIES_H_
#define UTILITIES_H_
#include <string>

	void toUpper(std::string &myString);  //uppercase a string, useful for confirming that To==TO==to==tO
	std::string intToString(int Number);  //take an int return a string
	void strip_char(std::string &s, char badchar);
	bool strip_unwanted_chars(std::string &mystring);

#endif /* UTILITIES_H_ */
