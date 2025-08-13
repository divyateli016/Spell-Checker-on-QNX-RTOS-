/*
 * spellchecker.h
 *
 *  Created on: Aug 9, 2025
 *      Author: divya
 */

#ifndef SPELLCHECKER_H_
#define SPELLCHECKER_H_
#include <time.h>


int load_dictionary(const char* fileName,char ***dict_out);

void string_convert(char*word);
//This function will analyze the input file and search the words in the dictionary

int analyze_inputfile(const char* fileName,char** dictionary, int word_count, int* correct_words,int* misspelled,clockid_t id,struct timespec* startTimeSpec,struct timespec* stopTimeSpec);

int search_word(char**buffer,int word_count,const char* word);


#endif /* SPELLCHECKER_H_ */
