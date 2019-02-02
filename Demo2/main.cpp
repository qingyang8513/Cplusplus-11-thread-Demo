/********************************************************
 * Creatint for practice, free learning purpose.
 * 
 * filename: main.c
 * author: Martin
 * date: Fri Feb 1 2019
 * description: This demo show the usage of std::mutex. 
 *              Note:
 *              (1) std::mutex::lock() and std::mutex::unlock() may cause some time useless.
 *              (2) std::mutex is not safe. When a thread crashed without unlock(), others would never get lock().
 * 
 ********************************************************/

#include "main.h"

//using namespace std;
const int N = 100;
int num(N);
std::mutex mt;

void showHelp(void);
void threadFunction1(void);
void threadFunction2(void);

int main(int argc, char *argv[])
{
    // Show some messages.
    showHelp();

    // Create two threads
    std::thread t1(threadFunction1);
    std::thread t2(threadFunction2);
    std::thread t3(threadFunction2);

    // std::join used to wait the thraed to exit, then quit the main function.
    t1.join();
    t2.join();
    t3.join();

    return 0;
}

void showHelp(void)
{
    std::cout << "Thread easy demo: std::mutex" << std::endl;
}

void threadFunction1(void)
{
    while(num > 0){
        mt.lock();
        if (num > 0) {
            --num;
            std::cout << "Thread ID: " << std::this_thread::get_id() << ", num = " << num << std::endl;
        }
        mt.unlock();
    }
}

void threadFunction2(void)
{
    while(num > 0){
        mt.lock();
        if (num > 0) {
            --num;
            std::cout << "Thread ID: " << std::this_thread::get_id() << ", num = " << num << std::endl;
        }
        mt.unlock();
    }
}

