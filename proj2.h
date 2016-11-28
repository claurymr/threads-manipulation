#include "utilities.cpp"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <time.h>
#include <vector>
#include <sys/time.h>
#include <string>
#include <mutex>

using namespace std;

string keyword;
string file_string;
unsigned long global_pos;
long count;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;


/*
 * purpose: search for occurrences of substrings in
 *          a file string.
 * receive: the thread id.
 * return: a thread value.
 */
void *search_subs_ocurrences(void *thread_id)
{
  
  long th_id;
  th_id = (long)thread_id;
  if(verbose)
    {
      pthread_mutex_lock( &mtx );
      cout << "Thread " << th_id << " started." << endl;
      pthread_mutex_unlock( &mtx );
    }
  
    
  long local_count = 0;
  size_t offset;
  pthread_mutex_lock( &mtx );
  int start = global_pos;
  unsigned int limit = global_pos + chunksize;
  global_pos = limit;
  pthread_mutex_unlock( &mtx );

  while(limit < file_string.length())
  {
    pthread_mutex_lock( &mtx );
    local_count = 0;
    start = global_pos;
    limit = global_pos + chunksize;
    global_pos = limit;
    pthread_mutex_unlock( &mtx );
  
    for(offset = file_string.find(keyword, start);
	((offset != string::npos) && (offset < limit));
	 offset = file_string.find(keyword, offset + keyword.length()))
    {
	local_count++;
    }
    pthread_mutex_lock( &mtx );
    count += local_count;
    pthread_mutex_unlock( &mtx );
  }
  if(verbose)
    {
      pthread_mutex_lock( &mtx );
      cout << "Thread " << th_id << " terminated." << endl;
      pthread_mutex_unlock( &mtx );
    }
  
  
  return(thread_id);
}


