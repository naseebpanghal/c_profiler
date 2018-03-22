/*
 * File Description: This file implements profiler to check processing time between two different locations in code.
 * Author: Naseeb Panghal
 * Creation Date: Sept 28, 2017
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

void naseeb_code_profiler(int flag)
{   
    typedef struct _node
    {
        unsigned long processing_time;
        struct _node *next;
    } node;
    static struct timeval tv1, tv2;
    static time_t start_time = 0;
    static time_t curr_time;
    static node *list_begin = NULL, *list_end = NULL;
    unsigned long avg_time = 0;
    unsigned int n_sec = 1;
    if(flag == 0)
    {
        gettimeofday(&tv1, NULL);
    }   
    else
    {
        gettimeofday(&tv2, NULL);
        node *temp = (node*) malloc(sizeof(node));
        temp->processing_time = ((tv2.tv_sec - tv1.tv_sec)*1000000 + (tv2.tv_usec - tv1.tv_usec))/1000;
        temp->next = NULL;
        if(list_begin == NULL && list_end == NULL)
        {
            /*Fist node in the list*/
            list_begin = list_end = temp;
        }
        else
        {   
            list_end->next = temp;
            list_end = temp; 
        }
        curr_time = time(NULL);
        if((curr_time - start_time) > (n_sec-1)) {
            unsigned long long sample_count = 0;
            while(list_begin != NULL)
            {   
                avg_time += list_begin->processing_time;
                node *del_node = list_begin;
                list_begin = list_begin->next;
                free(del_node);
                sample_count++;
            }
            avg_time /= sample_count;
            printf("Average processing time: %ld msec. Took %ld samples in %d seconds\n", avg_time, sample_count, n_sec);
            start_time = curr_time;
            list_begin = list_end = NULL;
        }
    }
}
