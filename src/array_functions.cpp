/*
 * functionstocomplete.cpp
 *
 *  Created on: Sep 10, 2017
 *      Author: keith
 *  Edited on: Sep 28, 2019
 *  	Author Allan Brewer Pedin IV
 */
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "constants.h"
#include "utilities.h"

using namespace std;

struct entry {
	string word;
	int number_occurences;
};
entry entries[constants::MAX_WORDS] = { };
int nextAvailableSpot = 0;

void clearArray() {
	for (int i = 0; i < nextAvailableSpot; i++) {
		entries[i] = { };
	}
	nextAvailableSpot = 0;
}

/*returns how many unique words are in array*/
int getArraySize() {
	return nextAvailableSpot;
}

/*gets word of entry at index i*/
std::string getArrayWordAt(int i) {
	return entries[i].word;
}
/* gets number of occurences of entry at index i*/
int getArrayWord_NumbOccur_At(int i) {
	return entries[i].number_occurences;
}
/*Keep track of how many times each token seen*/
void processToken(std::string &token) {
	strip_unwanted_chars(token);
	if (token.compare("") != 0) { //not empty
		bool tokenExists = false;
		for (int i = 0; i < nextAvailableSpot; i++) {
			string upperStr1 = entries[i].word;toUpper(upperStr1);
			string upperStr2 = token;toUpper(upperStr2);
			if (upperStr1==upperStr2) { //found token
				entries[i].number_occurences += 1;//add occurence
				tokenExists = true;
				break;
			}
		}
		if (!tokenExists) {//add token to list if this one doesnt exist
			entries[nextAvailableSpot].word = token;
			entries[nextAvailableSpot].number_occurences = 1;
			nextAvailableSpot += 1;
		}
	}
}

/* take 1 line and extract all the tokens from it
 * feed each token to processToken for recording*/
void processLine(std::string &myString) {
	std::string delimiter = " ";
	size_t pos = 0;
	std::string token;
	while ((pos = myString.find(delimiter)) != std::string::npos) {
	    token = myString.substr(0, pos);
	    processToken(token);
	    myString.erase(0, pos + delimiter.length());
	}
	processToken(myString);
}
/*iff myfile is open then close it*/
void closeFile(std::fstream &myfile) {
	myfile.close();
}
/*loop through whole file, one line at a time
 * call processLine on each line
 * returns false: myfstream is not open
 *         true: otherwise*/
bool processFile(std::fstream &myfstream) {
	if (!myfstream.is_open()) {
		return false;
	}
	std::string line;
	while (std::getline(myfstream, line)) {
		processLine(line);
	}
	closeFile(myfstream);
	return true;
}

/* if you are debugging the file must be in the project parent directory
 * in this case Project2 with the .project and .cProject files
 * opens file (exactly as the name says it does) */
bool openFile(std::fstream &myfile, const std::string &myFileName,std::ios_base::openmode mode = std::ios_base::in) {
	myfile.open(myFileName.c_str(),mode);
	return myfile.is_open() && !myfile.fail();
}


/* serializes all content in myEntryArray to file outputfilename
 * returns  FAIL_FILE_DID_NOT_OPEN if cannot open outputfilename
 * 			FAIL_NO_ARRAY_DATA if there are 0 entries in myEntryArray
 * 			SUCCESS if all data is written and outputfilename closes OK
 * */
int writeArraytoFile(const std::string &outputfilename) {
	ofstream fs;
	fs.open(outputfilename.c_str());
	//checks
	if(!fs.is_open()){
		return constants::FAIL_FILE_DID_NOT_OPEN;
	}
	if(nextAvailableSpot==0){
		return constants::FAIL_NO_ARRAY_DATA;
	}
	//write
	for(int i=0;i<nextAvailableSpot;i++){
		fs << entries[i].word<< " "<<entries[i].number_occurences<<std::endl;
	}
	fs.close();

	return constants::SUCCESS;
}
/*  helper for sort array, checks if j and j+1 are sorted based on sort order*/
bool checkSorted(int j,constants::sortOrder so){
		string upperStr1 = entries[j].word;toUpper(upperStr1);
		string upperStr2 = entries[j+1].word;toUpper(upperStr2);
		switch (so) {
		case constants::ASCENDING:
			return upperStr1>upperStr2;
		case constants::DESCENDING:
			return upperStr1<upperStr2;
		case constants::NONE:
			return true;
		case constants::NUMBER_OCCURRENCES:
			return entries[j + 1].number_occurences < entries[j].number_occurences;
		default:
			cout << "this should never happen pls dont give me a fake sort order"<< std::endl;
			throw 404;
		}
}
/*
 * Sort myEntryArray based on so enum value.
 * You must provide a solution that handles alphabetic sorting (A-Z)
 * The presence of the enum implies a switch statement based on its value
 */
void sortArray(constants::sortOrder so) {
	bool swapped = true;
	for (int i = 1; (i <= nextAvailableSpot) && swapped; i++) {
		swapped = false;
		for (int j = 0; j < (nextAvailableSpot - 1); j++) {
			if (checkSorted(j,so)){
				entries[j+1].word.swap(entries[j].word);
				std::swap(entries[j+1].number_occurences,entries[j].number_occurences);
				swapped = true;
			}
		}
	}
}
