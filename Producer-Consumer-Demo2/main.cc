/********************************************************
 * Creatint for practice, free learning purpose.
 * 
 * filename: main.cc
 * author: Martin
 * date: Fri Feb 1 2019
 * description: one producer and multi consumers
 * 
 ********************************************************/

#include "main.h"

static struct ItemRepository g_itemRepository;

void ProduceItem(ItemRepository *itemRepository, int item)
{
    std::unique_lock<std::mutex> lock(itemRepository->mtx);

    while(((itemRepository->write_position + 1) % ITEM_REPOSITORY_SIZE) == itemRepository->read_position) { // item buffer is full, just wait here.
        std::cout << "Producer is waiting for an empty slot...\n"; std::fflush(stdout);
        itemRepository->repo_not_full.wait(lock); // Wait for the ring buffer is not full.
    }

    itemRepository->item_buffer[itemRepository->write_position] = item; // Push the item to the buffer
    
    itemRepository->write_position++;
    if (itemRepository->write_position == ITEM_REPOSITORY_SIZE) {
        itemRepository->write_position = 0;
    }

    itemRepository->repo_not_empty.notify_all(); // Notify the consumer the buffer is not empty
    lock.unlock();
}

int ConsumeItem(ItemRepository *itemRepository)
{
    int data;
    std::unique_lock<std::mutex> lock(itemRepository->mtx);

    // item ring buffer is empty, just wait here.
    while(itemRepository->write_position == itemRepository->read_position) {
        std::cout << "Consumer is waiting for items...\n"; std::fflush(stdout);
        itemRepository->repo_not_empty.wait(lock);
    }

    data = itemRepository->item_buffer[itemRepository->read_position++];
    if (itemRepository->read_position >= ITEM_REPOSITORY_SIZE) {
        itemRepository->read_position = 0;
    }

    itemRepository->repo_not_full.notify_all(); // Notify the producer the buffer is not full
    lock.unlock();

    return data;
}

void ProducerTask(void)
{
    //std::this_thread::sleep_for(std::chrono::microseconds(500));
    sleep(1);
    for (int i = 1; i <= ITEM_TO_PRODUCE; ++i) {
        //std::this_thread::sleep_for(std::chrono::microseconds(10));
	    //usleep(200);
        std::cout << "Producer thread ID: " << std::this_thread::get_id() << ". Produce the " << i << "^th item..." << std::endl; std::fflush(stdout);
        ProduceItem(&g_itemRepository, i);
    }

    std::cout << "Producer thread ID: " << std::this_thread::get_id() << " is exiting..." << std::endl; std::fflush(stdout);
}

void ConsumerTask(void)
{
    bool ready_to_exit = false;
    while(1) {
        //std::this_thread::sleep_for(std::chrono::microseconds(500));
	    sleep(1);

        std::unique_lock<std::mutex> locking(g_itemRepository.mtx_item_counter);
        if (g_itemRepository.item_counter < ITEM_TO_PRODUCE) {
            int item = ConsumeItem(&g_itemRepository);
            g_itemRepository.item_counter++;
            std::cout << "Consumer thread ID: " << std::this_thread::get_id() << ". Consume the " << item << "^th item" << std::endl; std::fflush(stdout);
        }
        else {
            ready_to_exit = true;
        }
        
        if (ready_to_exit == true) {
            break;
        }
    }
}

void InitItemRepository(ItemRepository *itemRepository)
{
    memset(itemRepository->item_buffer, 0, sizeof(int) * ITEM_REPOSITORY_SIZE);
    itemRepository->write_position = 0;
    itemRepository->read_position = 0;
    itemRepository->item_counter = 0;
}

int main(int argc, char *argv[])
{
    InitItemRepository(&g_itemRepository);

    std::thread producer(ProducerTask); 
    std::thread consumer1(ConsumerTask);
    std::thread consumer2(ConsumerTask);
    std::thread consumer3(ConsumerTask);
    std::thread consumer4(ConsumerTask);
    std::thread consumer5(ConsumerTask);

    producer.join();
    consumer1.join();
    consumer2.join();
    consumer3.join();
    consumer4.join();
    consumer5.join();

    return 0;
}
