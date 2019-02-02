/********************************************************
 * Creatint for practice, free learning purpose.
 * 
 * filename: main.h
 * author: Martin
 * date: Fri Feb 1 2019
 * description: 
 * 
 ********************************************************/

#ifndef _MAIN_MAIN_MAIN_
#define _MAIN_MAIN_MAIN_

#include <unistd.h>
#include <cstdlib>
#include <condition_variable>
#include <iostream>
#include <string.h>
#include <thread>
#include <mutex>
#include <chrono>

#define ITEM_REPOSITORY_SIZE    10      /* Item buffer size */ 
#define ITEM_TO_PRODUCE         100     /* How many items we plan to produce */ 

typedef struct ItemRepository {
    int item_buffer[ITEM_REPOSITORY_SIZE]; /* Item ring buffer */ 
    size_t read_position;
    size_t write_position;
    std::mutex mtx;
    std::condition_variable repo_not_full;
    std::condition_variable repo_not_empty;
} Item_Repository;


#endif
