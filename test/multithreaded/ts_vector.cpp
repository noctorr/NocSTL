#include <cstdint>
#define NOC_DEBUG
#include ".../lib/Utils/threadsafe_containers.hpp"
#include <iostream>
#include <thread>
#include <cstdint>
#include <atomic>
#include <chrono>
#include <csignal>

static std::sig_atomic_t sig = 1;

struct Data {
    const char* username;
    float rating;
    std::uint8_t age;
};

static stl::vector<Data> DataHolder;
static std::atomic_bool Gate;

using namespace std::chrono_literals;
void Worker1(
    std::stop_token token
) {

    while (
        Gate.load(
            std::memory_order_acquire
        ) &&
        !token.stop_requested()
    ) {
        DataHolder.emplace_back(
            "Worker1",
            2.1f,
            19
        );

        std::this_thread::sleep_for(1s);
    }
}

void Worker2(
    std::stop_token token
) {
    while (
        Gate.load(
            std::memory_order_acquire
        ) &&
        !token.stop_requested()
    ) {
        DataHolder.emplace_back(
            "Worker2",
            5.f,
            22
        );

        std::this_thread::sleep_for(1s);
    }
}

void Worker3(
    std::stop_token token
) {
    while (
        Gate.load(
            std::memory_order_acquire
        ) &&
        !token.stop_requested()
    ) {
        DataHolder.emplace_back(
            "Worker3",
            4.9f,
            25
        );

        std::this_thread::sleep_for(1s);
    }
}

void initialise() {
    Gate.store(
        true,
        std::memory_order_relaxed
    );
}

void shutdown(int) {
    Gate.store(false, std::memory_order_release);
    sig = 0;
}

int main(void) {
    std::signal(SIGINT, shutdown);
    stl::vector<int> x { 1, 2, 3 };

    int dat[3] = {1, 4, 5};

    stl::vector<int> boom(dat);

//    std::cout << boom.at(0) << std::endl;
//    std::cout << x.at(2) << std::endl;

    boom.clear();
    std::cout << boom.size() << std::endl;

    boom.push_back(1);

    std::cout << boom.at(0) << std::endl;

    initialise();

    std::jthread t1(
        Worker1
    );
    std::puts("WORKER 1 INITIALISED!");
    std::jthread t2(
        Worker2
    );
    std::puts("WORKER 2 INITIALIZED!");
    std::jthread t3(
        Worker3
    );
    std::puts("WORKER 3 INITIALIZED!");
    while (sig) {
        std::cout << "Amount of concurrent hardware threads (hint): " << std::thread::hardware_concurrency() << std::endl;
        std::cout << "Size of DataVector currently: " << DataHolder.size() << std::endl;
        std::cout << "Capacity of DataVector currently: " << DataHolder.capacity() << std::endl;
        std::cout << "Max Size for DataVector allocator: " << DataHolder.get_max_alloc_size() << std::endl;
        std::this_thread::sleep_for(2s);
    }

  /*  for (
        int i = 0;
        i < 10;
        i++
    ) {
        std::thread t1(
            [](stl::vector<int>& x){
                for (int i = 0; i < 50; i++ ) {
                    x.push_back(i);
                }
            },
            std::ref(boom)
        );
        std::thread t2(
            [](stl::vector<int>& x) {
                for (int i = 0; i < 20; i++) {
                    x.push_back(100);
                }
            }, std::ref(boom)
        );
        t1.join();
        t2.join();
        boom.clear();
    }*/
    return 0;
}
