/*
 * functionstocomplete.h
 *
 *  Created on: Sep 10, 2017
 *      Author: keith
 */

#ifndef ARRAY_FUNCTIONS_H_
#define ARRAY_FUNCTIONS_H_
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "constants.h"
/*============================================================================
 * The following are declarations for functions that I will test
 * Please provide the definitions in the
 * included cpp file, do not erase the stuff I put in there please
 * DO NOT MODIFY THIS FILE, I WILL USE MY OWN COPY
/============================================================================*/

//zero out array that tracks words and their occurrences
void clearArray();

//how many unique words are in array
int getArraySize();

//get data at a particular location
std::string getArrayWordAt(int i);
int getArrayWord_NumbOccur_At(int i);

/*loop through whole file, one line at a time
 * call processLine on each line
 * returns false: myfstream is not open
 *         true: otherwise*/
bool processFile(std::fstream &myfstream);

/*take 1 line and extract all the tokens from it
feed each token to processToken for recording*/
void processLine(std::string &myString);

/*Keep track of how many times each token seen*/
void processToken(std::string &token);

/*if you are debugging the file must be in the project parent directory
  in this case Project2 with the .project and .cProject files*/
bool openFile(std::fstream& myfile, const std::string& myFileName,
		std::ios_base::openmode mode = std::ios_base::in);

/*iff myfile is open then close it*/
void closeFile(std::fstream& myfile);

/* serializes all content in myEntryArray to file outputfilename
 * returns  FAIL_FILE_DID_NOT_OPEN if cannot open outputfilename
 * 			FAIL_NO_ARRAY_DATA if there are 0 entries in myEntryArray
 * 			SUCCESS if all data is written and outputfilename closes OK
 * */
int writeArraytoFile(const std::string &outputfilename);

/*
 * Sort myEntryArray based on so enum value.
 * You must provide a solution that handles alphabetic sorting (A-Z)
 * The presence of the enum implies a switch statement based on its value
 */
void sortArray(constants::sortOrder so);

#endif /* ARRAY_FUNCTIONS_H_ */
