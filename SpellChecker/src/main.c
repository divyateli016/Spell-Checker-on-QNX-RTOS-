#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "spellchecker.h"
int main(int argc, char* argv[])
{
//	printf("argc = %d\n",argc);
//	To check if the correct arguments are assigned
//	for(int i=0;i<argc;i++)
//	{
//		printf("argv[%d] = %s\n",i,argv[i]);
//	}

	char **dict_out;
	int count = load_dictionary(argv[1], &dict_out);
	//After debugging
	//printf("After loading the dictionary %d\n",count);
	int correct_words=0;
	int misspelled = 0;
	clockid_t id = CLOCK_REALTIME;
	struct timespec start, stop;
	analyze_inputfile(argv[2], dict_out, count, &correct_words, &misspelled,id,&start,&stop);
	printf("Correct Words:  %d ",correct_words);
	printf("Incorrect Words: %d\n",misspelled);
	/**

	for(int i =0;i<10;i++)
	{
		printf("Dictionary content is %s\n",dict_out[i]);
	}
	**/
	int secs = stop.tv_sec-start.tv_sec;
	double nano_sec = (stop.tv_nsec-start.tv_nsec)/1e9;
	double total_time = (double)(secs+nano_sec);
	printf("Total Time = %f\n",total_time);



	return EXIT_SUCCESS;
}
