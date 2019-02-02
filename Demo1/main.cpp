#include "main.h"

//using namespace std;

void showHelp(void);
void threadFunction1(int n);
void threadFunction2(int &n);

int main(int argc, char *argv[])
{
    showHelp();

    int n = 0;
    std::thread t1(threadFunction1, n + 1);

    t1.join();
    std::cout << "Main thread ID: " << std::this_thread::get_id() << ", n = " << n << std::endl;

    n = 10;
    std::thread t2(threadFunction2, std::ref(n));
    std::thread t3(std::move(t2));

    t3.join();
    std::cout << "Main thread ID: " << std::this_thread::get_id() << ", n = " << n << std::endl;

    return 0;
}

void showHelp(void)
{
    std::cout << "Thread easy demo." << std::endl;
}

void threadFunction1(int n)
{
    std::cout << "Sub thread ID: " << std::this_thread::get_id() << ", n = " << n << std::endl;
    n += 10;
    std::this_thread::sleep_for(std::chrono::microseconds(10));
}

void threadFunction2(int &n)
{
    std::cout << "Sub thread ID: " << std::this_thread::get_id() << ", n = " << n << std::endl;
    n += 20;
    std::this_thread::sleep_for(std::chrono::microseconds(10));
}

