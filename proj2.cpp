#include "proj2.h"
#include <bitset>
#include <pthread.h>

using namespace std;

int main(int argc, char* argv[])
{
    // =============== SETUP =============== 
    int rc; // return code for pthread

    char* filename = NULL; // name of the input file
    // filename must be specified. parse_argv will check if filename is
    // given or not
    int threadcount = DEFAULT_THREAD_COUNT; // number of threads 
    chunksize = DEFAULT_CHUNK_SIZE;         // size of the chunk 
    verbose = DEFAULT_VERBOSE_FLAG;
    // default values are defined in proj2.h

    count = 0; // number of keyword found in the file
    pthread_t threads[threadcount];

    struct timeval start_time, end_time, diff;
    
    // for measuring running time

    // parsing arguments
    if(parse_argv(argc, argv, threadcount, 
                  &filename, keyword, chunksize) == false) {
        cout << endl;
        help_message(argv);
        exit(EXIT_FAILURE);
    }

    
    // end of parsing arguments

    // read the content of the file and store it as file_string
    if(read_file(filename, file_string) == false) {
        cout << "Unable to read file. Something is wrong." << endl;
        exit(EXIT_FAILURE);
    }
    // end of reading file

    

    // Make a simple summary of the arguments gotten
    if(verbose) {
        cout << "Counting the occurrence of " << keyword << endl;
        cout << "Chunk size:                " << chunksize << endl;
        cout << "Number of threads:         " << threadcount << endl;
        cout << endl;
    }
    // =============== END OF SETUP ===============

    

    // Creates the quantity of threads specified by threadcount
    for(long int i = 0; i < threadcount; i++)
      {
	rc = pthread_create(&threads[i], NULL, &search_subs_ocurrences, ( void *)i);
	
	if (rc){
	  cout << "Error:unable to create thread," << rc << endl;
	  exit(-1);
	}
      }

    for(long int j = 0; j < threadcount; j++)
      {
	pthread_join(threads[j], NULL);
      }

    gettimeofday(&start_time, NULL); // Record the start time
    //start_time = start_time.tv_sec+(start_time.tv_usec/1000000.0);
    
  
    gettimeofday(&end_time, NULL); // Record the end time
    end_time = (timeval)end_time.tv_sec+(end_time.tv_usec/1000000.0);

    timeval_diff(diff, start_time, end_time); // Get the difference of 
                                              // start and end time
    print_stats(diff, threadcount, chunksize, count, keyword);
}

