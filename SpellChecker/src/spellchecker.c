/*
 * spellchecker.c
 *
 *  Created on: Aug 9, 2025
 *      Author: divya
 */
#include "spellchecker.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

#define MAX_WORDLENGTH 31
int load_dictionary(const char* fileName,char ***dict_out)
{
	printf("Reading Dictionary...\n");
	FILE *fp;
	char word[MAX_WORDLENGTH];
	int word_count=0;
	int word_length = 0;
	int buffer_index = 0;
	fp = fopen(fileName,"r");

	if(fp == NULL)
	{
		printf("Failed to open the file\n");
	}
//	else
//	{
//		printf("File is opened\n");
//	}

	//Read the words in the file and store it into buffer
	while(fscanf(fp,"%30s",word)==1)
	{
		word_count++;
	}
	rewind(fp);
	//printf("Word count = %d\n",word_count);
	//assigning the memory to the buffer
	char** dictionary = malloc(word_count*sizeof(char*));
	if(dictionary==NULL)
	{
		printf("memory allocation failed\n");
	}
	//read the words and store into the buffer
	while(fscanf(fp,"%30s",word)==1)
	{
		word_length = strlen(word);
		//Allocate the memory
		char* tptr = malloc(word_length+1);
		if(tptr !=NULL)
		{
			strcpy(tptr ,word);
			dictionary[buffer_index]=tptr;
			buffer_index++;
		}
		else
		{
			printf("Error in memory allocation\n");
		}
	}
	fclose(fp);
	*dict_out = dictionary;
	printf("Dictionary has been loaded\n");
	return word_count;
}
void string_convert(char*word)
{
	char temp[strlen(word)+1];
	int i,j=0;
	for(i = 0;word[i]!='\0';i++)
	{
		//Check for the alpha neumeric character
		if(isalpha((unsigned char)word[i]))
		{
			temp[j] = toupper((unsigned char)word[i]);
			j++;
		}
	}
	temp[j] = '\0';
	strcpy(word,temp);
}

int search_word(char**buffer,int word_count,const char* word)
{
	for(int i=0;i<word_count;i++)
	{
		if(strcmp(buffer[i],word)==0)
		{
			return 1;
		}
	}
	return 0;
}
int analyze_inputfile(const char* fileName,char** dictionary, int word_count, int* correct_words,int* misspelled,clockid_t id,struct timespec* startTimeSpec,struct timespec* stopTimeSpec)
{

	char word[MAX_WORDLENGTH];
	*correct_words = 0;
	*misspelled = 0;
	printf("Reading input file...\n");

	//Read the input file for that we need to open it
	FILE* readinput = fopen(fileName,"r");
	if(readinput == NULL)
	{
		printf("Failed to open the input file\n");
	}
	printf("Staring analysis of input file...\n");

	//Bench marking of the analyis
//	struct timespec start,stop;
//	clockid_t Clock_id = CLOCK_REALTIME;
//	clock_gettime(Clock_id, &start);

	//Second method by passing the arguments to print the calculated time in main
	clock_gettime(id,startTimeSpec);

	//now read the words from the file
	while(fscanf(readinput,"%30s",word)==1)
	{
		//remove the special characters like \r\n
		string_convert(word);
		//printf("After converting word in input file %s\n",word);
		if(strlen(word)==0)
			continue;//Skip for the empty string

		//Check if the word is present in the dictionary

		if(search_word(dictionary, word_count, word)==1)
		{
			(*correct_words)++;
		}
		else
		{
			printf("Word %s NOT FOUND in dictionary.\n",word);
			(*misspelled)++;
		}
	}
//	clock_gettime(Clock_id,&stop);
//	int secs = stop.tv_sec-start.tv_sec;
//	double nano_sec = (stop.tv_nsec-start.tv_nsec)/1e9;
//	double total_time = (double)(secs+nano_sec);
//	printf("Total Time = %f\n",total_time);
	clock_gettime(id,stopTimeSpec);
   return 0;
}



